#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <fstream>

#ifndef _MSC_VER
typedef int errno_t;
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#else
#include <Windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <io.h>
#endif
#ifdef GLFX_GLSLANG
#include <ShaderLang.h>
#pragma comment(lib,"glslang.lib")
#pragma comment(lib,"OGLCompiler.lib")
#pragma comment(lib,"OSDependent.lib")
#pragma comment(lib,"SPIRV.lib")
#endif
#include "GL/glew.h"
#include "gl/glfx.h"
#include "glfxClasses.h"
#include "glfxParser.h"
#include "glfxErrorCheck.h"
#include "StringFunctions.h"

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif
#include "generated/glfxScanner.h"
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
}

TechniqueGroup::~TechniqueGroup()
{
	for (auto it = m_techniques.begin(); it != m_techniques.end(); ++it)
		delete it->second;
}

Program::Program(const map<ShaderType,Shader>& shaders,const PassState &p
	,const map<string, set<TextureSampler*> > &textureSamplersByShader,const string &compute_layout)
	:transformFeedback(false)
	,computeLayout(compute_layout)
	,transformFeedbackTopology(POINTS)
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

    m_separable=true;
	if (m_shaders[VERTEX_SHADER].name.length() || m_shaders[GEOMETRY_SHADER].name.length())
	{
		if (!m_shaders[FRAGMENT_SHADER].name.length())
			transformFeedback = true;
	}
	// tf needs only the vertex shader.
	if(transformFeedback)
	{
		m_shaders[GEOMETRY_SHADER].compiledShader=NULL;
	}
}

Program::Program()
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
	variants=prog.variants;
	passState = prog.passState;
	m_separable = prog.m_separable;
	transformFeedback = prog.transformFeedback;
	transformFeedbackTopology = prog.transformFeedbackTopology;
	computeLayout = prog.computeLayout;
	return *this;
}


#ifdef GLFX_GLSLANG
// Convert our shadertype list to Glslang's. Numerically, they are probably the same,
// but we can't rely on that.
EShLanguage ShaderTypeToEshLanguage(ShaderType t)
{
	switch(t)
	{
		case VERTEX_SHADER:
			return EShLangVertex;
		case TESSELATION_CONTROL_SHADER:		//= Hull shader
			return EShLangTessControl;
		case TESSELATION_EVALUATION_SHADER:	//= Domain Shader
			return EShLangTessEvaluation;
		case GEOMETRY_SHADER:
			return EShLangGeometry;
		case FRAGMENT_SHADER:
			return EShLangFragment;
		case COMPUTE_SHADER:
			return EShLangCompute;
		case NUM_OF_SHADER_TYPES:
		default:
			return EShLangCount;
	};
};

const char* DefaultConfig =
    "MaxLights 32\n"
    "MaxClipPlanes 6\n"
    "MaxTextureUnits 32\n"
    "MaxTextureCoords 32\n"
    "MaxVertexAttribs 64\n"
    "MaxVertexUniformComponents 4096\n"
    "MaxVaryingFloats 64\n"
    "MaxVertexTextureImageUnits 32\n"
    "MaxCombinedTextureImageUnits 80\n"
    "MaxTextureImageUnits 32\n"
    "MaxFragmentUniformComponents 4096\n"
    "MaxDrawBuffers 32\n"
    "MaxVertexUniformVectors 128\n"
    "MaxVaryingVectors 8\n"
    "MaxFragmentUniformVectors 16\n"
    "MaxVertexOutputVectors 16\n"
    "MaxFragmentInputVectors 15\n"
    "MinProgramTexelOffset -8\n"
    "MaxProgramTexelOffset 7\n"
    "MaxClipDistances 8\n"
    "MaxComputeWorkGroupCountX 65535\n"
    "MaxComputeWorkGroupCountY 65535\n"
    "MaxComputeWorkGroupCountZ 65535\n"
    "MaxComputeWorkGroupSizeX 1024\n"
    "MaxComputeWorkGroupSizeY 1024\n"
    "MaxComputeWorkGroupSizeZ 64\n"
    "MaxComputeUniformComponents 1024\n"
    "MaxComputeTextureImageUnits 16\n"
    "MaxComputeImageUniforms 8\n"
    "MaxComputeAtomicCounters 8\n"
    "MaxComputeAtomicCounterBuffers 1\n"
    "MaxVaryingComponents 60\n" 
    "MaxVertexOutputComponents 64\n"
    "MaxGeometryInputComponents 64\n"
    "MaxGeometryOutputComponents 128\n"
    "MaxFragmentInputComponents 128\n"
    "MaxImageUnits 8\n"
    "MaxCombinedImageUnitsAndFragmentOutputs 8\n"
    "MaxCombinedShaderOutputResources 8\n"
    "MaxImageSamples 0\n"
    "MaxVertexImageUniforms 0\n"
    "MaxTessControlImageUniforms 0\n"
    "MaxTessEvaluationImageUniforms 0\n"
    "MaxGeometryImageUniforms 0\n"
    "MaxFragmentImageUniforms 8\n"
    "MaxCombinedImageUniforms 8\n"
    "MaxGeometryTextureImageUnits 16\n"
    "MaxGeometryOutputVertices 256\n"
    "MaxGeometryTotalOutputComponents 1024\n"
    "MaxGeometryUniformComponents 1024\n"
    "MaxGeometryVaryingComponents 64\n"
    "MaxTessControlInputComponents 128\n"
    "MaxTessControlOutputComponents 128\n"
    "MaxTessControlTextureImageUnits 16\n"
    "MaxTessControlUniformComponents 1024\n"
    "MaxTessControlTotalOutputComponents 4096\n"
    "MaxTessEvaluationInputComponents 128\n"
    "MaxTessEvaluationOutputComponents 128\n"
    "MaxTessEvaluationTextureImageUnits 16\n"
    "MaxTessEvaluationUniformComponents 1024\n"
    "MaxTessPatchComponents 120\n"
    "MaxPatchVertices 32\n"
    "MaxTessGenLevel 64\n"
    "MaxViewports 16\n"
    "MaxVertexAtomicCounters 0\n"
    "MaxTessControlAtomicCounters 0\n"
    "MaxTessEvaluationAtomicCounters 0\n"
    "MaxGeometryAtomicCounters 0\n"
    "MaxFragmentAtomicCounters 8\n"
    "MaxCombinedAtomicCounters 8\n"
    "MaxAtomicCounterBindings 1\n"
    "MaxVertexAtomicCounterBuffers 0\n"
    "MaxTessControlAtomicCounterBuffers 0\n"
    "MaxTessEvaluationAtomicCounterBuffers 0\n"
    "MaxGeometryAtomicCounterBuffers 0\n"
    "MaxFragmentAtomicCounterBuffers 1\n"
    "MaxCombinedAtomicCounterBuffers 1\n"
    "MaxAtomicCounterBufferSize 16384\n"
    "MaxTransformFeedbackBuffers 4\n"
    "MaxTransformFeedbackInterleavedComponents 64\n"
    "MaxCullDistances 8\n"
    "MaxCombinedClipAndCullDistances 8\n"
    "MaxSamples 4\n"

    "nonInductiveForLoops 1\n"
    "whileLoops 1\n"
    "doWhileLoops 1\n"
    "generalUniformIndexing 1\n"
    "generalAttributeMatrixVectorIndexing 1\n"
    "generalVaryingIndexing 1\n"
    "generalSamplerIndexing 1\n"
    "generalVariableIndexing 1\n"
    "generalConstantMatrixVectorIndexing 1\n"
    ;

void ProcessConfigFile(TBuiltInResource &Resources)
{
    char** configStrings = 0;
    char* config = 0;

    if (config == 0)
	{
        config = new char[strlen(DefaultConfig) + 1];
        strcpy_s(config,strlen(DefaultConfig) + 1,DefaultConfig);
    }

    const char *delims	=" \t\n\r";
	char *context		=NULL;
    const char *token	=strtok_s(config,delims,&context);
    while (token)
	{
        const char* valueStr =strtok_s(0, delims,&context);
        if (valueStr == 0 || ! (valueStr[0] == '-' || (valueStr[0] >= '0' && valueStr[0] <= '9')))
		{
            std::cerr<<"Error: '"<<(valueStr?valueStr:"")<<"' bad .conf file.  Each name must be followed by one number.\n";
            return;
        }
        int value = atoi(valueStr);

        if (strcmp(token, "MaxLights") == 0)
            Resources.maxLights = value;
        else if (strcmp(token, "MaxClipPlanes") == 0)
            Resources.maxClipPlanes = value;
        else if (strcmp(token, "MaxTextureUnits") == 0)
            Resources.maxTextureUnits = value;
        else if (strcmp(token, "MaxTextureCoords") == 0)
            Resources.maxTextureCoords = value;
        else if (strcmp(token, "MaxVertexAttribs") == 0)
            Resources.maxVertexAttribs = value;
        else if (strcmp(token, "MaxVertexUniformComponents") == 0)
            Resources.maxVertexUniformComponents = value;
        else if (strcmp(token, "MaxVaryingFloats") == 0)
            Resources.maxVaryingFloats = value;
        else if (strcmp(token, "MaxVertexTextureImageUnits") == 0)
            Resources.maxVertexTextureImageUnits = value;
        else if (strcmp(token, "MaxCombinedTextureImageUnits") == 0)
            Resources.maxCombinedTextureImageUnits = value;
        else if (strcmp(token, "MaxTextureImageUnits") == 0)
            Resources.maxTextureImageUnits = value;
        else if (strcmp(token, "MaxFragmentUniformComponents") == 0)
            Resources.maxFragmentUniformComponents = value;
        else if (strcmp(token, "MaxDrawBuffers") == 0)
            Resources.maxDrawBuffers = value;
        else if (strcmp(token, "MaxVertexUniformVectors") == 0)
            Resources.maxVertexUniformVectors = value;
        else if (strcmp(token, "MaxVaryingVectors") == 0)
            Resources.maxVaryingVectors = value;
        else if (strcmp(token, "MaxFragmentUniformVectors") == 0)
            Resources.maxFragmentUniformVectors = value;
        else if (strcmp(token, "MaxVertexOutputVectors") == 0)
            Resources.maxVertexOutputVectors = value;
        else if (strcmp(token, "MaxFragmentInputVectors") == 0)
            Resources.maxFragmentInputVectors = value;
        else if (strcmp(token, "MinProgramTexelOffset") == 0)
            Resources.minProgramTexelOffset = value;
        else if (strcmp(token, "MaxProgramTexelOffset") == 0)
            Resources.maxProgramTexelOffset = value;
        else if (strcmp(token, "MaxClipDistances") == 0)
            Resources.maxClipDistances = value;
        else if (strcmp(token, "MaxComputeWorkGroupCountX") == 0)
            Resources.maxComputeWorkGroupCountX = value;
        else if (strcmp(token, "MaxComputeWorkGroupCountY") == 0)
            Resources.maxComputeWorkGroupCountY = value;
        else if (strcmp(token, "MaxComputeWorkGroupCountZ") == 0)
            Resources.maxComputeWorkGroupCountZ = value;
        else if (strcmp(token, "MaxComputeWorkGroupSizeX") == 0)
            Resources.maxComputeWorkGroupSizeX = value;
        else if (strcmp(token, "MaxComputeWorkGroupSizeY") == 0)
            Resources.maxComputeWorkGroupSizeY = value;
        else if (strcmp(token, "MaxComputeWorkGroupSizeZ") == 0)
            Resources.maxComputeWorkGroupSizeZ = value;
        else if (strcmp(token, "MaxComputeUniformComponents") == 0)
            Resources.maxComputeUniformComponents = value;
        else if (strcmp(token, "MaxComputeTextureImageUnits") == 0)
            Resources.maxComputeTextureImageUnits = value;
        else if (strcmp(token, "MaxComputeImageUniforms") == 0)
            Resources.maxComputeImageUniforms = value;
        else if (strcmp(token, "MaxComputeAtomicCounters") == 0)
            Resources.maxComputeAtomicCounters = value;
        else if (strcmp(token, "MaxComputeAtomicCounterBuffers") == 0)
            Resources.maxComputeAtomicCounterBuffers = value;
        else if (strcmp(token, "MaxVaryingComponents") == 0)
            Resources.maxVaryingComponents = value;
        else if (strcmp(token, "MaxVertexOutputComponents") == 0)
            Resources.maxVertexOutputComponents = value;
        else if (strcmp(token, "MaxGeometryInputComponents") == 0)
            Resources.maxGeometryInputComponents = value;
        else if (strcmp(token, "MaxGeometryOutputComponents") == 0)
            Resources.maxGeometryOutputComponents = value;
        else if (strcmp(token, "MaxFragmentInputComponents") == 0)
            Resources.maxFragmentInputComponents = value;
        else if (strcmp(token, "MaxImageUnits") == 0)
            Resources.maxImageUnits = value;
        else if (strcmp(token, "MaxCombinedImageUnitsAndFragmentOutputs") == 0)
            Resources.maxCombinedImageUnitsAndFragmentOutputs = value;
        else if (strcmp(token, "MaxCombinedShaderOutputResources") == 0)
            Resources.maxCombinedShaderOutputResources = value;
        else if (strcmp(token, "MaxImageSamples") == 0)
            Resources.maxImageSamples = value;
        else if (strcmp(token, "MaxVertexImageUniforms") == 0)
            Resources.maxVertexImageUniforms = value;
        else if (strcmp(token, "MaxTessControlImageUniforms") == 0)
            Resources.maxTessControlImageUniforms = value;
        else if (strcmp(token, "MaxTessEvaluationImageUniforms") == 0)
            Resources.maxTessEvaluationImageUniforms = value;
        else if (strcmp(token, "MaxGeometryImageUniforms") == 0)
            Resources.maxGeometryImageUniforms = value;
        else if (strcmp(token, "MaxFragmentImageUniforms") == 0)
            Resources.maxFragmentImageUniforms = value;
        else if (strcmp(token, "MaxCombinedImageUniforms") == 0)
            Resources.maxCombinedImageUniforms = value;
        else if (strcmp(token, "MaxGeometryTextureImageUnits") == 0)
            Resources.maxGeometryTextureImageUnits = value;
        else if (strcmp(token, "MaxGeometryOutputVertices") == 0)
            Resources.maxGeometryOutputVertices = value;
        else if (strcmp(token, "MaxGeometryTotalOutputComponents") == 0)
            Resources.maxGeometryTotalOutputComponents = value;
        else if (strcmp(token, "MaxGeometryUniformComponents") == 0)
            Resources.maxGeometryUniformComponents = value;
        else if (strcmp(token, "MaxGeometryVaryingComponents") == 0)
            Resources.maxGeometryVaryingComponents = value;
        else if (strcmp(token, "MaxTessControlInputComponents") == 0)
            Resources.maxTessControlInputComponents = value;
        else if (strcmp(token, "MaxTessControlOutputComponents") == 0)
            Resources.maxTessControlOutputComponents = value;
        else if (strcmp(token, "MaxTessControlTextureImageUnits") == 0)
            Resources.maxTessControlTextureImageUnits = value;
        else if (strcmp(token, "MaxTessControlUniformComponents") == 0)
            Resources.maxTessControlUniformComponents = value;
        else if (strcmp(token, "MaxTessControlTotalOutputComponents") == 0)
            Resources.maxTessControlTotalOutputComponents = value;
        else if (strcmp(token, "MaxTessEvaluationInputComponents") == 0)
            Resources.maxTessEvaluationInputComponents = value;
        else if (strcmp(token, "MaxTessEvaluationOutputComponents") == 0)
            Resources.maxTessEvaluationOutputComponents = value;
        else if (strcmp(token, "MaxTessEvaluationTextureImageUnits") == 0)
            Resources.maxTessEvaluationTextureImageUnits = value;
        else if (strcmp(token, "MaxTessEvaluationUniformComponents") == 0)
            Resources.maxTessEvaluationUniformComponents = value;
        else if (strcmp(token, "MaxTessPatchComponents") == 0)
            Resources.maxTessPatchComponents = value;
        else if (strcmp(token, "MaxPatchVertices") == 0)
            Resources.maxPatchVertices = value;
        else if (strcmp(token, "MaxTessGenLevel") == 0)
            Resources.maxTessGenLevel = value;
        else if (strcmp(token, "MaxViewports") == 0)
            Resources.maxViewports = value;
        else if (strcmp(token, "MaxVertexAtomicCounters") == 0)
            Resources.maxVertexAtomicCounters = value;
        else if (strcmp(token, "MaxTessControlAtomicCounters") == 0)
            Resources.maxTessControlAtomicCounters = value;
        else if (strcmp(token, "MaxTessEvaluationAtomicCounters") == 0)
            Resources.maxTessEvaluationAtomicCounters = value;
        else if (strcmp(token, "MaxGeometryAtomicCounters") == 0)
            Resources.maxGeometryAtomicCounters = value;
        else if (strcmp(token, "MaxFragmentAtomicCounters") == 0)
            Resources.maxFragmentAtomicCounters = value;
        else if (strcmp(token, "MaxCombinedAtomicCounters") == 0)
            Resources.maxCombinedAtomicCounters = value;
        else if (strcmp(token, "MaxAtomicCounterBindings") == 0)
            Resources.maxAtomicCounterBindings = value;
        else if (strcmp(token, "MaxVertexAtomicCounterBuffers") == 0)
            Resources.maxVertexAtomicCounterBuffers = value;
        else if (strcmp(token, "MaxTessControlAtomicCounterBuffers") == 0)
            Resources.maxTessControlAtomicCounterBuffers = value;
        else if (strcmp(token, "MaxTessEvaluationAtomicCounterBuffers") == 0)
            Resources.maxTessEvaluationAtomicCounterBuffers = value;
        else if (strcmp(token, "MaxGeometryAtomicCounterBuffers") == 0)
            Resources.maxGeometryAtomicCounterBuffers = value;
        else if (strcmp(token, "MaxFragmentAtomicCounterBuffers") == 0)
            Resources.maxFragmentAtomicCounterBuffers = value;
        else if (strcmp(token, "MaxCombinedAtomicCounterBuffers") == 0)
            Resources.maxCombinedAtomicCounterBuffers = value;
        else if (strcmp(token, "MaxAtomicCounterBufferSize") == 0)
            Resources.maxAtomicCounterBufferSize = value;
        else if (strcmp(token, "MaxTransformFeedbackBuffers") == 0)
            Resources.maxTransformFeedbackBuffers = value;
        else if (strcmp(token, "MaxTransformFeedbackInterleavedComponents") == 0)
            Resources.maxTransformFeedbackInterleavedComponents = value;
        else if (strcmp(token, "MaxCullDistances") == 0)
            Resources.maxCullDistances = value;
        else if (strcmp(token, "MaxCombinedClipAndCullDistances") == 0)
            Resources.maxCombinedClipAndCullDistances = value;
        else if (strcmp(token, "MaxSamples") == 0)
            Resources.maxSamples = value;

        else if (strcmp(token, "nonInductiveForLoops") == 0)
            Resources.limits.nonInductiveForLoops = (value != 0);
        else if (strcmp(token, "whileLoops") == 0)
            Resources.limits.whileLoops = (value != 0);
        else if (strcmp(token, "doWhileLoops") == 0)
            Resources.limits.doWhileLoops = (value != 0);
        else if (strcmp(token, "generalUniformIndexing") == 0)
            Resources.limits.generalUniformIndexing = (value != 0);
        else if (strcmp(token, "generalAttributeMatrixVectorIndexing") == 0)
            Resources.limits.generalAttributeMatrixVectorIndexing = (value != 0);
        else if (strcmp(token, "generalVaryingIndexing") == 0)
            Resources.limits.generalVaryingIndexing = (value != 0);
        else if (strcmp(token, "generalSamplerIndexing") == 0)
            Resources.limits.generalSamplerIndexing = (value != 0);
        else if (strcmp(token, "generalVariableIndexing") == 0)
            Resources.limits.generalVariableIndexing = (value != 0);
        else if (strcmp(token, "generalConstantMatrixVectorIndexing") == 0)
            Resources.limits.generalConstantMatrixVectorIndexing = (value != 0);
        else
            std::cerr<<"Warning: unrecognized limit ("<<token<<") in configuration file.\n";

        token = strtok_s(0,delims,&context);
    }
  //  if (configStrings)
   //     FreeFileData(configStrings);
}

void Program::GlslangValidateProgram(const string &shared_src,string variantDefs,ostringstream &sLog)
{
	sLog<<"Glslang validation"<<std::endl;
	bool res=true;
	EShMessages messages = EShMsgDefault;
	int defaultVersion=110;
	std::vector<glslang::TShader*> glslang_shaders;
	glslang::TProgram *glsl_program = new glslang::TProgram;
	for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
	{
		if(res&&m_shaders[i].compiledShader)
		{
			EShLanguage stage = ShaderTypeToEshLanguage((ShaderType)i);
			glslang::TShader* shader = new glslang::TShader(stage);
			glslang_shaders.push_back(shader);
			static int l=0;
			string shr=shared_src;
			if(l)
				shr=shared_src.substr(0,l);
	
			string preamble = m_shaders[i].preamble+variantDefs;
			const char* shaderStrings[]={ preamble.c_str(),shr.c_str(),m_shaders[i].compiledShader->source.c_str()};
			static int s=3;
			shader->setStrings(shaderStrings,s);
			TBuiltInResource Resources;
			ProcessConfigFile(Resources);
			res&=(int)shader->parse(&Resources,defaultVersion,EProfile::ECoreProfile,false,false,messages);
			const char *info=shader->getInfoLog();
			sLog<<info;
			if(res)
				glsl_program->addShader(shader);
		}
	}
	if(res)
	{
		res&=(int)(glsl_program->link(messages));
		sLog<<glsl_program->getInfoLog();
	}
	while(glslang_shaders.size() > 0)
	{
		delete glslang_shaders.back();
		glslang_shaders.pop_back();
	}
}
#endif

void GetVariantFormats(std::vector<VariantFormat> &variantFormats,std::string texelFormat)
{
	if(texelFormat==std::string("vec4"))
	{
		VariantFormat v;
		v.layoutDeclaration="rgba32f";
		v.typeLetter="";
		v.memberType="vec4";
		variantFormats.push_back(v);
		v.layoutDeclaration="rgba16f";
		v.typeLetter="";
		v.memberType="vec4";
		variantFormats.push_back(v);
		v.layoutDeclaration="rgba8ui";
		v.typeLetter="u";
		v.memberType="uvec4";
		variantFormats.push_back(v);
	}
	else if(texelFormat==std::string("float"))
	{
		VariantFormat v;
		v.layoutDeclaration="r32f";
		v.typeLetter="";
		v.memberType="vec4";
		variantFormats.push_back(v);
		v.layoutDeclaration="r16f";
		v.typeLetter="";
		v.memberType="vec4";
		variantFormats.push_back(v);
		v.layoutDeclaration="r8ui";
		v.typeLetter="u";
		v.memberType="uvec4";
		variantFormats.push_back(v);
	}
	else if(texelFormat==string("char4"))
	{
		VariantFormat v;
		v.layoutDeclaration="rgba8_snorm";
		v.typeLetter="";
		v.memberType="vec4";
		variantFormats.push_back(v);
		v.layoutDeclaration="rgba8i";
		v.typeLetter="i";
		v.memberType="ivec4";
		variantFormats.push_back(v);
	}
	else if(texelFormat==string("uchar4"))
	{
		VariantFormat v;
		v.layoutDeclaration="rgba8ui";
		v.typeLetter="u";
		v.memberType="uvec4";
		variantFormats.push_back(v);
	}
	else if(texelFormat==string("uint"))
	{
		VariantFormat v;
		v.layoutDeclaration="r32ui";
		v.typeLetter="u";
		v.memberType="uvec4";
		variantFormats.push_back(v);
	}
	else if(texelFormat==string("int"))
	{
		VariantFormat v;
		v.layoutDeclaration="r32i";
		v.typeLetter="u";
		v.memberType="uvec4";
		variantFormats.push_back(v);
	}
	else
	{
		GLFX_CERR<<"Non known variants for "<<texelFormat.c_str()<<std::endl;
	}
}

int Program::GetVariantNumber(const std::map<std::string,GLenum> variableFormats)
{
	int varnum=0;
	int mul=1;
	for(auto j:variantMap)
	{
		string varName=j.first;
		auto u=variableFormats.find(varName);
		GLenum format=GL_RGBA32F;
		if(u==variableFormats.end())
		{
			format=u->second;
		}
		varnum*=mul;
		int this_format=0;
		if(format==GL_RGBA16F)
			this_format=1;
		varnum+=this_format;
		mul*=(int)j.second.size();
	}
	return varnum;
}

unsigned Program::CompileAndLink(const string &shared_src,const std::map<std::string,DeclaredTexture*> &declaredTextures,string& log)
{
    GLint res=1;
    ostringstream sLog;
#ifdef GLFX_GLSLANG
	if(glfxIsGlslangValidationEnabled())
	{
		glslang::InitializeProcess();
	}
#endif
	variantMap.clear();
	for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
	{
        if(m_shaders[i].compiledShader&&m_shaders[i].compiledShader->variantDeclarations.size())
		{
			for(auto j=m_shaders[i].compiledShader->variantDeclarations.begin();j!=m_shaders[i].compiledShader->variantDeclarations.end();j++)
			{
				const DeclaredTexture *dec=declaredTextures.find(*j)->second;
				std::vector<VariantFormat> variantFormats;
				GetVariantFormats(variantFormats,dec->texel_format);
			
				variantMap[*j]=variantFormats;
			}
		}
	}

	int numVariants=1;
	for(auto v:variantMap)
	{
		numVariants*=(int)v.second.size();
	}
	if(!numVariants)
	{
		GLFX_CERR<<"No variants at all for this program"<<std::endl;
		numVariants=1;
	}
	// Each variant is a specific combination of the variant variables.
	for(int i=0;i<numVariants;i++)
	{
		vector<GLuint> shaders;
		Variant &v=variants[i];
		if(v.programId)
			glDeleteProgram(v.programId);
		v.programId=glCreateProgram();
		ostringstream variantDefs;
		int combination=i;
		// What are the variant choices for this particular variant?
		for(auto j:variantMap)
		{
			string varName=j.first;
			std::vector<VariantFormat> &variantFormats=j.second;
			int remainder=combination%(variantFormats.size());
			combination/=(int)(variantFormats.size());
			VariantFormat &v=variantFormats[remainder];
			variantDefs<<"#define format_for_"<<varName<<" "<<(v.layoutDeclaration.c_str())<<"\n";
			variantDefs<<"#define "<<varName<<"_image2D "<<(v.typeLetter.c_str())<<"image2D\n";
			variantDefs<<"#define "<<varName<<"_image2DArray "<<(v.typeLetter.c_str())<<"image2DArray\n";
			variantDefs<<"#define "<<varName<<"_image3D "<<(v.typeLetter.c_str())<<"image3D\n";
			variantDefs<<"#define convertToImageFormatof_"<<varName<<" "<<(v.memberType.c_str())<<"\n";
		}
		// This MUST match up with ShaderType enum definition.
		GLenum shaderTypes[NUM_OF_SHADER_TYPES]={GL_VERTEX_SHADER,
												GL_TESS_CONTROL_SHADER,
												GL_TESS_EVALUATION_SHADER,
												GL_GEOMETRY_SHADER,
												GL_FRAGMENT_SHADER,
												GL_COMPUTE_SHADER};
		for(int i=0;i<NUM_OF_SHADER_TYPES;i++)
		{
			if(m_shaders[i].compiledShader&&res)
			{
				shaders.push_back(glCreateShader(shaderTypes[i]));
				res &= CompileShader(shaders.back(), m_shaders[i].name,variantDefs.str(),shared_src,m_shaders[i].compiledShader->source, (ShaderType)i,  sLog);
				glAttachShader(v.programId, shaders.back());
			}
		}
	   // Some GL drivers INSIST on having glTransformFeedbackVaryings, even if we're just outputting the default
		// values from the shader.
		if(IsTransformFeedbackShader())
		{
			ShaderType outputShader=m_shaders[GEOMETRY_SHADER].compiledShader?GEOMETRY_SHADER:VERTEX_SHADER;
			const vector<string> &feedbackOutput=m_shaders[outputShader].compiledShader->feedbackOutput;
			if(feedbackOutput.size())
			{
				GLchar const **Strings=new GLchar const *[feedbackOutput.size()];
				for(int i=0;i<feedbackOutput.size();i++)
				{
					Strings[i]=feedbackOutput[i].c_str();
				}
				glTransformFeedbackVaryings(v.programId,(GLsizei)feedbackOutput.size(), Strings, GL_INTERLEAVED_ATTRIBS);
				delete Strings;
			}
		}
		if(m_separable)
			glProgramParameteri(v.programId, GL_PROGRAM_SEPARABLE, GL_TRUE);
		try
		{
			glLinkProgram(v.programId);
		}
		catch(...)
		{
			throw std::runtime_error("Link error");
		}
		if(res)
		{
			GLint lnk;
			glGetProgramiv(v.programId, GL_LINK_STATUS, &lnk);
			res&=lnk;
			if(!lnk)
			{
				sLog<<"Status: Link "<<(res ? "successful" : "failed")<<endl;
				int len=0;
				glGetProgramiv(v.programId, GL_INFO_LOG_LENGTH, &len);
				char infoLog[1024];
				glGetProgramInfoLog(v.programId,1024,&len,infoLog);
				sLog<<"Linkage details:"<<endl<<infoLog<<endl;
			}
		}
		if(!res)
		{
#ifdef GLFX_GLSLANG
			if(glfxIsGlslangValidationEnabled())
				GlslangValidateProgram(shared_src,variantDefs.str(),sLog);
#endif
		}
	
		for(vector<GLuint>::const_iterator it=shaders.begin();it!=shaders.end();++it)
		{
			glDetachShader(v.programId, *it);
			glDeleteShader(*it);
		}
	}
    log=sLog.str();
	
#ifdef GLFX_GLSLANG
	if(glfxIsGlslangValidationEnabled())
		glslang::FinalizeProcess();
#endif
    if(!res)
        return 0;

    return variants[0].programId;
}

static int dirExists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}
typedef struct stat Stat;

static std::wstring Utf8ToWString(const char *src_utf8)
{
	int src_length=(int)strlen(src_utf8);
#ifdef _MSC_VER
	int length = MultiByteToWideChar(CP_UTF8, 0, src_utf8,src_length, 0, 0);
#else
	int length=src_length;
#endif
	wchar_t *output_buffer = new wchar_t [length+1];
#ifdef _MSC_VER
	MultiByteToWideChar(CP_UTF8, 0, src_utf8, src_length, output_buffer, length);
#else
	mbstowcs(output_buffer, src_utf8, (size_t)length );
#endif
	output_buffer[length]=0;
	std::wstring wstr=std::wstring(output_buffer);
	delete [] output_buffer;
	return wstr;
}

int do_mkdir(const char *path_utf8)
{
    int             status = 0;
#ifdef _MSC_VER
    struct _stat64i32            st;
	std::wstring wstr=Utf8ToWString(path_utf8);
    if (_wstat (wstr.c_str(), &st) != 0)
#else
    Stat            st;
    if (stat(path_utf8, &st)!=0)
#endif
    {
        /* Directory does not exist. EEXIST for race condition */
#ifdef _MSC_VER
        if (_wmkdir(wstr.c_str()) != 0 && errno != EEXIST)
#else
        if (mkdir(path_utf8,S_IRWXU) != 0 && errno != EEXIST)
#endif
            status = -1;
    }
    else if (!(st.st_mode & S_IFDIR))
    {
        //errno = ENOTDIR;
        status = -1;
    }
	errno=0;
    return(status);
}

int Program::CompileShader(unsigned shader, const string& name,const string &variantDefs,const string &shared,const string &src, ShaderType type, ostringstream& sLog) const
{
	string preamble = m_shaders[type].preamble+variantDefs;
	const char* strSrc[] = { preamble.c_str(),shared.c_str(),src.c_str() };
	glShaderSource(shader, 3, strSrc, NULL);

	string bin_dir=glfxGetCacheDirectory();
	string binaryFilename;
	if(bin_dir.length())
	{
		do_mkdir(bin_dir.c_str());
		binaryFilename=bin_dir+"/";
		binaryFilename+=name+".glsl";
		std::ofstream ofstr(binaryFilename);
		ofstr.write(preamble.c_str(),strlen(preamble.c_str()));
		ofstr.write(shared.c_str(),strlen(shared.c_str()));
		ofstr.write(src.c_str(),strlen(src.c_str()));
		if(errno!=0)
		{
			GLFX_CERR<<"Error: Can't write cached file "<<binaryFilename.c_str()<<"; does the directory exist?"<<std::endl;
			DebugBreak();
		}
	}
    glCompileShader(shader);
    
    GLint res;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &res);
    //if(!tmp)
	{
		GLint ln;
		if(!res)
			sLog<<"Status: "<<name<<" shader compiled with errors"<<endl;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &ln);
		char* infoLog="";
		if(ln!=0)
		{
			infoLog=new char[ln];
			infoLog[0]=0;
			glGetShaderInfoLog(shader,ln, &ln, infoLog);
			if (strlen(infoLog)>0)
			{
				string fullBinaryPath=binaryFilename;
				char pth[_MAX_PATH];
				_getcwd(pth,_MAX_PATH);
				if(binaryFilename.find(":")>=binaryFilename.size())
					fullBinaryPath=(string(pth)+"/")+binaryFilename;
				sLog<<"Compilation details for "<<name<<" shader:"<<endl<<infoLog<<endl;
				sLog<<fullBinaryPath.c_str()<<": output glsl"<<endl;
			}
			delete[] infoLog;
		}
	}
    return res;
}
