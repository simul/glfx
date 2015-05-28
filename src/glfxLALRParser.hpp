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
     STORAGEQ = 267,
     GL_FRAGDEPTH = 268,
     SHADER_COMMAND = 269,
     SET_RASTERIZER_COMMAND = 270,
     SET_DEPTH_COMMAND = 271,
     SET_BLEND_COMMAND = 272,
     SV_DISPATCHTHREADID = 273,
     SV_GROUPTHREADID = 274,
     SV_GROUPID = 275,
     SV_VERTEXID = 276,
     NUM = 277,
     INCLUDE = 278,
     SAMPLER = 279,
     FLOAT = 280,
     LAYOUT = 281,
     LINE = 282,
     TECHNIQUE = 283,
     PASS = 284,
     GROUP = 285,
     RENDER_STATE_DECL = 286,
     QUOTED_STRING = 287,
     SHADER_LINE = 288,
     SHADER_TYPE = 289,
     COMPILE_SHADER = 290,
     CONSTRUCT_GS_WITH_SO = 291,
     STRUCT = 292,
     PRAGMA = 293,
     DEFINE = 294,
     UNDEF = 295,
     MACRO_DEFINITION = 296,
     EOL = 297,
     DECL_SHADER = 298,
     PROFILE = 299,
     WARNING = 300,
     DEF = 301,
     MESSAGE = 302,
     PACK_MATRIX = 303,
     RW_TEXTURE2D = 304,
     RW_TEXTURE3D = 305,
     RW_TEXTURE2DARRAY = 306,
     RW_TEXTURE3D_FLOAT4 = 307,
     TEXTURE2DMS = 308,
     TEXTURE2D = 309,
     TEXTURE3D = 310,
     IMAGE3D = 311,
     KNOWN_TYPE = 312,
     STRUCTUREDBUFFER = 313,
     RW_STRUCTUREDBUFFER = 314,
     RETURN = 315,
     BREAK = 316,
     CONTINUE = 317,
     DO = 318,
     FOR = 319,
     GOTO = 320,
     IF = 321,
     WHILE = 322,
     ELSE = 323,
     TIMES_EQUALS = 324,
     OVER_EQUALS = 325,
     PERCENT_EQUALS = 326,
     PLUS_EQUALS = 327,
     MINUS_EQUALS = 328,
     LEFT_SHIFT_EQUALS = 329,
     RIGHT_SHIFT_EQUALS = 330,
     AND_EQUALS = 331,
     XOR_EQUALS = 332,
     OR_EQUALS = 333,
     AND = 334,
     OR = 335,
     LESS_EQ = 336,
     GRTR_EQ = 337,
     LEFT_SHIFT = 338,
     RIGHT_SHIFT = 339,
     PLUS_PLUS = 340,
     MINUS_MINUS = 341,
     EQ_EQ = 342,
     NOT_EQ = 343,
     SA_MAXVERTEXCOUNT = 344,
     SA_NUMTHREADS = 345,
     SHADER_PROFILE = 346
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
