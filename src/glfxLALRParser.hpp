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
     SHADER = 260,
     CONSTANT_BUFFER = 261,
     PROGRAM = 262,
     INTERFACE = 263,
     IDENTIFIER = 264,
     SAMPLE = 265,
     SAMPLE_LOD = 266,
     GET_DIMS = 267,
     STORAGEQ = 268,
     GL_FRAGDEPTH = 269,
     SHADER_COMMAND = 270,
     SET_RASTERIZER_COMMAND = 271,
     SET_DEPTH_COMMAND = 272,
     SET_BLEND_COMMAND = 273,
     SV_DISPATCHTHREADID = 274,
     SV_GROUPTHREADID = 275,
     SV_GROUPID = 276,
     SV_VERTEXID = 277,
     NUM = 278,
     INCLUDE = 279,
     SAMPLER = 280,
     FLOAT = 281,
     LAYOUT = 282,
     LINE = 283,
     TECHNIQUE = 284,
     PASS = 285,
     GROUP = 286,
     RENDER_STATE_DECL = 287,
     QUOTED_STRING = 288,
     SHADER_LINE = 289,
     SHADER_TYPE = 290,
     COMPILE_SHADER = 291,
     CONSTRUCT_GS_WITH_SO = 292,
     STRUCT = 293,
     PRAGMA = 294,
     DEFINE = 295,
     UNDEF = 296,
     MACRO_DEFINITION = 297,
     EOL = 298,
     DECL_SHADER = 299,
     PROFILE = 300,
     WARNING = 301,
     DEF = 302,
     MESSAGE = 303,
     PACK_MATRIX = 304,
     RW_TEXTURE2D = 305,
     RW_TEXTURE3D = 306,
     RW_TEXTURE2DARRAY = 307,
     RW_TEXTURE3D_FLOAT4 = 308,
     TEXTURE2DMS = 309,
     TEXTURE2D = 310,
     TEXTURE3D = 311,
     IMAGE3D = 312,
     KNOWN_TYPE = 313,
     STRUCTUREDBUFFER = 314,
     RW_STRUCTUREDBUFFER = 315,
     RETURN = 316,
     BREAK = 317,
     CONTINUE = 318,
     DO = 319,
     FOR = 320,
     GOTO = 321,
     IF = 322,
     WHILE = 323,
     ELSE = 324,
     TIMES_EQUALS = 325,
     OVER_EQUALS = 326,
     PERCENT_EQUALS = 327,
     PLUS_EQUALS = 328,
     MINUS_EQUALS = 329,
     LEFT_SHIFT_EQUALS = 330,
     RIGHT_SHIFT_EQUALS = 331,
     AND_EQUALS = 332,
     XOR_EQUALS = 333,
     OR_EQUALS = 334,
     AND = 335,
     OR = 336,
     LESS_EQ = 337,
     GRTR_EQ = 338,
     LEFT_SHIFT = 339,
     RIGHT_SHIFT = 340,
     PLUS_PLUS = 341,
     MINUS_MINUS = 342,
     EQ_EQ = 343,
     NOT_EQ = 344,
     SA_MAXVERTEXCOUNT = 345,
     SA_NUMTHREADS = 346,
     SHADER_PROFILE = 347
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
