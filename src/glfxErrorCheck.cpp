#pragma once

#include "glfxErrorCheck.h"
#include "GL/glew.h"
#include "GL/Gl.h"
#include <Windows.h>
using namespace std;
void CheckGLError()
{
	int err=glGetError();
	if(err)
	{
		std::cerr<<__FILE__<<"("<<__LINE__<<"): warning B0001: "<<"gl error ";
		while(err!=GL_NO_ERROR)
		{
			const char *error=NULL;
			switch(err)
			{
				case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
				case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
				case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
				case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
				case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
				default:
					error="UNKNOWN";
				break;
			}
			if(error)
				cerr <<" "<<err<<" GL_" << error;
			err=glGetError();
			BreakIfDebugging();
        }
		std::cerr<<std::endl;
	}
}

void BreakIfDebugging()
{
#ifdef _MSC_VER
	DebugBreak();
#endif
}