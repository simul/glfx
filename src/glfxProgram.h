#ifndef GLFXPROGRAM_H
#define GLFXPROGRAM_H
#include <map>
#include <set>
#include <string>
#include "glfxClasses.h"
struct CompiledShader;
struct DeclaredTexture;
namespace glfxParser
{
	struct TextureSampler;

	struct VariantFormat
	{
		std::string layoutDeclaration;
		std::string typeLetter;
		std::string memberType;
	};

	//! A Program in glsl is equivalent to a Pass in hlsl.
	class Program
	{
	public:
		PassState passState;
		struct Shader
		{
			Shader():compiledShader(NULL)
			{
			}
			string	name;
			string	preamble;
			CompiledShader  *compiledShader;
			string  layout;
			string	outputStruct;
		};

		Program(const map<ShaderType, Shader>& shaders,const PassState &p,const std::map<std::string,std::set<TextureSampler*> > &textureSamplersByShader,const string &compute_layout);
		Program();
		Program(const Program& prog);
		~Program();
		const Program &operator=(const Program &);
		unsigned CompileAndLink(const std::string &shared_src,const std::map<std::string,DeclaredTexture*> &declaredTextures,std::string& log) ;
		struct Variant
		{
			Variant():programId(0)
			{
			}
			unsigned programId;
		};
		unsigned GetVariantPass(unsigned v) const
		{
			auto e=variants.find(v);
			if(e==variants.end())
				return 0;
			return e->second.programId;
		}
		int GetVariantNumber(const std::map<std::string,GLenum> variableFormats);
		const vector<VariantFormat> &GetVariantsForTexture(const std::string &name) const
		{
			auto i=variantMap.find(name);
			return i->second;
		}
		bool IsTransformFeedbackShader() const
		{
			return transformFeedback;
		}
		Topology GetOutputTopology() const
		{
			return transformFeedbackTopology;
		}
		void SetOutputTopology(Topology t)
		{
			transformFeedbackTopology=t;
		}
		Shader *GetShader(ShaderType type)
		{
			return &(m_shaders[type]);
		}
	private:
		int CompileShader(unsigned shader, const std::string& name,const std::string &variantDefs,const std::string &shared, const std::string &src, ShaderType type,ostringstream& sLog) const;
		std::string	computeLayout;
		// A map of the variable names to the vector of variants it each variable have.
		map<string,vector<VariantFormat> > variantMap;
		// The names of the RW textures that have variants.
		//std::vector<std::string> variantVariables;
		std::map<unsigned,Variant> variants;
		Shader		m_shaders[NUM_OF_SHADER_TYPES];
		bool		m_separable;
		bool		transformFeedback;
		Topology transformFeedbackTopology;
		friend int	::glfxparse();
#ifdef GLFX_GLSLANG
		void GlslangValidateProgram(const string &shared_src,string variantDefs,ostringstream &sLog);
#endif
	};
	class Technique
	{
	public:
		Technique(const map<std::string, Program>& passes);
		~Technique();
		map<string, Program> &GetPasses() 
		{
			return m_passes;
		}
	private:
		map<string, Program>   m_passes;
		friend int ::glfxparse();
	};
	class TechniqueGroup
	{
		vector<string> m_techniqueNames;
	public:
		~TechniqueGroup();
		map<string,Technique*> m_techniques;
		const vector<string> &GetTechniqueList();
	};
}
#endif