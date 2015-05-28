#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H

#include <string>
#include <vector>
#include <stdarg.h>

extern void StripDirectoryFromFilename(std::string &str);
extern std::string GetDirectoryFromFilename(const std::string &str);
extern void ClipWhitespace(std::string &Line);
extern size_t GoToLine(const std::string &Str,size_t line);
extern std::string StringOf(int i);
extern std::string StringOf(float i);
extern std::string stringof(int i);
extern std::string stringof(float f);
extern std::string digits(const char *txt);
//! Create a std::string using sprintf-style formatting, with variable arguments.
extern std::string stringFormat(std::string fmt, ...);
/// A quick-and-dirty, non-re-entrant formatting function. Use this only for debugging.
extern const char *QuickFormat(const char *format_str,...);
//! Proper find-and-replace function for strings:
extern void find_and_replace(std::string& source, std::string const& find, std::string const& replace);	
//! Divide a string into a vector of smaller strings, based on the given separator
extern std::vector<std::string> split(const std::string& source, char separator);

#endif

