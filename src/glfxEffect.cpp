#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <iostream>

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
#include <set>

void CheckGLError()
{
	int err=glGetError();
	if(err)
	{
		printf("gl error");
	}
}
#define GL_ERROR_CHECK CheckGLError();

Effect::Effect()
    : m_includes(0)
    , m_active(true)
	,current_group(NULL)
	,current_texture_number(0)
	,current_pass(0)
{
}

Effect::~Effect()
{
    for(map<string,Program*>::iterator it=m_programs.begin(); it!=m_programs.end(); ++it)
        delete it->second;
    for(map<string,Sampler*>::iterator it=m_samplers.begin(); it!=m_samplers.end(); ++it)
        delete it->second;
	std::set<CompiledShader*> comp;
    for(CompiledShaderMap::iterator it=m_compiledShaders.begin(); it!=m_compiledShaders.end(); ++it)
        comp.insert(it->second);
    for(std::set<CompiledShader*>::iterator it=comp.begin(); it!=comp.end(); ++it)
        delete (*it);
	for(auto i=textureSamplers.begin();i!=textureSamplers.end();i++)
		delete i->second;
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
		textureNumberMap[n]=current_texture_number;
		textureNameMap[current_texture_number]=n;
		current_texture_number++;
		// Now we will allocate sequential texture numbers to the sampler states that will be used with this texture...
		auto i=textureSamplersByTexture.find(n);
		if(i!=textureSamplersByTexture.end())
		{
			const vector<TextureSampler*> &ts=i->second;
			for(int j=0;j<ts.size();j++)
			{
				textureNumberMap[ts[j]->textureSamplerName]=current_texture_number;
				textureNameMap[current_texture_number]=ts[j]->textureSamplerName;
				current_texture_number++;
			}
		}
	}
	return texture_number;
}

void Effect::SetTexture(int texture_number,GLuint tex,int dims,int depth,GLenum format,bool write)
{
	// The effect knows the needed info: the format
	GL_ERROR_CHECK
    glActiveTexture(GL_TEXTURE0+texture_number);
	// Fall out silently if this texture is not set.
	GL_ERROR_CHECK
	if(!tex)
		return;
	if(dims==2)
	{
		if(write)
		{
			texture_number=0;
			glBindImageTexture(texture_number,
 				tex,
 				0,
 				GL_FALSE,
 				0,
 				GL_READ_WRITE,
				format);
		}
		//glBindImageTexture(0, volume_tid, 0, /*layered=*/GL_TRUE, 0, GL_READ_WRITE, GL_RGBA32F);
		else
		{
			// 2D but depth>1? That's an ARRAY texture.
			if(depth>1)
				glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
			else
				glBindTexture(GL_TEXTURE_2D,tex);
		}
	}
	else if(dims==3)
	{
		if(write)
		{
			texture_number=0;
			glBindImageTexture(texture_number,
 				tex,
 				0,
 				GL_TRUE,
 				0,
 				GL_READ_WRITE,
				format);
		//GL_RGBA32F);
/*
GL_INVALID_VALUE is generated if unit greater than or equal to the value of GL_MAX_IMAGE_UNITS (0x8F38).
GL_INVALID_VALUE is generated if texture is not the name of an existing texture object.
GL_INVALID_VALUE is generated if level or layer is less than zero.
*/
		}
		else
			glBindTexture(GL_TEXTURE_3D,tex);
	}
	else
	{
		throw std::runtime_error("Unknown texture dimension!");
	}
    glActiveTexture(GL_TEXTURE0+texture_number);
	if(current_pass)
	{
		GLint loc		=glGetUniformLocation(current_pass,textureNameMap[texture_number].c_str());
		if(loc>=0)
			glUniform1i(loc,texture_number);
	}
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
	if (tech.length() == 0)
	{
		std::cerr<<"Must have a technique"<<std::endl;
		assert(tech.length());
	/*	map<string, Program*>::const_iterator it = m_programs.find(pass);
		if (it == m_programs.end())
			return 0;

		unsigned ret = it->second->CompileAndLink(log);*/
		return 0;
	}
	else
	{
		TechniqueGroup *group=current_group;
		map<string, Technique*>::const_iterator it = group->m_techniques.find(tech);
		if (it == group->m_techniques.end())
			return 0;
		Technique *tech = it->second;
		map<string, Program>::const_iterator jt=tech->GetPasses().find(pass);
		unsigned ret = jt->second.CompileAndLink(log);
		passStates[ret]=jt->second.passState;
		return ret;
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
		textureSamplersByTexture[i->second->textureName].push_back(t2);
		*t2=*t;
		textureSamplersByShader[shaderName].insert(t2);
	}
}

const vector<string>& Effect::GetProgramList() const
{
    return m_programNames;
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


void Effect::SetFilenameList(const vector<string> &filenamesUtf8)
{
	m_filenames=filenamesUtf8;
	/*
	m_filenames.clear();
   const char **f=filenamesUtf8;
	while(*f!=NULL)
	{
		m_filenames.push_back(*f);
		f++;
	}*/
}

void Effect::PopulateProgramList()
{
    m_programNames.clear();
    for(map<string,Program*>::const_iterator it=m_programs.begin(); it!=m_programs.end(); ++it)
		m_programNames.push_back(it->first);
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
}

void Effect::Apply(unsigned pass)
{
	GL_ERROR_CHECK
	glUseProgram(pass);
	GL_ERROR_CHECK
	current_pass=pass;
	ApplyPassTextures(pass);

}

void Effect::Reapply(unsigned pass)
{
	Apply(pass);
}

void Effect::Unapply()
{
	glUseProgram(0);
	current_pass=0;
}

void Effect::ApplyPassTextures(unsigned pass)
{
	std::map<unsigned,PassState>::iterator j=passStates.find(pass);
	for(auto i=textureNumberMap.begin();i!=textureNumberMap.end();i++)
	{
	GL_ERROR_CHECK
		int texture_number=i->second;
		GLint loc		=glGetUniformLocation(current_pass,i->first.c_str());
	GL_ERROR_CHECK
		if(loc>=0)
			glUniform1i(loc,texture_number++);
	GL_ERROR_CHECK
		//0x8B4D
		// The texture numbers after this are for sampler states for this texture.
//		std::map<unsigned,PassState>::iterator i=passStates.find(pass);
		if(j!=passStates.end())
		{
			PassState &passState=j->second;
			auto k=passState.textureSamplersByTexture.find(i->first);
			const vector<TextureSampler*> &ts=k->second;
			for(auto l=ts.begin();l!=ts.end();l++)
			{
				GLint loc		=glGetUniformLocation(current_pass,(*l)->textureSamplerName.c_str()	);
				if(loc>=0)
				{
					GLuint sampler_state=m_sam
				glBindSampler(texture_number, sampler_state);
					glUniform1i(loc,texture_number++);
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
			GL_ERROR_CHECK
		for(std::map<int,bool>::iterator i=blendState.BlendEnable.begin();i!=blendState.BlendEnable.end();i++)
		{
			if(i->second)
				num++;
			if(blendState.RenderTargetWriteMask.find(i->first)!=blendState.RenderTargetWriteMask.end())
			{
				unsigned m=blendState.RenderTargetWriteMask[i->first];
				glColorMaski(i->first,(m&0x8)!=0,(m&0x4)!=0,(m&0x2)!=0,(m&0x1)!=0);
				GL_ERROR_CHECK
			}
			else glColorMaski(i->first,true,true,true,true);
		}
		if(!num)
		{
			glDisable(GL_BLEND);
			GL_ERROR_CHECK
		}
		else
		{
			glEnable(GL_BLEND);
			GL_ERROR_CHECK
			for(std::map<int,bool>::iterator i=blendState.BlendEnable.begin();i!=blendState.BlendEnable.end();i++)
			{
				if(i->second)
				{

					glBlendEquationSeparatei((unsigned)i->first, blendState.BlendOp,blendState.BlendOpAlpha);
			GL_ERROR_CHECK

					glBlendFuncSeparatei((unsigned)i->first, blendState.SrcBlend, blendState.DestBlend,
										   blendState.SrcBlendAlpha, blendState.DestBlendAlpha);
			GL_ERROR_CHECK
				}
				else
				{
					glBlendEquationSeparatei((unsigned)i->first, GL_FUNC_ADD,GL_FUNC_ADD);
			GL_ERROR_CHECK



					glBlendFuncSeparatei((unsigned)i->first, GL_ONE, GL_ZERO,
										   GL_ONE, GL_ZERO);
			GL_ERROR_CHECK
				}
			}
			if(blendState.AlphaToCoverageEnable)
				glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			GL_ERROR_CHECK
		}
	}
	// Now we will set the appropriate sampler states.
}