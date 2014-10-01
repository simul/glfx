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

Program::Program(const map<ShaderType,Shader>& shaders)
{
    map<ShaderType,Shader>::const_iterator it;
    
    ShaderType types[NUM_OF_SHADER_TYPES]={VS,TC,TE,GS,FS,CS};
    for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
	{
        it=shaders.find(types[i]);
        if(it!=shaders.end())
            m_shaders[i]=it->second;
    }

    m_separable=false;
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
	
    for(vector<GLuint>::const_iterator it=shaders.begin();it!=shaders.end();++it)
	{
        glDetachShader(programId, *it);
        glDeleteShader(*it);
    }
    
    GLint tmp;
    glGetProgramiv(programId, GL_LINK_STATUS, &tmp);
    res&=tmp;
    
    sLog<<"Status: Link "<<(res ? "successful" : "failed")<<endl;
    
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &tmp);
    char* infoLog = new char[tmp];
    glGetProgramInfoLog(programId, tmp, &tmp, infoLog);
    sLog<<"Linkage details:"<<endl<<infoLog<<endl;
    delete[] infoLog;
    
    log=sLog.str();

    if(!res)
        return 0;

    return programId;
}

int Program::CompileShader( unsigned shader, const Shader& shaderSrc, ostringstream& sLog ) const
{
    const char* strSrc=shaderSrc.src.c_str();
    glShaderSource(shader, 1, &strSrc, NULL);
    glCompileShader(shader);
    
    GLint tmp,res;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &tmp);
    res=tmp;
    
    sLog<<"Status: "<<shaderSrc.name<<" shader compiled with"<<(tmp ? "out" : "")<<" errors"<<endl;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tmp);

    char* infoLog=new char[tmp];
    glGetShaderInfoLog(shader, tmp, &tmp, infoLog);
    sLog<<"Compilation details for "<<shaderSrc.name<<" shader:"<<endl<<infoLog<<endl;
    delete[] infoLog;

    return res;
}
