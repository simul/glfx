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
     UNIFORM = 258,
     SHADER = 259,
     PROGRAM = 260,
     INTERFACE = 261,
     IDENTIFIER = 262,
     STORAGEQ = 263,
     GL_FRAGDEPTH = 264,
     SHADER_COMMAND = 265,
     SET_RASTERIZER_COMMAND = 266,
     SET_DEPTH_COMMAND = 267,
     SET_BLEND_COMMAND = 268,
     INPUT_SEMANTIC = 269,
     NUM = 270,
     INCLUDE = 271,
     SAMPLER = 272,
     FLOAT = 273,
     LAYOUT = 274,
     LINE = 275,
     TECHNIQUE = 276,
     PASS = 277,
     GROUP = 278,
     RENDER_STATE_DECL = 279,
     QUOTED_STRING = 280,
     SHADER_LINE = 281,
     SHADER_TYPE = 282,
     COMPILE_SHADER = 283,
     STRUCT = 284,
     DEFINE = 285,
     MACRO_DEFINITION = 286,
     EOL = 287,
     DECL_SHADER = 288,
     PROFILE = 289,
     CS_LAYOUT = 290,
     RW_TEXTURE3D_FLOAT4 = 291,
     TEXTURE2DMS = 292,
     KNOWN_TYPE = 293,
     RETURN = 294,
     BREAK = 295,
     CONTINUE = 296,
     DO = 297,
     FOR = 298,
     GOTO = 299,
     IF = 300,
     WHILE = 301,
     TIMES_EQUALS = 302,
     OVER_EQUALS = 303,
     PERCENT_EQUALS = 304,
     PLUS_EQUALS = 305,
     MINUS_EQUALS = 306,
     LEFT_SHIFT_EQUALS = 307,
     RIGHT_SHIFT_EQUALS = 308,
     AND_EQUALS = 309,
     XOR_EQUALS = 310,
     OR_EQUALS = 311,
     AND = 312,
     OR = 313,
     LESS_EQ = 314,
     GRTR_EQ = 315,
     LEFT_SHIFT = 316,
     RIGHT_SHIFT = 317,
     PLUS_PLUS = 318,
     MINUS_MINUS = 319,
     EQ_EQ = 320,
     NOT_EQ = 321
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
