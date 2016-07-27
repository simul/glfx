#include "StringFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef _MSC_VER
#define	sprintf_s(buffer, buffer_size, stringbuffer, ...) (snprintf(buffer, buffer_size, stringbuffer, ##__VA_ARGS__))
#endif

using std::string;
using std::vector;
size_t ttab;
bool IsWhitespace(char c)
{
	return (c==' '||c==13||c==10||c=='\t');
}
void ClipWhitespace(std::string &Line)
{
	while(Line.length()?IsWhitespace(Line[0]):false)
		Line=Line.substr(1,Line.length()-1);
	while(Line.length()?IsWhitespace(Line[Line.length()-1]):false)
		Line=Line.substr(0,Line.length()-1);
}

void Tab(string &out)
{
	for(size_t i=0;i<ttab;i++)
		out+="\t";
}
size_t GoToLine(const string &Str,size_t line)
{
	size_t pos=0;
	char txt[100];
	sprintf_s(txt,99,"\r\n");
	string CR;
	for(size_t i=0;i<line;i++)
	{
		pos=Str.find(13,pos);
		pos++;
	}
	//pos++;
	return pos;
}

string stringof(int i)
{
	char txt[100];
	sprintf_s(txt,99,"%d",i);
	return string(txt);
}
string stringof(float f)
{
	char txt[100];
	sprintf_s(txt,99,"%g",f);
	return string(txt);
}
string StringOf(int i)
{
	char txt[100];
	sprintf_s(txt,99,"%d",i);
	return string(txt);
}
string StringOf(float i)
{
	char txt[100];
	sprintf_s(txt,99,"%g",i);
	return string(txt);
}

extern std::string digits(const char *txt)
{
	std::string d;
	const char *t=txt;
	while(*t)
	{
		if(*t>='0'&&*t<='9')
			d+=*t;
		t++;
	}
	return d;
}

void StripDirectoryFromFilename(string &str)
{
	int pos=(int)str.find("\\");
	int fs_pos=(int)str.find("/");
	if(pos<0||(fs_pos>=0&&fs_pos<pos))
		pos=fs_pos;
	do
	{
		str=str.substr(pos+1,str.length()-pos);
		pos=(int)str.find("\\");
		fs_pos=(int)str.find("/");
		if(pos<0||(fs_pos>=0&&fs_pos<pos))
			pos=fs_pos;
	} while(pos>=0);
}

string GetDirectoryFromFilename(const string &str)
{
	int pos=(int)str.find_last_of("\\");
	int fs_pos=(int)str.find_last_of("/");
	if(pos<0||(fs_pos>=0&&fs_pos>pos))
		pos=fs_pos;
	if(pos<0)
		return "";
	return str.substr(0,pos);
}

std::string stringFormat(std::string fmt, ...)
{
	int size=(int)fmt.size()+100;
	std::string str;
	va_list ap;
	int n=-1;
	const char *format_str=fmt.c_str();
	while(n<0||n>=size)
	{
		str.resize(size);
		va_start(ap, fmt);
		//n = vsnprintf_s((char *)str.c_str(), size, size,format_str, ap);
		n = vsnprintf((char *)str.c_str(), size,format_str, ap);
		va_end(ap);
		if(n> -1 && n < size)
		{
			str.resize(n);
			return str;
		}
		if (n > -1)
			size=n+1;
		else
			size*=2;
	}
	return str;
}
const char *QuickFormat(const char *format_str,...)
{
	int size=(int)strlen(format_str)+100;
	static std::string str;
	va_list ap;
	int n=-1;
	while(n<0||n>=size)
	{
		str.resize(size);
		va_start(ap, format_str);
		//n = vsnprintf_s((char *)str.c_str(), size, size,format_str, ap);
		n = vsnprintf((char *)str.c_str(), size,format_str, ap);
		va_end(ap);
		if(n> -1 && n < size)
		{
			str.resize(n);
			return str.c_str();
		}
		if (n > -1)
			size=n+1;
		else
			size*=2;
	}
	return str.c_str();
}
void find_and_replace(std::string& source, std::string const& find, std::string const& replace)
{
	for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length() - find.length() + 1;
	}
}

vector<string> split(const string& source, char separator)
{
	vector<string> vec;
	int pos=0;
	while(pos>=0&&pos<source.length())
	{
		int nextpos=(int)source.find(separator,pos);
		if(nextpos<0)
			nextpos=(int)source.length();
		if(nextpos>=0)
			vec.push_back(source.substr(pos,nextpos-pos));
		pos=nextpos+1;
	}
	return vec;
}