#ifndef GLFXEFFECT_H
#define GLFXEFFECT_H
#include "glfxClasses.h"
#include <map>
#include <string>
namespace glfxParser
{
	//! A shader to be compiled. 
	struct CompiledShader
	{
		ShaderType shaderType;
		int version;
		std::string m_functionName;
	};
	typedef std::map<std::string,CompiledShader*> CompiledShaderMap;
	typedef std::map<std::string,std::string> StringMap;
	class Effect
	{
		map<std::string, Program*>   m_programs;
		vector<std::string>          m_programNames;
		map<std::string, Technique*> m_techniques;
		vector<std::string>          m_techniqueNames;
		map<std::string, Sampler*>   m_samplers;
		map<std::string, std::string>     m_shaders;
		map<std::string, std::string>     m_shaderLayouts;
		CompiledShaderMap			m_compiledShaders;
		struct InterfaceDcl
		{
			string id;
			int atLine;

			InterfaceDcl(string s, int l) : id(s), atLine(l) {}
			InterfaceDcl() {}
		};
		map<string, InterfaceDcl>   m_interfaces;
		vector<string>				m_filenames;
		ostringstream               m_sharedCode;
		ostringstream               m_log;
		int                         m_includes;
		bool                        m_active;
		string                      m_dir;
		string						m_filename;
    
	public:
		ostringstream& Log();
		unsigned BuildProgram(const string& tech, const string& pass, string& log) const;
		//unsigned BuildProgram(const string& prog) const;
		unsigned CreateSampler(const string& sampler) const;
		const vector<string>& GetProgramList() const;
		const vector<string>& GetTechniqueList() const;
		const vector<string>& GetFilenameList() const;
		Technique *GetTechniqueByName(const char *name) ;
		void SetFilenameList(const vector<string> &filenamesUtf8);
		void PopulateProgramList();
		bool& Active();
		string& Dir();
		string& Filename();
		~Effect();
		Effect();
		friend int ::glfxparse();
		friend int ::glfxlex();
	};
	extern Effect *gEffect;
}
#endif