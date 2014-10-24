#ifndef SIMUL_BASE_STRINGTOWSTRING_H
#define SIMUL_BASE_STRINGTOWSTRING_H
#include <string>
	
extern std::wstring Utf8ToWString(const char *utf8);
extern std::wstring Utf8ToWString(std::string utf8);
extern std::string WStringToUtf8(const wchar_t *src_w);
extern std::string WStringToUtf8(std::wstring wstr);
extern const std::wstring &StringToWString(const std::string &text);
extern const std::string &WStringToString(const std::wstring &text);
extern void WStringToAsciiString(char *output,const std::wstring &text);

#endif