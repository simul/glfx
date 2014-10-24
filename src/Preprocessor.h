#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
// shared #include file for Lexer and Parser.
#include <string>
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
extern void preprocess(const char *file);

#endif