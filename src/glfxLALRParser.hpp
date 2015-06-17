/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_GLFX_SRC_GLFXLALRPARSER_HPP_INCLUDED
# define YY_GLFX_SRC_GLFXLALRPARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int glfxdebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WHITESPACE = 258,
     UNIFORM = 259,
     REGISTER = 260,
     SHADER = 261,
     CONSTANT_BUFFER = 262,
     PROGRAM = 263,
     INTERFACE = 264,
     IDENTIFIER = 265,
     SAMPLE = 266,
     SAMPLE_LOD = 267,
     LOAD = 268,
     GET_DIMS = 269,
     STORAGEQ = 270,
     GL_FRAGDEPTH = 271,
     SHADER_COMMAND = 272,
     SET_RASTERIZER_COMMAND = 273,
     SET_DEPTH_COMMAND = 274,
     SET_BLEND_COMMAND = 275,
     SV_DISPATCHTHREADID = 276,
     SV_GROUPTHREADID = 277,
     SV_GROUPID = 278,
     SV_VERTEXID = 279,
     NUM = 280,
     INCLUDE = 281,
     SAMPLER = 282,
     FLOAT = 283,
     LAYOUT = 284,
     LINE = 285,
     TECHNIQUE = 286,
     PASS = 287,
     GROUP = 288,
     RENDER_STATE_DECL = 289,
     QUOTED_STRING = 290,
     SHADER_LINE = 291,
     SHADER_TYPE = 292,
     COMPILE_SHADER = 293,
     CONSTRUCT_GS_WITH_SO = 294,
     STRUCT = 295,
     PRAGMA = 296,
     DEFINE = 297,
     UNDEF = 298,
     MACRO_DEFINITION = 299,
     EOL = 300,
     DECL_SHADER = 301,
     PROFILE = 302,
     WARNING = 303,
     DEF = 304,
     MESSAGE = 305,
     PACK_MATRIX = 306,
     RW_TEXTURE2D = 307,
     RW_TEXTURE3D = 308,
     RW_TEXTURE2DARRAY = 309,
     RW_TEXTURE3D_FLOAT4 = 310,
     TEXTURE2DMS = 311,
     TEXTURE2D = 312,
     TEXTURE2DARRAY = 313,
     TEXTURE3D = 314,
     TEXTURECUBE = 315,
     IMAGE3D = 316,
     KNOWN_TYPE = 317,
     STRUCTUREDBUFFER = 318,
     RW_STRUCTUREDBUFFER = 319,
     RETURN = 320,
     BREAK = 321,
     CONTINUE = 322,
     DO = 323,
     FOR = 324,
     GOTO = 325,
     IF = 326,
     WHILE = 327,
     ELSE = 328,
     TIMES_EQUALS = 329,
     OVER_EQUALS = 330,
     PERCENT_EQUALS = 331,
     PLUS_EQUALS = 332,
     MINUS_EQUALS = 333,
     LEFT_SHIFT_EQUALS = 334,
     RIGHT_SHIFT_EQUALS = 335,
     AND_EQUALS = 336,
     XOR_EQUALS = 337,
     OR_EQUALS = 338,
     AND = 339,
     OR = 340,
     LESS_EQ = 341,
     GRTR_EQ = 342,
     LEFT_SHIFT = 343,
     RIGHT_SHIFT = 344,
     PLUS_PLUS = 345,
     MINUS_MINUS = 346,
     EQ_EQ = 347,
     NOT_EQ = 348,
     SA_MAXVERTEXCOUNT = 349,
     SA_NUMTHREADS = 350,
     SATURATE = 351,
     SHADER_PROFILE = 352
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE glfxlval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int glfxparse (void *YYPARSE_PARAM);
#else
int glfxparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int glfxparse (void);
#else
int glfxparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_GLFX_SRC_GLFXLALRPARSER_HPP_INCLUDED  */
