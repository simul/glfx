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
     STORAGEQ = 264,
     GL_FRAGDEPTH = 265,
     SHADER_COMMAND = 266,
     SET_RASTERIZER_COMMAND = 267,
     SET_DEPTH_COMMAND = 268,
     SET_BLEND_COMMAND = 269,
     SV_DISPATCHTHREADID = 270,
     SV_GROUPTHREADID = 271,
     SV_GROUPID = 272,
     SV_VERTEXID = 273,
     NUM = 274,
     INCLUDE = 275,
     SAMPLER = 276,
     FLOAT = 277,
     LAYOUT = 278,
     LINE = 279,
     TECHNIQUE = 280,
     PASS = 281,
     GROUP = 282,
     RENDER_STATE_DECL = 283,
     QUOTED_STRING = 284,
     SHADER_LINE = 285,
     SHADER_TYPE = 286,
     COMPILE_SHADER = 287,
     CONSTRUCT_GS_WITH_SO = 288,
     STRUCT = 289,
     DEFINE = 290,
     MACRO_DEFINITION = 291,
     EOL = 292,
     DECL_SHADER = 293,
     PROFILE = 294,
     RW_TEXTURE2D = 295,
     RW_TEXTURE3D = 296,
     RW_TEXTURE2DARRAY = 297,
     RW_TEXTURE3D_FLOAT4 = 298,
     TEXTURE2DMS = 299,
     IMAGE3D = 300,
     KNOWN_TYPE = 301,
     STRUCTUREDBUFFER = 302,
     RW_STRUCTUREDBUFFER = 303,
     RETURN = 304,
     BREAK = 305,
     CONTINUE = 306,
     DO = 307,
     FOR = 308,
     GOTO = 309,
     IF = 310,
     WHILE = 311,
     ELSE = 312,
     TIMES_EQUALS = 313,
     OVER_EQUALS = 314,
     PERCENT_EQUALS = 315,
     PLUS_EQUALS = 316,
     MINUS_EQUALS = 317,
     LEFT_SHIFT_EQUALS = 318,
     RIGHT_SHIFT_EQUALS = 319,
     AND_EQUALS = 320,
     XOR_EQUALS = 321,
     OR_EQUALS = 322,
     AND = 323,
     OR = 324,
     LESS_EQ = 325,
     GRTR_EQ = 326,
     LEFT_SHIFT = 327,
     RIGHT_SHIFT = 328,
     PLUS_PLUS = 329,
     MINUS_MINUS = 330,
     EQ_EQ = 331,
     NOT_EQ = 332,
     SA_MAXVERTEXCOUNT = 333,
     SA_NUMTHREADS = 334,
     CS_LAYOUT = 335
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
