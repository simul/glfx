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

#include <map>
#include <string>
#include <sstream>
#include <vector>

void glfxWrite(const char *);
int glfxparse();
int glfxlex();
typedef unsigned GLenum;
namespace glfxParser
{
	using namespace std;
	struct TextureSampler
	{
		std::string textureName;
		std::string samplerStateName;
		bool global;
		std::string textureSamplerName() const
		{
			return (textureName+"_")+samplerStateName;
		}
	};
	/// Values that represent ShaderType.
	enum ShaderType
	{
		VERTEX_SHADER,
		TESSELATION_CONTROL_SHADER,		//= Hull shader
		TESSELATION_EVALUATION_SHADER,	//= Domain Shader
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		COMPUTE_SHADER,
		NUM_OF_SHADER_TYPES
	};
	enum RenderState
	{
		RASTERIZER_STATE
		,DEPTHSTENCIL_STATE
		,BLEND_STATE
		,SAMPLER_STATE			// One of these things is not like the others...
		,NUMRENDERSTATES
	};
	enum ShaderCommand
	{
		SetVertexShader
		,SetHullShader
		,SetDomainShader
		,SetGeometryShader
		,SetFragmentShader
		,SetComputeShader
		,NumShaderTypes
		,SetRasterizerState
		,SetDepthStencilState
		,SetBlendState
		,NumShaderCommands
	};
	enum Topology
	{
		UNDEFINED_TOPOLOGY=0
		,POINTS
		,LINES
		,TRIANGLES
	};
}
namespace glfxParser
{
	/*
	Blending in OpenGL:
		GL_ZERO;
		GL_ONE;
		GL_SRC_COLOR;
		GL_ONE_MINUS_SRC_COLOR;
		GL_SRC_ALPHA;
		GL_ONE_MINUS_SRC_ALPHA;
		GL_DST_ALPHA;
		GL_ONE_MINUS_DST_ALPHA;
		GL_DST_COLOR;
		GL_ONE_MINUS_DST_COLOR;
		UNIMPLEMENTED_BLEND_SRC_ALPHA_SAT:
		UNIMPLEMENTED_BLEND_BLEND_FACTOR:
		UNIMPLEMENTED_BLEND_INV_BLEND_FACTOR:
		GL_SRC1_COLOR;
		GL_ONE_MINUS_SRC1_COLOR;
		GL_SRC1_ALPHA;
		GL_ONE_MINUS_SRC1_ALPHA;
	*/
	
	struct BlendState
	{
		BlendState();
		GLenum SrcBlend;			
		GLenum DestBlend;			
		GLenum BlendOp;				
		GLenum SrcBlendAlpha;		
		GLenum DestBlendAlpha;		
		GLenum BlendOpAlpha;		
		bool AlphaToCoverageEnable;
		std::map<int,bool> BlendEnable;
		std::map<int,unsigned char> RenderTargetWriteMask;
	};
	struct DepthStencilState
	{
		DepthStencilState();
		bool DepthEnable;
		int DepthWriteMask;
		GLenum DepthFunc;
	};
	struct RasterizerState
	{
		RasterizerState();
		GLenum	FillMode;
		GLenum	CullMode;
		bool	FrontCounterClockwise;
		int		DepthBias;
		float	DepthBiasClamp;
		float	SlopeScaledDepthBias;
		bool	DepthClipEnable;
		bool	ScissorEnable;
		bool	MultisampleEnable;
		bool	AntialiasedLineEnable;
	};
	struct SamplerState
	{
		SamplerState();
		GLenum	MinFilter,MagFilter;
		GLenum	AddressU;
		GLenum	AddressV;
		GLenum	AddressW;
		float MipLODBias;
		float MaxLod;
		float MinLod;
		float MaxAnisotropy;
	};
	struct StructMember
	{
		string type;
		string name;
		string semantic;
	};
	struct Struct
	{
		vector< StructMember>     m_structMembers;
	};
	class Sampler
	{
		map<string, string>     m_stringParams;
		map<string, unsigned>   m_intParams;
		map<string, float>      m_floatParams;

		map<string, unsigned>   m_cmpModes;
		map<string, unsigned>   m_compareFuncs;
		map<string, unsigned>   m_minFilters;
		map<string, unsigned>   m_magFilters;
		map<string, unsigned>   m_wrapModes;

	public:
		Sampler();
		string Descriptor() const;
		void SetParam(const string& param, const string& val);
		void SetParam(const string& param, unsigned val);
		void SetParam(const string& param, float val);
		unsigned CreateSamplerObject() const;
	};
	struct PassState
	{
		PassState() :transformFeedbackTopology(UNDEFINED_TOPOLOGY)
		{
		}
		std::string depthStencilState;
		std::string blendState;
		// When setting a texture, set the appropriate sampler states as well.
		std::map<std::string,std::vector<TextureSampler*> > textureSamplersByTexture;
		Topology transformFeedbackTopology;//POINTS, LINES, TRIANGLES
	};

} // glfxParser
#include "glfxProgram.h"
