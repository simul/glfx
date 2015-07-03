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
	class Effect
	{
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
		vector<string>				m_filenames;
		ostringstream               m_sharedCode;
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
		};
		std::map<std::string,int> textureNumberMap;
		std::map<int, TextureAssignment> textureAssignmentMap;
		std::map<int, int> textureDimensions;
		/// We keep a map of texture 
		std::map<std::string, unsigned> prepared_sampler_states;
		unsigned current_pass;
		// Create the gl objects for samplers defined in the fx file.
		void CreateDefinedSamplers();
		bool PassHasTransformFeedback(unsigned pass);
	public:
		struct InterfaceDcl
		{
			string id;
			int atLine;

			InterfaceDcl(string s, int l) : id(s), atLine(l) {}
			InterfaceDcl() {}
		};
		std::map<std::string, InterfaceDcl>   m_interfaces;
		std::map<std::string, Struct*>			m_structs;
		std::map<string, DeclaredTexture> additionalTextureDeclarations;
		const std::map<std::string,DeclaredTexture> &GetDeclaredTextures() const
		{
			return m_declaredTextures;
		}
		void Clear();
		ostringstream& Log();
		unsigned BuildProgram(const string& tech, const string& pass, string& log);
		//unsigned BuildProgram(const string& prog) const;
		unsigned CreateSampler(const string& sampler) const;
		// merge in the textureSamplers:
		void MergeTextureSamplers(const std::map<std::string,TextureSampler*> &ts,const std::string &shaderName);
		const vector<string>& GetTechniqueGroupList() const;
		const vector<string>& GetTechniqueList() const;
		const vector<string>& GetFilenameList() const;
		bool IsDeclared(std::string str);
		string GetDeclaredType(std::string str);
		Technique *GetTechniqueByName(const char *name) ;
		TechniqueGroup *GetTechniqueGroupByName(const char *name);
		TechniqueGroup *GetTechniqueGroupByIndex(int idx);
		void SetFilenameList(const vector<string> &filenamesUtf8);
		void PopulateProgramList();
		void Apply(unsigned pass);
		void Reapply(unsigned pass);
		void Unapply();
		void ApplyPassTextures(unsigned pass);
		void ApplyPassState(unsigned pass);
		bool& Active();
		string& Dir();
		string& Filename();
		~Effect();
		Effect();
		friend void ::glfxWrite(const char *);
		friend int ::glfxparse();
		friend int ::glfxlex();
		TechniqueGroup *current_group;
		int GetTextureNumber(const char *name);
		int GetImageNumber(const char *name);
		void SetTexture(int texture_number,unsigned tex,int dims,int depth,GLenum format,bool write);
		void SetSamplerState(const char *name, unsigned sam);
		void SetTex(int texture_number,const TextureAssignment &t,int location_in_shader);
	};
	extern Effect *gEffect;
}
#endif