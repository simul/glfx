/* Copyright (c) 2011, Max Aizenshtein <max.sniffer@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#pragma once

#if defined(__MINGW32__) || defined(__CYGWIN__)
#   define GLFX_APIENTRY __cdecl
#elif (_MSC_VER >= 800)
#   define GLFX_APIENTRY __cdecl
#else
#   define GLFX_APIENTRY
#endif

#ifndef GLFX_STATIC
#   ifdef GLFX_BUILD
#       ifdef _MSC_VER
#           define GLFXAPI extern __declspec(dllexport)
#       else
#           define GLFXAPI __attribute__((__visibility__("default")))
#       endif
#   else
#       ifdef _MSC_VER
#           define GLFXAPI extern __declspec(dllimport)
#       else
#           define GLFXAPI
#       endif
#   endif
#else
#   define GLFXAPI extern
#endif

extern "C" {

/**************************************************
* glfxGenEffect
* Return value: Effect id
**************************************************/
GLFXAPI int GLFX_APIENTRY glfxGenEffect();

/**************************************************
* glfxCreateEffectFromFile
* Input:
*   effect				-- GLFX effect id
*   file				-- File name
*   shaderPathsUtf8		-- NULL-terminated list of paths for include files.
*   macros				-- NULL-terminated list of macros to be predefined
*   defs				-- list of corresponding macro definitions
* Return value: Status
**************************************************/
GLFXAPI bool GLFX_APIENTRY glfxParseEffectFromFile(int effect, const char* file, const char **shaderPathsUtf8, const char **macros, const char **defs);

/**************************************************
* glfxCreateEffectFromMemory
* Input:
*   effect  -- GLFX effect id
*   src    -- Source
* Return value: Status
**************************************************/
GLFXAPI bool GLFX_APIENTRY glfxParseEffectFromMemory( int effect, const char* src ,const char *filename=0);

/**************************************************
* glfxCompileProgram
* Input:
*   effect  -- GLFX effect id
*   program -- Program name
* Return value: GL program id if success, 0 otherwise
**************************************************/
//GLFXAPI GLuint GLFX_APIENTRY glfxCompileProgram(int effect, const char* program);
GLFXAPI GLuint GLFX_APIENTRY glfxCompileProgram(int effect, const char* technique, const char *pass);

/**************************************************
* glfxGetProgramCount
* Return value: Number of programs
**************************************************/
GLFXAPI int GLFX_APIENTRY glfxGetProgramCount(int effect);

GLFXAPI int glfxGetEffectTextureNumber(int effect,const char *name);
/**************************************************
* glfxGetProgramName
* Input:
*   effect  -- GLFX effect id
*   program -- Index of program
*   name    -- Destination address
*   bufSize -- Size of the buffer
**************************************************/
GLFXAPI void GLFX_APIENTRY glfxGetProgramName(int effect, int program, char* name, int bufSize);

/**************************************************
* glfxGetProgramIndex
* Input:
*   effect  -- GLFX effect id
*   name -- name of program
**************************************************/
GLFXAPI size_t GLFX_APIENTRY glfxGetProgramIndex(int effect, const char* name);

//! Get the number of techniques in the effect
GLFXAPI size_t GLFX_APIENTRY glfxGetTechniqueCount(int effect);
GLFXAPI size_t GLFX_APIENTRY glfxGetTechniqueGroupCount(int effect);
GLFXAPI const char *GLFX_APIENTRY glfxGetTechniqueGroupName(int effect,int g);
GLFXAPI void GLFX_APIENTRY glfxUseTechniqueGroup(int effect,int g);

//! Get the name of the technique at the given index.
GLFXAPI const char* GLFX_APIENTRY glfxGetTechniqueName(int effect, int technum);
//! Get the number of passes in the technique
GLFXAPI size_t GLFX_APIENTRY glfxGetPassCount(int effect, const char* tech_name);
//! Get the name of the pass at the given index.
GLFXAPI const char* GLFX_APIENTRY glfxGetPassName(int effect, const char *tech_name,int pass_num);
//! Compile the pass and return its GLSL program identifier.
GLFXAPI GLuint GLFX_APIENTRY glfxCompilePass(int effect, const char *tech_name, const char *pass_name);
GLFXAPI void GLFX_APIENTRY glfxApplyPassState(int effect,GLuint pass);

/**************************************************
* glfxGenerateSampler
* Input:
*   effect  -- GLFX effect id
*   sampler -- Sampler name
* Return value: GL sampler id if success, -1 otherwise
**************************************************/
GLFXAPI int GLFX_APIENTRY glfxGenerateSampler(int effect, const char* sampler);

/**************************************************
* glfxGetEffectLog
* Input:
*   effect  -- GLFX effect id
*   log     -- Destination address
*   bufSize -- Size of the buffer
**************************************************/
GLFXAPI void GLFX_APIENTRY glfxGetEffectLog(int effect, char* log, int bufSize);


/**************************************************
* glfxDeleteEffect
* Input:
*   effect  -- GLFX effect id
**************************************************/
GLFXAPI void GLFX_APIENTRY glfxDeleteEffect(int effect);

}

#ifdef __cplusplus

/**************************************************
* glfxGetProgramName
* Input:
*   effect  -- GLFX effect id
*   program -- Index of program
**************************************************/
GLFXAPI const char* GLFX_APIENTRY glfxGetProgramName(int effect, int program);

/**************************************************
* glfxGetProgramIndex
* Input:
*   effect  -- GLFX effect id
*   name -- name of program
**************************************************/
GLFXAPI size_t GLFX_APIENTRY glfxGetProgramIndex(int effect, const char* name);

/**************************************************
* glfxGetEffectLog
* Input:
*   effect  -- GLFX effect id
* Return value: Log string
**************************************************/
GLFXAPI const char* GLFX_APIENTRY glfxGetEffectLog(int effect);

#endif
