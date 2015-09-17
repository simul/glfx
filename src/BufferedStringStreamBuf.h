#ifndef BUFFEREDSTRINGSTREAMBUF_H
#define BUFFEREDSTRINGSTREAMBUF_H

#include <streambuf>
#include <iostream>
#include <cstdio>

class BufferedStringStreamBuf : public std::streambuf
{
public:
	BufferedStringStreamBuf(int bufferSize) 
	{
		if (bufferSize)
		{
			char *ptr = new char[bufferSize];
			setp(ptr, ptr + bufferSize);
		}
		else
			setp(0, 0);
	}
	virtual ~BufferedStringStreamBuf() 
	{
		//sync();
		delete[] pbase();
	}
	virtual void writeString(const std::string &str) = 0;
private:
	int	overflow(int c)
	{
		sync();

		if (c != EOF)
		{
			if (pbase() == epptr())
			{
				std::string temp;
				temp += char(c);
				writeString(temp);
			}
			else
				sputc((char)c);
		}

		return 0;
	}

	int	sync()
	{
		if (pbase() != pptr())
		{
			int len = int(pptr() - pbase());
			std::string temp(pbase(), len);
			writeString(temp);
			setp(pbase(), epptr());
		}
		return 0;
	}
};
#endif
