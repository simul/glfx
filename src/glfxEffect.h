#ifndef GLFXEFFECT_H
#define GLFXEFFECT_H
#include "glfxClasses.h"
#include <map>
#include <string>
#include <set>

namespace glfxParser
{
	typedef std::map<std::string,CompiledShader*> CompiledShaderMap;
	typedef std::map<std::string,std::string> StringMap;
	typedef std::map<std::string,int> ProfileMap;
	struct InterfaceDcl
	{
		string id;
		int atLine;

		InterfaceDcl(string s, int l) : id(s), atLine(l) {}
		InterfaceDcl() {}
	};
	class Effect
	{
	protected:
		std::map<std::string,TechniqueGroup*>		m_techniqueGroups;
		std::vector<std::string>					m_techniqueNames;
		std::vector<std::string>					m_techniqueGroupNames;
		std::map<std::string,Sampler*>				m_samplers;
		std::map<std::string,BlendState*>			m_blendStates;
		std::map<std::string,DepthStencilState*>	m_depthStencilStates;
		std::map<std::string,SamplerState*>			m_samplerStates;
		std::map<std::string,DeclaredTexture>		m_declaredTextures;
		std::map<std::string,RasterizerState*>		m_rasterizerStates;
		std::map<std::string,ComputeLayout>			m_shaderLayouts;
		std::map<unsigned,PassState>				passStates;
		std::map<unsigned,Program*>					passProgramMap;
		std::map<std::string, unsigned>				samplerObjects;
		//! For GLFX we will define a mapping in source between HLSL-style profile id's (e.g. vs_4_0) and the corresponding GLSL version numbers.
		//! We will use the keyword Profile.
		//! e.g.
		//!		Profile vs_4_0(410);
		ProfileMap					m_profileToVersion;
		CompiledShaderMap			m_compiledShaders;
		std::map<std::string,std::vector<Function*> > functions;
		vector<string>				m_filenames;
		string						m_sharedCode;
		ostringstream               m_log;
		int                         m_includes;
		bool                        m_active;
		string                      m_dir;
		string						m_filename;
		std::map<std::string, TextureSampler*> textureSamplers;
		std::map<std::string,std::set<TextureSampler*> > textureSamplersByTexture;
		std::map<std::string,std::set<TextureSampler*> > textureSamplersByShader;
		// But to apply the ts, we must map them by pass.
		std::map<unsigned,std::set<TextureSampler*> > textureSamplersByPass;

		// sampler state objects by name
		//static std::map<std::string,unsigned> glSamplerStates;
		std::map<string, unsigned> Effect::glSamplerStates;

		int current_texture_number;
		int current_image_number;
		struct TextureAssignment
		{
			unsigned tex;		//GLuint
			int depth;
			unsigned format;	//GLenum
			bool write;
			int write_mip;
		};
		std::map<std::string,int> textureNumberMap;
		std::map<int, TextureAssignment> textureAssignmentMap;
		std::map<int, int> textureDimensions;
		std::map<std::string, InterfaceDcl>		m_interfaces;
		std::map<std::string, Struct*>			m_structs;
		std::map<string, DeclaredTexture>		additionalTextureDeclarations;
		/// We keep a map of texture 
		std::map<std::string, unsigned> prepared_sampler_states;
		unsigned current_pass;
		// Create the gl objects for samplers defined in the fx file.
		void CreateDefinedSamplers();
		bool PassHasTransformFeedback(unsigned pass);
	public:
		~Effect();
		Effect();
		// GET INFO
		const CompiledShaderMap &GetCompiledShaders() const
		{
			return m_compiledShaders;
		}
		const ProfileMap &GetProfileToVersion() const
		{
			return m_profileToVersion;
		}
		const std::map<std::string,DeclaredTexture> &GetDeclaredTextures() const
		{
			return m_declaredTextures;
		}
		const std::map<std::string, InterfaceDcl>		&GetInterfaces() const
		{
			return m_interfaces;
		}
		const std::map<std::string, Struct*>		&GetStructs() const
		{
			return m_structs;
		}
		const std::map<std::string, ComputeLayout>		&GetComputeLayouts() const
		{
			return m_shaderLayouts;
		}
		const std::map<std::string,std::set<TextureSampler*> > GetTextureSamplersByShader() const
		{
			return textureSamplersByShader;
		}
		const std::map<std::string,std::vector<Function*> > GetFunctions() const
		{
			return functions;
		}
		string GetDeclaredType(std::string str) const;
		Technique *GetTechniqueByName(const char *name);
		TechniqueGroup *GetTechniqueGroupByName(const char *name);
		TechniqueGroup *GetTechniqueGroupByIndex(int idx);
		string& Dir();
		string& Filename();
		int GetTextureNumber(const char *name);
		int GetImageNumber(const char *name);
		// MODIFY
		void Clear();
		void SetSharedCode(const string &str);
		ostringstream& Log();
		unsigned BuildProgram(const string& tech, const string& pass, string& log);
		unsigned CreateSampler(const string& sampler) const;
		void SetTexture(int texture_number,unsigned tex,int dims,int depth,GLenum format,bool write,int write_mip);
		void SetSamplerState(const char *name, unsigned sam);
		void SetTex(int texture_number,const TextureAssignment &t,int location_in_shader);
		bool SetVersionForProfile(int v,const std::string &prof);
		
		void AddComputeLayout(const std::string &name,const ComputeLayout &tg);
		CompiledShader *AddCompiledShader(const std::string &compiledShaderName,const std::string &fnName,ShaderType sType,int version_num);
		void AddTechnique(const std::string &techname,const std::string &group,Technique *t);
		void AddTechniqueGroup(const std::string &groupName,const TechniqueGroup &tg);
		bool AddCompiledShader(ShaderType sType,const std::string &lvalCompiledShaderName,const std::string &rvalCompiledShaderName);
		void DeclareRasterizerState(const std::string &name,const RasterizerState &buildRasterizerState);
		void DeclareBlendState(const std::string &name,const BlendState &buildBlendState);
		void DeclareDepthStencilState(const std::string &name,const DepthStencilState &buildDepthStencilState);
		void DeclareSamplerState(const std::string &name,const SamplerState &buildSamplerState);
		Function * DeclareFunction(const std::string &functionName,Function &buildFunction);
		void DeclareStruct(const string &name,const Struct &ts);
		bool DeclareTexture(const string &name,const DeclaredTexture &ts);
		bool DeclareTextureSampler(const TextureSampler *ts);
		bool DeclareInterface(const string &name,const InterfaceDcl &ts);
		// merge in the textureSamplers:
		void MergeTextureSamplers(const std::map<std::string,TextureSampler*> &ts,const std::string &shaderName);
		const vector<string>& GetTechniqueGroupList() const;
		const vector<string>& GetTechniqueList() const;
		const vector<string>& GetFilenameList() const;
		bool IsDeclared(std::string str);
		void SetFilenameList(const vector<string> &filenamesUtf8);
		void PopulateProgramList();
		// USAGE
		void Apply(unsigned pass);
		void Reapply(unsigned pass);
		void Unapply();
		void ApplyPassTextures(unsigned pass);
		void ApplyPassState(unsigned pass);
		bool& Active();
		// STATE
		TechniqueGroup *current_group;
	};
	extern Effect *gEffect;
}
#endif