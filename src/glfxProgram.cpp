#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cassert>

#ifndef _MSC_VER
typedef int errno_t;
#include <errno.h>
#endif

#include "GL/glew.h"
#include "gl/glfx.h"
#include "glfxClasses.h"
#include "glfxParser.h"

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif
#include "glfxScanner.h"
#include "glfxProgram.h"
const vector<string> &TechniqueGroup::GetTechniqueList()
{
	m_techniqueNames.clear();
	for (map<string, Technique*>::const_iterator it = m_techniques.begin(); it != m_techniques.end(); ++it)
		m_techniqueNames.push_back(it->first);
	return m_techniqueNames;
}

Technique::Technique(const map<std::string, Program>& passes)
	:m_passes(passes)
{
}

Program::Program(const map<ShaderType,Shader>& shaders)
{
    map<ShaderType,Shader>::const_iterator it;
    
    ShaderType types[NUM_OF_SHADER_TYPES]={VERTEX_SHADER,TESSELATION_CONTROL_SHADER,TESSELATION_EVALUATION_SHADER,GEOMETRY_SHADER,FRAGMENT_SHADER,COMPUTE_SHADER};
    for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
	{
        it=shaders.find(types[i]);
        if(it!=shaders.end())
            m_shaders[i]=it->second;
    }

    m_separable=false;
}

Program::Program()
{
}

Program::Program(const Program& prog)
{
	operator=(prog);
}

const Program& Program::operator=(const Program& prog)
{
	for (int i = 0; i<NUM_OF_SHADER_TYPES; i++)
	{
		m_shaders[i] = prog.m_shaders[i];
	}
	m_separable = prog.m_separable;
	return *this;
}

unsigned Program::CompileAndLink(string& log) const
{
    vector<GLuint> shaders;
    ostringstream sLog;
    
    GLuint programId=glCreateProgram();
    
    GLint res=1;
    GLenum shaderTypes[NUM_OF_SHADER_TYPES]={GL_VERTEX_SHADER,
                                            GL_TESS_CONTROL_SHADER,
                                            GL_TESS_EVALUATION_SHADER,
                                            GL_GEOMETRY_SHADER,
                                            GL_FRAGMENT_SHADER,
                                            GL_COMPUTE_SHADER};
    for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
	{
        if(m_shaders[i].src.size()>0)
		{
            shaders.push_back(glCreateShader(shaderTypes[i]));
            res&=CompileShader(shaders.back(), m_shaders[i], sLog);
            glAttachShader(programId, shaders.back());
        }
    }
    
    if(m_separable)
        glProgramParameteri(programId, GL_PROGRAM_SEPARABLE, GL_TRUE);
	
    glLinkProgram(programId);
    
    if(res)
	{
		GLint lnk;
		glGetProgramiv(programId, GL_LINK_STATUS, &lnk);
		res&=lnk;
		if(!lnk)
		{
			sLog<<"Status: Link "<<(res ? "successful" : "failed")<<endl;
			int len=0;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len);
			char infoLog[1024];
			glGetProgramInfoLog(programId,1024,&len,infoLog);
			sLog<<"Linkage details:"<<endl<<infoLog<<endl;
		}
	}
	
    for(vector<GLuint>::const_iterator it=shaders.begin();it!=shaders.end();++it)
	{
        glDetachShader(programId, *it);
        glDeleteShader(*it);
    }
	
    log=sLog.str();

    if(!res)
        return 0;

    return programId;
}

int Program::CompileShader( unsigned shader, const Shader& shaderSrc, ostringstream& sLog ) const
{
    const char* strSrc=shaderSrc.src.c_str();
    const char* layout=shaderSrc.layout.c_str();
    glShaderSource(shader, 1, &strSrc, NULL);
    glCompileShader(shader);
    
    GLint tmp,res;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &tmp);
    res=tmp;
    //if(!tmp)
	{
		if(!tmp)
			sLog<<"Status: "<<shaderSrc.name<<" shader compiled with"<<(tmp ? "out" : "")<<" errors"<<endl;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tmp);

		char* infoLog=new char[tmp];
		glGetShaderInfoLog(shader, tmp, &tmp, infoLog);
		if (strlen(infoLog)>0)
			sLog<<"Compilation details for "<<shaderSrc.name<<" shader:"<<endl<<infoLog<<endl;
		delete[] infoLog;
	}
    return res;
}
