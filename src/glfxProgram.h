#ifndef GLFXPROGRAM_H
#define GLFXPROGRAM_H

namespace glfxParser
{
	//! A Program in glsl is equivalent to a Pass in hlsl.
	class Program
	{
	public:
		struct Shader
		{
			string  name;
			string  src;
		};

		Program(const map<ShaderType, Shader>& shaders);
		Program();
		Program(const Program& prog);
		const Program &operator=(const Program &);
		unsigned CompileAndLink(string& log) const;
        
	private:
		int CompileShader(unsigned shader, const Shader& shaderSrc, ostringstream& sLog) const;

		Shader  m_shaders[NUM_OF_SHADER_TYPES];
		bool    m_separable;
		friend int ::glfxparse();
	};
	class Technique
	{
	public:
		Technique(const map<std::string, Program>& passes);
		 map<string, Program>   &GetPasses() 
		{
			return m_passes;
		}
	private:
		map<string, Program>   m_passes;
		friend int ::glfxparse();
	};
}
#endif