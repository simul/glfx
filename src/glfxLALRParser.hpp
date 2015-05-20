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
     SAMPLING_COMMAND = 265,
     STORAGEQ = 266,
     GL_FRAGDEPTH = 267,
     SHADER_COMMAND = 268,
     SET_RASTERIZER_COMMAND = 269,
     SET_DEPTH_COMMAND = 270,
     SET_BLEND_COMMAND = 271,
     SV_DISPATCHTHREADID = 272,
     SV_GROUPTHREADID = 273,
     SV_GROUPID = 274,
     SV_VERTEXID = 275,
     NUM = 276,
     INCLUDE = 277,
     SAMPLER = 278,
     FLOAT = 279,
     LAYOUT = 280,
     LINE = 281,
     TECHNIQUE = 282,
     PASS = 283,
     GROUP = 284,
     RENDER_STATE_DECL = 285,
     QUOTED_STRING = 286,
     SHADER_LINE = 287,
     SHADER_TYPE = 288,
     COMPILE_SHADER = 289,
     CONSTRUCT_GS_WITH_SO = 290,
     STRUCT = 291,
     PRAGMA = 292,
     DEFINE = 293,
     UNDEF = 294,
     MACRO_DEFINITION = 295,
     EOL = 296,
     DECL_SHADER = 297,
     PROFILE = 298,
     WARNING = 299,
     DEF = 300,
     MESSAGE = 301,
     PACK_MATRIX = 302,
     RW_TEXTURE2D = 303,
     RW_TEXTURE3D = 304,
     RW_TEXTURE2DARRAY = 305,
     RW_TEXTURE3D_FLOAT4 = 306,
     TEXTURE2DMS = 307,
     TEXTURE2D = 308,
     TEXTURE3D = 309,
     IMAGE3D = 310,
     KNOWN_TYPE = 311,
     STRUCTUREDBUFFER = 312,
     RW_STRUCTUREDBUFFER = 313,
     RETURN = 314,
     BREAK = 315,
     CONTINUE = 316,
     DO = 317,
     FOR = 318,
     GOTO = 319,
     IF = 320,
     WHILE = 321,
     ELSE = 322,
     TIMES_EQUALS = 323,
     OVER_EQUALS = 324,
     PERCENT_EQUALS = 325,
     PLUS_EQUALS = 326,
     MINUS_EQUALS = 327,
     LEFT_SHIFT_EQUALS = 328,
     RIGHT_SHIFT_EQUALS = 329,
     AND_EQUALS = 330,
     XOR_EQUALS = 331,
     OR_EQUALS = 332,
     AND = 333,
     OR = 334,
     LESS_EQ = 335,
     GRTR_EQ = 336,
     LEFT_SHIFT = 337,
     RIGHT_SHIFT = 338,
     PLUS_PLUS = 339,
     MINUS_MINUS = 340,
     EQ_EQ = 341,
     NOT_EQ = 342,
     SA_MAXVERTEXCOUNT = 343,
     SA_NUMTHREADS = 344,
     CS_LAYOUT = 345
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
