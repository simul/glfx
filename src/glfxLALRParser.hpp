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
     NUM = 273,
     INCLUDE = 274,
     SAMPLER = 275,
     FLOAT = 276,
     LAYOUT = 277,
     LINE = 278,
     TECHNIQUE = 279,
     PASS = 280,
     GROUP = 281,
     RENDER_STATE_DECL = 282,
     QUOTED_STRING = 283,
     SHADER_LINE = 284,
     SHADER_TYPE = 285,
     COMPILE_SHADER = 286,
     CONSTRUCT_GS_WITH_SO = 287,
     STRUCT = 288,
     DEFINE = 289,
     MACRO_DEFINITION = 290,
     EOL = 291,
     DECL_SHADER = 292,
     PROFILE = 293,
     RW_TEXTURE2D = 294,
     RW_TEXTURE3D = 295,
     RW_TEXTURE2DARRAY = 296,
     RW_TEXTURE3D_FLOAT4 = 297,
     TEXTURE2DMS = 298,
     IMAGE3D = 299,
     KNOWN_TYPE = 300,
     STRUCTUREDBUFFER = 301,
     RW_STRUCTUREDBUFFER = 302,
     RETURN = 303,
     BREAK = 304,
     CONTINUE = 305,
     DO = 306,
     FOR = 307,
     GOTO = 308,
     IF = 309,
     WHILE = 310,
     ELSE = 311,
     TIMES_EQUALS = 312,
     OVER_EQUALS = 313,
     PERCENT_EQUALS = 314,
     PLUS_EQUALS = 315,
     MINUS_EQUALS = 316,
     LEFT_SHIFT_EQUALS = 317,
     RIGHT_SHIFT_EQUALS = 318,
     AND_EQUALS = 319,
     XOR_EQUALS = 320,
     OR_EQUALS = 321,
     AND = 322,
     OR = 323,
     LESS_EQ = 324,
     GRTR_EQ = 325,
     LEFT_SHIFT = 326,
     RIGHT_SHIFT = 327,
     PLUS_PLUS = 328,
     MINUS_MINUS = 329,
     EQ_EQ = 330,
     NOT_EQ = 331,
     SA_MAXVERTEXCOUNT = 332,
     SA_NUMTHREADS = 333,
     CS_LAYOUT = 334
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
