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

#include "glfxClasses.h"

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
        string	semantic;
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

struct CompilableShader
{
	std::string shaderName;
	std::string returnType;
	std::string shaderContent;
	std::string csLayout;
	std::string returnable;
	int main_linenumber;
	int content_linenumber;
	int current_filenumber;
	vector<glfxstype::variable> vars;
};
extern string Compile(glfxParser::ShaderType shaderType,const CompilableShader &sh);
extern void stringReplaceAll(std::string& str, const std::string& from, const std::string& to);
extern int glfxprintf ( FILE * , const char * format, ... );
extern string glfxreadblock(unsigned char openChar, unsigned char closeChar);
extern void glfxerror(const char*);
extern int glfxparse();
extern void resetGlfxParse();
extern void glfxWarning(const char* e);
extern bool is_equal(const string& a, const char * b);

extern void glfxPushState(int s);
extern void glfxPopState();
extern const char *glfxGetStateText();