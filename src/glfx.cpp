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

vector<string> shaderPathsUtf8;
FileLoader fileLoader;

#include "Preprocessor.h"

FILE* OpenFile(const char *filename_utf8,std::string &fullPathNameUtf8)
{
	fullPathNameUtf8	=fileLoader.FindFileInPathStack(filename_utf8,shaderPathsUtf8);
	if(!fullPathNameUtf8.length())
		return NULL;
	wstring filenamew=StringToWString(fullPathNameUtf8);
	FILE *f=_wfopen(filenamew.c_str(),L"r");
	return f;
}

void CloseFile(FILE *f)
{
	fclose(f);
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

Effect *gEffect=NULL;
bool gLexPassthrough=true;


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
		if(numberlen>0&&numberlen<8)
		{
			std::string filenumber_str=line.substr(numberstart,numberlen);
			std::string err_msg=line.substr(numberstart+numberlen,line.length()-numberstart-numberlen);
			if(third_colon>=0)
			{
				third_colon-=numberstart+numberlen;
				err_msg.replace(0,1,"(");
			}
			const char *err_warn	=is_error?"error":"warning";
			if(third_colon>=0)
			{
				std::string rep="): ";
				rep+=err_warn;
				rep+=" C7555: ";
				err_msg.replace(third_colon,1,rep);
			}
			int filenumber=atoi(filenumber_str.c_str());
			string filename=sourceFilesUtf8[filenumber];
			// e.g. already defined at 2(157)
			int already=(int)err_msg.find("already defined at ");
			if(already>=0&&already<err_msg.length())
			{
				int numberpos=already+19;
				int brack_pos=err_msg.find("(",numberpos);
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

bool GLFX_APIENTRY glfxParseEffectFromFile( int effect, const char* file,const char **file_paths_utf8)
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
		defines["GLFX"] = "1";
		preprocess(file,defines);
		src=preproOutput.str();
		gEffects[effect]->SetFilenameList(GetPreprocessorFilenamesUtf8());
	}
	catch(...)
	{
	}
	retVal&=glfxParseEffectFromMemory(effect,src.c_str(),file);
	//gEffects[effect]->SetFilenameList(filenamesUtf8);
/*    fopen_s(&glfxin, file, "r");
    if(glfxin==NULL)
	{
        gEffects[effect]->Log()<<"Cannot open file "<<file<<endl;
        gEffects[effect]->Active()=false;
        return false;
    }
    try {
        glfxdebug=1;
        gEffect=gEffects[effect];
        
        string fname(file);
        size_t lastSlash=fname.find_last_of('/')+1;
        size_t lastBackSlash=fname.find_last_of('\\')+1;
        lastSlash=max(lastSlash, lastBackSlash);
        gEffect->Dir()=fname.substr(0, lastSlash);
        gEffect->Filename()=fname;

        glfxrestart(glfxin);
        glfxset_lineno(1);
        glfxparse();
    }
    catch(const char* err) {
        gEffect->Log()<<err<<endl;
        gEffect->Active()=false;
        retVal=false;
    }
    catch(const string& err) {
        gEffect->Log()<<err<<endl;
        gEffect->Active()=false;
        retVal=false;
    }
    catch(...) {
        gEffect->Log()<<"Unknown error occurred during parsing of "<<file<<endl;
        gEffect->Active()=false;
        retVal=false;
    }

    glfxpop_buffer_state();
    fclose(glfxin);
    gEffect->PopulateProgramList();
	*/
    return retVal;
}

bool GLFX_APIENTRY glfxParseEffectFromMemory( int effect, const char* src,const char *filename)
{
    bool retVal=true;
    try
	{
        gEffect=gEffects[effect];
        gEffect->Dir()="";
		if(filename)
		  gEffect->Filename()=filename;
        glfx_scan_string(src);
        glfxset_lineno(1);
        glfxparse();
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
    catch(...)
	{
        gEffect->Log()<<"Unknown error occurred during parsing of source"<<endl;
        gEffect->Active()=false;
        retVal=false;
    }

    glfxpop_buffer_state();

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

int GLFX_APIENTRY glfxGetProgramCount(int effect)
{
    return (int)gEffects[effect]->GetProgramList().size();
}

void GLFX_APIENTRY glfxGetProgramName(int effect, int program, char* name, int bufSize)
{
    const vector<string>& tmpList = gEffects[effect]->GetProgramList();
    if(program > (int)tmpList.size())
        return;
    strcpy_s(name, bufSize, tmpList[program].c_str());
}

const char* GLFX_APIENTRY glfxGetProgramName(int effect, int program)
{
    const vector<string>& tmpList = gEffects[effect]->GetProgramList();
    if(program > (int)tmpList.size())
        return "";
    return tmpList[program].c_str();
}

size_t GLFX_APIENTRY glfxGetProgramIndex(int effect, const char* name)
{
    const vector<string>& tmpList = gEffects[effect]->GetProgramList();
    for(int i=0;i<(int)tmpList.size();i++)
	{
		if(strcmp(tmpList[i].c_str(),name)==0)
	        return i;
	}
    return tmpList.size();
}

size_t GLFX_APIENTRY glfxGetTechniqueCount(int effect)
{
	return (int)gEffects[effect]->GetTechniqueList().size();
}

const char* GLFX_APIENTRY glfxGetTechniqueName(int effect, int technum)
{
	const vector<string>& tmpList = gEffects[effect]->GetTechniqueList();
	if (technum > (int)tmpList.size())
		return "";
	return tmpList[technum].c_str();
}

size_t GLFX_APIENTRY glfxGetPassCount(int effect, const char* tech_name)
{
	 Technique *tech=gEffects[effect]->GetTechniqueByName(tech_name);
	if (!tech)
		return 0;
	return tech->GetPasses().size();
}

const char* GLFX_APIENTRY glfxGetPassName(int effect, const char *tech_name, int pass_num)
{
	 Technique *tech = gEffects[effect]->GetTechniqueByName(tech_name);
	if (!tech)
		return 0;
	std::map<string, Program>::const_iterator i = tech->GetPasses().begin();
	for (int j = 0; j < pass_num; j++,i++)
	{
	}
	return i->first.c_str();
}

GLuint GLFX_APIENTRY glfxCompilePass(int effect, const char *tech_name, const char *pass_name)
{
	 Technique *tech = gEffects[effect]->GetTechniqueByName(tech_name);
	if (!tech)
		return 0;
	const Program &p = tech->GetPasses()[string(pass_name)];
	return glfxCompileProgram(effect, tech_name, pass_name);
}

GLuint GLFX_APIENTRY glfxCompileProgram(int effect, const char* technique, const char *pass)
{
	if ((size_t)effect >= gEffects.size() || gEffects[effect] == NULL || pass == NULL || !gEffects[effect]->Active())
        return 0;

    string slog;
	string technique_str;
    unsigned progid;
	try
	{
		if (technique)
			technique_str = technique;
		progid = gEffects[effect]->BuildProgram(technique_str, pass, slog);
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
