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
     GET_DIMS = 268,
     STORAGEQ = 269,
     GL_FRAGDEPTH = 270,
     SHADER_COMMAND = 271,
     SET_RASTERIZER_COMMAND = 272,
     SET_DEPTH_COMMAND = 273,
     SET_BLEND_COMMAND = 274,
     SV_DISPATCHTHREADID = 275,
     SV_GROUPTHREADID = 276,
     SV_GROUPID = 277,
     SV_VERTEXID = 278,
     NUM = 279,
     INCLUDE = 280,
     SAMPLER = 281,
     FLOAT = 282,
     LAYOUT = 283,
     LINE = 284,
     TECHNIQUE = 285,
     PASS = 286,
     GROUP = 287,
     RENDER_STATE_DECL = 288,
     QUOTED_STRING = 289,
     SHADER_LINE = 290,
     SHADER_TYPE = 291,
     COMPILE_SHADER = 292,
     CONSTRUCT_GS_WITH_SO = 293,
     STRUCT = 294,
     PRAGMA = 295,
     DEFINE = 296,
     UNDEF = 297,
     MACRO_DEFINITION = 298,
     EOL = 299,
     DECL_SHADER = 300,
     PROFILE = 301,
     WARNING = 302,
     DEF = 303,
     MESSAGE = 304,
     PACK_MATRIX = 305,
     RW_TEXTURE2D = 306,
     RW_TEXTURE3D = 307,
     RW_TEXTURE2DARRAY = 308,
     RW_TEXTURE3D_FLOAT4 = 309,
     TEXTURE2DMS = 310,
     TEXTURE2D = 311,
     TEXTURE3D = 312,
     IMAGE3D = 313,
     KNOWN_TYPE = 314,
     STRUCTUREDBUFFER = 315,
     RW_STRUCTUREDBUFFER = 316,
     RETURN = 317,
     BREAK = 318,
     CONTINUE = 319,
     DO = 320,
     FOR = 321,
     GOTO = 322,
     IF = 323,
     WHILE = 324,
     ELSE = 325,
     TIMES_EQUALS = 326,
     OVER_EQUALS = 327,
     PERCENT_EQUALS = 328,
     PLUS_EQUALS = 329,
     MINUS_EQUALS = 330,
     LEFT_SHIFT_EQUALS = 331,
     RIGHT_SHIFT_EQUALS = 332,
     AND_EQUALS = 333,
     XOR_EQUALS = 334,
     OR_EQUALS = 335,
     AND = 336,
     OR = 337,
     LESS_EQ = 338,
     GRTR_EQ = 339,
     LEFT_SHIFT = 340,
     RIGHT_SHIFT = 341,
     PLUS_PLUS = 342,
     MINUS_MINUS = 343,
     EQ_EQ = 344,
     NOT_EQ = 345,
     SA_MAXVERTEXCOUNT = 346,
     SA_NUMTHREADS = 347,
     SHADER_PROFILE = 348
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
