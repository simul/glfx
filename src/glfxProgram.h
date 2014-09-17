#ifndef GLFXPROGRAM_H
#define GLFXPROGRAM_H

namespace glfxParser
{
	class Program
	{
	public:
		struct Shader
		{
			string  name;
			string  src;
		};

		Program(const map<ShaderType, Shader>& shaders);
		unsigned CompileAndLink(string& log) const;
        
	private:
		int CompileShader(unsigned shader, const Shader& shaderSrc, ostringstream& sLog) const;

		Shader  m_shaders[NUM_OF_SHADER_TYPES];
		bool    m_separable;

		friend int ::glfxparse();
	};
}
#endif