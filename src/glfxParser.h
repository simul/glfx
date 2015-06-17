/* Copyright (c) 2011, Max Aizenshtein <max.sniffer@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "glfxClasses.h"

#ifdef _WIN32
#define strerror_r(err_code, sys_msg, sizeofsys_msg) strerror_s(sys_msg, sizeofsys_msg, err_code)
#endif

#ifdef __ORBIS__
#define strerror_r(err_code, sys_msg, sizeofsys_msg) strerror_s(sys_msg, sizeofsys_msg, err_code)
#include <libdbg.h>
#endif


using namespace std;
using namespace glfxParser;
/// Values that represent LayoutType.
enum LayoutType
{
    CS_LAYOUT_TYPE,
	NORMAL_LAYOUT_TYPE
};

/// Values that represent SamplerParam.
enum SamplerParam
{
    SAMPLER_PARAM_STRING,
    SAMPLER_PARAM_INT,
    SAMPLER_PARAM_FLOAT
};

/// Values that represent RegisterParamType.
enum RegisterParamType
{
    REGISTER_NONE,
    REGISTER_INT,
    REGISTER_NAME,
	SEMANTIC
};

struct ShaderParameterType
{
	union
	{
        int num;
        float fnum;
        bool boolean;
	};
	std::string str;
};
//typedef enum yytokentype;
//! This is the struct that the parser uses to store data about document elements.
struct glfxstype
{
    glfxstype() {}
	std::vector<glfxstype> children;
	// A structure for various things we will want to store lists of.
    struct variable
	{
        string	storage;
        string	type;
        string	identifier;
        string	template_;
		int type_enum;		// corresponds to yytokentype enum
    };

	// Render state commands, like "DepthWriteMask = ZERO" and so on.
	struct render_state_command
	{
		string	name;
		string	value;
		int		index;
		union
		{
			int ival;
			float fval;
			bool bval;
		};
	};

    struct samplerVar
	{
        string	binding;
        string	name;
    };
	int								token;
	int								lineno;
    union
	{
        int								num;
        unsigned						unum;
        float							fnum;
        bool							boolean;
		Technique						*tech;
        Program							*prog;
		Sampler							*samp; 
		map<string, Program>			*passes;
        map<ShaderType, Program::Shader>*shaders;
        vector<variable>				*vars;
        vector<samplerVar>				*texNames;
    };
    
    union
	{
        SamplerParam		samplerParamType;
        ShaderType			sType;
		ShaderCommand		sCommand;
        RegisterParamType	rType;
		LayoutType			layoutType;
    };

    // Carrying these around is bad luck, or more like bad performance. But whatever...
    string strs[5];
};

namespace glfxParser
{
	extern RenderState			renderState;
	extern bool gLexPassthrough;
	extern bool read_shader;
	extern bool read_function;
	
	#ifdef LINUX
	int fopen_s(FILE** pFile, const char *filename, const char *mode);
	#endif
	
	extern GLenum toBlendGLEnum(const std::string &str);
	extern GLenum toBlendOpGLEnum(const std::string &str);
	extern GLenum toDepthFuncGLEnum(const std::string &str);
	extern GLenum toFillModeGLenum(const std::string &str);
	extern GLenum toCullModeGLenum(const std::string &str);
	extern GLenum toMinFilterModeGLEnum(const std::string &str);
	extern GLenum toMagFilterModeGLEnum(const std::string &str);
	extern GLenum toAddressModeGLEnum(const std::string &str);
}
														   
#define YYSTYPE glfxstype

#if 1
#define YYDEBUG 1
extern int glfxdebug;
#endif

/// The GLSL texture types. "g" stands for the data type - could be "u" for unsigned int, "i" for int, or nothing - for float.
enum GLTextureType
{
	unknwownTextureType
	, gsampler1D				//	GL_TEXTURE_1D						1D texture
	, gsampler2D				//	GL_TEXTURE_2D						2D texture
	, gsampler3D				//	GL_TEXTURE_3D						3D texture
	, gsamplerCube				//	GL_TEXTURE_CUBE_MAP					Cubemap Texture
	, gsampler2DRect			//	GL_TEXTURE_RECTANGLE				Rectangle Texture
	, gsampler1DArray			//	GL_TEXTURE_1D_ARRAY					1D Array Texture
	, gsampler2DArray			//	GL_TEXTURE_2D_ARRAY					2D Array Texture
	, gsamplerCubeArray			//	GL_TEXTURE_CUBE_MAP_ARRAY			Cubemap Array Texture		(requires GL 4.0 or ARB_texture_cube_map_array)
	, gsamplerBuffer			//	GL_TEXTURE_BUFFER					Buffer Texture
	, gsampler2DMS				//	GL_TEXTURE_2D_MULTISAMPLE			Multisample Texture
	, gsampler2DMSArray			//	GL_TEXTURE_2D_MULTISAMPLE_ARRAY		Multisample Array Texture
	, sampler1DShadow			//	GL_TEXTURE_1D
	, sampler2DShadow			//	GL_TEXTURE_2D
	, samplerCubeShadow			//	GL_TEXTURE_CUBE_MAP
	, sampler2DRectShadow		//	GL_TEXTURE_RECTANGLE
	, sampler1DArrayShadow		//	GL_TEXTURE_1D_ARRAY
	, sampler2DArrayShadow		//	GL_TEXTURE_2D_ARRAY
	, samplerCubeArrayShadow	//	GL_TEXTURE_CUBE_MAP_ARRAY
	// Read-write textures - "images" in GLSL parlance:
	, gimage1D					//	GL_TEXTURE_1D or single layer from GL_TEXTURE_1D_ARRAY
	, gimage2D					//	GL_TEXTURE_2D or single layer from:GL_TEXTURE_2D_ARRAY GL_TEXTURE_CUBE_MAP GL_TEXTURE_CUBE_MAP_ARRAY GL_TEXTURE_3D
	, gimage3D					//	GL_TEXTURE_3D
	, gimageCube				//	GL_TEXTURE_CUBE_MAP
	, gimage2DRect				//	GL_TEXTURE_RECTANGLE
	, gimage1DArray				//	GL_TEXTURE_1D_ARRAY
	, gimage2DArray				//	GL_TEXTURE_2D_ARRAY
	, gimageCubeArray			//	GL_TEXTURE_CUBE_MAP_ARRAY (requires GL 4.0 or ARB_texture_cube_map_array)
	, gimageBuffer				//	GL_TEXTURE_BUFFER
	, gimage2DMS				//	GL_TEXTURE_2D_MULTISAMPLE or single layer from: GL_TEXTURE_2D_MULTISAMPLE_ARRAY
	, gimage2DMSArray			//	GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};
inline int GetTextureDimension(GLTextureType glTextureType,bool array_as_2d=false)
{
	switch(glTextureType)
	{
	case gsampler1D:
	case sampler1DShadow:
	case gsamplerBuffer:
		return 1;
		break;
	case gsampler3D:
	case gimage3D:
		return 3;
		break;
	case gsamplerCubeArray:
	case samplerCubeArrayShadow:
	case gimage2DArray:
	case gimage2DMSArray:
	case gsampler2DArray:
	case gsampler2DMSArray:
	case sampler2DArrayShadow:
		return array_as_2d?2:3;
		break;
	default:
		return 2;
		break;
	}
}
struct DeclaredTexture
{
	std::string type;
	GLTextureType type_enum;
};
/// A struct representing a function that has been parsed from source.
struct Function
{
	void clear()
	{
		for(auto i=textureSamplers.begin();i!=textureSamplers.end();i++)
		{
			delete i->second;
		}
		(*this)=Function();
	}
	void operator=(const Function &f)
	{
		returnType			=f.returnType;
		content				=f.content;
		main_linenumber		=f.main_linenumber;
		content_linenumber	=f.content_linenumber;
		current_filenumber	=f.current_filenumber;
		parameters			=f.parameters;					// the original parameters as defined in the source code.
		expanded_parameters	=f.expanded_parameters;
		textureSamplers.clear();
		textureSamplersByTexture.clear();
		textureSamplersBySampler.clear();
		for(auto i=f.textureSamplers.begin();i!=f.textureSamplers.end();i++)
		{
			TextureSampler *ts=new TextureSampler;
			*ts=*(i->second);
		//	ts->samplerStateName=i->second->samplerStateName;
		//	ts->textureName=i->second->textureName;
		//	ts->global=i->second->global;
			textureSamplers[i->first]=ts;
			textureSamplersBySampler[ts->samplerStateName].insert(ts);
			textureSamplersByTexture[ts->textureName].insert(ts);
		}
	}
	std::string returnType;
	std::string content;
	int main_linenumber;
	int content_linenumber;
	int current_filenumber;
	std::vector<glfxstype::variable> parameters;					// the original parameters as defined in the source code.
	std::vector<glfxstype::variable> expanded_parameters;			// the expanded parameter list including textureSamplers.
	std::map<std::string,TextureSampler*> textureSamplers;			// this owns the TextureSamplers.
	std::map<std::string,std::set<TextureSampler*> > textureSamplersByTexture;
	std::map<std::string,std::set<TextureSampler*> > textureSamplersBySampler;
	void removeTextureSampler(std::string tsname)
	{
		auto i=textureSamplers.find(tsname);
		if(i==textureSamplers.end())
			return;
		TextureSampler *ts=i->second;
		std::set<TextureSampler*> byTex=textureSamplersByTexture[ts->textureName];
		auto j=byTex.find(ts);
		if(j!=byTex.end())
			byTex.erase(j);
		
		std::set<TextureSampler*> bySam=textureSamplersBySampler[ts->samplerStateName];
		j=bySam.find(ts);
		if(j!=bySam.end())
			bySam.erase(j);
		delete ts;
		textureSamplers.erase(i);
	}
};
struct ComputeLayout
{
	int x,y,z;
	std::string text();
};
struct CompilableShader
{
	std::string shaderName;
	Function function;
	ComputeLayout csLayout;
	std::string returnable;
	int main_linenumber;
	int content_linenumber;
	int current_filenumber;
};
//! A shader to be compiled. 
struct CompiledShader
{
	ShaderType shaderType;
	int version;
	Topology transformFeedbackTopology;
	std::vector<std::string> feedbackOutput;
	std::string m_functionName;
	std::string source;
	std::string outputStruct;
	std::string outputStructName;
};
extern void Compile(glfxParser::ShaderType shaderType,const CompilableShader &sh,CompiledShader *com);
extern void stringReplaceAll(std::string& str, const std::string& from, const std::string& to);
extern int glfxprintf ( FILE * , const char * format, ... );
extern string glfxreadblock(unsigned char openChar, unsigned char closeChar);
extern void glfxerror(const char*);
extern int glfxparse();
extern void resetGlfxLex();
extern void resetGlfxParse();
extern void glfxWarning(const char* e);
extern bool is_equal(const string& a, const char * b);

extern void glfxPushState(int s);
extern void glfxPopState();
extern const char *glfxGetStateText();