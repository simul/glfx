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

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif
#include "glfxScanner.h"
#include "glfxProgram.h"
#include "glfxErrorCheck.h"
#include <set>

Effect::Effect()
    : m_includes(0)
    , m_active(true)
	,current_group(NULL)
	,current_texture_number(0)
	,current_image_number(0)
	,current_pass(0)
{
}

Effect::~Effect()
{
  //  for(map<string,Program*>::iterator it=m_programs.begin(); it!=m_programs.end(); ++it)
  //      delete it->second;
    for(map<string,Sampler*>::iterator it=m_samplers.begin(); it!=m_samplers.end(); ++it)
		delete it->second;
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
}

void Effect::Clear()
{
	for(auto i=functions.begin();i!=functions.end();i++)
	{
		for(auto j=i->second.begin();j!=i->second.end();j++)
			delete *j;
	}
	functions.clear();
	m_techniqueGroups.clear();
	m_techniqueNames.clear();
	m_techniqueGroupNames.clear();
	m_samplers.clear();
	m_blendStates.clear();
	m_depthStencilStates.clear();
	m_samplerStates.clear();
	m_declaredTextures.clear();
	m_rasterizerStates.clear();
	m_shaderLayouts.clear();
	passStates.clear();
	passProgramMap.clear();
	samplerObjects.clear();
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
		textureNumberMap[n]						=current_texture_number;
		if (m_declaredTextures.find(n) == m_declaredTextures.end())
		{
			GLFX_CERR << "Texture " << name << " is not declared." << std::endl;
			current_texture_number++;
			return texture_number;
		}
		else
		{
			textureDimensions[current_texture_number] = GetTextureDimension(m_declaredTextures[n].type_enum,true);
		}
		current_texture_number++;
		// Now we will allocate sequential texture numbers to the sampler states that will be used with this texture...
		auto i=textureSamplersByTexture.find(n);
		if(i!=textureSamplersByTexture.end())
		{
			const set<TextureSampler*> &ts=i->second;
			for(auto j=ts.begin();j!=ts.end();j++)
			{
				textureDimensions[current_texture_number] = GetTextureDimension(m_declaredTextures[n].type_enum,true);
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
	}
	else
	{
		textureNumberMap[n] = current_image_number + 1000;
		textureDimensions[current_image_number + 1000] = GetTextureDimension(m_declaredTextures[n].type_enum,true);
		current_image_number++;
	}
	return image_number;
}

void Effect::SetTexture(int texture_number,GLuint tex,int dims,int depth,GLenum format,bool write)
{
	TextureAssignment &t=textureAssignmentMap[texture_number+(write?1000:0)];
	t.tex		=tex;
	if (tex!=0&&textureDimensions[texture_number+(write?1000:0)] != dims)
		GLFX_CERR << "Texture dimension mismatch" << std::endl;
	t.depth		=depth;
	t.format	=format;
	t.write		=write;
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

void Effect::SetTex(int texture_number,const TextureAssignment &t,int location_in_shader)
{
	// The effect knows the needed info: the format
	GLFX_ERROR_CHECK
	// Fall out silently if this texture is not set.
	//if(!t.tex)
	//	return;
	if(t.write)
	{
		glBindImageTexture(texture_number-1000,
 			t.tex,
 			0,
			textureDimensions[texture_number] == 3,
 			0,
 			GL_READ_WRITE,
			t.format);
		texture_number-=1000;
/*	GL_INVALID_VALUE is generated if unit greater than or equal to the value of GL_MAX_IMAGE_UNITS (0x8F38).
	GL_INVALID_VALUE is generated if texture is not the name of an existing texture object.
	GL_INVALID_VALUE is generated if level or layer is less than zero.	*/
	GLFX_ERROR_CHECK
	}
	else
	{
		glActiveTexture(GL_TEXTURE0+texture_number);
		GLFX_ERROR_CHECK
		if (textureDimensions[texture_number] == 2)
		{
			// 2D but depth>1? That's an ARRAY texture.
			if(t.depth>1)
				glBindTexture(GL_TEXTURE_2D_ARRAY,t.tex);
			else
				glBindTexture(GL_TEXTURE_2D,t.tex);
			GLFX_ERROR_CHECK
		}
		else if (textureDimensions[texture_number] == 3)
		{
			glBindTexture(GL_TEXTURE_3D,t.tex);
			GLFX_ERROR_CHECK
		}
		else
		{
			throw std::runtime_error("Unknown texture dimension!");
		}
	}
	glUniform1i(location_in_shader,texture_number);
	GLFX_ERROR_CHECK
}

bool& Effect::Active()
{
    return m_active;
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
	if(tech.length() == 0)
	{
		std::cerr<<"Must have a technique"<<std::endl;
		assert(tech.length());
		return 0;
	}
	else
	{
		TechniqueGroup *group=current_group;
		map<string, Technique*>::iterator it = group->m_techniques.find(tech);
		if (it == group->m_techniques.end())
			return 0;
		Technique *t	=it->second;
		map<string, Program>::iterator jt=t->GetPasses().begin();
		if(pass.length())
			jt=t->GetPasses().find(pass);
		if(jt==t->GetPasses().end())
			return 0;

		unsigned programId = jt->second.CompileAndLink(m_sharedCode.str(),log);
		if(programId)
		{
			GLFX_ERROR_CHECK
			glObjectLabel(GL_PROGRAM,
				programId,
				tech.length(),
				tech.c_str());
			GLFX_ERROR_CHECK
			passStates[programId] = jt->second.passState;
			passProgramMap[programId]=&jt->second;
			if(jt->second.IsTransformFeedbackShader())
			{
				Program::Shader *gs=jt->second.GetShader(GEOMETRY_SHADER);
				if(gs)
				{
					if(gs->compiledShader)
						jt->second.SetOutputTopology(gs->compiledShader->transformFeedbackTopology);
				}
			/*	else
				{
					Program::Shader *vs=jt->second.GetShader(VERTEX_SHADER);
					if(vs->compiledShader)
						jt->second.SetOutputTopology(vs->compiledShader->transformFeedbackTopology);
				}*/
			}
		}
		return programId;
	}
}

ostringstream& Effect::Log()
{
    return m_log;
}

unsigned Effect::CreateSampler(const string& sampler) const
{
    map<string,Sampler*>::const_iterator it=m_samplers.find(sampler);
    if(it==m_samplers.end())
        throw "Sampler not found";
    return it->second->CreateSamplerObject();
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
	map<string, TechniqueGroup*>::const_iterator jt=m_techniqueGroups.find(name);
	TechniqueGroup *group=jt->second;
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

string Effect::GetDeclaredType(std::string name)
{
	if(m_samplerStates.find(name)!=m_samplerStates.end())
		return "SamplerState";
	auto i=m_declaredTextures.find(name);
	if(i!=m_declaredTextures.end())
		return i->second.type;
	return "unknown";
}

void Effect::SetFilenameList(const vector<string> &filenamesUtf8)
{
	m_filenames=filenamesUtf8;
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
		decl << "uniform " << i->second.type << " " << i->first << ";\n";
	}
	m_sharedCode.str(decl.str()+m_sharedCode.str());

	// save shared code?
	string bin_dir=glfxGetBinaryDirectory();
	if(bin_dir.length())
	{
		do_mkdir(bin_dir.c_str());
		string outputFilename=bin_dir+"/";
		outputFilename+=this->Filename()+".glfxo";
		std::ofstream ofstr(outputFilename.c_str());
		const string &str=m_sharedCode.str();
		ofstr.write(str.c_str(),str.length());
		if(errno!=0)
		{
			GLFX_CERR<<"Error: Can't write cached file "<<outputFilename.c_str()<<"; does the directory exist?"<<std::endl;
			DebugBreak();
		}
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
	ApplyPassTextures(pass);
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
					break;
					case LINES:
						glBeginTransformFeedback(GL_LINES);
					break;
					case POINTS:
						glBeginTransformFeedback(GL_POINTS);
					break;
				default:
					break;
				};
			}
		}
	}
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

void Effect::ApplyPassTextures(unsigned pass)
{
	if(!pass)
		return;
	GLFX_ERROR_CHECK
	std::map<unsigned,PassState>::iterator j=passStates.find(pass);
	for(auto i=textureNumberMap.begin();i!=textureNumberMap.end();i++)
	{
	GLFX_ERROR_CHECK
		int main_texture_number		=i->second;
		int texture_number			=main_texture_number;
		const TextureAssignment &ta	=textureAssignmentMap[main_texture_number];
		GLint loc					=glGetUniformLocation(current_pass,i->first.c_str());
	GLFX_ERROR_CHECK
		if(loc>=0)
		{
			SetTex(texture_number,ta,loc);
			if(!ta.write)
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
							SetTex(texture_number, ta, loc2);
						}
						else if (c != glSamplerStates.end())
						{
							GLuint sampler_state =c->second;
							glBindSampler(texture_number, sampler_state);
							SetTex(texture_number, ta, loc2);
						}
						else
						{
							SetTex(main_texture_number, ta, loc2);
						}
					}
					texture_number++;
				}
			}
		}
	}
}

void Effect::ApplyPassState(unsigned pass)
{
	std::map<unsigned,PassState>::iterator i=passStates.find(pass);
	if(i==passStates.end())
		return;
	PassState &passState=i->second;
	if(passState.depthStencilState.length()>0)
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