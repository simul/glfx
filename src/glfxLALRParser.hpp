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
     INPUT_SEMANTIC = 270,
     NUM = 271,
     INCLUDE = 272,
     SAMPLER = 273,
     FLOAT = 274,
     LAYOUT = 275,
     LINE = 276,
     TECHNIQUE = 277,
     PASS = 278,
     GROUP = 279,
     RENDER_STATE_DECL = 280,
     QUOTED_STRING = 281,
     SHADER_LINE = 282,
     SHADER_TYPE = 283,
     COMPILE_SHADER = 284,
     STRUCT = 285,
     DEFINE = 286,
     MACRO_DEFINITION = 287,
     EOL = 288,
     DECL_SHADER = 289,
     PROFILE = 290,
     CS_LAYOUT = 291,
     RW_TEXTURE2D = 292,
     RW_TEXTURE3D = 293,
     RW_TEXTURE3D_FLOAT4 = 294,
     TEXTURE2DMS = 295,
     IMAGE3D = 296,
     KNOWN_TYPE = 297,
     RETURN = 298,
     BREAK = 299,
     CONTINUE = 300,
     DO = 301,
     FOR = 302,
     GOTO = 303,
     IF = 304,
     WHILE = 305,
     ELSE = 306,
     TIMES_EQUALS = 307,
     OVER_EQUALS = 308,
     PERCENT_EQUALS = 309,
     PLUS_EQUALS = 310,
     MINUS_EQUALS = 311,
     LEFT_SHIFT_EQUALS = 312,
     RIGHT_SHIFT_EQUALS = 313,
     AND_EQUALS = 314,
     XOR_EQUALS = 315,
     OR_EQUALS = 316,
     AND = 317,
     OR = 318,
     LESS_EQ = 319,
     GRTR_EQ = 320,
     LEFT_SHIFT = 321,
     RIGHT_SHIFT = 322,
     PLUS_PLUS = 323,
     MINUS_MINUS = 324,
     EQ_EQ = 325,
     NOT_EQ = 326
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
