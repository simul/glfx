#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
// shared #include file for Lexer and Parser.
#include <vector>
#include <string>
#include <map>
struct PreprocessorType
{
	PreprocessorType() {}
	union
	{
		int num;
	};
	std::string str;
};

#define YYSTYPE PreprocessorType
// These are the callback functions for file handling that we will send to the preprocessor.
extern FILE* (*prepro_open)(const char *filename_utf8,std::string &fullPathName);
extern void (*prepro_close)(FILE *f);
extern std::ostringstream preproOutput;
extern void preprocess(const char *file, std::map<std::string, std::string> defines = std::map<std::string, std::string>());
// Are we in an active  #if #endif block?
extern bool inActiveBlock();
extern std::vector<std::string> GetPreprocessorFilenamesUtf8();
extern void WriteLineNumber();
extern void WriteLineNumber(int);
extern bool IsDefined(std::string name);
extern void DefineMacro(std::string name,std::string definition);
extern void UndefineMacro(std::string name);
extern void ClearParserState();
#endif