#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <fstream>
#include <iostream>
#include <windows.h>

#ifndef _MSC_VER
typedef int errno_t;
#include <errno.h>
#endif

#include "GL/glew.h"

// workaround for Linux distributions that haven't yet upgraded to GLEW 1.9
#ifndef GL_COMPUTE_SHADER
#define GL_COMPUTE_SHADER 0x91B9
#endif

#include "gl/glfx.h"
#include "glfxClasses.h"
#include "glfxParser.h"
#include "glfxEffect.h"
#include "StringFunctions.h"

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif
#include "generated/glfxScanner.h"
#include "glfxProgram.h"
#include "glfxErrorCheck.h"
#include <set>

Effect::Effect()
    :current_group(NULL)
	,current_texture_number(0)
	,current_image_number(0)
	,current_pass(0)
{
}

Effect::~Effect()
{
	Clear();
}

void Effect::Clear()
{
	for (auto it = m_techniqueGroups.begin(); it != m_techniqueGroups.end(); ++it)
		delete it->second;
	std::set<CompiledShader*> comp;
    for(CompiledShaderMap::iterator it=m_compiledShaders.begin(); it!=m_compiledShaders.end(); ++it)
        comp.insert(it->second);
    for(std::set<CompiledShader*>::iterator it=comp.begin(); it!=comp.end(); ++it)
        delete (*it);
	for(auto i=textureSamplers.begin();i!=textureSamplers.end();i++)
		delete i->second;
	for (auto i = glSamplerStates.begin(); i != glSamplerStates.end(); i++)
		glDeleteSamplers(1,&(i->second));
	for(auto i=functions.begin();i!=functions.end();i++)
	{
		for(auto j=i->second.begin();j!=i->second.end();j++)
			delete *j;
	}
	functions.clear();
	m_techniqueGroups.clear();
	m_techniqueNames.clear();
	m_techniqueGroupNames.clear();
	m_blendStates.clear();
	m_depthStencilStates.clear();
	m_samplerStates.clear();
	for (auto i = m_declaredTextures.begin(); i != m_declaredTextures.end(); i++)
		delete i->second;
	m_declaredTextures.clear();
	m_declaredTexturesByNumber.clear();
	m_rasterizerStates.clear();
	m_shaderLayouts.clear();
	passStates.clear();
	passProgramMap.clear();
	samplerObjects.clear();
}

void Effect::SetSharedCode(const string &str)
{
	m_sharedCode=str;
}

int Effect::GetTextureNumber(const char *name)
{
	int texture_number=current_texture_number;
	std::string n(name);
	if(textureNumberMap.find(n)!=textureNumberMap.end())
	{
		texture_number=textureNumberMap[n];
	}
	else
	{
		if(stricmp(name,"cloudDensity")==0)
		{
			std::cerr<<"cloudDensity";
		}
		textureNumberMap[n]				=current_texture_number;
		if (m_declaredTextures.find(n) == m_declaredTextures.end())
		{
			m_log << "Texture " << name << " is not declared." << std::endl;
			current_texture_number++;
			return texture_number;
		}
		else
		{
			textureDimensions[current_texture_number] = GetTextureDimension(m_declaredTextures[n]->type_enum,true);
		}
		current_texture_number++;
		// Now we will allocate sequential texture numbers to the sampler states that will be used with this texture...
		auto i=textureSamplersByTexture.find(n);
		if(i!=textureSamplersByTexture.end())
		{
			const set<TextureSampler*> &ts=i->second;
			for(auto j=ts.begin();j!=ts.end();j++)
			{
				textureDimensions[current_texture_number] = GetTextureDimension(m_declaredTextures[n]->type_enum,true);
				current_texture_number++;
			}
		}
	}
	return texture_number;
}

int Effect::GetImageNumber(const char *name)
{
	int image_number=current_image_number;
	std::string n(name);
	if(textureNumberMap.find(n)!=textureNumberMap.end())
	{
		image_number			=textureNumberMap[n]-1000;
		if(image_number<0)
			return -1;
	}
	else
	{
		// Is it declared??
		auto u=m_declaredTextures.find(n);
		if(u==m_declaredTextures.end())
			return 0;
		if(!IsTextureWriteable(u->second->type_enum))
			return 0;
		if(stricmp(name,"cloudDensity")==0)
		{
			std::cerr<<"cloudDensity";
		}
		textureNumberMap[n]=current_image_number+1000;
		textureDimensions[current_image_number+1000]=GetTextureDimension(m_declaredTextures[n]->type_enum,true);
		current_image_number++;
	}
	return image_number;
}

void Effect::SetTexture(int texture_number,GLuint tex,int dims,int depth,GLenum format,bool write,int mip,bool layered,int layer,bool cubemap)
{
	TextureAssignment &t=textureAssignmentMap[texture_number+(write?1000:0)];
	DeclaredTexture *dec=m_declaredTexturesByNumber[texture_number+(write?1000:0)];

	bool dec_write=dec?IsTextureWriteable(dec->type_enum):false;
	if(dec!=NULL&&dec_write!=write)
	{
		GLFX_CERR << "Texture declared as writeable?" << std::endl;
	}
	t.tex			=tex;
	if (tex!=0&&textureDimensions[texture_number+(write?1000:0)] != dims)
		GLFX_CERR << "Texture dimension mismatch" << std::endl;
	t.depth			=depth;
	if(format>0)
		t.format	=format;
	t.write_mip		=mip;
	t.layered		=layered;
	t.layer			=layer;
	t.cubemap		=cubemap;
}

void Effect::SetSamplerState(const char *name, unsigned sam)
{
	if (sam)
		prepared_sampler_states[name] = sam;
	else
	{
		auto i = prepared_sampler_states.find(name);
		if (i != prepared_sampler_states.end())
			prepared_sampler_states.erase(i);
	}
}

void Effect::AddComputeLayout(const std::string &name,const ComputeLayout &tg)
{
	m_shaderLayouts[name]=tg;
}

void Effect::AddTechniqueGroup(const std::string &groupName,const TechniqueGroup &tg)
{
	if(m_techniqueGroups.find(groupName)==m_techniqueGroups.end())
		m_techniqueGroups[groupName]=new TechniqueGroup;
	*(m_techniqueGroups[groupName])=tg;
}

void Effect::AddTechnique(const std::string &techname,const std::string &tg,Technique *t)
{
	if(m_techniqueGroups.find(tg)==m_techniqueGroups.end())
	{
		m_techniqueGroups[tg]=new TechniqueGroup;
	}
	TechniqueGroup *g=m_techniqueGroups[tg];
	g->m_techniques[techname] = t;
}
	string GetTypeOfParameter(const vector<glfxstype::variable> &parameters,const string &name)
	{
		for(vector<glfxstype::variable>::const_iterator j=parameters.begin();j!=parameters.end();j++)
		{
			if(name==j->identifier)
				return j->type;
		}
		return "";
	}

Function *Effect::DeclareFunction(const std::string &functionName, Function &buildFunction)
{
	Function *f				=new Function;

	
		ostringstream params;
		bool start=true;
		set<string> usedSamplerStates;
		std::map<std::string,TextureSampler*> nonParameterTextureSamplers=buildFunction.textureSamplers;
		for(vector<glfxstype::variable>::iterator j=buildFunction.parameters.begin();j!=buildFunction.parameters.end();j++)
		{
			string type=j->type;
			// We SHOULD check the type but don't yet.
			string name=j->identifier;
			// Is the paramater in our declarations list?
			auto a=buildFunction.declarations.find(name);
			if(a!=buildFunction.declarations.end())
			{
				buildFunction.declarations.erase(a);
			}
			// Is this one of the textures in the textureSampler list?
			auto u=buildFunction.textureSamplersByTexture.find(name);
			if(u!=buildFunction.textureSamplersByTexture.end())
			{
				// the type remains the same.
				for(auto v=u->second.begin();v!=u->second.end();v++)
				{
					if(start)
						start=false;
					else
						params<<", ";
					TextureSampler *ts=*v;
					usedSamplerStates.insert(ts->samplerStateName);
					params<<j->storage<<" "<<j->type<<" "<<ts->textureSamplerName();
				
					glfxstype::variable p;
					p.storage		=j->storage;
					p.type			=j->type;
					p.identifier	=(ts->textureName+"_")+ts->samplerStateName;
					p.template_		=j->template_;
					buildFunction.expanded_parameters.push_back(p);
					nonParameterTextureSamplers.erase(ts->textureSamplerName());
				}
			}
			else
			{
				auto a=usedSamplerStates.find(name);
				if(a!=usedSamplerStates.end())
					continue;
				u=buildFunction.textureSamplersBySampler.find(name);
				if(u!=buildFunction.textureSamplersBySampler.end())
				{
					// the type must become sampler2D, sampler3D etc. EITHER
					// the type is declared for the texture in the vars list, OR it is
					// in m_declaredTextures.
					for(auto v=u->second.begin();v!=u->second.end();v++)
					{
						if(start)
							start=false;
						else
							params<<", ";
						TextureSampler *ts=*v;
						string type=GetTypeOfParameter(buildFunction.parameters,ts->textureName);
						if(type.length()==0)
						{
							type = gEffect->GetDeclaredTextures().find(ts->textureName)->second->type;
						}
						params<<j->storage<<" "<<type<<" "<<ts->textureName<<"_"<<ts->samplerStateName;
						
						glfxstype::variable p;
						p.storage			=j->storage;
						p.type				=type;
						p.identifier		=ts->textureSamplerName();
						p.template_			=j->template_;
						buildFunction.expanded_parameters.push_back(p);
					
						nonParameterTextureSamplers.erase(ts->textureSamplerName());
					}
				}
				else
				{
					buildFunction.expanded_parameters.push_back(*j);
					if(start)
						start=false;
					else
						params<<", ";
					params<<j->storage<<" "<<j->type<<" "<<j->identifier;
				}
			}
		}
		// Any textureSamplers not passed up the line are added to the effect's list of global textureSamplers.
		// Note: This is only temporary until we stop including unused functions in the shared code.
		for(std::map<std::string,TextureSampler*>::const_iterator i=nonParameterTextureSamplers.begin();i!=nonParameterTextureSamplers.end();i++)
		{
			// use the one in the stored function, which is permanent, not buildFunction, which is temporary.
			TextureSampler *ts=nonParameterTextureSamplers[i->first];
			ts->global=true;
			//if(!gEffect->DeclareTextureSampler(i->second))
			//	errSem(string("Can't find texture declaration for ")+i->first);
		}


		
		buildFunction.params=params.str();

	*f						=buildFunction;










	gEffect->functions[functionName].push_back(f);
	for(auto p=f->textureSamplersByTexture.begin();p!=f->textureSamplersByTexture.end();p++)
	{
		auto q=p->second.begin();
		if(q!=p->second.end())
		{
			string t=string(" ")+(*q)->textureName+" ";
			find_and_replace(f->content,t,(*q)->textureSamplerName());
		}
	}
	return f;
}

void Effect::DeclareRasterizerState(const std::string &name,const RasterizerState &buildRasterizerState)
{
	RasterizerState *rs=new RasterizerState;
	*rs=buildRasterizerState;
	m_rasterizerStates[name]=rs;
}

void Effect::DeclareBlendState(const std::string &name,const BlendState &buildBlendState)
{
	BlendState *bs=new BlendState;
	*bs=buildBlendState;
	m_blendStates[name]=bs;
}

void Effect::DeclareDepthStencilState(const std::string &name,const DepthStencilState &buildDepthStencilState)
{
	DepthStencilState *ds=new DepthStencilState;
	*ds=buildDepthStencilState;
	m_depthStencilStates[name]=ds;
}

void Effect::DeclareSamplerState(const std::string &name,const SamplerState &buildSamplerState)
{
	SamplerState *ss=new SamplerState;
	*ss=buildSamplerState;
	m_samplerStates[name]=ss;
}

void Effect::DeclareStruct(const string &name,const Struct &ts)
{
	Struct *rs					=new Struct;
	*rs							=ts;
	m_structs[name]	=rs;
}

void Effect::SetTex(int texture_number,int dim,const TextureAssignment &t,int location_in_shader)
{
	// The effect knows the needed info: the format
	GLFX_ERROR_CHECK
	if(texture_number>=1000)
	{
		if(t.format>0)
			glBindImageTexture(texture_number-1000
 				,t.tex
 				,t.write_mip
				,t.layered		//dim == 3
				,t.layered?t.layer:0	// 0
				,GL_READ_WRITE
				,t.format);
		texture_number-=1000;
	/*	GL_INVALID_VALUE is generated if unit greater than or equal to the value of GL_MAX_IMAGE_UNITS (0x8F38).
		GL_INVALID_VALUE is generated if texture is not the name of an existing texture object.
		GL_INVALID_VALUE is generated if level or layer is less than zero.	*/
		GLFX_ERROR_CHECK
	}
	else
	{
	GLFX_ERROR_CHECK
		glActiveTexture(GL_TEXTURE0+texture_number);
		GLFX_ERROR_CHECK
		if (dim == 2)
		{
			// 2D but depth>1? That's an ARRAY texture.
			if(t.cubemap)
			{
				glBindTexture(GL_TEXTURE_CUBE_MAP,t.tex);
				glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
			}
			else if(t.depth>1)
				glBindTexture(GL_TEXTURE_2D_ARRAY,t.tex);
			else
				glBindTexture(GL_TEXTURE_2D,t.tex);
			GLFX_ERROR_CHECK
		}
		else if (dim == 3)
		{
			glBindTexture(GL_TEXTURE_3D,t.tex);
			GLFX_ERROR_CHECK
		}
		else
		{
	GLFX_ERROR_CHECK
			throw std::runtime_error("Unknown texture dimension!");
	GLFX_ERROR_CHECK
		}
	GLFX_ERROR_CHECK
	}
	GLFX_ERROR_CHECK
	glUniform1i(location_in_shader,texture_number);
	GLFX_ERROR_CHECK
}

bool Effect::SetVersionForProfile(int profileNum,const std::string &profileName)
{
	if(m_profileToVersion.find(profileName)!=m_profileToVersion.end())
	{
		return false;
	}
	m_profileToVersion[profileName]=profileNum;
	return true;
}

bool Effect::AddCompiledShader(ShaderType sType,const std::string &lvalCompiledShaderName,const std::string &rvalCompiledShaderName)
{
	CompiledShader *compiledShader	=m_compiledShaders[rvalCompiledShaderName];
	CompiledShaderMap::iterator i	=m_compiledShaders.find(lvalCompiledShaderName);
	if(i!=gEffect->m_compiledShaders.end())
	{
		delete i->second;
		// TODO: Warn here about double-compiling a shader.
		m_log<<("double-compiling shader ")<<std::endl;
	}
	if(sType!=compiledShader->shaderType)
	{
		m_log<<((((string("Shader type mismatch for ")+lvalCompiledShaderName+" - can't assign ")+ShaderTypeToString(sType)+" shader to ")+ShaderTypeToString(compiledShader->shaderType)+" shader").c_str());

		return false;
	}
	m_compiledShaders[lvalCompiledShaderName]=compiledShader;
	return true;
}

string& Effect::Filename()
{
    return m_filename;
}

string& Effect::Dir()
{
    return m_dir;
}

unsigned Effect::BuildProgram(const string& tech, const string& pass, string& log)
{
	GLFX_ERROR_CHECK
	TechniqueGroup *group	=current_group;
	map<string, Technique*>::iterator it = group->m_techniques.find(tech);
	if (it == group->m_techniques.end())
	{
		std::cerr<<"Can't find technique: "<<tech.c_str()<<std::endl;
		return 0;
	}
	Technique *t			=it->second;
	map<string, Program>::iterator pp=t->GetPasses().begin();
	if(pass.length())
		pp=t->GetPasses().find(pass);
	if(pp==t->GetPasses().end())
		return 0;
	unsigned programId		= pp->second.CompileAndLink(m_sharedCode,m_declaredTextures,log);
	if(programId)
	{
		GLFX_ERROR_CHECK
		glObjectLabel(GL_PROGRAM,
			programId,
			(GLsizei)tech.length(),
			tech.c_str());
		GLFX_ERROR_CHECK
		passStates[programId] = pp->second.passState;
		passProgramMap[programId]=&pp->second;
		if(pp->second.IsTransformFeedbackShader())
		{
			Program::Shader *gs=pp->second.GetShader(GEOMETRY_SHADER);
			if(gs)
			{
				if(gs->compiledShader)
					pp->second.SetOutputTopology(gs->compiledShader->transformFeedbackTopology);
			}
		}
	}
	return programId;
}

ostringstream& Effect::Log()
{
    return m_log;
}

bool Effect::IsTextureDeclared(const string &name)
{
	if(m_declaredTextures.find(name)!=m_declaredTextures.end())
		return true;
	return false;
}

bool Effect::DeclareTexture(const string &name,const DeclaredTexture &ts)
{
	DeclaredTexture *t=new DeclaredTexture(ts);
	m_declaredTextures[name]=t;
	int num=0;
	bool write=IsTextureWriteable(ts.type_enum);
	if(write)
		num=GetImageNumber(name.c_str())+1000;
	else
		num=GetTextureNumber(name.c_str());
	if(m_declaredTexturesByNumber.find(num)!=m_declaredTexturesByNumber.end())
	{
		GLFX_CERR<<"Already declared texture number "<<num<<std::endl;
	}
	else
	{
		m_declaredTexturesByNumber[num]=t;
	}
	declarations.push_back(t);
	return true;
}

bool Effect::DeclareTextureSampler(const TextureSampler *ts)
{
	auto i=additionalTextureDeclarations.find(ts->textureSamplerName());
	if(i!=additionalTextureDeclarations.end())
		return true;
	string tsname		=ts->textureSamplerName();
	string texture_name	=ts->textureName;
	if (IsDeclared(texture_name))
	{
		string sampler_type =(GetDeclaredTextures()).find(texture_name)->second->type;
		DeclaredTexture *t=new DeclaredTexture;
		additionalTextureDeclarations[tsname]=t;
		t->type			=sampler_type;
		auto d=GetDeclaredTextures();
		t->type_enum = (d.find(texture_name))->second->type_enum;
		// We know that this texture-sampler combo will be used in this shader.
		return true;
	}
	return false;
}

void Effect::MergeTextureSamplers(const std::map<std::string,TextureSampler*> &ts,const std::string &shaderName)
{
	for(auto i=ts.begin();i!=ts.end();i++)
	{
		const TextureSampler *t=i->second;
		auto j=textureSamplers.find(i->first);
		if(j!=textureSamplers.end())
		{
			textureSamplersByShader[shaderName].insert(j->second);
			continue;
		}
		TextureSampler *t2=new TextureSampler();
		textureSamplers[i->first]=t2;
		textureSamplersByTexture[i->second->textureName].insert(t2);
		*t2=*t;
		textureSamplersByShader[shaderName].insert(t2);
	}
}

const vector<string>& Effect::GetTechniqueList() const
{
	return m_techniqueNames;
}

const vector<string>& Effect::GetTechniqueGroupList() const
{
	return m_techniqueGroupNames;
}

Technique *Effect::GetTechniqueByName(const char *name) 
{
	return (current_group->m_techniques.find(string(name)))->second;
}

TechniqueGroup *Effect::GetTechniqueGroupByIndex(int idx)
{
	int i=0;
	map<string, TechniqueGroup*>::const_iterator it;
	for (it = m_techniqueGroups.begin(); it != m_techniqueGroups.end()&&i<idx; ++it)
	{
		i++;
	}
	TechniqueGroup *group=NULL;
	if(it!=m_techniqueGroups.end())
		group=it->second;
	return group;
}

TechniqueGroup *Effect::GetTechniqueGroupByName(const char *name)
{
	map<string, TechniqueGroup*>::const_iterator pp=m_techniqueGroups.find(name);
	TechniqueGroup *group=pp->second;
	return group;
}

const vector<string>& Effect::GetFilenameList() const
{
    return m_filenames;
}

bool Effect::IsDeclared(string name)
{
	if(m_samplerStates.find(name)!=m_samplerStates.end())
		return true;
	if(m_declaredTextures.find(name)!=m_declaredTextures.end())
		return true;
	return false;
}

bool IsIntegerType(const string &type)
{
	if(type.substr(0,3)=="int"||type.substr(0,4)=="ivec"||type.substr(0,4)=="uvec"||type.substr(0,4)=="uint")
	{
		return true;
	}
	return false;
}

void Effect::Compile(glfxParser::ShaderType shaderType,const CompilableShader &sh,const std::string &compiledName)
{
	CompiledShader *compiledShader=m_compiledShaders[compiledName];
	compiledShader->transformFeedbackTopology = UNDEFINED_TOPOLOGY;
	std::ostringstream shaderCode;
	std::ostringstream extraDeclarations;
	std::ostringstream finalCode;
	// Put together the source.
	string shaderContent;
	std::set<const Function *> fns;
	AccumulateFunctionsUsed(sh.function,fns);
	// Insert the textures declared that the functions use.
	std::set<string> declarationNames;
	for(auto u=fns.begin();u!=fns.end();u++)
	{
		for(auto v=(*u)->declarations.begin();v!=(*u)->declarations.end();v++)
		{
			declarationNames.insert(*v);
		}
	}
	for(auto w:declarationNames)
	{
		string dec_name=w;
		const DeclaredTexture *dec=m_declaredTextures[dec_name];
		WriteLineNumber(shaderCode,dec->file_number,dec->line_number);
		if(IsTextureWriteable(dec->type_enum))
			shaderCode<<"#ifdef IN_COMPUTE_SHADER\n";
		shaderCode<<dec->layout<<"uniform ";
		if(dec->variant)
			shaderCode<<dec_name<<"_";
		shaderCode<<dec->type<<" "<<dec_name<<";\n";
		if(IsTextureWriteable(dec->type_enum))
			shaderCode<<"#endif\n";
		if(dec->variant)
			compiledShader->variantDeclarations.insert(dec_name);
	}

	std::map<int,const Function *> ordered_fns;
	for(auto u=fns.begin();u!=fns.end();u++)
	{
		// Add only the called functions, not the main one. That goes at the end.
		if(*u!=sh.function)
			ordered_fns[(*u)->main_linenumber]=*u;
	}
	
	for(auto u=ordered_fns.begin();u!=ordered_fns.end();u++)
	{
		const Function *F=(u->second);
		WriteLineNumber(shaderCode,F->current_filenumber,F->content_linenumber);
		shaderCode<< F->returnType<<" "<<F->name<<"("<<F->params<<")"<<"\n{\n"<<F->content<<"\n}\n";
	}
	// main function. If it's not a GS, we include the function itself, then call it from main().
	if(shaderType!=GEOMETRY_SHADER)
	{
		WriteLineNumber(shaderCode,sh.function->current_filenumber,sh.function->content_linenumber);
		shaderCode<<sh.function->returnType<<" "<< sh.function->name<<"("<<sh.function->params<<")"<<"\n{\n"<<sh.function->content<<"\n}\n";
		if(sh.function->returnType!=string("void"))
		{
			shaderContent=sh.function->returnType+" ";
			shaderContent+="retval=";
		}
		shaderContent+=sh.function->name;
		shaderContent+="(";
	}
	else
	{
		shaderContent=sh.function->content;
	}
	// Add shader parameters
	for(vector<glfxstype::variable>::const_iterator it=sh.function->parameters.begin();it!=sh.function->parameters.end();++it)
	{
		bool as_interface=(shaderType!=VERTEX_SHADER);
		string outBlockNamespace=it->identifier;
		string type(it->type);
		string storage(it->storage);
		if(storage.length()==0)
			storage="in";
		if(storage==string("inout"))
		{
			size_t brack_pos=type.find("<");
			if(it->template_.size())
			{
				string output_type=type;
				type=it->template_;
				stringReplaceAll(output_type,"PointStream","points");
				stringReplaceAll(output_type,"LineStream","line_strip");
				stringReplaceAll(output_type,"TriangleStream","triangle_strip");
			}
		}
		map<string,Struct*>::const_iterator u=gEffect->GetStructs().find(type);
	
		if(u!=gEffect->GetStructs().end())
		{
			const Struct *s=u->second;
		// Geometry shader outputs have the "inout" storage specifier, and a template-looking type.
		// We must convert them to something like:
		// layout(output_primitive,maxverts=vert_count) out;
		// and an untemplated output type.
		//	points
		//	line_strip
		//	triangle_strip
			if(storage==string("inout"))
			{
				compiledShader->outputStruct=type;
				string output_type=it->type;
				{
					if (output_type.find("PointStream")<output_type.length())
					{
						compiledShader->transformFeedbackTopology = POINTS;
					}
					if (output_type.find("LineStream")<output_type.length())
					{
						compiledShader->transformFeedbackTopology = LINES;
					}
					if (output_type.find("TriangleStream")<output_type.length())
					{
						compiledShader->transformFeedbackTopology = TRIANGLES;
					}
					stringReplaceAll(output_type,"PointStream","points");
					stringReplaceAll(output_type,"LineStream","line_strip");
					stringReplaceAll(output_type,"TriangleStream","triangle_strip");
					shaderCode<<"layout("<<output_type<<",max_vertices="<<sh.maxGSVertexCount<<") out;\n";
	
				}
				// In the actual shader code, convert HLSL-style member function calls to GLSL type
				// stream commands:
				string appendcall=outBlockNamespace+".Append";
				size_t pos=shaderContent.find(appendcall);
				while(pos<shaderContent.size())
				{
					// We must replace something of the form vSream.Append(OUT)
					// with something like:
					// vStream.pos	=OUT.pos;
					// vStream.txc	=OUT.txc;
					// EmitVertex();

					// First extract the name of the appended struct:
					size_t startpos=shaderContent.find("(",pos);
					size_t endpos=shaderContent.find(")",startpos);
					if(startpos>=shaderContent.length()||endpos>=shaderContent.length())
						break;
			
					string localStructName=shaderContent.substr(startpos+1,endpos-startpos-1);
					ostringstream vertexEmitCode;
					for(int i=0;i<(int)s->m_structMembers.size();i++)
					{
						const StructMember &m=s->m_structMembers[i];
						vertexEmitCode<<outBlockNamespace<<"."<<m.name<<"="<<localStructName<<"."<<m.name<<"; ";
					}
					vertexEmitCode<<"EmitVertex()";
					shaderContent.replace(shaderContent.begin()+pos,shaderContent.begin()+endpos+1,vertexEmitCode.str());
					pos=shaderContent.find(appendcall,endpos);
			
				}
				stringReplaceAll(shaderContent,outBlockNamespace+".RestartStrip()","EndPrimitive();");
				as_interface=true;
				storage="out";
			}
			// Geometry shader storage (line,lineadj,point) needs special consideration.
			// it gets moved to this kind of declaration:
			// layout(triangles) in;
			// layout (triangle_strip, max_vertices=6) out;
			if(storage==string("line")||storage==string("point")||storage==string("triangle")||storage==string("lineadj")||storage==string("triangleadj"))
			{
				// primitive type			vertices per primitive
				//	points					1
				//	lines					2
				//	lines_adjacency			4
				//	triangles				3
				//	triangles_adjacency		6
				storage+="s";
				stringReplaceAll(storage,"adjs","s_adjacency");
				shaderCode<<"layout("<<storage<<") in;\n";
				storage="in";
				as_interface=true;
			}
			if(as_interface)
			{
				string interfaceName	=outBlockNamespace;
				if(shaderType!=GEOMETRY_SHADER)
				{
					interfaceName+="IO";
					extraDeclarations<<type<<" "<<outBlockNamespace<<";\n";
				}
				shaderCode<<storage<<" "<<type<<"IO\n";
				shaderCode<<"{\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					shaderCode<<'\t';
					if(IsIntegerType(m.type))
						shaderCode<<"flat ";
					shaderCode<<m.type<<' '<<m.name<<";"<<endl;
				}
				shaderCode<<"} "<<interfaceName<<";\n";
				// Now we have to copy... EVERY MEMBER from the "interface" to the struct instance. Thanks, OpenGL!
				if(shaderType!=GEOMETRY_SHADER)
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					extraDeclarations<<outBlockNamespace<<"."<<m.name<<"="<<interfaceName<<"."<<m.name<<";\n";
				}
				if(shaderType==GEOMETRY_SHADER)
					compiledShader->outputStructName=type+"IO";
			}
			else
			{
				extraDeclarations<<type<<" "<<outBlockNamespace<<";\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					string sem=(type+"_")+m.name;
					if(m.semantic.length())
						sem=(sem+"_")+m.semantic;
					// If built-in, it's implicit: don't add it as a declaration.
					if(m.semantic==string("gl_VertexID"))
					{
						sem=m.semantic;
					}
					else
					{
						shaderCode<<storage<<' '<<m.type<<' '<<sem<<";"<<endl;
					}
					extraDeclarations<<outBlockNamespace<<"."<<m.name<<"="<<sem<<";\n";
				}
			}
		}
		else 
		{
			if(it->template_.length()>0)
			{
				extraDeclarations<<it->type<<" "<<outBlockNamespace<<"="<<it->template_<<";\n"<<endl;
			}
			else
			{
			// First put #line in to make sure that all our definitions produce correct-looking warnings/errors.
				shaderCode<<"#line "<<sh.main_linenumber<<" "<<sh.current_filenumber<<endl;
				shaderCode<<it->storage<<" "<<type<<" "<<it->identifier<<";\n"<<endl;
			}
		}
		if(shaderType!=GEOMETRY_SHADER)
		{
			if(it!=sh.function->parameters.begin())
				shaderContent+=",";
			shaderContent+=outBlockNamespace;
		}
	}
	if(shaderType!=GEOMETRY_SHADER)
	{
		shaderContent+=");\n";
	}
	// Add the return variable.
	if(sh.function->returnType!=string("void"))
	{
		map<string,Struct*>::const_iterator u=gEffect->GetStructs().find(sh.function->returnType);
		if(u==gEffect->GetStructs().end())
		{
			string returnVariable="returnVariable";
			// if we're returning a simple type, we declare it as an output.
			shaderCode<<"out "<<sh.function->returnType<<" "<<returnVariable<<";\n";
			finalCode<<returnVariable<<"="<<"retval"<<";"<<endl;
		}
		else
		{
			string returnVariable="retval";
			//finalCode<<sh.function->returnType<<" "<<returnVariable<<";\n";
			bool as_interface=(shaderType!=FRAGMENT_SHADER);
			const Struct *s=u->second;
			string outBlockNamespace="outBlockNamespace";
			if(as_interface)
			{
				string output_name=sh.function->returnType+"IO";
				shaderCode<<"out "<<output_name<<"\n{\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					shaderCode<<"\t";
					if(IsIntegerType(m.type))
						shaderCode<<"flat ";
					shaderCode<<m.type<<" "<<m.name<<";\n";
					string output_member_name=(output_name+".")+m.name;
					compiledShader->feedbackOutput.push_back(output_member_name);
				}
				shaderCode<<"} "<<outBlockNamespace<<";"<<endl;
				if(shaderType==VERTEX_SHADER)
				{
					compiledShader->outputStruct=sh.function->returnType;
					compiledShader->outputStructName=sh.function->returnType+"IO";
				}
			}
			if(returnVariable.find("(")<returnVariable.length())
			{
				returnVariable="returnVariable";
				finalCode<<sh.function->returnType<<" "<<returnVariable<<"="<<"retval"<<";"<<endl;
			}
			for(int i=0;i<(int)s->m_structMembers.size();i++)
			{
				const StructMember &m=s->m_structMembers[i];
				string sem=(sh.function->returnType+"_")+m.name;
				if(m.semantic.length())
					sem=(sem+"_")+m.semantic;
				// Special outputs:
				if(m.semantic==string("gl_Position")||m.semantic==string("SV_POSITION"))
				{
					string builtin_name="gl_Position";
					// It's implicit, don't declare:
					//shaderCode<<"out "<<m.type<<' '<<builtin_name<<";"<<endl;
					// Flip y of output because we consider GL textures to be "upside-down".
					finalCode<<returnVariable<<"."<<m.name<<".y*=rescaleVertexShaderY;"<<endl;
					finalCode<<builtin_name<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
				else if(m.semantic.substr(0,9)==string("SV_DEPTH"))
				{
					string builtin_name="gl_FragDepth";
					finalCode<<builtin_name<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
				else if(m.semantic.substr(0,9)==string("SV_TARGET"))
				{
					string numstr=m.semantic.substr(9,m.semantic.length()-9);
					int num=0;
					 char * pEnd;
					num=strtol(numstr.c_str(),&pEnd,10);
					if(num>=0)
						shaderCode<<"layout(location = "<<num<<") ";
				}
				else
				{
					if(shaderType==FRAGMENT_SHADER)
						continue;
				}
				if(as_interface)
				{
					if(outBlockNamespace.length())
						finalCode<<outBlockNamespace<<".";
					finalCode<<m.name<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
				else
				{
					shaderCode<<"out "<<m.type<<' '<<sem<<";"<<endl;
					finalCode<<sem<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
			}
		}
	}
	// Add definition and code
	shaderCode<<"#line "<<sh.main_linenumber<<" "<<sh.current_filenumber<<endl;
	shaderCode<<"void main()\n{\n";
	if(extraDeclarations.str().length())
		shaderCode<<extraDeclarations.str()<<"\n";
	shaderCode<<"#line "<<sh.content_linenumber<<" "<<sh.current_filenumber<<endl;
	shaderCode<<shaderContent<<"\n"<<finalCode.str()<<"\n}\n";

	compiledShader->source=shaderCode.str();
	// now we must put a #line directive in the shared code, because we've just snipped out a bunch of what was there:
}

const CompiledShader *Effect::AddCompiledShader(const std::string &compiledShaderName,const std::string &fnName,ShaderType sType,int version_num
																					,std::string outputStruct
																					,std::string outputStructName
																					,std::string source)
{
	CompiledShader *compiledShader			=new CompiledShader;
	m_compiledShaders[compiledShaderName]	=compiledShader;
	compiledShader->m_functionName			=fnName;
	compiledShader->shaderType				=sType;
	compiledShader->version					=version_num;

	compiledShader->outputStruct			=outputStruct;
	compiledShader->outputStructName		=outputStructName;
	compiledShader->source					=source;

	return compiledShader;
}

string Effect::GetDeclaredType(std::string name) const
{
	if(m_samplerStates.find(name)!=m_samplerStates.end())
		return "SamplerState";
	auto i=m_declaredTextures.find(name);
	if(i!=m_declaredTextures.end())
		return i->second->type;
	return "unknown";
}

void Effect::SetFilenameList(const vector<string> &filenamesUtf8)
{
	m_filenames=filenamesUtf8;
}

void Effect::AccumulateFunctionsUsed(const Function *f,std::set<const Function *> &s) const
{	
	s.insert(f);
	for(auto u=f->functionsCalled.begin();u!=f->functionsCalled.end();u++)
	{
		AccumulateFunctionsUsed(*u,s);
	}
}

extern int do_mkdir(const char *path_utf8);

void Effect::PopulateProgramList()
{
	m_techniqueNames.clear();
	map<string, TechniqueGroup*>::const_iterator ig=m_techniqueGroups.find("");
	if(ig!=m_techniqueGroups.end())
	{
		TechniqueGroup *group=ig->second;
		for (map<string, Technique*>::const_iterator it = group->m_techniques.begin(); it != group->m_techniques.end(); ++it)
			m_techniqueNames.push_back(it->first);
	}
	m_techniqueGroupNames.clear();
	for (map<string, TechniqueGroup*>::const_iterator it = m_techniqueGroups.begin(); it != m_techniqueGroups.end(); ++it)
		m_techniqueGroupNames.push_back(it->first);
	CreateDefinedSamplers();

	ostringstream decl;
	for(auto i=additionalTextureDeclarations.begin();i!=gEffect->additionalTextureDeclarations.end();i++)
	{
		decl << "uniform " << i->second->type << " " << i->first << ";\n";
	}
	m_sharedCode=(decl.str()+m_sharedCode);

	// save shared code?
	string bin_dir=glfxGetCacheDirectory();
	if(bin_dir.length())
	{
		do_mkdir(bin_dir.c_str());
		string outputFilename=bin_dir+"/";
		outputFilename+=this->Filename()+".glfxo";
		std::ofstream ofstr(outputFilename.c_str());
		const string &str=m_sharedCode;
		ofstr.write(str.c_str(),str.length());
		if(errno!=0)
		{
			GLFX_CERR<<"Error: Can't write cached file "<<outputFilename.c_str()<<"; does the directory exist?"<<std::endl;
			DebugBreak();
		}
		//else
		//	std::cerr<<outputFilename.c_str()<<": Warning B0000: shared source for "<<Filename()<<std::endl;
	}
}

void Effect::CreateDefinedSamplers()
{
	for(auto i=textureSamplers.begin();i!=textureSamplers.end();i++)
	{
		string samplerName=i->second->samplerStateName;
		const SamplerState *S=m_samplerStates[samplerName];
		if(!S)
			continue;
		GLuint samplerObj;
		glGenSamplers(1, &samplerObj);
		glSamplerParameteri(samplerObj, GL_TEXTURE_MIN_FILTER, S->MinFilter);
		glSamplerParameteri(samplerObj, GL_TEXTURE_MAG_FILTER, S->MagFilter);
		glSamplerParameteri(samplerObj, GL_TEXTURE_WRAP_S, S->AddressU);
		glSamplerParameteri(samplerObj, GL_TEXTURE_WRAP_T, S->AddressV);
		glSamplerParameteri(samplerObj, GL_TEXTURE_WRAP_R, S->AddressW);
	/*		NOT yet implemented:
		glSamplerParameterf(samplerObj, GL_TEXTURE_MIN_LOD, S->MinLod);
		glSamplerParameterf(samplerObj, GL_TEXTURE_MAX_LOD, S->MaxLod);
		glSamplerParameterf(samplerObj, GL_TEXTURE_LOD_BIAS, S->LodBias);
		glSamplerParameteri(samplerObj, GL_TEXTURE_COMPARE_MODE, S->CompareMode);
		glSamplerParameteri(samplerObj, GL_TEXTURE_COMPARE_FUNC, S->CompareFunc);
		glSamplerParameteri(samplerObj, GL_TEXTURE_MAX_ANISOTROPY_EXT, S->MaxAnisotropy);*/
		glSamplerStates[samplerName]=samplerObj;
	}
}

bool Effect::PassHasTransformFeedback(unsigned pass)
{
	auto i=passProgramMap.find(pass);
	if(i==passProgramMap.end())
		return false;
	return (i->second->IsTransformFeedbackShader());
}

void Effect::Apply(unsigned pass)
{
	GLFX_ERROR_CHECK
	glUseProgram(pass);
	GLFX_ERROR_CHECK
	current_pass=pass;
	current_pass=ApplyPassTextures(pass);
	glUseProgram(current_pass);
	GLFX_ERROR_CHECK
	if (PassHasTransformFeedback(pass))
	{
		glEnable(GL_RASTERIZER_DISCARD);
	//	If no geometry shader is present, while transform feedback is active the mode parameter to glDrawArrays must match those specified in the following table :

	//	Transform Feedback primitiveMode	Allowed Render Primitive modes
	//		GL_POINTS	GL_POINTS
	//		GL_LINES	GL_LINES, GL_LINE_LOOP, GL_LINE_STRIP, GL_LINES_ADJACENCY, GL_LINE_STRIP_ADJACENCY
	//		GL_TRIANGLES	GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES_ADJACENCY, GL_TRIANGLE_STRIP_ADJACENCY
	//		If a geometry shader is present, the output primitive type from the geometry shader must match those provided in the following table :

	//	Transform Feedback primitiveMode	Allowed Geometry Shader Output Primitive Type
	//		GL_POINTS	points
	//		GL_LINES	line_strip
//			GL_TRIANGLES	triangle_strip
		
	GLFX_ERROR_CHECK
		auto i=passProgramMap.find(pass);
		if(i!=passProgramMap.end())
		{
			if(i->second->IsTransformFeedbackShader())
			{
				Topology t=i->second->GetOutputTopology();
				/*
If Transform Feedback is active, the transform feedback mode must match the applicable primitive mode.

That mode is determined as follows:
	If a Geometry Shader is active, then the applicable primitive mode is the GS's output primitive type.
	If no GS is active but a Tessellation Evaluation Shader is active, then the applicable primitive mode is the TES's output primitive type.
	Otherwise, the applicable primitive type is the primitive mode provided to the drawing command.
				*/

				switch(t)
				{
					case TRIANGLES:
						glBeginTransformFeedback(GL_TRIANGLES);
	GLFX_ERROR_CHECK
					break;
					case LINES:
						glBeginTransformFeedback(GL_LINES);
	GLFX_ERROR_CHECK
					break;
					case POINTS:
						glBeginTransformFeedback(GL_POINTS);
	GLFX_ERROR_CHECK
					break;
				default:
	GLFX_ERROR_CHECK
					break;
				};
			}
		}
	}
	GLFX_ERROR_CHECK
}

void Effect::Reapply(unsigned pass)
{
	Apply(pass);
}

void Effect::Unapply()
{
	if (glIsEnabled(GL_RASTERIZER_DISCARD))
	{
		glEndTransformFeedback();
		glDisable(GL_RASTERIZER_DISCARD);
	}
	glUseProgram(0);
	current_pass=0;
}

unsigned Effect::ApplyPassTextures(unsigned pass)
{
	if(!pass)
		return 0;
	GLFX_ERROR_CHECK
	auto p=passProgramMap.find(pass);
	// The variant is chosen by 
	std::map<string,GLenum> variableFormats;
	for(auto i=textureNumberMap.begin();i!=textureNumberMap.end();i++)
	{
		int main_texture_number		=i->second;
		const TextureAssignment &ta	=textureAssignmentMap[main_texture_number];
		if(main_texture_number<1000)
			continue;
		GLenum f=ta.format;
		variableFormats[i->first]=f;
	}
	int variantNumber=p->second->GetVariantNumber(variableFormats);
	 current_pass=pass;
	if(variantNumber)
		current_pass=p->second->GetVariantPass(variantNumber);
	std::map<unsigned,PassState>::iterator j=passStates.find(pass);
	for(auto i=textureNumberMap.begin();i!=textureNumberMap.end();i++)
	{
	GLFX_ERROR_CHECK
		int main_texture_number		=i->second;
	if(textureDimensions.find(main_texture_number)==textureDimensions.end())
	{
		GLFX_CERR<<"No dimension for texture "<<main_texture_number<<std::endl;
		continue;
	}
	int dim	=textureDimensions[main_texture_number];
		int texture_number			=main_texture_number;
		const TextureAssignment &ta	=textureAssignmentMap[main_texture_number];
		GLint loc					=glGetUniformLocation(current_pass,i->first.c_str());
	GLFX_ERROR_CHECK
		if(loc>=0)
		{
			SetTex(texture_number,dim,ta,loc);
			if(texture_number<1000)
				glBindSampler(texture_number,0);
	GLFX_ERROR_CHECK
		}
		texture_number++;
	GLFX_ERROR_CHECK
		// The texture numbers after this are for sampler states for this texture.
		if (j != passStates.end())
		{
			PassState &passState = j->second;
			auto k = passState.textureSamplersByTexture.find(i->first);
			if (k != passState.textureSamplersByTexture.end())
			{
				const vector<TextureSampler*> &ts = k->second;
				for (auto l = ts.begin(); l != ts.end(); l++)
				{
					GLint loc2 = glGetUniformLocation(current_pass, (*l)->textureSamplerName().c_str());
					if (loc2 >= 0)
					{
						GLFX_ERROR_CHECK
						auto b =prepared_sampler_states.find((*l)->samplerStateName);
						auto c =glSamplerStates.find((*l)->samplerStateName);
						// Have we set a sampler state override?
						if (b!= prepared_sampler_states.end())
						{
							GLuint sampler_state =b->second;
							glBindSampler(texture_number, sampler_state);
							SetTex(texture_number,dim, ta, loc2);
						}
						else if (c != glSamplerStates.end())
						{
							GLuint sampler_state =c->second;
							glBindSampler(texture_number, sampler_state);
							SetTex(texture_number,dim,ta, loc2);
						}
						else
						{
							SetTex(main_texture_number,dim,ta, loc2);
						}
					}
					texture_number++;
				}
			}
		}
	}
	return current_pass;
}

void Effect::ApplyPassState(unsigned pass)
{
	std::map<unsigned,PassState>::iterator i=passStates.find(pass);
	if(i==passStates.end())
		return;
	PassState &passState=i->second;
	if(passState.depthStencilState.length()>0)
	{
		if(m_depthStencilStates.find(passState.depthStencilState)==m_depthStencilStates.end())
		{
			m_log<<"Depth state not found: "<<passState.depthStencilState<<std::endl;
			glDisable(GL_DEPTH_TEST);
			glDepthMask(0);
		}
		else
		{
			DepthStencilState &depthStencilState=*m_depthStencilStates[passState.depthStencilState];
			if(depthStencilState.DepthEnable)
			{
				glEnable(GL_DEPTH_TEST);
				glDepthMask(depthStencilState.DepthWriteMask);
				glDepthFunc(depthStencilState.DepthFunc);
			}
			else
				glDisable(GL_DEPTH_TEST);
		}
	}
	if(passState.blendState.length()>0)
	{
		BlendState &blendState=*m_blendStates[passState.blendState];
		int num=0;
			GLFX_ERROR_CHECK
		for(std::map<int,bool>::iterator i=blendState.BlendEnable.begin();i!=blendState.BlendEnable.end();i++)
		{
			if(i->second)
				num++;
			if(blendState.RenderTargetWriteMask.find(i->first)!=blendState.RenderTargetWriteMask.end())
			{
				unsigned m=blendState.RenderTargetWriteMask[i->first];
				glColorMaski(i->first,(m&0x8)!=0,(m&0x4)!=0,(m&0x2)!=0,(m&0x1)!=0);
				GLFX_ERROR_CHECK
			}
			else glColorMaski(i->first,true,true,true,true);
		}
		if(!num)
		{
			glDisable(GL_BLEND);
			glBlendEquationSeparatei(0, GL_FUNC_ADD,GL_FUNC_ADD);
			glBlendFuncSeparatei(0,  GL_ONE, GL_ZERO,   GL_ONE, GL_ZERO);
			GLFX_ERROR_CHECK
		}
		else
		{
			glEnable(GL_BLEND);
			GLFX_ERROR_CHECK
			for(std::map<int,bool>::iterator i=blendState.BlendEnable.begin();i!=blendState.BlendEnable.end();i++)
			{
				if(i->second)
				{

					glBlendEquationSeparatei((unsigned)i->first, blendState.BlendOp,blendState.BlendOpAlpha);
			GLFX_ERROR_CHECK
					glBlendFuncSeparatei((unsigned)i->first, blendState.SrcBlend, blendState.DestBlend,
										   blendState.SrcBlendAlpha, blendState.DestBlendAlpha);
			GLFX_ERROR_CHECK
				}
				else
				{
					glBlendEquationSeparatei((unsigned)i->first, GL_FUNC_ADD,GL_FUNC_ADD);
			GLFX_ERROR_CHECK
					glBlendFuncSeparatei((unsigned)i->first, GL_ONE, GL_ZERO,
										   GL_ONE, GL_ZERO);
			GLFX_ERROR_CHECK
				}
			}
			if(blendState.AlphaToCoverageEnable)
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			GLFX_ERROR_CHECK
		}
	}
	// Now we will set the appropriate sampler states.
}

void Effect::SaveToCache(const std::string &filename)
{
	std::ofstream ofs(filename);
	ofs<<"source: "<<m_filename<<endl;
	for(map<string,TechniqueGroup*>::const_iterator i=m_techniqueGroups.begin();i!=m_techniqueGroups.end();i++)
	{
		string groupname=i->first;
		ofs<<"group "<<i->first<<"\n{\n";
		TechniqueGroup *g=i->second;
		for(map<string,Technique*>::const_iterator j=g->m_techniques.begin();j!=g->m_techniques.end();j++)
		{
			ofs<<"\ttechnique "<<j->first<<"\t\n{\n";
			Technique *t=j->second;
			for(map<string,Program>::const_iterator k=t->GetPasses().begin();k!=t->GetPasses().end();k++)
			{
				ofs<<"\ttechnique "<<j->first<<"\t\n{\n";
				ofs<<"\t\n}\n";
			}
			ofs<<"\t\n}\n";
		}
		ofs<<"\n}\n";
	}
	std::map<std::string,TechniqueGroup*>				m_techniqueGroups;
	std::map<std::string,BlendState*>					m_blendStates;
	std::map<std::string,DepthStencilState*>			m_depthStencilStates;
	std::map<std::string,SamplerState*>					m_samplerStates;
	std::map<std::string,DeclaredTexture>				m_declaredTextures;
	std::map<std::string,RasterizerState*>				m_rasterizerStates;
	std::map<std::string,ComputeLayout>					m_shaderLayouts;
	std::map<unsigned,PassState>						passStates;
	std::map<unsigned,Program*>							passProgramMap;
	std::map<std::string,unsigned>						samplerObjects;
	ProfileMap											m_profileToVersion;
	CompiledShaderMap									m_compiledShaders;
	std::map<std::string,std::vector<Function*> >		functions;
	vector<string>										m_filenames;
	string												m_sharedCode;
	std::map<std::string, TextureSampler*>				textureSamplers;
}

void Effect::LoadFromCache(const std::string &filename)
{
}