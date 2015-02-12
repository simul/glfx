#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <cstdio>
#include <cassert>

#ifndef _MSC_VER
typedef int errno_t;
#include <errno.h>
#endif

#include "GL/glew.h"

// workaround for Linux distributions that haven't yet upgraded to GLEW 1.9
#ifndef GL_COMPUTE_SHADER
#define GL_COMPUTE_SHADER 0x91B9
#endif

#include "gl/glfx.h"
#include "glfxClasses.h"
#include "glfxParser.h"
#include "glfxEffect.h"

#ifdef _MSC_VER
#define YY_NO_UNISTD_H
#endif
#include "glfxScanner.h"
#include "glfxProgram.h"
#include <set>

Effect::Effect()
    : m_includes(0)
    , m_active(true)
	,current_group(NULL)
{}

Effect::~Effect()
{
    for(map<string,Program*>::iterator it=m_programs.begin(); it!=m_programs.end(); ++it)
        delete it->second;
    for(map<string,Sampler*>::iterator it=m_samplers.begin(); it!=m_samplers.end(); ++it)
        delete it->second;
	std::set<CompiledShader*> comp;
    for(CompiledShaderMap::iterator it=m_compiledShaders.begin(); it!=m_compiledShaders.end(); ++it)
        comp.insert(it->second);
    for(std::set<CompiledShader*>::iterator it=comp.begin(); it!=comp.end(); ++it)
        delete (*it);
}

bool& Effect::Active()
{
    return m_active;
}

string& Effect::Filename()
{
    return m_filename;
}

string& Effect::Dir()
{
    return m_dir;
}

unsigned Effect::BuildProgram(const string& tech, const string& pass, string& log) const
{
	if (tech.length() == 0)
	{
		map<string, Program*>::const_iterator it = m_programs.find(pass);
		if (it == m_programs.end())
			return 0;

		unsigned ret = it->second->CompileAndLink(log);
		return ret;
	}
	else
	{
		TechniqueGroup *group=m_techniqueGroups.find("")->second;
		map<string, Technique*>::const_iterator it = group->m_techniques.find(tech);
		if (it == group->m_techniques.end())
			return 0;
		Technique *tech = it->second;
		map<string, Program>::const_iterator jt=tech->GetPasses().find(pass);
		unsigned ret = jt->second.CompileAndLink(log);
		return ret;
	}
}
/*
unsigned Effect::BuildProgram(const string& prog) const
{
    string trash;
    return BuildProgram(prog, trash);
}
*/
ostringstream& Effect::Log()
{
    return m_log;
}

unsigned Effect::CreateSampler(const string& sampler) const
{
    map<string,Sampler*>::const_iterator it=m_samplers.find(sampler);
    if(it==m_samplers.end())
        throw "Sampler not found";

    return it->second->CreateSamplerObject();
}

const vector<string>& Effect::GetProgramList() const
{
    return m_programNames;
}

const vector<string>& Effect::GetTechniqueList() const
{
	return m_techniqueNames;
}

const vector<string>& Effect::GetTechniqueGroupList() const
{
	return m_techniqueGroupNames;
}

Technique *Effect::GetTechniqueByName(const char *name) 
{
	TechniqueGroup *group=m_techniqueGroups.find("")->second;
	return (group->m_techniques.find(string(name)))->second;
}
TechniqueGroup *Effect::GetTechniqueGroupByIndex(int idx)
{
	int i=0;
	map<string, TechniqueGroup*>::const_iterator it;
	for (it = m_techniqueGroups.begin(); it != m_techniqueGroups.end()&&i<idx; ++it)
	{
		i++;
	}
	TechniqueGroup *group=it->second;
	return group;
}

TechniqueGroup *Effect::GetTechniqueGroupByName(const char *name)
{
	map<string, TechniqueGroup*>::const_iterator jt=m_techniqueGroups.find(name);
	TechniqueGroup *group=jt->second;
	return group;
}


const vector<string>& Effect::GetFilenameList() const
{
    return m_filenames;
}


void Effect::SetFilenameList(const vector<string> &filenamesUtf8)
{
	m_filenames=filenamesUtf8;
	/*
	m_filenames.clear();
   const char **f=filenamesUtf8;
	while(*f!=NULL)
	{
		m_filenames.push_back(*f);
		f++;
	}*/
}

void Effect::PopulateProgramList()
{
    m_programNames.clear();
    for(map<string,Program*>::const_iterator it=m_programs.begin(); it!=m_programs.end(); ++it)
		m_programNames.push_back(it->first);
	m_techniqueNames.clear();
	TechniqueGroup *group=m_techniqueGroups.find("")->second;
	for (map<string, Technique*>::const_iterator it = group->m_techniques.begin(); it != group->m_techniques.end(); ++it)
		m_techniqueNames.push_back(it->first);
	m_techniqueGroupNames.clear();
	for (map<string, TechniqueGroup*>::const_iterator it = m_techniqueGroups.begin(); it != m_techniqueGroups.end(); ++it)
		m_techniqueGroupNames.push_back(it->first);
}