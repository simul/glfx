/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         glfxparse
#define yylex           glfxlex
#define yyerror         glfxerror
#define yylval          glfxlval
#define yychar          glfxchar
#define yydebug         glfxdebug
#define yynerrs         glfxnerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 4 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"

	//#define YYFPRINTF glfxprintf
	#define YYDEBUG 1
    #include <iostream>
    #include <map>
    #include <string>
    #include <vector>
    #include <sstream>
    
    #include "glfxParser.h"
    #include "glfxClasses.h"

    using namespace std;
    using namespace glfxParser;
    
    #ifdef _MSC_VER
		// MS's C++ compiler is more strict than gcc
    
		// bison related
		// Disable the warning about default being present but no other cases in switch
		#pragma warning( disable:4065 )

		// No unistd.h (for flex)
		#define YY_NO_UNISTD_H
		#define YYERROR_VERBOSE
    #endif
    #include "glfxScanner.h"
    #include "glfxEffect.h"

    static void errSyn(const char *e);
    static void errSem(const string& str, int line=-1);
	RasterizerState buildRasterizerState;
	Struct buildStruct;
	BlendState buildBlendState;
	DepthStencilState buildDepthStencilState;
	SamplerState buildSamplerState;
	static int last_linenumber=0;
	static int current_filenumber=0;
	static int global_linenumber=0;
	std::string currentCsLayout;
	int last_recorded_linenum	=0;
	int global_linenum			=0;
	int filenum					=0;
	#pragma optimize("",off)
	bool is_equal(const string& a, const char * b)
	{
		size_t sz = a.size();
		if (strlen(b) != sz)
			return false;
		for (size_t i = 0; i < sz; ++i)
			if (tolower(a[i]) != tolower(b[i]))
				return false;
		return true;
	}
	bool toBool(const string &str)
	{
		if(is_equal(str,"TRUE"))
			return true;
		else if(is_equal(str,"FALSE"))
			return false;
		else errSem("Expected boolean.");
		return false;
	}
	void WriteLineNumber(std::ostringstream &str,int fileno,int lineno)
	{
		str<<"#line "<<lineno<<" "<<fileno<<endl;
	}
	void WriteLineNumber(std::ostringstream &str,int lineno)
	{
		WriteLineNumber(str,current_filenumber,lineno);//.c_str()<<"\""<<endl;
	}
	static bool write_line_number_next=false;
	static void Skip()
	{
		write_line_number_next=true;
	}
	static string GetLayoutForTemplateType(string s)
	{
		if(s==string("vec4"))
		{
			return "";
		}
		return "";
	}

/* Line 371 of yacc.c  */
#line 161 "src/glfxLALRParser.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "glfxLALRParser.hpp".  */
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
     RW_TEXTURE3D_FLOAT4 = 292,
     TEXTURE2DMS = 293,
     IMAGE3D = 294,
     KNOWN_TYPE = 295,
     RETURN = 296,
     BREAK = 297,
     CONTINUE = 298,
     DO = 299,
     FOR = 300,
     GOTO = 301,
     IF = 302,
     WHILE = 303,
     ELSE = 304,
     TIMES_EQUALS = 305,
     OVER_EQUALS = 306,
     PERCENT_EQUALS = 307,
     PLUS_EQUALS = 308,
     MINUS_EQUALS = 309,
     LEFT_SHIFT_EQUALS = 310,
     RIGHT_SHIFT_EQUALS = 311,
     AND_EQUALS = 312,
     XOR_EQUALS = 313,
     OR_EQUALS = 314,
     AND = 315,
     OR = 316,
     LESS_EQ = 317,
     GRTR_EQ = 318,
     LEFT_SHIFT = 319,
     RIGHT_SHIFT = 320,
     PLUS_PLUS = 321,
     MINUS_MINUS = 322,
     EQ_EQ = 323,
     NOT_EQ = 324
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 296 "src/glfxLALRParser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   496

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  214
/* YYNRULES -- Number of states.  */
#define YYNSTATES  436

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,     2,     2,     2,    90,    85,     2,
      74,    75,    88,    86,    71,    87,    93,    89,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    79,    70,
      77,    76,    78,    82,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    80,     2,    81,    84,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,    83,    73,    91,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    24,    29,
      31,    36,    39,    43,    47,    51,    58,    63,    70,    76,
      81,    91,    99,   107,   113,   117,   120,   122,   124,   128,
     129,   137,   141,   145,   149,   151,   153,   155,   161,   165,
     167,   169,   170,   171,   172,   176,   177,   180,   181,   185,
     187,   188,   192,   195,   196,   200,   202,   203,   206,   209,
     212,   213,   215,   218,   220,   226,   228,   231,   233,   236,
     238,   249,   255,   263,   273,   278,   284,   286,   295,   300,
     305,   306,   309,   310,   314,   316,   319,   321,   322,   326,
     329,   331,   335,   337,   341,   343,   347,   352,   356,   360,
     363,   365,   368,   370,   376,   384,   390,   398,   408,   412,
     415,   418,   422,   424,   426,   428,   429,   431,   432,   436,
     438,   442,   444,   448,   450,   452,   454,   456,   458,   460,
     462,   464,   466,   468,   470,   472,   478,   480,   484,   486,
     490,   492,   496,   498,   502,   504,   508,   510,   514,   518,
     520,   524,   528,   532,   536,   538,   542,   546,   548,   552,
     556,   558,   562,   566,   570,   572,   574,   577,   580,   583,
     585,   587,   589,   591,   593,   595,   597,   602,   607,   611,
     615,   618,   621,   625,   627,   629,   633,   638,   640,   644,
     646,   648,   652,   654,   656,   659,   662,   663,   668,   671,
     672,   675,   677,   681,   682,   685,   687,   692,   694,   697,
     701,   702,   704,   706,   708
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    95,    96,    -1,    -1,     7,   110,     8,
     114,    70,   112,    -1,    33,    -1,    97,    -1,     4,   100,
     101,     8,    70,    -1,     4,     8,     8,    70,    -1,    36,
      -1,    20,   103,     8,    70,    -1,    20,   104,    -1,    37,
       8,    70,    -1,    37,     8,    71,    -1,    31,    32,    33,
      -1,    30,     8,    72,   172,    73,    70,    -1,    25,     8,
     173,    70,    -1,    35,     8,    74,    16,    75,    70,    -1,
      34,     8,    76,   130,    70,    -1,    20,   110,   102,   112,
      -1,    99,     8,     8,    74,   116,    75,   115,   113,   112,
      -1,     6,   110,     8,    72,   125,    73,   112,    -1,    22,
     110,     8,    72,   122,    73,   112,    -1,    21,   110,    16,
      16,   112,    -1,    21,    16,    16,    -1,     5,   111,    -1,
      38,    -1,    39,    -1,    77,     8,    78,    -1,    -1,    74,
      16,    71,    16,    71,    16,    75,    -1,    74,   107,    75,
      -1,    74,   105,    75,    -1,   105,    71,   106,    -1,   106,
      -1,   108,    -1,     8,    -1,   108,    71,   108,    71,   108,
      -1,     8,    76,   109,    -1,     8,    -1,    16,    -1,    -1,
      -1,    -1,    72,   135,    73,    -1,    -1,    79,     8,    -1,
      -1,   116,    71,   117,    -1,   117,    -1,    -1,   119,   118,
     121,    -1,    80,    81,    -1,    -1,   120,     8,     8,    -1,
       9,    -1,    -1,    79,    16,    -1,    79,    15,    -1,    79,
       8,    -1,    -1,   123,    -1,   123,   124,    -1,   124,    -1,
      23,     8,    72,   125,    73,    -1,   126,    -1,   126,   129,
      -1,   129,    -1,   126,   128,    -1,   128,    -1,     8,    74,
      19,    71,    19,    71,    19,    71,    19,    75,    -1,    12,
      74,     8,    75,    70,    -1,    13,    74,     8,    71,    16,
      75,    70,    -1,    14,    74,     8,    71,   127,    71,    16,
      75,    70,    -1,   131,    76,   132,    70,    -1,    11,    74,
     130,    75,    70,    -1,     8,    -1,    29,    74,     8,    71,
       8,    74,    75,    75,    -1,    28,    74,    16,    75,    -1,
       8,    74,    75,   133,    -1,    -1,    79,   134,    -1,    -1,
     134,    71,   168,    -1,   168,    -1,   135,   141,    -1,   141,
      -1,    -1,    21,    16,    16,    -1,   179,   138,    -1,   139,
      -1,   138,    71,   139,    -1,   140,    -1,   140,    76,   164,
      -1,     8,    -1,    74,   140,    75,    -1,   140,    80,    16,
      81,    -1,   140,    80,    81,    -1,   140,    74,    75,    -1,
     145,    70,    -1,    70,    -1,   137,    70,    -1,   144,    -1,
      47,    74,   145,    75,   141,    -1,    47,    74,   145,    75,
     141,    49,   141,    -1,    48,    74,   145,    75,   141,    -1,
      44,   141,    48,    74,   145,    75,    70,    -1,    45,    74,
     142,    70,   143,    70,   143,    75,   141,    -1,    46,     8,
      70,    -1,    43,    70,    -1,    42,    70,    -1,    41,   143,
      70,    -1,   136,    -1,   145,    -1,   137,    -1,    -1,   145,
      -1,    -1,    72,   135,    73,    -1,   146,    -1,   145,    71,
     146,    -1,   148,    -1,   160,   147,   146,    -1,    76,    -1,
      50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,    -1,
      55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,    -1,
     149,    -1,   149,    82,   145,    79,   148,    -1,   150,    -1,
     149,    61,   150,    -1,   151,    -1,   150,    60,   151,    -1,
     152,    -1,   151,    83,   152,    -1,   153,    -1,   152,    84,
     153,    -1,   154,    -1,   153,    85,   154,    -1,   155,    -1,
     154,    68,   155,    -1,   154,    69,   155,    -1,   156,    -1,
     155,    77,   156,    -1,   155,    78,   156,    -1,   155,    62,
     156,    -1,   155,    63,   156,    -1,   157,    -1,   156,    64,
     157,    -1,   156,    65,   157,    -1,   158,    -1,   157,    86,
     158,    -1,   157,    87,   158,    -1,   159,    -1,   158,    88,
     159,    -1,   158,    89,   159,    -1,   158,    90,   159,    -1,
     160,    -1,   162,    -1,    66,   160,    -1,    67,   160,    -1,
     161,   159,    -1,    85,    -1,    88,    -1,    86,    -1,    87,
      -1,    91,    -1,    92,    -1,   166,    -1,   162,    80,   145,
      81,    -1,   162,    74,   163,    75,    -1,   162,    74,    75,
      -1,   162,    93,     8,    -1,   162,    66,    -1,   162,    67,
      -1,   163,    71,   146,    -1,   146,    -1,   146,    -1,    72,
     165,    73,    -1,    72,   165,    71,    73,    -1,   164,    -1,
     165,    71,   164,    -1,     8,    -1,   167,    -1,    74,   145,
      75,    -1,    16,    -1,    19,    -1,     9,   169,    -1,    10,
     169,    -1,    -1,     8,     8,   171,    70,    -1,    79,     8,
      -1,    -1,   172,   170,    -1,   170,    -1,    72,   174,    73,
      -1,    -1,   174,   175,    -1,   175,    -1,   176,    76,   178,
      70,    -1,    98,    -1,     8,   177,    -1,    80,    16,    81,
      -1,    -1,     8,    -1,    16,    -1,    19,    -1,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   103,   107,   111,   114,   117,   129,   135,
     139,   147,   153,   159,   165,   168,   186,   226,   236,   253,
     260,   325,   330,   334,   341,   347,   352,   352,   357,   363,
     367,   378,   382,   387,   391,   395,   399,   403,   408,   413,
     417,   422,   428,   434,   438,   445,   450,   454,   456,   468,
     480,   484,   515,   520,   524,   533,   538,   541,   546,   551,
     557,   562,   569,   580,   594,   601,   607,   617,   630,   638,
     646,   655,   659,   664,   671,   720,   781,   788,   814,   825,
     832,   835,   840,   844,   849,   853,   860,   866,   870,   883,
     888,   892,   896,   900,   904,   908,   912,   916,   920,   924,
     929,   933,   937,   941,   945,   949,   953,   957,   961,   965,
     969,   973,   979,   984,   988,   993,   995,  1000,  1004,  1009,
    1013,  1017,  1021,  1025,  1029,  1030,  1031,  1032,  1033,  1034,
    1035,  1036,  1037,  1038,  1042,  1046,  1051,  1055,  1059,  1063,
    1067,  1071,  1075,  1079,  1083,  1087,  1092,  1096,  1100,  1104,
    1108,  1112,  1116,  1120,  1124,  1128,  1132,  1136,  1140,  1144,
    1148,  1152,  1156,  1160,  1164,  1168,  1172,  1176,  1180,  1184,
    1184,  1184,  1184,  1184,  1184,  1188,  1192,  1196,  1200,  1204,
    1208,  1212,  1216,  1220,  1224,  1229,  1236,  1243,  1247,  1254,
    1258,  1262,  1266,  1270,  1274,  1282,  1291,  1294,  1306,  1311,
    1314,  1319,  1323,  1327,  1330,  1335,  1339,  1448,  1453,  1459,
    1465,  1468,  1473,  1478,  1483
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHITESPACE", "UNIFORM", "SHADER",
  "PROGRAM", "INTERFACE", "IDENTIFIER", "STORAGEQ", "GL_FRAGDEPTH",
  "SHADER_COMMAND", "SET_RASTERIZER_COMMAND", "SET_DEPTH_COMMAND",
  "SET_BLEND_COMMAND", "INPUT_SEMANTIC", "NUM", "INCLUDE", "SAMPLER",
  "FLOAT", "LAYOUT", "LINE", "TECHNIQUE", "PASS", "GROUP",
  "RENDER_STATE_DECL", "QUOTED_STRING", "SHADER_LINE", "SHADER_TYPE",
  "COMPILE_SHADER", "STRUCT", "DEFINE", "MACRO_DEFINITION", "EOL",
  "DECL_SHADER", "PROFILE", "CS_LAYOUT", "RW_TEXTURE3D_FLOAT4",
  "TEXTURE2DMS", "IMAGE3D", "KNOWN_TYPE", "RETURN", "BREAK", "CONTINUE",
  "DO", "FOR", "GOTO", "IF", "WHILE", "ELSE", "TIMES_EQUALS",
  "OVER_EQUALS", "PERCENT_EQUALS", "PLUS_EQUALS", "MINUS_EQUALS",
  "LEFT_SHIFT_EQUALS", "RIGHT_SHIFT_EQUALS", "AND_EQUALS", "XOR_EQUALS",
  "OR_EQUALS", "AND", "OR", "LESS_EQ", "GRTR_EQ", "LEFT_SHIFT",
  "RIGHT_SHIFT", "PLUS_PLUS", "MINUS_MINUS", "EQ_EQ", "NOT_EQ", "';'",
  "','", "'{'", "'}'", "'('", "')'", "'='", "'<'", "'>'", "':'", "'['",
  "']'", "'?'", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'~'", "'!'", "'.'", "$accept", "prog", "tok", "line_statement",
  "ignore_line_statement", "shader_and_layout", "texture_type",
  "optional_templateval", "layout_params", "cs_layout_spec",
  "normal_layout_spec", "tx_layout", "layout_s", "cs_layout", "layout_el",
  "layout_def", "lex_fx", "shader_fx", "lex_passthrough",
  "function_content", "read_block", "optional_return_semantic",
  "param_declaration_list", "param_declaration", "opt_sq", "param",
  "opt_storage", "location", "tech_def", "pass_list", "pass_def",
  "prog_def", "shaders_list", "vec4", "shader_fn", "shader_def",
  "shader_compile", "shader_lvalue", "shader_rvalue", "shader_layout",
  "shader_layout_list", "statement_list", "line_statement_in_shader",
  "declaration", "init_declarator_list", "init_declarator", "declarator",
  "statement", "for_init_statement", "optional_expression",
  "compound_statement", "expression", "assignment_exp",
  "assignment_operator", "conditional_exp", "logical_or_exp",
  "logical_and_exp", "inclusive_or_exp", "exclusive_or_exp", "and_exp",
  "equality_exp", "relational_exp", "shift_expression", "additive_exp",
  "mult_exp", "cast_exp", "unary_exp", "unary_operator", "postfix_exp",
  "argument_exp_list", "initializer", "initializer_list", "primary_exp",
  "const", "layout", "read_parenthesis", "struct_member",
  "optional_semantic", "struct_members", "optional_render_state_list",
  "render_state_list", "render_state_command", "render_state_identifier",
  "optional_index", "render_state_rvalue", "type_spec", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
      59,    44,   123,   125,    40,    41,    61,    60,    62,    58,
      91,    93,    63,   124,    94,    38,    43,    45,    42,    47,
      37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    97,    98,    99,   100,   100,   101,   101,
     102,   103,   104,   105,   105,   106,   106,   107,   108,   109,
     109,   110,   111,   112,   113,   114,   115,   115,   116,   116,
     116,   117,   118,   118,   119,   120,   120,   121,   121,   121,
     121,   122,   123,   123,   124,   125,   126,   126,   126,   126,
     127,   128,   128,   128,   129,   129,   130,   130,   131,   132,
     132,   133,   133,   134,   134,   135,   135,   135,   136,   137,
     138,   138,   139,   139,   140,   140,   140,   140,   140,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   142,   142,   142,   143,   143,   144,   145,
     145,   146,   146,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   148,   148,   149,   149,   150,   150,
     151,   151,   152,   152,   153,   153,   154,   154,   154,   155,
     155,   155,   155,   155,   156,   156,   156,   157,   157,   157,
     158,   158,   158,   158,   159,   160,   160,   160,   160,   161,
     161,   161,   161,   161,   161,   162,   162,   162,   162,   162,
     162,   162,   163,   163,   164,   164,   164,   165,   165,   166,
     166,   166,   167,   167,   168,   168,   169,   170,   171,   171,
     172,   172,   173,   173,   174,   174,   175,   175,   176,   177,
     177,   178,   178,   178,   179
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     5,     4,     1,
       4,     2,     3,     3,     3,     6,     4,     6,     5,     4,
       9,     7,     7,     5,     3,     2,     1,     1,     3,     0,
       7,     3,     3,     3,     1,     1,     1,     5,     3,     1,
       1,     0,     0,     0,     3,     0,     2,     0,     3,     1,
       0,     3,     2,     0,     3,     1,     0,     2,     2,     2,
       0,     1,     2,     1,     5,     1,     2,     1,     2,     1,
      10,     5,     7,     9,     4,     5,     1,     8,     4,     4,
       0,     2,     0,     3,     1,     2,     1,     0,     3,     2,
       1,     3,     1,     3,     1,     3,     4,     3,     3,     2,
       1,     2,     1,     5,     7,     5,     7,     9,     3,     2,
       2,     3,     1,     1,     1,     0,     1,     0,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     3,     1,
       3,     3,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     1,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     3,     3,
       2,     2,     3,     1,     1,     3,     4,     1,     3,     1,
       1,     3,     1,     1,     2,     2,     0,     4,     2,     0,
       2,     1,     3,     0,     2,     1,     4,     1,     2,     3,
       0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,    42,    41,    41,     0,    41,    41,
       0,     0,     0,     5,     0,     0,     9,     0,     2,     6,
       0,     0,    26,    27,    29,    25,     0,     0,     0,     0,
      11,     0,     0,     0,   203,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    45,    36,     0,    34,     0,
      35,     0,     0,    43,     0,     0,     0,     0,     0,    14,
       0,     0,    12,    13,     0,     8,     0,     0,     0,     0,
       0,     0,    32,    31,     0,    10,     0,    19,    43,     0,
     210,     0,   207,     0,   205,     0,    16,     0,   201,     0,
      76,     0,     0,     0,    50,    28,     7,     0,     0,     0,
       0,     0,     0,    65,    69,    67,     0,    43,    39,    40,
      38,    33,    35,     0,     0,     0,    23,     0,     0,    61,
      63,     0,   208,     0,   202,   204,     0,   199,     0,   200,
       0,    18,     0,    55,     0,    49,    53,     0,     0,     0,
       0,     0,     0,    43,    68,    66,    80,     4,     0,     0,
       0,    43,    62,     0,    24,   211,   212,   213,     0,     0,
       0,    15,     0,    17,    56,    47,     0,    60,     0,     0,
       0,     0,     0,     0,    21,     0,     0,    37,     0,     0,
      22,   209,   206,   198,   197,     0,    48,     0,     0,    52,
       0,    51,    54,     0,     0,     0,     0,    78,     0,    74,
       0,     0,     0,    46,    87,    43,    59,    58,    57,    75,
      71,     0,     0,     0,    82,    30,    64,     0,   189,   192,
     193,     0,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,    87,     0,   169,   171,   172,   170,   173,
     174,     0,   112,     0,    86,   102,     0,   119,   121,   134,
     136,   138,   140,   142,   144,   146,   149,   154,   157,   160,
     164,     0,   165,   175,   190,     0,    20,     0,     0,     0,
       0,    79,     0,     0,   189,     0,   116,   110,   109,     0,
     115,     0,     0,     0,   166,   167,     0,     0,    44,    85,
     101,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   123,     0,   168,   164,   180,   181,     0,     0,
       0,    94,     0,    89,    90,    92,    72,     0,     0,   196,
     196,    81,    84,    77,    88,   111,     0,   114,     0,   113,
     108,     0,     0,   118,   191,   120,   137,     0,   139,   141,
     143,   145,   147,   148,   152,   153,   150,   151,   155,   156,
     158,   159,   161,   162,   163,   122,   178,   183,     0,     0,
     179,     0,     0,     0,     0,     0,     0,     0,   194,   195,
       0,     0,   117,     0,     0,     0,     0,   177,   176,    95,
      91,    98,     0,   184,    93,     0,    97,     0,    73,    83,
       0,     0,   103,   105,   135,   182,   187,     0,    96,     0,
       0,   117,     0,     0,   185,     0,   106,     0,   104,   186,
     188,     0,     0,     0,   107,    70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    82,    20,    24,    43,    53,    29,
      30,    47,    48,    49,    50,   110,    26,    25,    77,   205,
      69,   188,   134,   135,   167,   136,   137,   191,   118,   119,
     120,   102,   103,   213,   104,   105,    92,   106,   176,   271,
     341,   241,   242,   243,   333,   334,   335,   244,   348,   275,
     245,   246,   247,   323,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   378,
     404,   417,   263,   264,   342,   388,    88,   160,    89,    57,
      83,    84,    85,   122,   158,   265
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -388
static const yytype_int16 yypact[] =
{
    -388,   417,  -388,     3,  -388,  -388,  -388,   -36,  -388,  -388,
      18,    39,    22,  -388,    65,    68,  -388,   106,  -388,  -388,
     114,   129,  -388,  -388,    35,  -388,   149,   165,   168,   170,
    -388,   112,   172,   184,   134,   164,   206,   166,   167,    59,
     232,   176,   240,   244,   182,  -388,   179,   -50,  -388,   185,
     186,   189,   245,  -388,   250,   195,    12,   200,   263,  -388,
       1,   256,  -388,  -388,   199,  -388,   196,   205,   139,   207,
      36,   168,  -388,  -388,   268,  -388,   216,  -388,  -388,   265,
     209,   274,  -388,    -4,  -388,   215,  -388,   284,  -388,    -3,
    -388,   219,   225,   223,   146,  -388,  -388,   222,   226,   227,
     228,   231,   233,   139,  -388,  -388,   234,  -388,  -388,  -388,
    -388,  -388,  -388,   179,   241,   283,  -388,   300,   242,   265,
    -388,   297,  -388,   298,  -388,  -388,    16,   238,   246,  -388,
     310,  -388,   251,  -388,   -48,  -388,   252,   312,     1,   318,
     323,   325,   320,  -388,  -388,  -388,   326,  -388,   268,   266,
     267,  -388,  -388,   257,  -388,  -388,  -388,  -388,   270,   333,
     272,  -388,   276,  -388,   339,   275,   279,   277,   341,   280,
     282,   288,   291,   292,  -388,   294,   281,  -388,   355,   139,
    -388,  -388,  -388,  -388,  -388,   364,  -388,   365,   302,  -388,
      95,  -388,  -388,   305,   306,   363,   372,  -388,   307,  -388,
     309,   308,   313,  -388,   237,  -388,  -388,  -388,  -388,  -388,
    -388,   314,   316,   315,   321,  -388,  -388,   317,   380,  -388,
    -388,   375,   327,   334,   335,   237,   332,   387,   336,   337,
     327,   327,  -388,   237,   327,  -388,  -388,  -388,  -388,  -388,
    -388,   117,  -388,   350,  -388,  -388,   124,  -388,  -388,   -51,
     347,   343,   348,   340,   131,   -13,   162,   142,    92,  -388,
      90,   327,   -21,  -388,  -388,    -7,  -388,   361,   416,   420,
     221,  -388,   366,   424,  -388,   373,   374,  -388,  -388,   396,
     342,   376,   327,   327,  -388,  -388,   177,    26,  -388,  -388,
    -388,  -388,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,   327,   327,   327,   327,   327,   327,   327,   327,
     327,   327,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
    -388,  -388,  -388,   327,  -388,  -388,  -388,  -388,   278,   327,
     441,  -388,    -7,   384,  -388,    52,  -388,   385,   382,  -388,
    -388,   388,  -388,  -388,  -388,  -388,   386,  -388,   391,   374,
    -388,    56,    64,  -388,  -388,  -388,   347,    29,   343,   348,
     340,   131,   -13,   -13,   162,   162,   162,   162,   142,   142,
      92,    92,  -388,  -388,  -388,  -388,  -388,  -388,    99,   -53,
    -388,    41,    -7,   383,   311,   -10,   443,   393,  -388,  -388,
     221,   327,   327,   237,   237,   327,   327,  -388,  -388,  -388,
    -388,  -388,   311,  -388,  -388,   389,  -388,   394,  -388,  -388,
     104,   397,   415,  -388,  -388,  -388,  -388,    -5,  -388,   447,
     398,   327,   237,    32,  -388,   400,  -388,   399,  -388,  -388,
    -388,   450,   237,   401,  -388,  -388
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,  -388,
    -388,  -388,   402,  -388,   -52,  -388,   204,  -388,   -49,  -388,
    -388,  -388,  -388,   319,  -388,  -388,  -388,  -388,  -388,  -388,
     353,   296,  -388,  -388,   377,   378,   344,  -388,  -388,  -388,
    -388,   253,  -388,   197,  -388,    96,   147,  -225,  -388,  -384,
    -388,  -220,  -289,  -388,    89,  -388,   192,   193,   191,   194,
     198,   -67,   -87,   -71,   -70,  -254,  -218,  -388,  -388,  -388,
    -387,  -388,  -388,  -388,   100,   152,   404,  -388,  -388,  -388,
    -388,   406,  -388,  -388,  -388,  -388
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -215
static const yytype_int16 yytable[] =
{
     279,   331,   276,   355,    80,    87,   405,   324,   411,    90,
     293,    21,   284,   285,   287,   416,   289,    81,   292,   112,
      80,    71,   114,   164,   155,    72,    34,   165,   398,   116,
      91,   294,   156,    81,   375,   157,   430,   427,    28,   377,
     274,    22,    23,   325,   108,   326,   327,    35,   219,   301,
     302,   220,   109,   328,    36,   372,   373,   374,   147,   329,
     349,   289,   351,   352,   303,   304,   423,   332,   424,   124,
     128,   406,   330,    37,   357,   325,    38,   325,   325,   325,
     325,   325,   325,   325,   325,   325,   325,   325,   325,   325,
     325,   325,   325,   325,   174,   403,   177,   292,   230,   231,
     292,   354,   180,   206,   402,   429,   234,   415,   395,   379,
     207,   208,    42,   403,    39,   383,   399,   235,   236,   237,
     238,   385,    40,   239,   240,   218,   383,   292,   384,    62,
      63,   393,   385,   219,   403,   292,   220,    41,   221,   394,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
      97,    98,    99,   100,   -56,   133,   266,    44,   222,   223,
     224,   225,   226,   227,   228,   229,   322,   101,   412,   413,
     396,   410,   276,    45,   397,   292,    46,   325,    51,   420,
     309,   310,   311,   230,   231,   218,    52,   232,    54,   233,
     288,   234,    55,   219,   291,   292,   220,   428,   221,   299,
     300,   276,   235,   236,   237,   238,    56,   434,   239,   240,
      27,    31,    32,    33,   364,   365,   366,   367,   222,   223,
     224,   225,   226,   227,   228,   229,   305,   306,   307,   308,
     339,   340,   362,   363,   368,   369,    58,   370,   371,    59,
      64,    61,    60,   230,   231,   218,    65,   232,    66,   233,
     353,   234,    67,   219,    68,    70,   220,    74,   221,    75,
      73,    76,   235,   236,   237,   238,    78,    79,   239,   240,
      86,    87,    93,    94,    95,    96,   113,   107,   222,   223,
     224,   225,   226,   227,   228,   229,   274,   115,   117,   121,
     123,   126,   127,   130,   219,   131,   138,   220,   132,   149,
     139,   140,   141,   230,   231,   142,   143,   232,   150,   233,
     146,   234,   148,   153,   154,   151,   161,   159,   162,   274,
     168,   163,   235,   236,   237,   238,   170,   219,   239,   240,
     220,   171,   166,   172,   175,   274,   173,   178,   181,   179,
     182,   183,   184,   219,   230,   231,   220,   185,   133,   192,
     218,   199,   234,   376,   187,   193,   190,   194,   219,   195,
     189,   220,   196,   235,   236,   237,   238,   197,   198,   239,
     240,   200,   202,   203,   204,   209,   210,   230,   231,   211,
     212,   216,   214,   402,   215,   234,   269,   217,  -214,   267,
     268,   273,   272,   230,   231,   281,   235,   236,   237,   238,
     270,   234,   239,   240,   277,   278,   280,   295,   230,   231,
     282,   283,   235,   236,   237,   238,   234,     2,   239,   240,
     290,     3,     4,     5,     6,   298,   296,   235,   236,   237,
     238,   336,   297,   239,   240,   337,   338,     7,     8,     9,
     344,   343,    10,   345,   346,   292,   350,    11,    12,   380,
      13,    14,    15,    16,    17,   382,   386,   387,   401,   390,
     391,   392,   407,   408,   422,   419,   425,   421,   426,   433,
     418,   431,   152,   111,   432,   201,   435,   347,   400,   381,
     144,   145,   169,   186,   414,   356,   286,   359,   358,   125,
     409,   360,   389,   129,     0,     0,   361
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-388)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     225,     8,   222,   292,     8,     8,    16,   261,   392,     8,
      61,     8,   230,   231,   234,   402,   241,    21,    71,    71,
       8,    71,    74,    71,     8,    75,     8,    75,    81,    78,
      29,    82,    16,    21,   323,    19,   423,   421,    74,   328,
       8,    38,    39,   261,     8,    66,    67,     8,    16,    62,
      63,    19,    16,    74,    32,   309,   310,   311,   107,    80,
     280,   286,   282,   283,    77,    78,    71,    74,    73,    73,
      73,    81,    93,     8,   294,   293,     8,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   143,   384,   148,    71,    66,    67,
      71,    75,   151,     8,    72,    73,    74,   396,    79,   329,
      15,    16,    77,   402,     8,    74,    75,    85,    86,    87,
      88,    80,     8,    91,    92,     8,    74,    71,    76,    70,
      71,    75,    80,    16,   423,    71,    19,     8,    21,    75,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      11,    12,    13,    14,     8,     9,   205,     8,    41,    42,
      43,    44,    45,    46,    47,    48,    76,    28,   393,   394,
      71,   391,   392,     8,    75,    71,     8,   395,     8,    75,
      88,    89,    90,    66,    67,     8,    74,    70,    16,    72,
      73,    74,     8,    16,    70,    71,    19,   422,    21,    68,
      69,   421,    85,    86,    87,    88,    72,   432,    91,    92,
       6,     7,     8,     9,   301,   302,   303,   304,    41,    42,
      43,    44,    45,    46,    47,    48,    64,    65,    86,    87,
       9,    10,   299,   300,   305,   306,    72,   307,   308,    33,
       8,    74,    76,    66,    67,     8,    70,    70,     8,    72,
      73,    74,     8,    16,    72,    76,    19,    71,    21,    70,
      75,    16,    85,    86,    87,    88,    16,    72,    91,    92,
      70,     8,    16,    74,    78,    70,     8,    70,    41,    42,
      43,    44,    45,    46,    47,    48,     8,    71,    23,    80,
      16,    76,     8,    74,    16,    70,    74,    19,    75,    16,
      74,    74,    74,    66,    67,    74,    73,    70,     8,    72,
      76,    74,    71,    16,    16,    73,    70,    79,     8,     8,
       8,    70,    85,    86,    87,    88,     8,    16,    91,    92,
      19,     8,    80,     8,     8,     8,    16,    71,    81,    72,
      70,     8,    70,    16,    66,    67,    19,    71,     9,     8,
       8,    70,    74,    75,    79,    75,    79,    75,    16,    71,
      81,    19,    71,    85,    86,    87,    88,    75,    74,    91,
      92,    16,     8,     8,    72,    70,    70,    66,    67,    16,
       8,    73,    75,    72,    75,    74,    71,    74,     8,    75,
      74,    16,    75,    66,    67,     8,    85,    86,    87,    88,
      79,    74,    91,    92,    70,    70,    74,    60,    66,    67,
      74,    74,    85,    86,    87,    88,    74,     0,    91,    92,
      70,     4,     5,     6,     7,    85,    83,    85,    86,    87,
      88,    70,    84,    91,    92,    19,    16,    20,    21,    22,
      16,    75,    25,    70,    48,    71,    70,    30,    31,     8,
      33,    34,    35,    36,    37,    71,    71,    75,    75,    71,
      74,    70,    19,    70,    49,    71,    19,    70,    70,    19,
      81,    71,   119,    71,    75,   179,    75,   280,   382,   332,
     103,   103,   138,   164,   395,   293,   233,   296,   295,    83,
     390,   297,   340,    89,    -1,    -1,   298
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    95,     0,     4,     5,     6,     7,    20,    21,    22,
      25,    30,    31,    33,    34,    35,    36,    37,    96,    97,
      99,     8,    38,    39,   100,   111,   110,   110,    74,   103,
     104,   110,   110,   110,     8,     8,    32,     8,     8,     8,
       8,     8,    77,   101,     8,     8,     8,   105,   106,   107,
     108,     8,    74,   102,    16,     8,    72,   173,    72,    33,
      76,    74,    70,    71,     8,    70,     8,     8,    72,   114,
      76,    71,    75,    75,    71,    70,    16,   112,    16,    72,
       8,    21,    98,   174,   175,   176,    70,     8,   170,   172,
       8,    29,   130,    16,    74,    78,    70,    11,    12,    13,
      14,    28,   125,   126,   128,   129,   131,    70,     8,    16,
     109,   106,   108,     8,   108,    71,   112,    23,   122,   123,
     124,    80,   177,    16,    73,   175,    76,     8,    73,   170,
      74,    70,    75,     9,   116,   117,   119,   120,    74,    74,
      74,    74,    74,    73,   128,   129,    76,   112,    71,    16,
       8,    73,   124,    16,    16,     8,    16,    19,   178,    79,
     171,    70,     8,    70,    71,    75,    80,   118,     8,   130,
       8,     8,     8,    16,   112,     8,   132,   108,    71,    72,
     112,    81,    70,     8,    70,    71,   117,    79,   115,    81,
      79,   121,     8,    75,    75,    71,    71,    75,    74,    70,
      16,   125,     8,     8,    72,   113,     8,    15,    16,    70,
      70,    16,     8,   127,    75,    75,    73,    74,     8,    16,
      19,    21,    41,    42,    43,    44,    45,    46,    47,    48,
      66,    67,    70,    72,    74,    85,    86,    87,    88,    91,
      92,   135,   136,   137,   141,   144,   145,   146,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   166,   167,   179,   112,    75,    74,    71,
      79,   133,    75,    16,     8,   143,   145,    70,    70,   141,
      74,     8,    74,    74,   160,   160,   135,   145,    73,   141,
      70,    70,    71,    61,    82,    60,    83,    84,    85,    68,
      69,    62,    63,    77,    78,    64,    65,    86,    87,    88,
      89,    90,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    76,   147,   159,   160,    66,    67,    74,    80,
      93,     8,    74,   138,   139,   140,    70,    19,    16,     9,
      10,   134,   168,    75,    16,    70,    48,   137,   142,   145,
      70,   145,   145,    73,    75,   146,   150,   145,   151,   152,
     153,   154,   155,   155,   156,   156,   156,   156,   157,   157,
     158,   158,   159,   159,   159,   146,    75,   146,   163,   145,
       8,   140,    71,    74,    76,    80,    71,    75,   169,   169,
      71,    74,    70,    75,    75,    79,    71,    75,    81,    75,
     139,    75,    72,   146,   164,    16,    81,    19,    70,   168,
     145,   143,   141,   141,   148,   146,   164,   165,    81,    71,
      75,    70,    49,    71,    73,    19,    70,   143,   141,    73,
     164,    71,    75,    19,   141,    75
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1792 of yacc.c  */
#line 103 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 108 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 112 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 115 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 118 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		bool compute_only=((yyvsp[(2) - (5)]).strs[0]==string("image3D"));

		ostringstream decl;
		if(compute_only)
			decl<<"#ifdef USE_GL_COMPUTE_SHADER\n";
		decl<<GetLayoutForTemplateType((yyvsp[(3) - (5)]).strs[0])<<" uniform "<<(yyvsp[(2) - (5)]).strs[0]<<" "<<(yyvsp[(4) - (5)]).strs[0]<<";";
		if(compute_only)
			decl<<"\n#endif\n";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 130 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 136 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 140 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(2) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(4) - (4)]).strs[0];
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 148 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 154 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 166 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 169 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		Struct *rs					=new Struct;
		*rs							=buildStruct;
		string name					=(yyvsp[(2) - (6)]).strs[0];
		gEffect->m_structs[name]	=rs;
		// Set to default:
		buildStruct					=Struct();
		gEffect->m_sharedCode<<"struct "<<(yyvsp[(2) - (6)]).strs[0]<<"\n{\n";
		for(int i=0;i<(int)rs->m_structMembers.size();i++)
		{
			const StructMember &m=rs->m_structMembers[i];
			gEffect->m_sharedCode<<m.type<<" "<<m.name<<";\n";
		
		}
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,(yyvsp[(6) - (6)]).lineno+last_linenumber-global_linenumber);
		gEffect->m_sharedCode<<"};";
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 187 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).lineno		=(yyvsp[(4) - (4)]).lineno;
		RenderState t=renderState;
		string name=(yyvsp[(2) - (4)]).strs[0];
		if(t==RASTERIZER_STATE)
		{
			RasterizerState *rs=new RasterizerState;
			*rs=buildRasterizerState;
			gEffect->m_rasterizerStates[name]=rs;
			// Set to default:
			buildRasterizerState=RasterizerState();
		}
		if(t==BLEND_STATE)
		{
			BlendState *bs=new BlendState;
			*bs= buildBlendState;
			gEffect->m_blendStates[name]=bs;
			// Set to default:
			buildBlendState=BlendState();
		}
		if(t==DEPTHSTENCIL_STATE)
		{
			DepthStencilState *ds=new DepthStencilState;
			*ds=buildDepthStencilState;
			gEffect->m_depthStencilStates[name]=ds;
			// Set to default:
			buildDepthStencilState=DepthStencilState();
		}
		if(t==SAMPLER_STATE)
		{
			SamplerState *ss=new SamplerState;
			*ss=buildSamplerState;
			gEffect->m_samplerStates[name]=ss;
			// Set to default:
			buildSamplerState=SamplerState();
		}
		int true_linenumber=(yyvsp[(4) - (4)]).lineno+(last_linenumber-global_linenumber);
	//	WriteLineNumber(true_linenumber);
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 227 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string profileName		=(yyvsp[(2) - (6)]).strs[0];
		int profileNum			=(yyvsp[(4) - (6)]).num;
		if(gEffect->m_profileToVersion.find(profileName)!=gEffect->m_profileToVersion.end())
		{
			glfxWarning("redefining profile ");
		}
		gEffect->m_profileToVersion[profileName]=profileNum;
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 237 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		// We here declare that a named shader should be compiled with the specified profile (e.g. GLSL 4.30)
		// and assign a variable name to the shader/profile combination. Later on, in pass definitions,
		// we can assign the shader to one or more passes.
		string compiledShaderName		=(yyvsp[(2) - (5)]).strs[0];
		CompiledShader *cs				=gEffect->m_compiledShaders[(yyvsp[(4) - (5)]).strs[0]];
		CompiledShader *compiledShader	=NULL;
		CompiledShaderMap::iterator i	=gEffect->m_compiledShaders.find(compiledShaderName);
		if(i!=gEffect->m_compiledShaders.end())
		{
			delete i->second;
			// TODO: Warn here about double-compiling a shader.
			glfxWarning("double-compiling shader ");
		}
		gEffect->m_compiledShaders[compiledShaderName]=compiledShader=cs;
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 254 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 261 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		std::string shaderName		=(yyvsp[(3) - (9)]).strs[0];
		std::string returnType		=(yyvsp[(2) - (9)]).strs[0];
		std::string shaderContent	=(yyvsp[(8) - (9)]).strs[0];
		ostringstream shaderCode;
		ostringstream extraDeclarations;
		int main_linenumber=(yyvsp[(1) - (9)]).lineno+(last_linenumber-global_linenumber);
		int content_linenumber=(yyvsp[(8) - (9)]).lineno+(last_linenumber-global_linenumber);
		// Add shader parameters
		for(vector<YYSTYPE::variable>::const_iterator it=(yyvsp[(5) - (9)]).vars->begin();it!=(yyvsp[(5) - (9)]).vars->end();++it)
		{
			string structInstanceName=it->identifier;
			string type(it->type);
			map<string,Struct*>::const_iterator u=gEffect->m_structs.find(type);
			map<string, Effect::InterfaceDcl>::const_iterator varType=gEffect->m_interfaces.find(type);
			int lineno;
			if(u!=gEffect->m_structs.end())
			{
				extraDeclarations<<type<<" "<<structInstanceName<<";\n";
				const Struct *s=u->second;
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					string sem=m.name;
					if(m.semantic.length())
						sem=m.semantic;
					//shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
					shaderCode<<it->storage<<' '<<m.type<<' '<<sem<<"_;"<<endl;
					extraDeclarations<<structInstanceName<<"."<<m.name<<"="<<sem<<"_;\n";
				}
				continue;
			}
			else if(varType!=gEffect->m_interfaces.end())
			{
				type+=varType->second.id;
				lineno=varType->second.atLine;
			}
			else
				lineno=(yyvsp[(1) - (9)]).lineno;
			if(it->semantic.length()>0)
			{
				shaderCode<<"#define "<<it->identifier<<" "<<it->semantic<<endl;
			}
			else
			{
			// First put #line in to make sure that all our definitions produce correct-looking warnings/errors.
				shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
				shaderCode<<it->storage<<' '<<type<<' '<<it->identifier<<';'<<endl;
			}
		}
		delete (yyvsp[(5) - (9)]).vars;
		// Add definition and code
		shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
		shaderCode<<"void main()\n{\n";
		if(extraDeclarations.str().length())
			shaderCode<<extraDeclarations.str()<<"\n";
		shaderCode<<"#line "<<content_linenumber<<" "<<current_filenumber<<endl;
		shaderCode<<shaderContent<<"\n}\n";
		gEffect->m_shaderLayouts[shaderName]	=currentCsLayout;
		gEffect->m_shaders[shaderName]			=shaderCode.str();
		// now we must put a #line directive in the shared code, because we've just snipped out a bunch of what was there:
		
		gEffect->m_sharedCode<<"#line "<<(glfxget_lineno()+(last_linenumber-global_linenumber))<<" "<<current_filenumber<<endl;
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 326 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 331 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_techniques[(yyvsp[(3) - (7)]).strs[0]] = (yyvsp[(5) - (7)]).tech;
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 335 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 342 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 348 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 353 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 358 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 363 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 368 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	std::string ret="(";
	ret+=(yyvsp[(2) - (7)]).strs[0];
	ret+=",";
	ret+=(yyvsp[(4) - (7)]).strs[0];
	ret+=",";
	ret+=(yyvsp[(6) - (7)]).strs[0];
	ret+=")";
	(yyval).strs[0]=ret;
}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 379 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 383 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 388 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 392 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 396 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 400 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 404 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 409 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		   }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 414 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 418 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 422 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 428 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
    gLexPassthrough=false;
}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 434 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 438 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 445 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 451 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 454 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 457 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars=(yyvsp[(1) - (3)]).vars;

		YYSTYPE::variable var;
		var.storage=(yyvsp[(3) - (3)]).strs[0];
		var.type=(yyvsp[(3) - (3)]).strs[1];
		var.identifier=(yyvsp[(3) - (3)]).strs[2];
		var.semantic=(yyvsp[(3) - (3)]).strs[4];
    
		(yyval).vars->push_back(var);
	}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 469 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		YYSTYPE::variable var;
		var.storage=(yyvsp[(1) - (1)]).strs[0];
		var.type=(yyvsp[(1) - (1)]).strs[1];
		var.identifier=(yyvsp[(1) - (1)]).strs[2];
		var.semantic=(yyvsp[(1) - (1)]).strs[4];
    
		(yyval).vars = new vector<YYSTYPE::variable>;
		(yyval).vars->push_back(var);
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 480 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 485 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    ostringstream prepend;
	string semantic;
    switch((yyvsp[(3) - (3)]).rType)
	{
    case REGISTER_INT:
        prepend<<"layout(location="<<(yyvsp[(3) - (3)]).num<<") ";
        break;
    case REGISTER_NAME:
        prepend<<"layout(location="<<(yyvsp[(3) - (3)]).strs[0]<<") ";
        break;
    case SEMANTIC:
		semantic=(yyvsp[(3) - (3)]).strs[0];
        break;
    }
    prepend<<(yyvsp[(1) - (3)]).strs[0];

	string storage	=prepend.str();
	string type		=(yyvsp[(1) - (3)]).strs[1];
	string id		=(yyvsp[(1) - (3)]).strs[2]+(yyvsp[(2) - (3)]).strs[0];

    (yyval).strs[0]=storage;
    (yyval).strs[1]=type;
    (yyval).strs[2]=id;

    (yyval).strs[3]=(yyvsp[(2) - (3)]).strs[0];
    (yyval).strs[3]+=(yyvsp[(3) - (3)]).strs[0];
    (yyval).strs[4]=semantic;
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 516 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="[]";
				}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 520 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 525 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (3)]).strs[0];
		string type		=(yyvsp[(2) - (3)]).strs[0];
		string id		=(yyvsp[(3) - (3)]).strs[0];
		(yyval).strs[0]		= storage	;
		(yyval).strs[1]		= type		;
		(yyval).strs[2]		= id		;
	}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 534 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 538 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 542 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 547 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
	}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 552 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 557 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 563 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 570 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).passes = (yyvsp[(1) - (2)]).passes;
	string name = (yyvsp[(2) - (2)]).strs[0];
	Program *p = (yyvsp[(2) - (2)]).prog;
	if (p)
	{
		(*(yyval).passes)[name] = *(p);
	}
	delete (yyvsp[(2) - (2)]).prog;
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 581 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	map < string, Program > *m=new map < string, Program >;
	(yyval).passes = m;
	string name = (yyvsp[(1) - (1)]).strs[0];
	Program *p = (yyvsp[(1) - (1)]).prog;
	if (p)
	{
		Program &newp = (*m)[name];
		newp= *p;
	}
	delete p;
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 595 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable = (yyvsp[(1) - (5)]).boolean;
	(yyval).prog = (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0] = (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 602 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders));
    delete (yyvsp[(1) - (1)]).shaders;
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 608 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		ShaderType sType	=(yyvsp[(2) - (2)]).sType;
		string src			=(yyvsp[(2) - (2)]).strs[0];
		string name			=(yyvsp[(2) - (2)]).strs[1];
		(*map1)[sType].src	=src;
		(*map1)[sType].name	=name;
		(yyval).shaders			=map1;
	}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 618 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		string src			=(yyvsp[(1) - (1)]).strs[0];
		string name			=(yyvsp[(1) - (1)]).strs[1];
		ShaderType sType	=(yyvsp[(1) - (1)]).sType;
		(yyval).strs[0]			=src;
		(yyval).strs[1]			=name;
		(yyval).sType			=sType;
		(*map1)[sType].src	=src;
		(*map1)[sType].name	=name;
		(yyval).shaders=map1;
	}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 631 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 639 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 647 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 656 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 660 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
			 }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 665 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 672 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[1]="";
				(yyval).strs[0]="";
				(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
				glfxParser::ShaderType shaderType=(yyvsp[(1) - (4)]).sType;
				glfxParser::ShaderCommand shaderCommand=(yyvsp[(1) - (4)]).sCommand;
				if(shaderType<NUM_OF_SHADER_TYPES&&(yyvsp[(3) - (4)]).num>0)
				{
					// Assemble the shader
					ostringstream theShader;
					theShader<<"#version "<<(yyvsp[(1) - (4)]).num<<endl;
					theShader<<(yyvsp[(3) - (4)]).strs[1];
					// RVK: Must do this because layout(u,v,w) causes problems for non-compute shaders in some compilers:
					if(shaderType==COMPUTE_SHADER)
						theShader<<"#define USE_GL_COMPUTE_SHADER 1"<<endl;
					string shaderName=((yyvsp[(3) - (4)]).strs[0]);
					if(_stricmp(shaderName.c_str(),"NULL")!=0)
					{
						theShader<<gEffect->m_sharedCode.str();
						map<string, string>::const_iterator it=gEffect->m_shaders.find(shaderName);
						if(it==gEffect->m_shaders.end())
						{
							int ylineno=(yyvsp[(3) - (4)]).lineno;
							int true_linenumber=ylineno+(last_linenumber-global_linenumber);
							ostringstream errMsg;
							errMsg<<"Unable to find referenced shader \""<<shaderName<<'\"';
							errSem(errMsg.str(), true_linenumber);
						}
						else
						{
							if(shaderType==COMPUTE_SHADER)
								theShader<<gEffect->m_shaderLayouts[shaderName]<<"\n";
						// Currently in case of error it never returns (throw)
						// TODO: Handle continuation in case of error
							theShader<<it->second;
						}
					}
					(yyval).strs[1]=shaderName;
					(yyval).strs[0]=theShader.str();
				}
				else if(shaderCommand<NumShaderCommands)
				{
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[1];
					(yyval).strs[1]=(yyvsp[(1) - (4)]).strs[0];
				}
				(yyval).sType=(yyvsp[(1) - (4)]).sType;
			}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 721 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[1]="";
				(yyval).strs[0]="";
				(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
				// the shader_variable is something like vs_main, for which we have a compile command like:
				//												VertexShader vs_layers=CompileShader(430,VS_Layers());
				// i.e. it's a combination of shadertype, profile, and function name.
				// so these are stored in gEffect->m_compiledSHaders.
				string compiledShaderName=(yyvsp[(3) - (5)]).strs[0];
				CompiledShaderMap::iterator i=gEffect->m_compiledShaders.find(compiledShaderName);
				if(i==gEffect->m_compiledShaders.end())
				{
					if(_stricmp(compiledShaderName.c_str(),"NULL")==0)
					{
					}
					else
					{
						ostringstream errMsg;
						errMsg<<"Unable to find compiled shader \""<<compiledShaderName<<'\"';
						errSem(errMsg.str(), (yyvsp[(3) - (5)]).lineno);
					}
				}
				else
				{
					CompiledShader *compiledShader	=i->second;
					(yyval).num							=compiledShader->version;
					(yyval).sCommand						=(yyvsp[(1) - (5)]).sCommand;
					(yyval).sType						=(yyvsp[(1) - (5)]).sType;
					ostringstream theShader;
					theShader << "#version " << compiledShader->version << endl;
					glfxParser::ShaderCommand shaderCommand=(yyvsp[(1) - (5)]).sCommand;
					if(shaderCommand==COMPUTE_SHADER)
						theShader<<"#define USE_GL_COMPUTE_SHADER 1"<<endl;
					if(shaderCommand<NumShaderCommands)
					{
						string shaderName=compiledShader->m_functionName;
						if(_stricmp(shaderName.c_str(),"NULL")!=0)
						{
							theShader<<gEffect->m_sharedCode.str();
							map<string, string>::const_iterator it=gEffect->m_shaders.find(shaderName);
							if(it==gEffect->m_shaders.end())
							{
								ostringstream errMsg;
								errMsg<<"Unable to find referenced shader \""<<shaderName<<'\"';
								errSem(errMsg.str(), (yyvsp[(3) - (5)]).lineno);
							}
							else
							{
								if(shaderCommand==COMPUTE_SHADER)
									theShader<<gEffect->m_shaderLayouts[shaderName]<<"\n";
								// Currently in case of error it never returns (throw)
								// TODO: Handle continuation in case of error
									theShader<<it->second;
							}
						}
						(yyval).strs[1]=shaderName;
						(yyval).strs[0]=theShader.str();
					}
				}
			}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 782 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string compiledShaderName	=(yyvsp[(1) - (1)]).strs[0];
			(yyval).strs[0]					=compiledShaderName;
			(yyval).num						=0;
			(yyval).lineno					=(yyvsp[(1) - (1)]).lineno;
		}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 789 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).lineno					=(yyvsp[(5) - (8)]).lineno;
			string profileName								=(yyvsp[(3) - (8)]).strs[0];
			ProfileMap::iterator i							=gEffect->m_profileToVersion.find(profileName);
			int version_num=0;
			if(i==gEffect->m_profileToVersion.end())
			{
				ostringstream msg;
				msg<<"Profile not found"<<profileName<<endl;
				errSem(msg.str().c_str());
			}
			else
				version_num=i->second;
			stringstream ss;
			ss << (yyvsp[(5) - (8)]).strs[0]<<"Compiled"<<version_num;
			string compiledShaderName						=ss.str();
			(yyval).strs[0]										=compiledShaderName;

			CompiledShader *compiledShader	=gEffect->m_compiledShaders[compiledShaderName];

			gEffect->m_compiledShaders[compiledShaderName]	=compiledShader=new CompiledShader;
			compiledShader->m_functionName					=(yyvsp[(5) - (8)]).strs[0];
			compiledShader->shaderType						=(yyvsp[(1) - (8)]).sType;
			compiledShader->version							=(yyval).num=version_num;
		}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 815 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 826 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 832 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 836 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 840 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 845 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 850 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 854 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
					(yyval).strs[0]	+=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 861 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 866 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 871 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno+1;
		(yyval).strs[0]			=(yyvsp[(1) - (3)]).strs[0]+" ";
		(yyval).strs[0]			+=(yyvsp[(2) - (3)]).strs[0]+" ";
		(yyval).strs[0]			+=(yyvsp[(3) - (3)]).strs[0];
		(yyval).strs[0]			+='\n';
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 884 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+" ";
			(yyval).strs[0]+=(yyvsp[(2) - (2)]).strs[0];
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 889 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 893 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 897 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 901 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 905 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 909 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 913 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 917 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 921 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 925 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
				}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 930 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 934 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 938 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 942 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 946 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 950 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 954 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 958 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0];
				}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 962 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 966 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 970 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 974 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
				(yyval).strs[1]=(yyvsp[(2) - (3)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (3)]).lineno;
			}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 980 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 985 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 989 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 993 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 996 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1000 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1005 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1010 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1014 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1018 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1022 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1026 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1039 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1043 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1047 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
	}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1052 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1056 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1060 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1064 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1068 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1072 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1076 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1080 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1084 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1088 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1093 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1097 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1101 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1105 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1109 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1113 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1117 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1121 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1125 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1129 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1133 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1137 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1141 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1145 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1149 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1153 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1157 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1161 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1165 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1169 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1173 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1177 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1181 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1185 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1189 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1193 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1197 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1201 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1205 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1209 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1213 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1217 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1221 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1225 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1230 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<string> children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1237 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<string> children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1244 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1248 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<string> children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1255 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1259 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1263 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1267 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1271 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1275 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1283 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1291 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1295 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno		=(yyvsp[(3) - (4)]).lineno;
							string name		=(yyvsp[(2) - (4)]).strs[0];
							string type		=(yyvsp[(1) - (4)]).strs[0];
							string sem		=(yyvsp[(3) - (4)]).strs[0];
							StructMember s;
							s.type		=type;
							s.semantic	=sem;
							s.name		=name;
							buildStruct.m_structMembers.push_back(s);
					}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1307 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1311 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1315 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1320 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1324 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1327 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1331 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1336 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1340 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno		=(yyvsp[(3) - (4)]).lineno;
							string name		=(yyvsp[(1) - (4)]).strs[0];
							string value	=(yyvsp[(3) - (4)]).strs[0];
							int index		=(yyvsp[(1) - (4)]).num;
							int ival		=(yyvsp[(3) - (4)]).num;
							float fval		=(yyvsp[(3) - (4)]).fnum;
							bool bval		=(ival!=0);
							if(renderState==RASTERIZER_STATE)
							{
								if(is_equal(name,"FillMode"))
									buildRasterizerState.FillMode=(GLenum)toFillModeGLenum(value);
								else if(is_equal(name,"CullMode"))
									buildRasterizerState.CullMode=(GLenum)toCullModeGLenum(value);
								else if(is_equal(name,"FrontCounterClockwise"))
									buildRasterizerState.FrontCounterClockwise=toBool(value);
								else if(is_equal(name,"DepthBias"))
									buildRasterizerState.DepthBias=ival;
								else if(is_equal(name,"DepthBiasClamp"))
									buildRasterizerState.DepthBiasClamp=fval;
								else if(is_equal(name,"SlopeScaledDepthBias"))
									buildRasterizerState.SlopeScaledDepthBias=fval;
								else if(is_equal(name,"DepthClipEnable"))
									buildRasterizerState.DepthClipEnable=toBool(value);
								else if(is_equal(name,"ScissorEnable"))
									buildRasterizerState.ScissorEnable=toBool(value);
								else if(is_equal(name,"MultisampleEnable"))
									buildRasterizerState.MultisampleEnable=toBool(value);
								else if(is_equal(name,"AntialiasedLineEnable"))
									buildRasterizerState.AntialiasedLineEnable=toBool(value);
								else
								{
									ostringstream str;
									str<<"Unknown rasterizer state command: "<<name;
									errSem(str.str().c_str());
								}
							}
							if(renderState==DEPTHSTENCIL_STATE)
							{
								if(is_equal(name,"DepthEnable"))
									buildDepthStencilState.DepthEnable		=toBool(value);
								else if(is_equal(name,"DepthWriteMask"))
								{
									if(is_equal(value,"ALL"))
										buildDepthStencilState.DepthWriteMask	=1;
									else if(is_equal(value,"ZERO"))
										buildDepthStencilState.DepthWriteMask	=0;
									else 
										errSem("Unknown depth write mask");
								}
								else if(is_equal(name,"DepthFunc"))
									buildDepthStencilState.DepthFunc=(GLenum)toDepthFuncGLEnum(value);
								else
								{
									ostringstream str;
									str<<"Unknown DepthStencil state command: "<<name;
									errSem(str.str().c_str());
								}
							}
							if(renderState==BLEND_STATE)
							{
								if(is_equal(name,"SrcBlend"))
									buildBlendState.SrcBlend=(GLenum)toBlendGLEnum(value);
								else if(is_equal(name,"DestBlend"))
									buildBlendState.DestBlend=(GLenum)toBlendGLEnum(value);
								else if(is_equal(name,"BlendOp"))
									buildBlendState.BlendOp=(GLenum)toBlendOpGLEnum(value);
								else if(is_equal(name,"SrcBlendAlpha"))
									buildBlendState.SrcBlendAlpha=(GLenum)toBlendGLEnum(value);
								else if(is_equal(name,"DestBlendAlpha"))
									buildBlendState.DestBlendAlpha=(GLenum)toBlendGLEnum(value);
								else if(is_equal(name,"BlendOpAlpha"))
									buildBlendState.BlendOpAlpha=(GLenum)toBlendOpGLEnum(value);
								else if(is_equal(name,"AlphaToCoverageEnable"))
									buildBlendState.AlphaToCoverageEnable=toBool(value);
								else if(is_equal(name,"BlendEnable"))
									buildBlendState.BlendEnable[index]=toBool(value);
								else if(is_equal(name,"RenderTargetWriteMask"))
									buildBlendState.RenderTargetWriteMask[index]=ival;
								else
								{
									ostringstream str;
									str<<"Unknown blend state command: "<<name;
									errSem(str.str().c_str());
								}
							}
							if(renderState==SAMPLER_STATE)
							{
								if(is_equal(name,"Filter"))
								{
									buildSamplerState.MinFilter			=(GLenum)toMinFilterModeGLEnum(value);
									buildSamplerState.MagFilter			=(GLenum)toMagFilterModeGLEnum(value);
								}
								else if(is_equal(name,"AddressU"))
									buildSamplerState.AddressU			=(GLenum)toAddressModeGLEnum(value);
								else if(is_equal(name,"AddressV"))
									buildSamplerState.AddressV			=(GLenum)toAddressModeGLEnum(value);
								else if(is_equal(name,"AddressW"))
									buildSamplerState.AddressW			=(GLenum)toAddressModeGLEnum(value);
								else
								{
									ostringstream str;
									str<<"Unknown Sampler state command: "<<name;
									errSem(str.str().c_str());
								}
							}
						}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1449 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1454 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1460 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1465 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1469 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1474 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1479 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1484 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 4047 "src/glfxLALRParser.cpp"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 1487 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


void glfxWarning(const char* e)
{
    ostringstream errMsg;
	int lex_linenumber=glfxget_lineno();
	int true_linenumber=lex_linenumber+last_linenumber-global_linenumber;
    errMsg<<current_filenumber<<"("<< true_linenumber<<") : glfx warning: \""<<glfxget_text()<<"\" "<<e;
	gEffect->Log()<<errMsg;
}

void glfxerror(const char* e)
{
    errSyn(e);
}

void errSyn(const char* e)
{
    ostringstream errMsg;
	int lex_linenumber=glfxget_lineno();
	int true_linenumber=lex_linenumber+last_linenumber-global_linenumber;
    errMsg<<current_filenumber<<"("<< true_linenumber<<") : glfx syntax error: \""<<glfxget_text()<<"\" "<<e<<" in "<<glfxGetStateText();
    throw std::runtime_error(errMsg.str());
}

void errSem(const string& str, int lex_linenumber)
{
    ostringstream errMsg;
    
    if(lex_linenumber==-1)
        lex_linenumber= glfxget_lineno();
	int true_linenumber=lex_linenumber+last_linenumber-global_linenumber;
    errMsg<<current_filenumber<<"("<<true_linenumber<<") : glfx error: "<<str<<" in "<<glfxGetStateText();
    throw errMsg.str();
}
