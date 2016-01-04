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
	struct TextureAssignment
	{
		unsigned tex;		//GLuint
		int depth;
		unsigned format;	//GLenum
		int write_mip;
		bool layered;		///< Whether it is layered.
		bool cubemap;		///< Whether it's a cubemap.
		int layer;			///< Which layer of a texture array.
	};
	//! For GLFX we will define a mapping in source between HLSL-style profile id's (e.g. vs_4_0) and the corresponding GLSL version numbers.
	//! We will use the keyword Profile.
	//! e.g.
	//!		Profile vs_4_0(410);
	class Effect
	{
	public:
		~Effect();
		Effect();
	protected:
// FUNDAMENTAL DATA: This must be cached if we want to reload the effect without rebuilding it from source.
		string												m_dir;
		string												m_filename;
		std::vector<Declaration *>							declarations;
		std::map<std::string,TechniqueGroup*>				m_techniqueGroups;
		std::map<std::string,BlendState*>					m_blendStates;
		std::map<std::string,DepthStencilState*>			m_depthStencilStates;
		std::map<std::string,SamplerState*>					m_samplerStates;

		std::map<std::string,DeclaredTexture*>				m_declaredTextures;
		std::map<int,DeclaredTexture*>						m_declaredTexturesByNumber;
		std::map<std::string,int>							textureNumberMap;

		std::map<std::string,RasterizerState*>				m_rasterizerStates;
		std::map<std::string,ComputeLayout>					m_shaderLayouts;
		std::map<unsigned,PassState>						passStates;
		std::map<unsigned,Program*>							passProgramMap;
		std::map<std::string,unsigned>						samplerObjects;
		ProfileMap											m_profileToVersion;
		CompiledShaderMap									m_compiledShaders;
		std::map<std::string,std::vector<Function*> >		functions;
		vector<string>										m_filenames;
		string												m_sharedCode;
		std::map<std::string, TextureSampler*>				textureSamplers;
		// But to apply the ts, we must map them by pass.
		std::map<unsigned,std::set<TextureSampler*> >		textureSamplersByPass;
		std::map<std::string, Struct*>						m_structs;
	
// SHORTCUT DATA CREATED FROM OTHER VALUES
		std::map<string, unsigned> glSamplerStates;		//!< Sampler state objects by name
		std::map<std::string,std::set<TextureSampler*> >	textureSamplersByTexture;
		std::map<std::string,std::set<TextureSampler*> >	textureSamplersByShader;
		std::vector<std::string>							m_techniqueNames;
		std::vector<std::string>							m_techniqueGroupNames;
// TEMPORARIES USED IN CONSTRUCTION
		std::map<string, DeclaredTexture *>					additionalTextureDeclarations;
// STATE
		ostringstream										m_log;
		std::map<int,int>									textureDimensions;
		std::map<int,TextureAssignment>						textureAssignmentMap;
		
		unsigned											current_pass;
		int													current_texture_number;
		int													current_image_number;
		std::map<std::string, unsigned>						prepared_sampler_states;	///< We keep a map of texture sampler states.
		// Create the gl objects for samplers defined in the fx file.
		bool PassHasTransformFeedback(unsigned pass);
		void SetTex(int texture_number,int dim,const TextureAssignment &t,int location_in_shader);
// POST-INIT
		void CreateDefinedSamplers();
	public:
		void SaveToCache(const std::string &filename);
		void LoadFromCache(const std::string &filename);
// GET INFO
		const CompiledShaderMap &GetCompiledShaders() const
		{
			return m_compiledShaders;
		}
		const ProfileMap &GetProfileToVersion() const
		{
			return m_profileToVersion;
		}
		const std::map<std::string,DeclaredTexture*> &GetDeclaredTextures() const
		{
			return m_declaredTextures;
		}
		const std::map<std::string, Struct*>		&GetStructs() const
		{
			return m_structs;
		}
		const std::map<std::string, ComputeLayout>		&GetComputeLayouts() const
		{
			return m_shaderLayouts;
		}
		const std::map<std::string,std::set<TextureSampler*> > &GetTextureSamplersByShader() const
		{
			return textureSamplersByShader;
		}
		const std::map<std::string,std::vector<Function*> > &GetFunctions() const
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
		//unsigned GetProgramVariant(unsigned main_program);
		unsigned CreateSampler(const string& sampler) const;
		bool SetVersionForProfile(int v,const std::string &prof);
		void AddComputeLayout(const std::string &name,const ComputeLayout &tg);
		void Compile(glfxParser::ShaderType shaderType,const CompilableShader &sh,const std::string &compiledShaderName);
		const CompiledShader *AddCompiledShader(const std::string &compiledShaderName
														,const std::string &fnName
														,ShaderType sType
														,int version_num
														,std::string outputStruct=""
														,std::string outputStructName=""
														,std::string source="");
		void AddTechnique(const std::string &techname,const std::string &group,Technique *t);
		void AddTechniqueGroup(const std::string &groupName,const TechniqueGroup &tg);
		bool AddCompiledShader(ShaderType sType,const std::string &lvalCompiledShaderName,const std::string &rvalCompiledShaderName);
		void DeclareRasterizerState(const std::string &name,const RasterizerState &buildRasterizerState);
		void DeclareBlendState(const std::string &name,const BlendState &buildBlendState);
		void DeclareDepthStencilState(const std::string &name,const DepthStencilState &buildDepthStencilState);
		void DeclareSamplerState(const std::string &name,const SamplerState &buildSamplerState);
		Function * DeclareFunction(const std::string &functionName,Function &buildFunction);
		void DeclareStruct(const string &name,const Struct &ts);
bool IsTextureDeclared(const string &name);
		bool DeclareTexture(const string &name,const DeclaredTexture &ts);
		bool DeclareTextureSampler(const TextureSampler *ts);
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
		// Returns the variant pass if needed.
		unsigned ApplyPassTextures(unsigned pass);
		void ApplyPassState(unsigned pass);
		void SetTexture(int texture_number,unsigned tex,int dims,int depth,GLenum format,bool write,int write_mip,bool layered,int layer,bool cubemap);
		void SetSamplerState(const char *name, unsigned sam);
		
		void AccumulateFunctionsUsed(const Function *f,std::set<const Function *> &s) const;
		// STATE
		TechniqueGroup *current_group;
	};
	extern Effect *gEffect;
}
#endif