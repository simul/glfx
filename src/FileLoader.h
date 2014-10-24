#pragma once
#include <vector>

class FileLoader
{
public:
	FileLoader();
	bool FileExists(const char *filename_utf8) const;
	const char *FindFileInPathStack(const char *filename_utf8,const std::vector<std::string> &path_stack_utf8) const;
	void AcquireFileContents(void*& pointer, unsigned int& bytes, const char* filename_utf8,bool open_as_text);
	double GetFileDate(const char* filename_utf8);
	void ReleaseFileContents(void* pointer);
	void Save(void* pointer, unsigned int bytes, const char* filename_utf8,bool save_as_text);
};