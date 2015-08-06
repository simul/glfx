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
#include "StringToWString.h"
#include "StringFunctions.h"
#include "FileLoader.h"
#include "glfxErrorCheck.h"
#include <direct.h>
static std::string binaryDirectory;

#pragma optimize("",off)

vector<string> shaderPathsUtf8;
FileLoader fileLoader;

#include "Preprocessor.h"

FILE* OpenFile(const char *filename_utf8,std::string &fullPathNameUtf8)
{
	GLFX_ERRNO_BREAK
	fullPathNameUtf8	=fileLoader.FindFileInPathStack(filename_utf8,shaderPathsUtf8);
	GLFX_ERRNO_BREAK
	if(!fullPathNameUtf8.length())
		return NULL;
	if(fullPathNameUtf8.find(":")>=fullPathNameUtf8.length())
	{
		char pth[_MAX_PATH];
		_getcwd(pth,_MAX_PATH);
		fullPathNameUtf8=(string(pth)+"/")+fullPathNameUtf8;
	}
	GLFX_ERRNO_BREAK
	wstring filenamew=StringToWString(fullPathNameUtf8);
	FILE *f=NULL;//_wfopen(filenamew.c_str(),L"r");
	_wfopen_s(&f,filenamew.c_str(),L"r");
	GLFX_ERRNO_BREAK
	string path=fullPathNameUtf8;
	int last_slash=(int)path.find_last_of("/");
	int last_bslash=(int)path.find_last_of("\\");
	if(last_bslash>last_slash)
		last_slash=last_bslash;
	if(last_slash>0)
		path=path.substr(0,last_slash);
	shaderPathsUtf8.push_back(path);
	GLFX_ERRNO_BREAK
	return f;
}

void CloseFile(FILE *f)
{
	if(f)
	{
	// Pop the current path of this file.
		shaderPathsUtf8.pop_back();
		fclose(f);
	}
}

using namespace std;

namespace glfxParser
{
#ifndef _MSC_VER

errno_t strcpy_s(char* dst, size_t size, const char* src)
{
    assert(size >= (strlen(src) + 1));
    strncpy(dst, src, size-1);
    dst[size-1]='\0';
    return errno;
}

int fopen_s(FILE** pFile, const char *filename, const char *mode)
{
    *pFile = fopen(filename, mode);
    return errno;
}

int fdopen_s(FILE** pFile, int fildes, const char *mode)
{
    *pFile = fdopen(fildes, mode);
    return errno;
}

#endif

GLenum toBlendGLEnum(const std::string &str)
{
	if(is_equal(str,"SRC_ALPHA"))
		return GL_SRC_ALPHA;
	else if(is_equal(str,"INV_SRC_ALPHA"))
		return GL_ONE_MINUS_SRC_ALPHA;
	else if(is_equal(str,"ZERO"))
		return GL_ZERO;
	else if(is_equal(str,"ONE"))
		return GL_ONE;
	else if(is_equal(str,"SRC_COLOR"))
		return GL_SRC_COLOR;
	else if(is_equal(str,"INV_SRC_COLOR"))
		return GL_ONE_MINUS_SRC_COLOR;
	else if(is_equal(str,"DEST_ALPHA"))
		return GL_DST_ALPHA;
	else if(is_equal(str,"INV_DEST_ALPHA"))
		return GL_ONE_MINUS_DST_ALPHA;
	else if(is_equal(str,"DEST_COLOR"))
		return GL_DST_COLOR;
	else if(is_equal(str,"INV_DEST_COLOR"))
		return GL_ONE_MINUS_DST_COLOR;
	else if(is_equal(str,"SRC_ALPHA_SAT"))
	{
		ostringstream str;
		str<<"unknown blend type: "<<str;
		glfxerror(str.str().c_str());
		return 0;
	}
	else if(is_equal(str,"BLEND_FACTOR"))
	{
		ostringstream str;
		str<<"unknown blend type: "<<str;
		glfxerror(str.str().c_str());
		return 0;
	}
	else if(is_equal(str,"INV_BLEND_FACTOR"))
	{
		ostringstream str;
		str<<"unknown blend type: "<<str;
		glfxerror(str.str().c_str());
		return 0;
	}
	else if(is_equal(str,"SRC1_COLOR"))
		return GL_SRC1_COLOR;
	else if(is_equal(str,"INV_SRC1_COLOR"))
		return GL_ONE_MINUS_SRC1_COLOR;
	else if(is_equal(str,"SRC1_ALPHA"))
		return GL_SRC1_ALPHA;
	else if(is_equal(str,"INV_SRC1_ALPHA"))
		return GL_ONE_MINUS_SRC1_ALPHA;
	else
	{
		ostringstream str;
		str<<"unknown blend type: "<<str;
		glfxerror(str.str().c_str());
	}
	return 0;
}

GLenum toBlendOpGLEnum(const std::string &str)
{
	if(is_equal(str,"ADD"))
		return GL_FUNC_ADD;
	else if(is_equal(str,"SUBTRACT"))
		return GL_FUNC_SUBTRACT;
	else if(is_equal(str,"MAX"))
		return GL_FUNC_ADD;
	else
	{
		ostringstream str;
		str<<"unknown blend operation: "<<str;
		glfxerror(str.str().c_str());
	}
	return 0;
}

GLenum toFillModeGLenum(const std::string &str)
{
	if(is_equal(str,"WIREFRAME"))
		return GL_POLYGON;
	else if(is_equal(str,"SOLID"))
		return GL_LINES;
	else if(is_equal(str,"NONE"))
		return GL_POINTS;
	else
	{
		ostringstream err;
		err<<"unknown fill mode: "<<str;
		glfxerror(err.str().c_str());
	}
	return 0;
}

GLenum toCullModeGLenum(const std::string &str)
{
	if(is_equal(str,"FRONT"))
		return GL_FRONT;
	else if(is_equal(str,"BACK"))
		return GL_BACK;
	else if(is_equal(str,"NONE"))
		return GL_FRONT_AND_BACK;
	else
	{
		ostringstream err;
		err<<"unknown cull mode: "<<str;
		glfxerror(err.str().c_str());
	}
	return 0;
}

GLenum toDepthFuncGLEnum(const std::string &str)
{
	if(is_equal(str,"ALWAYS"))
		return GL_ALWAYS;
	else if(is_equal(str,"NEVER"))
		return GL_NEVER;
	else if(is_equal(str,"LESS"))
		return GL_LESS;
	else if(is_equal(str,"GREATER"))
		return GL_GREATER;
	else if(is_equal(str,"LESS_EQUAL"))
		return GL_LEQUAL;
	else if(is_equal(str,"GREATER_EQUAL"))
		return GL_GEQUAL;
	else
	{
		ostringstream str;
		str<<"unknown depth function: "<<str;
		glfxerror(str.str().c_str());
	}
	return 0;
}

GLenum toMinFilterModeGLEnum(const std::string &str)
{
	/* These are the D3D11 filters we will support GL analogues to. There are also comparison, max and min filters, which we will ignore:
	MIN_MAG_MIP_POINT                        
	MIN_MAG_POINT_MIP_LINEAR                 
	MIN_POINT_MAG_LINEAR_MIP_POINT           
	MIN_POINT_MAG_MIP_LINEAR                 
	MIN_LINEAR_MAG_MIP_POINT                 
	MIN_LINEAR_MAG_POINT_MIP_LINEAR          
	MIN_MAG_LINEAR_MIP_POINT                 
	MIN_MAG_MIP_LINEAR                       
	ANISOTROPIC   */
	if(is_equal(str,"MIN_MAG_MIP_POINT"))
		return GL_NEAREST;
	else if(is_equal(str,"MIN_MAG_POINT_MIP_LINEAR"))
		return GL_NEAREST;		
	else if(is_equal(str,"MIN_POINT_MAG_LINEAR_MIP_POINT"))
		return GL_NEAREST;	
	else if(is_equal(str,"MIN_LINEAR_MAG_POINT_MIP_LINEAR"))
		return GL_LINEAR;//GL_LINEAR_MIPMAP_LINEAR doesn't work properly
	else if(is_equal(str,"MIN_MAG_LINEAR_MIP_POINT"))
		return GL_LINEAR_MIPMAP_NEAREST;	
	else if(is_equal(str,"MIN_MAG_MIP_LINEAR"))
		return GL_LINEAR_MIPMAP_LINEAR;//GL_LINEAR_MIPMAP_LINEAR doesn't work properly	
	else if(is_equal(str,"ANISOTROPIC"))
		return GL_LINEAR_MIPMAP_LINEAR;//GL_LINEAR_MIPMAP_LINEAR doesn't work properly	
	else
	{
		ostringstream str;
		str<<"unknown filter mode: "<<str;
		glfxerror(str.str().c_str());
	}
	return 0;
}

GLenum toMagFilterModeGLEnum(const std::string &str)
{
	if(is_equal(str,"MIN_MAG_MIP_POINT"))
		return GL_NEAREST;
	else if(is_equal(str,"MIN_MAG_POINT_MIP_LINEAR"))
		return GL_NEAREST;		
	else if(is_equal(str,"MIN_POINT_MAG_LINEAR_MIP_POINT"))
		return GL_LINEAR;	
	else if(is_equal(str,"MIN_LINEAR_MAG_POINT_MIP_LINEAR"))
		return GL_NEAREST;
	else if(is_equal(str,"MIN_MAG_LINEAR_MIP_POINT"))
		return GL_LINEAR;	
	else if(is_equal(str,"MIN_MAG_MIP_LINEAR"))
		return GL_LINEAR;	
	else if(is_equal(str,"ANISOTROPIC"))
		return GL_LINEAR;	
	else
	{
		ostringstream str;
		str<<"unknown filter mode: "<<str;
		glfxerror(str.str().c_str());
	}
	return 0;
}

GLenum toAddressModeGLEnum(const std::string &str)
{
	if(is_equal(str,"Wrap"))
		return GL_REPEAT;
	else if(is_equal(str,"Mirror"))
		return GL_MIRRORED_REPEAT;
	else if(is_equal(str,"Clamp"))
		return GL_CLAMP_TO_EDGE;
	else
	{
		ostringstream str;
		str<<"unknown addressing mode: "<<str;
		glfxerror(str.str().c_str());
	}
	return 0;
}


BlendState::BlendState():SrcBlend(GL_SRC_ALPHA)	
					,DestBlend(GL_ONE_MINUS_SRC_ALPHA)
					,BlendOp(GL_FUNC_ADD)		
					,SrcBlendAlpha(GL_SRC_ALPHA)
					,DestBlendAlpha(GL_ONE_MINUS_SRC_ALPHA)
					,BlendOpAlpha(GL_FUNC_ADD)	
					,AlphaToCoverageEnable(false)
{
}

DepthStencilState::DepthStencilState()
	:DepthEnable(true)
	,DepthWriteMask(GL_ONE)
	,DepthFunc(GL_LEQUAL)
{}

RasterizerState::RasterizerState()
	:FillMode(GL_POLYGON)
		,CullMode(GL_CULL_FACE)
		,FrontCounterClockwise(true)
		,DepthBias(0)
		,DepthBiasClamp(0.0f)
		,SlopeScaledDepthBias(0.0f)
		,DepthClipEnable(false)
		,ScissorEnable(false)
		,MultisampleEnable(false)
		,AntialiasedLineEnable(false)
{
}
SamplerState::SamplerState()
	:MinFilter(GL_LINEAR_MIPMAP_LINEAR)
	,MagFilter(GL_LINEAR)
	,AddressU(GL_CLAMP_TO_EDGE)
	,AddressV(GL_CLAMP_TO_EDGE)
	,AddressW(GL_CLAMP_TO_EDGE)
{
}

Effect *gEffect=NULL;
bool gLexPassthrough=true;

RenderState	 renderState;
bool read_shader=false;
bool read_function=false;
#pragma optimize("",off)
static std::string RewriteErrorLine(std::string line,const vector<string> &sourceFilesUtf8)
{
	bool is_error=true;
	int errpos=(int)line.find("ERROR");
	if(errpos<0)
		errpos=(int)line.find("error");
	if(errpos<0)
	{
		errpos=(int)line.find("WARNING");
		is_error=false;
	}
	if(errpos<0)
	{
		errpos=(int)line.find("warning");
		is_error=false;
	}
	if(errpos>=0)
	{
		int first_colon		=(int)line.find(":");
		int second_colon	=(int)line.find(":",first_colon+1);
		int third_colon		=(int)line.find(":",second_colon+1);
		int fourth_colon	=(int)line.find(":",third_colon+1);
		int first_bracket	=(int)line.find("(");
		int second_bracket	=(int)line.find(")",first_bracket+1);
		int numberstart,numberlen=0;
	//somefile.glsl(263): error C2065: 'space_' : undeclared identifier
		if(third_colon>=0&&second_colon>=0&&(second_colon-first_colon)<5)
		{
			numberstart	=first_colon+1;
			numberlen	=second_colon-first_colon-1;
		}
	//	ERROR: 0:11: 'assign' :  cannot convert from '2-component vector of float' to 'float'
		else if((third_colon<0||numberlen>6)&&second_bracket>=0)
		{
			if(first_colon<first_bracket)
			{
				numberstart	=first_colon+1;
				numberlen	=first_bracket-first_colon-1;
			}
			else
			{
				numberstart=0;
				numberlen=first_bracket;
			}
		}
		else
		{
			numberstart=0;
			numberlen=first_bracket;
		}
		if(numberlen>=0&&numberlen<8)
		{
			std::string filenumber_str=line.substr(numberstart,numberlen);
			std::string err_msg=line.substr(numberstart+numberlen,line.length()-numberstart-numberlen);
			if(third_colon>=0&&fourth_colon!=third_colon+1)
			{
				third_colon-=numberstart+numberlen;
				err_msg.replace(0,1,"(");
			}
			const char *err_warn	=is_error?"error":"warning";
			if(third_colon>=0&&fourth_colon!=third_colon+1)
			{
				std::string rep="): ";
				rep+=err_warn;
				rep+=" C7555: ";
				err_msg.replace(third_colon,1,rep);
			}
			int filenumber = 0;
			if (filenumber_str.length())
				filenumber=atoi(filenumber_str.c_str());
			string filename=sourceFilesUtf8[filenumber];
			// e.g. already defined at 2(157)
			int already=(int)err_msg.find("already defined at ");
			if(already>=0&&already<err_msg.length())
			{
				int numberpos=already+19;
				int brack_pos=(int)err_msg.find("(",numberpos);
				string first_def_file_no=err_msg.substr(numberpos,brack_pos-numberpos);
				int already_filenumber=atoi(first_def_file_no.c_str());
				string already_filename=sourceFilesUtf8[filenumber];
				err_msg.replace(numberpos,brack_pos-numberpos,(string("\n\tsee first definition at "+already_filename).c_str()));
			}
			std::string err_line	=filename+err_msg;
			return err_line;
		}
	}
	return line;
}
void PutFilenamesInLog(string &slog,vector<string> filenames)
{
	// now rewrite log to use filenames.
	string newlog;
	if(slog.find("No errors")>=slog.length())
	{
		int pos=0;
		int next=(int)slog.find('\n',pos+1);
		while(next>=0)
		{
			std::string line		=slog.substr(pos,next-pos);
			std::string error_line	=RewriteErrorLine(line,filenames);
			if(error_line.length())
			{
				newlog+=error_line+"\n";
			}
			pos=next+1;
			next=(int)slog.find('\n',pos);
		}
		slog=newlog;
	}
}

Sampler::Sampler()
{
    m_stringParams["WrapS"]="repeat";
    m_stringParams["WrapT"]="repeat";
    m_stringParams["WrapR"]="repeat";
    m_stringParams["MinFilter"]="trilinear";
    m_stringParams["MagFilter"]="linear";
    m_stringParams["Format"]="float";
    m_stringParams["Type"]="sampler";
    m_floatParams["MinLod"]=-1000;
    m_floatParams["MaxLod"]=1000;
    m_floatParams["LodBias"]=0;
    m_stringParams["CmpMode"]="none";
    m_stringParams["CmpFunc"]="lequal";
    m_intParams["Dim"]=2;
    m_intParams["Array"]=0;
    m_intParams["MS"]=0;
    m_intParams["Rect"]=0;
    m_intParams["Aniso"]=1;

    m_compareFuncs["lequal"]=GL_LEQUAL;
    m_compareFuncs["gequal"]=GL_GEQUAL;
    m_compareFuncs["less"]=GL_LESS;
    m_compareFuncs["greater"]=GL_GREATER;
    m_compareFuncs["equal"]=GL_EQUAL;
    m_compareFuncs["notequal"]=GL_NOTEQUAL;
    m_compareFuncs["always"]=GL_ALWAYS;
    m_compareFuncs["never"]=GL_NEVER;

    m_cmpModes["none"]=GL_NONE;
    m_cmpModes["ref"]=GL_COMPARE_REF_TO_TEXTURE;
    
    m_minFilters["point"]=GL_NEAREST;
    m_minFilters["linear"]=GL_LINEAR;
    m_minFilters["nearest"]=GL_NEAREST_MIPMAP_NEAREST;
    m_minFilters["bilinear"]=GL_NEAREST_MIPMAP_LINEAR;
    m_minFilters["trilinear"]=GL_LINEAR_MIPMAP_LINEAR;

    m_magFilters["nearest"]=GL_NEAREST;
    m_magFilters["point"]=GL_NEAREST;
    m_magFilters["linear"]=GL_LINEAR;
    m_magFilters["bilinear"]=GL_LINEAR;

    m_wrapModes["repeat"]=GL_REPEAT;
    m_wrapModes["mirroredRepeat"]=GL_MIRRORED_REPEAT;
    m_wrapModes["clampToEdge"]=GL_CLAMP_TO_EDGE;
    m_wrapModes["clampToBorder"]=GL_CLAMP_TO_BORDER;
}

void Sampler::SetParam(const string& param, float val)
{
    m_floatParams[param]=val;
}

void Sampler::SetParam(const string& param, unsigned val)
{
    if(param=="Rect" && val) {
        m_stringParams["MinFilter"]="linear";
        m_stringParams["WrapS"]="clampToEdge";
        m_stringParams["WrapT"]="clampToEdge";
        m_stringParams["WrapR"]="clampToEdge";
    }
    m_intParams[param]=val;
}

void Sampler::SetParam(const string& param, const string& val)
{
    if(param=="Dim")
        m_intParams["Dim"]=0;
    m_stringParams[param]=val;
}

string Sampler::Descriptor() const
{
    ostringstream dcl;
    bool isBuffer=false;

    const string& format = m_stringParams.find("Format")->second;

    if(format=="int")
        dcl<<'i';
    else if(format=="uint")
        dcl<<'u';
    else if(format!="float")
        throw "Unknown format type\n";

    dcl<<m_stringParams.find("Type")->second;

    if(m_intParams.find("Dim")->second)
        dcl<<m_intParams.find("Dim")->second<<'D';
    else {
        string dim(m_stringParams.find("Dim")->second);
        dcl<<dim;
        if(dim=="Buffer")
            isBuffer=true;
        else if(dim!="Cube")
            throw "Unknown type of sampler dimension\n";
    }

    if(m_intParams.find("Rect")->second) {
        if(m_intParams.find("Dim")->second!=2 || !m_intParams.find("Array")->second || !m_intParams.find("MS")->second)
            throw "Can't use Rect with current parameters\n";
        dcl<<"Rect";
    }

    if(m_intParams.find("MS")->second) {
        if(m_intParams.find("Dim")->second!=2)
            throw "Can't use MS with dimension other than 2\n";
        dcl<<"MS";
    }

    if(m_intParams.find("Array")->second) {
        if(m_intParams.find("Dim")->second==3 || isBuffer)
            throw "Can't use Array with dimension 3 or buffer\n";
        dcl<<"Array";
    }

    if(m_stringParams.find("CmpMode")->second=="ref") {
        if(isBuffer)
            throw "Can't use comparison with buffer\n";
        dcl<<"Shadow";
    }
    else if(m_stringParams.find("CmpMode")->second!="none")
        throw "Unknown compare mode\n";

    return dcl.str();
}

unsigned Sampler::CreateSamplerObject() const
{
    GLuint samplerObj;
    glGenSamplers(1, &samplerObj);
    glSamplerParameteri(samplerObj, GL_TEXTURE_MIN_FILTER, m_minFilters.find(m_stringParams.find("MinFilter")->second)->second);
    glSamplerParameteri(samplerObj, GL_TEXTURE_MAG_FILTER, m_magFilters.find(m_stringParams.find("MagFilter")->second)->second);
    glSamplerParameteri(samplerObj, GL_TEXTURE_WRAP_S, m_wrapModes.find(m_stringParams.find("WrapS")->second)->second);
    glSamplerParameteri(samplerObj, GL_TEXTURE_WRAP_T, m_wrapModes.find(m_stringParams.find("WrapT")->second)->second);
    glSamplerParameteri(samplerObj, GL_TEXTURE_WRAP_R, m_wrapModes.find(m_stringParams.find("WrapR")->second)->second);
    glSamplerParameterf(samplerObj, GL_TEXTURE_MIN_LOD, m_floatParams.find("MinLod")->second);
    glSamplerParameterf(samplerObj, GL_TEXTURE_MAX_LOD, m_floatParams.find("MaxLod")->second);
    glSamplerParameterf(samplerObj, GL_TEXTURE_LOD_BIAS, m_floatParams.find("LodBias")->second);
    glSamplerParameteri(samplerObj, GL_TEXTURE_COMPARE_MODE, m_cmpModes.find(m_stringParams.find("CmpMode")->second)->second);
    glSamplerParameteri(samplerObj, GL_TEXTURE_COMPARE_FUNC, m_compareFuncs.find(m_stringParams.find("CmpFunc")->second)->second);
    glSamplerParameteri(samplerObj, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_intParams.find("Aniso")->second);

    return samplerObj;
}

vector<Effect*> gEffects;

} // glfxParser

using namespace glfxParser;

int GLFX_APIENTRY glfxGenEffect()
{
    gEffects.push_back(new Effect);
    return (int)gEffects.size()-1;
}

bool GLFX_APIENTRY glfxParseEffectFromFile(int effect, const char* file, const char **file_paths_utf8, const char **macros, const char **defs) 
{
    bool retVal=true;
    shaderPathsUtf8.clear();
	const char **path=file_paths_utf8;
	while(*path)
	{
		shaderPathsUtf8.push_back(*path);
		path++;
	}
	shaderPathsUtf8.push_back(GetDirectoryFromFilename(string(file)));
	string src;
	try
	{
		prepro_open=&OpenFile;
		prepro_close=&CloseFile;
		std::map<std::string, std::string> defines;
		const char **m = macros,**d=defs;
		while(*m&&*d)
		{
			defines[*m] = *d;
			m++;
			d++;
		}
		defines["GLFX"] = "1";
		retVal&=preprocess(file, defines);
	GLFX_ERRNO_CHECK
		src=preproOutput.str();
		gEffects[effect]->SetFilenameList(GetPreprocessorFilenamesUtf8());
		if(!retVal)
			return false;
	}
	catch(...)
	{
	}
	retVal&=glfxParseEffectFromMemory(effect,src.c_str(),file);
	GLFX_ERRNO_CHECK
    return retVal;
}

bool GLFX_APIENTRY glfxParseEffectFromMemory(int effect, const char* src,const char *filename)
{
    bool retVal=true;
    try
	{
        gEffect=gEffects[effect];
        gEffect->Dir()="";
		if(filename)
			gEffect->Filename()=filename;
		gEffect->Log().clear();
        glfx_scan_string(src);
        glfxset_lineno(1);
		resetGlfxLex();
		resetGlfxParse();
	GLFX_ERRNO_CHECK
        glfxparse();
	// Flex/Bison sets errno, even when it doesn't report an error. So we reset it:
		errno=0;
    }
    catch(const char* err)
	{
        gEffect->Log()<<err<<endl;
        gEffect->Active()=false;
        retVal=false;
    }
    catch(const string& err)
	{
        gEffect->Log()<<err<<endl;
        gEffect->Active()=false;
        retVal=false;
    }
    catch(const std::exception& exc)
	{
        gEffect->Log()<<exc.what()<<endl;
        gEffect->Active()=false;
        retVal=false;
    }
    catch(...)
	{
        gEffect->Log()<<"Unknown error occurred during parsing of source"<<endl;
        gEffect->Active()=false;
        retVal=false;
    }
    glfxpop_buffer_state();
	if(retVal)
	    gEffect->PopulateProgramList();
	string log=gEffect->Log().str();
	PutFilenamesInLog(log,gEffects[effect]->GetFilenameList());
	gEffect->Log().str(log);
    return retVal;
}

void GLFX_APIENTRY glfxDeleteEffect(int effect)
{
    if((size_t)effect<gEffects.size() && gEffects[effect]!=NULL) {
        if(gEffect==gEffects[effect])
            gEffect=NULL;
        delete gEffects[effect];
        gEffects[effect]=NULL;
    }
}

void GLFX_APIENTRY glfxGetEffectLog(int effect, char* log, int bufSize)
{
    if((size_t)effect>=gEffects.size() || gEffects[effect]==NULL)
        return;

    if(!strcpy_s(log, bufSize, gEffects[effect]->Log().str().c_str()))
        gEffects[effect]->Log().str("");
}

static string gLog;
const char* GLFX_APIENTRY glfxGetEffectLog(int effect)
{
    if((size_t)effect>=gEffects.size() || gEffects[effect]==NULL)
        return "";

    gLog=gEffects[effect]->Log().str();
    gEffects[effect]->Log().str("");
    return gLog.c_str();
}


int GLFX_APIENTRY glfxGetEffectTextureNumber(int e,const char *name)
{
	if(e<0||e>=gEffects.size())
		return -1;
    return gEffects[e]->GetTextureNumber(name);
}

int GLFX_APIENTRY glfxGetEffectImageNumber(int e,const char *name)
{
	if(e<0||e>=gEffects.size())
		return -1;
    return gEffects[e]->GetImageNumber(name);
}

void GLFX_APIENTRY glfxSetEffectTexture(int e,int texture_number,GLuint tex,int dims,int depth,GLenum format,bool write,int write_mip)
{
	if(e<0||e>=gEffects.size())
		return ;
	gEffects[e]->SetTexture( texture_number, tex, dims, depth,format, write,write_mip);
}

void GLFX_APIENTRY glfxSetEffectSamplerState(int e, const char *name, GLuint sampler)
{
	if(e<0||e>=gEffects.size())
		return ;
	gEffects[e]->SetSamplerState( name, sampler);
}

size_t GLFX_APIENTRY glfxGetTechniqueCount(int e)
{
	if(e<0||e>=gEffects.size())
		return 0;
	GLFX_ERROR_CHECK
	if(gEffects[e]->current_group==NULL)
		gEffects[e]->current_group=gEffects[e]->GetTechniqueGroupByName("");
	GLFX_ERROR_CHECK
	return (int)gEffects[e]->current_group->GetTechniqueList().size();
}

size_t GLFX_APIENTRY glfxGetTechniqueIndex(int e, const char* name)
{
	if(e<0||e>=gEffects.size())
		return 0;
	if (gEffects[e]->current_group == NULL)
		gEffects[e]->current_group = gEffects[e]->GetTechniqueGroupByName("");
	const vector<string>& tmpList = gEffects[e]->current_group->GetTechniqueList();
	for (int i = 0; i<(int)tmpList.size(); i++)
	{
		if (strcmp(tmpList[i].c_str(), name) == 0)
			return i;
	}
	return tmpList.size();
}

GLFXAPI void GLFX_APIENTRY glfxSetCacheDirectory(const char *dir)
{
	binaryDirectory=dir;
}
static bool glslang_validation=true;
GLFXAPI bool GLFX_APIENTRY glfxIsGlslangValidationEnabled()
{
	return glslang_validation;
}

GLFXAPI void GLFX_APIENTRY glfxSetGlslangValidationEnabled(bool v)
{
	glslang_validation=v;
}

GLFXAPI const char * GLFX_APIENTRY glfxGetCacheDirectory()
{
	return binaryDirectory.c_str();
}

size_t GLFX_APIENTRY glfxGetTechniqueGroupCount(int effect)
{
	return (int)gEffects[effect]->GetTechniqueGroupList().size();
}

GLFXAPI void GLFX_APIENTRY glfxApply(int effect,GLuint pass)
{
	gEffects[effect]->Apply(pass);
}

GLFXAPI void GLFX_APIENTRY glfxReapply(int e,GLuint pass)
{
	if(e<0||e>=gEffects.size())
		return ;
	gEffects[e]->Reapply(pass);
}

GLFXAPI void GLFX_APIENTRY glfxUnapply(int e)
{
	if(e<0||e>=gEffects.size())
		return ;
	gEffects[e]->Unapply();
}

GLFXAPI void GLFX_APIENTRY glfxUseTechniqueGroup(int e,int g)
{
	if(e<0||e>=gEffects.size())
		return ;
	gEffects[e]->current_group=gEffects[e]->GetTechniqueGroupByIndex(g);
}

const char* GLFX_APIENTRY glfxGetTechniqueGroupName(int e, int g)
{
	if(e<0||e>=gEffects.size())
		return "";
	const vector<string>& tmpList = gEffects[e]->GetTechniqueGroupList();
	if (g > (int)tmpList.size())
		return "";
	return tmpList[g].c_str();
}

const char* GLFX_APIENTRY glfxGetTechniqueName(int e, int technum)
{
	if(e<0||e>=gEffects.size())
		return "";
	TechniqueGroup *g = gEffects[e]->current_group;
	GLFX_ERROR_CHECK
	const vector<string>& tmpList = g->GetTechniqueList();
	GLFX_ERROR_CHECK
	if (technum > (int)tmpList.size())
		return "";
	GLFX_ERROR_CHECK
	return tmpList[technum].c_str();
}

size_t GLFX_APIENTRY glfxGetPassCount(int e, const char* tech_name)
{
	if(e<0||e>=gEffects.size())
		return 0;
	GLFX_ERROR_CHECK
	TechniqueGroup *g = gEffects[e]->current_group;
	GLFX_ERROR_CHECK
	 Technique *tech=g->m_techniques[tech_name];
	GLFX_ERROR_CHECK
	if (!tech)
		return 0;
	GLFX_ERROR_CHECK
	return tech->GetPasses().size();
}

const char* GLFX_APIENTRY glfxGetPassName(int e, const char *tech_name, int pass_num)
{
	if(e<0||e>=gEffects.size())
		return "";
	GLFX_ERROR_CHECK
	TechniqueGroup *g = gEffects[e]->current_group;
	GLFX_ERROR_CHECK
	 Technique *tech=g->m_techniques[tech_name];
	GLFX_ERROR_CHECK
	if (!tech)
		return 0;
	GLFX_ERROR_CHECK
	std::map<string, Program>::const_iterator i = tech->GetPasses().begin();
	for(int j=0;j<pass_num&&i!=tech->GetPasses().end();j++,i++);
	GLFX_ERROR_CHECK
	return i->first.c_str();
}

GLuint GLFX_APIENTRY glfxCompilePass(int e, const char *tech_name, const char *pass_name)
{
	if(e<0||e>=gEffects.size())
		return 0;
	TechniqueGroup *g=gEffects[e]->current_group;
	Technique *tech=g->m_techniques[tech_name];
	if (!tech)
		return 0;
	GLFX_ERROR_CHECK
	const Program &p=tech->GetPasses()[string(pass_name)];
	GLuint pr=glfxCompileProgram(e, tech_name, pass_name);
	return pr;
}
GLFXAPI void GLFX_APIENTRY glfxApplyPassState(int e,GLuint pass)
{
	if(e<0||e>=gEffects.size())
		return ;
	if(e>=0&&e<gEffects.size())
		gEffects[e]->ApplyPassState(pass);
}

GLuint GLFX_APIENTRY glfxCompileProgram(int effect, const char* technique, const char *pass)
{
	if ((size_t)effect >= gEffects.size() || gEffects[effect] == NULL || pass == NULL || !gEffects[effect]->Active())
        return 0;
	GLFX_ERROR_CHECK

    string slog;
	string technique_str;
    unsigned progid;
	try
	{
		if (technique)
			technique_str = technique;
		progid = gEffects[effect]->BuildProgram(technique_str, pass?pass:"", slog);
	}
	catch(const char* err)
	{
		slog+=err;
		progid=0;
	}
	catch(const string& err)
	{
		slog+=err;
		progid=0;
	}
	catch(...)
	{
		slog+="Error during compilation";
		progid=0;
	}
	if(!progid)
	{
		slog+="Program not built.";
	}
	PutFilenamesInLog(slog,gEffects[effect]->GetFilenameList());

    gEffects[effect]->Log()<<slog;

    return progid;
}

int GLFX_APIENTRY glfxGenerateSampler(int effect, const char* sampler)
{
    if((size_t)effect>=gEffects.size() || gEffects[effect]==NULL || sampler==NULL || !gEffects[effect]->Active())
        return -1;
    string slog;
    unsigned sampId;
    try
	{
        sampId=gEffects[effect]->CreateSampler(sampler);
    }
    catch(const char* err)
	{
        slog+=err;
        sampId=-1;
    }
    gEffects[effect]->Log()<<slog;
    return sampId;
}
