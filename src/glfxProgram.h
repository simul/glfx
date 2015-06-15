#ifndef GLFXPROGRAM_H
#define GLFXPROGRAM_H
#include <map>
#include <set>
#include "glfxClasses.h"
namespace glfxParser
{
	struct TextureSampler;
	//! A Program in glsl is equivalent to a Pass in hlsl.
	class Program
	{
	public:
		PassState passState;
		struct Shader
		{
			string  name;
			string  src;
			string  layout;
			string	compiledShaderName;
		};

		Program(const map<ShaderType, Shader>& shaders,const PassState &p,const std::map<std::string,std::set<TextureSampler*> > &textureSamplersByShader,const string &compute_layout);
		Program();
		Program(const Program& prog);
		~Program();
		const Program &operator=(const Program &);
		unsigned CompileAndLink(string& log) ;
		unsigned programId;
		bool IsTransformFeedbackShader() const
		{
			return transformFeedback;
		}
	private:
		int CompileShader(unsigned shader, const Shader& shaderSrc, ShaderType type,  ostringstream& sLog) const;
		std::string computeLayout;
		Shader  m_shaders[NUM_OF_SHADER_TYPES];
		bool    m_separable;
		bool    transformFeedback;
		friend int ::glfxparse();
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