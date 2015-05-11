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
     PROGRAM = 261,
     INTERFACE = 262,
     IDENTIFIER = 263,
     SAMPLING_COMMAND = 264,
     STORAGEQ = 265,
     GL_FRAGDEPTH = 266,
     SHADER_COMMAND = 267,
     SET_RASTERIZER_COMMAND = 268,
     SET_DEPTH_COMMAND = 269,
     SET_BLEND_COMMAND = 270,
     SV_DISPATCHTHREADID = 271,
     SV_GROUPTHREADID = 272,
     SV_GROUPID = 273,
     SV_VERTEXID = 274,
     NUM = 275,
     INCLUDE = 276,
     SAMPLER = 277,
     FLOAT = 278,
     LAYOUT = 279,
     LINE = 280,
     TECHNIQUE = 281,
     PASS = 282,
     GROUP = 283,
     RENDER_STATE_DECL = 284,
     QUOTED_STRING = 285,
     SHADER_LINE = 286,
     SHADER_TYPE = 287,
     COMPILE_SHADER = 288,
     CONSTRUCT_GS_WITH_SO = 289,
     STRUCT = 290,
     DEFINE = 291,
     UNDEF = 292,
     MACRO_DEFINITION = 293,
     EOL = 294,
     DECL_SHADER = 295,
     PROFILE = 296,
     RW_TEXTURE2D = 297,
     RW_TEXTURE3D = 298,
     RW_TEXTURE2DARRAY = 299,
     RW_TEXTURE3D_FLOAT4 = 300,
     TEXTURE2DMS = 301,
     IMAGE3D = 302,
     KNOWN_TYPE = 303,
     STRUCTUREDBUFFER = 304,
     RW_STRUCTUREDBUFFER = 305,
     RETURN = 306,
     BREAK = 307,
     CONTINUE = 308,
     DO = 309,
     FOR = 310,
     GOTO = 311,
     IF = 312,
     WHILE = 313,
     ELSE = 314,
     TIMES_EQUALS = 315,
     OVER_EQUALS = 316,
     PERCENT_EQUALS = 317,
     PLUS_EQUALS = 318,
     MINUS_EQUALS = 319,
     LEFT_SHIFT_EQUALS = 320,
     RIGHT_SHIFT_EQUALS = 321,
     AND_EQUALS = 322,
     XOR_EQUALS = 323,
     OR_EQUALS = 324,
     AND = 325,
     OR = 326,
     LESS_EQ = 327,
     GRTR_EQ = 328,
     LEFT_SHIFT = 329,
     RIGHT_SHIFT = 330,
     PLUS_PLUS = 331,
     MINUS_MINUS = 332,
     EQ_EQ = 333,
     NOT_EQ = 334,
     SA_MAXVERTEXCOUNT = 335,
     SA_NUMTHREADS = 336,
     CS_LAYOUT = 337
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
