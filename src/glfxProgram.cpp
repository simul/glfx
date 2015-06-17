#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cassert>

#ifndef _MSC_VER
typedef int errno_t;
#include <errno.h>
#else
#include <Windows.h>
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

Technique::~Technique()
{
	for (auto it = m_passes.begin(); it != m_passes.end(); ++it)
		glDeleteProgram(it->second.programId);
}

TechniqueGroup::~TechniqueGroup()
{
	for (auto it = m_techniques.begin(); it != m_techniques.end(); ++it)
		delete it->second;
}

Program::Program(const map<ShaderType,Shader>& shaders,const PassState &p
	, const map<string, set<TextureSampler*> > &textureSamplersByShader, const string &compute_layout)
	: programId(0), transformFeedback(false), computeLayout(compute_layout),transformFeedbackTopology(POINTS)
{
	passState=p;
    map<ShaderType,Shader>::const_iterator it;
    ShaderType types[NUM_OF_SHADER_TYPES]={VERTEX_SHADER,TESSELATION_CONTROL_SHADER,TESSELATION_EVALUATION_SHADER,GEOMETRY_SHADER,FRAGMENT_SHADER,COMPUTE_SHADER};
    for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
	{
        it=shaders.find(types[i]);
        if(it!=shaders.end())
		{
            m_shaders[i]=it->second;
			string shaderName=it->second.name;
			auto j=textureSamplersByShader.find(shaderName);
			if(j!=textureSamplersByShader.end())
			{
				const set<TextureSampler*> &ts=j->second;
				for(auto k=ts.begin();k!=ts.end();k++)
				{
					passState.textureSamplersByTexture[(*k)->textureName].push_back(*k);
				}
			}
		}
    }

    m_separable=false;
	if (m_shaders[VERTEX_SHADER].name.length() || m_shaders[GEOMETRY_SHADER].name.length())
	{
		if (!m_shaders[FRAGMENT_SHADER].name.length())
			transformFeedback = true;
	}
}

Program::Program()
: programId(0)
{
}

Program::Program(const Program& prog)
{
	operator=(prog);
}

Program::~Program()
{

}

const Program& Program::operator=(const Program& prog)
{
	for (int i = 0; i<NUM_OF_SHADER_TYPES; i++)
	{
		m_shaders[i] = prog.m_shaders[i];
	}
	passState = prog.passState;
	programId = prog.programId;
	m_separable = prog.m_separable;
	transformFeedback = prog.transformFeedback;
	transformFeedbackTopology = prog.transformFeedbackTopology;
	computeLayout = prog.computeLayout;
	return *this;
}

unsigned Program::CompileAndLink(const string &shared_src,string& log) 
{
    vector<GLuint> shaders;
    ostringstream sLog;
	if (programId)
		glDeleteProgram(programId);
    programId=glCreateProgram();

    GLint res=1;
	// This MUST match up with ShaderType enum definition.
    GLenum shaderTypes[NUM_OF_SHADER_TYPES]={GL_VERTEX_SHADER,
                                            GL_TESS_CONTROL_SHADER,
                                            GL_TESS_EVALUATION_SHADER,
                                            GL_GEOMETRY_SHADER,
                                            GL_FRAGMENT_SHADER,
                                            GL_COMPUTE_SHADER};
    for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
	{
        if(m_shaders[i].compiledShader)
		{
            shaders.push_back(glCreateShader(shaderTypes[i]));
			res &= CompileShader(shaders.back(), m_shaders[i].name,shared_src,m_shaders[i].compiledShader->source, (ShaderType)i,  sLog);
            glAttachShader(programId, shaders.back());
        }
    }
   // const GLchar* feedbackVaryings[] = { "outValue" };
//glTransformFeedbackVaryings(programId, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
	if(IsTransformFeedbackShader()&&m_shaders[GEOMETRY_SHADER].compiledShader)
	{
		const vector<string> &feedbackOutput=m_shaders[GEOMETRY_SHADER].compiledShader->feedbackOutput;
		GLchar const **Strings=new GLchar const *[feedbackOutput.size()];
		for(int i=0;i<feedbackOutput.size();i++)
		{
			Strings[i]=feedbackOutput[i].c_str();
			//[] = {"gl_Position", "block.Color"}; 
		}
		glTransformFeedbackVaryings(programId, feedbackOutput.size(), Strings, GL_INTERLEAVED_ATTRIBS);
		delete Strings;
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
			if(!res&&IsDebuggerPresent())
				DebugBreak();
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

int Program::CompileShader(unsigned shader, const string& name,const string &shared,const string &src, ShaderType type, ostringstream& sLog) const
{
	ostringstream s;
	if (type == COMPUTE_SHADER)
	{
		s << "#define IN_COMPUTE_SHADER 1" << endl;
		s << computeLayout << "\n"; 
	}
	string str = s.str();
	string preamble = m_shaders[type].preamble;
	const char* strSrc[] = { preamble.c_str(),str.c_str(),shared.c_str(),src.c_str() };
	glShaderSource(shader, 4, strSrc, NULL);
    glCompileShader(shader);
    
    GLint tmp,res;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &tmp);
    res=tmp;
    //if(!tmp)
	{
		if(!tmp)
			sLog<<"Status: "<<name<<" shader compiled with errors"<<endl;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tmp);

		char* infoLog=new char[tmp];
		glGetShaderInfoLog(shader, tmp, &tmp, infoLog);
		if (strlen(infoLog)>0)
			sLog<<"Compilation details for "<<name<<" shader:"<<endl<<infoLog<<endl;
		//if(!res&&IsDebuggerPresent())
		//	DebugBreak();
		delete[] infoLog;
	}
    return res;
}
