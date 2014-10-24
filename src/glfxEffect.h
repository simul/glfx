#ifndef GLFXEFFECT_H
#define GLFXEFFECT_H

namespace glfxParser
{
	class Effect
	{
		map<string, Program*>   m_programs;
		vector<string>          m_programNames;
		map<string, Technique*> m_techniques;
		vector<string>          m_techniqueNames;
		map<string, Sampler*>   m_samplers;
		map<string, string>     m_shaders;
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