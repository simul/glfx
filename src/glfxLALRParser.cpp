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
#define YYLAST   507

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  89
/* YYNRULES -- Number of rules.  */
#define YYNRULES  219
/* YYNRULES -- Number of states.  */
#define YYNSTATES  451

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
      81,    91,    99,   101,   109,   115,   119,   122,   124,   126,
     130,   131,   139,   142,   144,   150,   158,   162,   166,   170,
     172,   174,   176,   182,   186,   188,   190,   191,   192,   193,
     197,   198,   201,   202,   206,   208,   209,   213,   216,   217,
     221,   223,   224,   227,   230,   233,   234,   236,   239,   241,
     247,   249,   252,   254,   257,   259,   270,   276,   284,   294,
     299,   305,   307,   316,   321,   326,   327,   330,   331,   335,
     337,   340,   342,   343,   347,   350,   352,   356,   358,   362,
     364,   368,   373,   377,   381,   384,   386,   389,   391,   397,
     405,   411,   419,   429,   433,   436,   439,   443,   445,   447,
     449,   450,   452,   453,   457,   459,   463,   465,   469,   471,
     473,   475,   477,   479,   481,   483,   485,   487,   489,   491,
     493,   499,   501,   505,   507,   511,   513,   517,   519,   523,
     525,   529,   531,   535,   539,   541,   545,   549,   553,   557,
     559,   563,   567,   569,   573,   577,   579,   583,   587,   591,
     593,   595,   598,   601,   604,   606,   608,   610,   612,   614,
     616,   618,   623,   628,   632,   636,   639,   642,   646,   648,
     650,   654,   659,   661,   665,   667,   669,   673,   675,   677,
     680,   683,   684,   689,   692,   693,   696,   698,   702,   703,
     706,   708,   713,   715,   718,   722,   723,   725,   727,   729
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      95,     0,    -1,    95,    96,    -1,    -1,     7,   113,     8,
     117,    70,   115,    -1,    33,    -1,    97,    -1,     4,   100,
     101,     8,    70,    -1,     4,     8,     8,    70,    -1,    36,
      -1,    20,   106,     8,    70,    -1,    20,   107,    -1,    37,
       8,    70,    -1,    37,     8,    71,    -1,    31,    32,    33,
      -1,    30,     8,    72,   175,    73,    70,    -1,    25,     8,
     176,    70,    -1,    35,     8,    74,    16,    75,    70,    -1,
      34,     8,    76,   133,    70,    -1,    20,   113,   102,   115,
      -1,    99,     8,     8,    74,   119,    75,   118,   116,   115,
      -1,     6,   113,     8,    72,   128,    73,   115,    -1,   105,
      -1,    24,   113,     8,    72,   103,    73,   115,    -1,    21,
     113,    16,    16,   115,    -1,    21,    16,    16,    -1,     5,
     114,    -1,    38,    -1,    39,    -1,    77,     8,    78,    -1,
      -1,    74,    16,    71,    16,    71,    16,    75,    -1,   103,
     104,    -1,   104,    -1,    22,     8,    72,   125,    73,    -1,
      22,   113,     8,    72,   125,    73,   115,    -1,    74,   110,
      75,    -1,    74,   108,    75,    -1,   108,    71,   109,    -1,
     109,    -1,   111,    -1,     8,    -1,   111,    71,   111,    71,
     111,    -1,     8,    76,   112,    -1,     8,    -1,    16,    -1,
      -1,    -1,    -1,    72,   138,    73,    -1,    -1,    79,     8,
      -1,    -1,   119,    71,   120,    -1,   120,    -1,    -1,   122,
     121,   124,    -1,    80,    81,    -1,    -1,   123,     8,     8,
      -1,     9,    -1,    -1,    79,    16,    -1,    79,    15,    -1,
      79,     8,    -1,    -1,   126,    -1,   126,   127,    -1,   127,
      -1,    23,     8,    72,   128,    73,    -1,   129,    -1,   129,
     132,    -1,   132,    -1,   129,   131,    -1,   131,    -1,     8,
      74,    19,    71,    19,    71,    19,    71,    19,    75,    -1,
      12,    74,     8,    75,    70,    -1,    13,    74,     8,    71,
      16,    75,    70,    -1,    14,    74,     8,    71,   130,    71,
      16,    75,    70,    -1,   134,    76,   135,    70,    -1,    11,
      74,   133,    75,    70,    -1,     8,    -1,    29,    74,     8,
      71,     8,    74,    75,    75,    -1,    28,    74,    16,    75,
      -1,     8,    74,    75,   136,    -1,    -1,    79,   137,    -1,
      -1,   137,    71,   171,    -1,   171,    -1,   138,   144,    -1,
     144,    -1,    -1,    21,    16,    16,    -1,   182,   141,    -1,
     142,    -1,   141,    71,   142,    -1,   143,    -1,   143,    76,
     167,    -1,     8,    -1,    74,   143,    75,    -1,   143,    80,
      16,    81,    -1,   143,    80,    81,    -1,   143,    74,    75,
      -1,   148,    70,    -1,    70,    -1,   140,    70,    -1,   147,
      -1,    47,    74,   148,    75,   144,    -1,    47,    74,   148,
      75,   144,    49,   144,    -1,    48,    74,   148,    75,   144,
      -1,    44,   144,    48,    74,   148,    75,    70,    -1,    45,
      74,   145,    70,   146,    70,   146,    75,   144,    -1,    46,
       8,    70,    -1,    43,    70,    -1,    42,    70,    -1,    41,
     146,    70,    -1,   139,    -1,   148,    -1,   140,    -1,    -1,
     148,    -1,    -1,    72,   138,    73,    -1,   149,    -1,   148,
      71,   149,    -1,   151,    -1,   163,   150,   149,    -1,    76,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,    59,
      -1,   152,    -1,   152,    82,   148,    79,   151,    -1,   153,
      -1,   152,    61,   153,    -1,   154,    -1,   153,    60,   154,
      -1,   155,    -1,   154,    83,   155,    -1,   156,    -1,   155,
      84,   156,    -1,   157,    -1,   156,    85,   157,    -1,   158,
      -1,   157,    68,   158,    -1,   157,    69,   158,    -1,   159,
      -1,   158,    77,   159,    -1,   158,    78,   159,    -1,   158,
      62,   159,    -1,   158,    63,   159,    -1,   160,    -1,   159,
      64,   160,    -1,   159,    65,   160,    -1,   161,    -1,   160,
      86,   161,    -1,   160,    87,   161,    -1,   162,    -1,   161,
      88,   162,    -1,   161,    89,   162,    -1,   161,    90,   162,
      -1,   163,    -1,   165,    -1,    66,   163,    -1,    67,   163,
      -1,   164,   162,    -1,    85,    -1,    88,    -1,    86,    -1,
      87,    -1,    91,    -1,    92,    -1,   169,    -1,   165,    80,
     148,    81,    -1,   165,    74,   166,    75,    -1,   165,    74,
      75,    -1,   165,    93,     8,    -1,   165,    66,    -1,   165,
      67,    -1,   166,    71,   149,    -1,   149,    -1,   149,    -1,
      72,   168,    73,    -1,    72,   168,    71,    73,    -1,   167,
      -1,   168,    71,   167,    -1,     8,    -1,   170,    -1,    74,
     148,    75,    -1,    16,    -1,    19,    -1,     9,   172,    -1,
      10,   172,    -1,    -1,     8,     8,   174,    70,    -1,    79,
       8,    -1,    -1,   175,   173,    -1,   173,    -1,    72,   177,
      73,    -1,    -1,   177,   178,    -1,   178,    -1,   179,    76,
     181,    70,    -1,    98,    -1,     8,   180,    -1,    80,    16,
      81,    -1,    -1,     8,    -1,    16,    -1,    19,    -1,     8,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   102,   102,   103,   107,   111,   114,   117,   129,   135,
     139,   147,   153,   159,   165,   168,   186,   226,   236,   253,
     260,   355,   360,   363,   366,   373,   379,   384,   384,   389,
     395,   399,   410,   414,   417,   421,   425,   429,   434,   438,
     442,   446,   450,   455,   460,   464,   469,   475,   481,   485,
     492,   497,   501,   503,   515,   527,   531,   562,   567,   571,
     580,   585,   588,   593,   598,   604,   609,   616,   627,   641,
     648,   654,   664,   677,   685,   693,   702,   706,   711,   718,
     767,   828,   835,   861,   872,   879,   882,   887,   891,   896,
     900,   909,   916,   920,   933,   938,   942,   946,   950,   954,
     958,   962,   966,   970,   974,   979,   983,   987,   991,   995,
     999,  1003,  1007,  1011,  1015,  1019,  1023,  1029,  1034,  1038,
    1043,  1045,  1050,  1054,  1059,  1063,  1067,  1071,  1075,  1079,
    1080,  1081,  1082,  1083,  1084,  1085,  1086,  1087,  1088,  1092,
    1096,  1101,  1105,  1109,  1113,  1117,  1121,  1125,  1129,  1133,
    1137,  1142,  1146,  1150,  1154,  1158,  1162,  1166,  1170,  1174,
    1178,  1182,  1186,  1190,  1194,  1198,  1202,  1206,  1210,  1214,
    1218,  1222,  1226,  1230,  1234,  1234,  1234,  1234,  1234,  1234,
    1238,  1242,  1246,  1250,  1254,  1258,  1262,  1266,  1270,  1274,
    1279,  1286,  1293,  1297,  1304,  1308,  1312,  1316,  1320,  1324,
    1332,  1341,  1344,  1356,  1361,  1364,  1369,  1373,  1377,  1380,
    1385,  1389,  1498,  1503,  1509,  1515,  1518,  1523,  1528,  1533
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
  "optional_templateval", "layout_params", "technique_decls",
  "group_technique_decl", "technique_decl", "cs_layout_spec",
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
      96,    96,    96,    96,    97,    98,    99,   100,   100,   101,
     101,   102,   103,   103,   104,   105,   106,   107,   108,   108,
     109,   109,   110,   111,   112,   112,   113,   114,   115,   116,
     117,   118,   118,   119,   119,   119,   120,   121,   121,   122,
     123,   123,   124,   124,   124,   124,   125,   126,   126,   127,
     128,   129,   129,   129,   129,   130,   131,   131,   131,   132,
     132,   133,   133,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   138,   139,   140,   141,   141,   142,   142,   143,
     143,   143,   143,   143,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   145,   145,
     145,   146,   146,   147,   148,   148,   149,   149,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   151,
     151,   152,   152,   153,   153,   154,   154,   155,   155,   156,
     156,   157,   157,   157,   158,   158,   158,   158,   158,   159,
     159,   159,   160,   160,   160,   161,   161,   161,   161,   162,
     163,   163,   163,   163,   164,   164,   164,   164,   164,   164,
     165,   165,   165,   165,   165,   165,   165,   166,   166,   167,
     167,   167,   168,   168,   169,   169,   169,   170,   170,   171,
     171,   172,   173,   174,   174,   175,   175,   176,   176,   177,
     177,   178,   178,   179,   180,   180,   181,   181,   181,   182
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     5,     4,     1,
       4,     2,     3,     3,     3,     6,     4,     6,     5,     4,
       9,     7,     1,     7,     5,     3,     2,     1,     1,     3,
       0,     7,     2,     1,     5,     7,     3,     3,     3,     1,
       1,     1,     5,     3,     1,     1,     0,     0,     0,     3,
       0,     2,     0,     3,     1,     0,     3,     2,     0,     3,
       1,     0,     2,     2,     2,     0,     1,     2,     1,     5,
       1,     2,     1,     2,     1,    10,     5,     7,     9,     4,
       5,     1,     8,     4,     4,     0,     2,     0,     3,     1,
       2,     1,     0,     3,     2,     1,     3,     1,     3,     1,
       3,     4,     3,     3,     2,     1,     2,     1,     5,     7,
       5,     7,     9,     3,     2,     2,     3,     1,     1,     1,
       0,     1,     0,     3,     1,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     3,     3,     2,     2,     3,     1,     1,
       3,     4,     1,     3,     1,     1,     3,     1,     1,     2,
       2,     0,     4,     2,     0,     2,     1,     3,     0,     2,
       1,     4,     1,     2,     3,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,    47,    46,    46,     0,    46,    46,
      46,     0,     0,     0,     5,     0,     0,     9,     0,     2,
       6,     0,    22,     0,    27,    28,    30,    26,     0,     0,
       0,     0,    11,     0,     0,     0,     0,   208,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,    41,
       0,    39,     0,    40,     0,     0,    48,     0,     0,     0,
       0,     0,     0,    14,     0,     0,    12,    13,     0,     8,
       0,     0,     0,     0,     0,     0,    37,    36,     0,    10,
       0,    19,    48,     0,     0,   215,     0,   212,     0,   210,
       0,    16,     0,   206,     0,    81,     0,     0,     0,    55,
      29,     7,     0,     0,     0,     0,     0,     0,    70,    74,
      72,     0,    48,    44,    45,    43,    38,    40,     0,     0,
       0,    24,     0,     0,    66,    68,     0,     0,    33,     0,
     213,     0,   207,   209,     0,   204,     0,   205,     0,    18,
       0,    60,     0,    54,    58,     0,     0,     0,     0,     0,
       0,    48,    73,    71,    85,     4,     0,     0,     0,    48,
      67,     0,    48,    32,     0,    25,   216,   217,   218,     0,
       0,     0,    15,     0,    17,    61,    52,     0,    65,     0,
       0,     0,     0,     0,     0,    21,     0,     0,    42,     0,
       0,    35,     0,    23,   214,   211,   203,   202,     0,    53,
       0,     0,    57,     0,    56,    59,     0,     0,     0,     0,
      83,     0,    79,     0,     0,     0,     0,    51,    92,    48,
      64,    63,    62,    80,    76,     0,     0,     0,    87,    31,
      69,    34,     0,   194,   197,   198,     0,   122,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,    92,     0,
     174,   176,   177,   175,   178,   179,     0,   117,     0,    91,
     107,     0,   124,   126,   139,   141,   143,   145,   147,   149,
     151,   154,   159,   162,   165,   169,     0,   170,   180,   195,
       0,    20,     0,     0,     0,     0,    84,     0,     0,   194,
       0,   121,   115,   114,     0,   120,     0,     0,     0,   171,
     172,     0,     0,    49,    90,   106,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   128,     0,   173,
     169,   185,   186,     0,     0,     0,    99,     0,    94,    95,
      97,    77,     0,     0,   201,   201,    86,    89,    82,    93,
     116,     0,   119,     0,   118,   113,     0,     0,   123,   196,
     125,   142,     0,   144,   146,   148,   150,   152,   153,   157,
     158,   155,   156,   160,   161,   163,   164,   166,   167,   168,
     127,   183,   188,     0,     0,   184,     0,     0,     0,     0,
       0,     0,     0,   199,   200,     0,     0,   122,     0,     0,
       0,     0,   182,   181,   100,    96,   103,     0,   189,    98,
       0,   102,     0,    78,    88,     0,     0,   108,   110,   140,
     187,   192,     0,   101,     0,     0,   122,     0,     0,   190,
       0,   111,     0,   109,   191,   193,     0,     0,     0,   112,
      75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    87,    21,    26,    46,    56,   127,
     128,    22,    31,    32,    50,    51,    52,    53,   115,    28,
      27,    81,   219,    73,   201,   142,   143,   178,   144,   145,
     204,   123,   124,   125,   107,   108,   227,   109,   110,    97,
     111,   187,   286,   356,   256,   257,   258,   348,   349,   350,
     259,   363,   290,   260,   261,   262,   338,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   393,   419,   432,   278,   279,   357,   403,    93,
     171,    94,    61,    88,    89,    90,   130,   169,   280
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -400
static const yytype_int16 yypact[] =
{
    -400,   424,  -400,     2,  -400,  -400,  -400,   -48,  -400,  -400,
    -400,    16,    21,    13,  -400,    42,    50,  -400,    65,  -400,
    -400,    93,  -400,   106,  -400,  -400,    -1,  -400,   124,   133,
     162,   171,  -400,    99,   169,   175,   183,   136,   161,   204,
     163,   174,    -6,   244,   193,   256,   257,   194,  -400,   191,
      29,  -400,   203,   197,   209,   264,  -400,   265,   210,   211,
      14,   214,   278,  -400,     1,   271,  -400,  -400,   215,  -400,
     212,   221,    40,   222,    15,   162,  -400,  -400,   285,  -400,
     225,  -400,  -400,   274,   277,   223,   288,  -400,    -4,  -400,
     229,  -400,   293,  -400,    -7,  -400,   232,   237,   233,   112,
    -400,  -400,   235,   238,   243,   248,   249,   251,    40,  -400,
    -400,   252,  -400,  -400,  -400,  -400,  -400,  -400,   191,   240,
     309,  -400,   319,   258,   274,  -400,   321,   -16,  -400,   314,
    -400,   316,  -400,  -400,    28,   254,   268,  -400,   331,  -400,
     270,  -400,    44,  -400,   266,   336,     1,   337,   339,   340,
     333,  -400,  -400,  -400,   342,  -400,   285,   280,   281,  -400,
    -400,   286,  -400,  -400,   282,  -400,  -400,  -400,  -400,   292,
     344,   294,  -400,   295,  -400,   356,   296,   290,   298,   364,
     303,   304,   310,   311,   305,  -400,   299,   313,  -400,   370,
      40,  -400,   274,  -400,  -400,  -400,  -400,  -400,   383,  -400,
     387,   324,  -400,    95,  -400,  -400,   327,   328,   384,   391,
    -400,   326,  -400,   332,   329,   335,   338,  -400,   228,  -400,
    -400,  -400,  -400,  -400,  -400,   341,   345,   343,   334,  -400,
    -400,  -400,   346,   403,  -400,  -400,   399,   318,   350,   352,
     228,   349,   418,   353,   358,   318,   318,  -400,   228,   318,
    -400,  -400,  -400,  -400,  -400,  -400,   108,  -400,   363,  -400,
    -400,    77,  -400,  -400,   -50,   374,   357,   366,   362,   159,
      68,   165,   145,    76,  -400,   167,   318,   -47,  -400,  -400,
      -3,  -400,   365,   422,   435,   236,  -400,   377,   437,  -400,
     386,   392,  -400,  -400,   414,   351,   394,   318,   318,  -400,
    -400,   168,    69,  -400,  -400,  -400,  -400,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,   318,   318,   318,
     318,   318,   318,   318,   318,   318,   318,  -400,  -400,  -400,
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,   318,  -400,
    -400,  -400,  -400,    51,   318,   457,  -400,    -3,   395,  -400,
      32,  -400,   396,   393,  -400,  -400,   398,  -400,  -400,  -400,
    -400,   397,  -400,   400,   392,  -400,    92,   115,  -400,  -400,
    -400,   374,   -23,   357,   366,   362,   159,    68,    68,   165,
     165,   165,   165,   145,   145,    76,    76,  -400,  -400,  -400,
    -400,  -400,  -400,   117,   -43,  -400,    48,    -3,   401,   302,
      -9,   453,   404,  -400,  -400,   236,   318,   318,   228,   228,
     318,   318,  -400,  -400,  -400,  -400,  -400,   302,  -400,  -400,
     402,  -400,   406,  -400,  -400,   127,   405,   429,  -400,  -400,
    -400,  -400,    62,  -400,   454,   409,   318,   228,   269,  -400,
     410,  -400,   407,  -400,  -400,  -400,   461,   228,   411,  -400,
    -400
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,  -400,
     360,  -400,  -400,  -400,  -400,   413,  -400,   -60,  -400,   151,
    -400,   -57,  -400,  -400,  -400,  -400,   315,  -400,  -400,  -400,
    -400,   297,  -400,   361,   301,  -400,  -400,   376,   385,   348,
    -400,  -400,  -400,  -400,   247,  -400,   201,  -400,   100,   152,
    -240,  -400,  -399,  -400,  -235,  -304,  -400,    82,  -400,   190,
     192,   189,   195,   188,   -64,  -113,   -63,   -61,  -227,  -233,
    -400,  -400,  -400,  -396,  -400,  -400,  -400,    98,   149,   412,
    -400,  -400,  -400,  -400,   417,  -400,  -400,  -400,  -400
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -220
static const yytype_int16 yytable[] =
{
     294,    92,   291,   370,    85,   346,   126,   420,   426,    95,
      23,   308,   299,   300,   302,   117,   304,    86,   119,   341,
     342,   431,    85,   113,    37,   121,    30,   343,   307,    38,
      96,   114,   309,   344,   390,    86,   166,   442,   413,   392,
      24,    25,   445,   340,   167,    39,   345,   168,   307,   339,
      40,   102,   103,   104,   105,   155,   410,   162,    41,   289,
     364,   304,   366,   367,    66,    67,   136,   234,   106,   132,
     235,   347,   421,    42,   372,   340,    45,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   185,   418,   188,   387,   388,   389,
      75,    43,   191,   220,    76,   193,   398,   430,   399,   394,
     221,   222,   400,   418,    44,   175,   233,   245,   246,   176,
     -61,   141,   398,   414,   234,   249,   391,   235,   400,   236,
     316,   317,    47,   438,   418,   439,   250,   251,   252,   253,
     307,    48,   254,   255,   369,   318,   319,   306,   307,   237,
     238,   239,   240,   241,   242,   243,   244,    29,    33,    34,
      35,    36,   281,   307,   324,   325,   326,   408,   427,   428,
      49,   425,   291,    55,   245,   246,   233,   340,   247,    54,
     248,   303,   249,    58,   234,    57,   307,   235,   411,   236,
     409,    59,   412,   250,   251,   252,   253,   443,   307,   254,
     255,   291,   435,   379,   380,   381,   382,   449,    60,   237,
     238,   239,   240,   241,   242,   243,   244,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   314,   315,   320,
     321,   322,   323,    62,   245,   246,   233,    63,   247,    64,
     248,   368,   249,   337,   234,   354,   355,   235,    65,   236,
     377,   378,    68,   250,   251,   252,   253,   383,   384,   254,
     255,   385,   386,    69,    70,    71,    72,    74,    78,   237,
     238,   239,   240,   241,   242,   243,   244,   289,    77,    79,
      80,    82,    83,    84,    91,   234,    92,    98,   235,    99,
     100,   101,   112,   118,   245,   246,   120,   122,   247,   126,
     248,   135,   249,   129,   131,   134,   138,   139,   140,   146,
     289,   156,   147,   250,   251,   252,   253,   148,   234,   254,
     255,   235,   149,   150,   151,   157,   289,   158,   154,   161,
     164,   159,   165,   170,   234,   245,   246,   235,   172,   173,
     174,   417,   444,   249,   179,   181,   177,   182,   183,   184,
     186,   189,   196,   190,   250,   251,   252,   253,   192,   233,
     254,   255,   195,   194,   197,   141,   198,   234,   245,   246,
     235,   202,   205,   211,   417,   200,   249,   203,   206,   207,
     210,   208,   209,   212,   245,   246,   213,   250,   251,   252,
     253,   216,   249,   254,   255,   217,   218,   223,   224,   226,
     225,   228,   230,   250,   251,   252,   253,   229,   231,   254,
     255,  -219,   232,   285,   284,   288,   282,   245,   246,   283,
     292,   287,   293,   295,     2,   249,   296,   297,     3,     4,
       5,     6,   298,   305,   310,   351,   250,   251,   252,   253,
     311,   352,   254,   255,     7,     8,     9,   313,    10,    11,
     312,   353,   358,   359,    12,    13,   360,    14,    15,    16,
      17,    18,   361,   307,   365,   395,   397,   401,   402,   405,
     407,   406,   422,   440,   423,   436,   416,   434,   437,   441,
     448,   446,   447,   433,   152,   160,   450,   163,   116,   215,
     199,   214,   429,   153,   180,   301,   362,   415,   371,   396,
     374,   376,   373,   424,   404,   133,   137,   375
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-400)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint16 yycheck[] =
{
     240,     8,   237,   307,     8,     8,    22,    16,   407,     8,
       8,    61,   245,   246,   249,    75,   256,    21,    78,    66,
      67,   417,     8,     8,     8,    82,    74,    74,    71,     8,
      29,    16,    82,    80,   338,    21,     8,   436,    81,   343,
      38,    39,   438,   276,    16,    32,    93,    19,    71,   276,
       8,    11,    12,    13,    14,   112,    79,    73,     8,     8,
     295,   301,   297,   298,    70,    71,    73,    16,    28,    73,
      19,    74,    81,     8,   309,   308,    77,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   151,   399,   156,   324,   325,   326,
      71,     8,   159,     8,    75,   162,    74,   411,    76,   344,
      15,    16,    80,   417,     8,    71,     8,    66,    67,    75,
       8,     9,    74,    75,    16,    74,    75,    19,    80,    21,
      62,    63,     8,    71,   438,    73,    85,    86,    87,    88,
      71,     8,    91,    92,    75,    77,    78,    70,    71,    41,
      42,    43,    44,    45,    46,    47,    48,     6,     7,     8,
       9,    10,   219,    71,    88,    89,    90,    75,   408,   409,
       8,   406,   407,    74,    66,    67,     8,   410,    70,     8,
      72,    73,    74,     8,    16,    16,    71,    19,    71,    21,
      75,     8,    75,    85,    86,    87,    88,   437,    71,    91,
      92,   436,    75,   316,   317,   318,   319,   447,    72,    41,
      42,    43,    44,    45,    46,    47,    48,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    68,    69,    64,
      65,    86,    87,    72,    66,    67,     8,    33,    70,    76,
      72,    73,    74,    76,    16,     9,    10,    19,    74,    21,
     314,   315,     8,    85,    86,    87,    88,   320,   321,    91,
      92,   322,   323,    70,     8,     8,    72,    76,    71,    41,
      42,    43,    44,    45,    46,    47,    48,     8,    75,    70,
      16,    16,    72,    72,    70,    16,     8,    16,    19,    74,
      78,    70,    70,     8,    66,    67,    71,    23,    70,    22,
      72,     8,    74,    80,    16,    76,    74,    70,    75,    74,
       8,    71,    74,    85,    86,    87,    88,    74,    16,    91,
      92,    19,    74,    74,    73,    16,     8,     8,    76,     8,
      16,    73,    16,    79,    16,    66,    67,    19,    70,     8,
      70,    72,    73,    74,     8,     8,    80,     8,     8,    16,
       8,    71,     8,    72,    85,    86,    87,    88,    72,     8,
      91,    92,    70,    81,    70,     9,    71,    16,    66,    67,
      19,    81,     8,    74,    72,    79,    74,    79,    75,    75,
      75,    71,    71,    70,    66,    67,    16,    85,    86,    87,
      88,     8,    74,    91,    92,     8,    72,    70,    70,     8,
      16,    75,    73,    85,    86,    87,    88,    75,    73,    91,
      92,     8,    74,    79,    71,    16,    75,    66,    67,    74,
      70,    75,    70,    74,     0,    74,     8,    74,     4,     5,
       6,     7,    74,    70,    60,    70,    85,    86,    87,    88,
      83,    19,    91,    92,    20,    21,    22,    85,    24,    25,
      84,    16,    75,    16,    30,    31,    70,    33,    34,    35,
      36,    37,    48,    71,    70,     8,    71,    71,    75,    71,
      70,    74,    19,    19,    70,    70,    75,    71,    49,    70,
      19,    71,    75,    81,   108,   124,    75,   127,    75,   192,
     175,   190,   410,   108,   146,   248,   295,   397,   308,   347,
     311,   313,   310,   405,   355,    88,    94,   312
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    95,     0,     4,     5,     6,     7,    20,    21,    22,
      24,    25,    30,    31,    33,    34,    35,    36,    37,    96,
      97,    99,   105,     8,    38,    39,   100,   114,   113,   113,
      74,   106,   107,   113,   113,   113,   113,     8,     8,    32,
       8,     8,     8,     8,     8,    77,   101,     8,     8,     8,
     108,   109,   110,   111,     8,    74,   102,    16,     8,     8,
      72,   176,    72,    33,    76,    74,    70,    71,     8,    70,
       8,     8,    72,   117,    76,    71,    75,    75,    71,    70,
      16,   115,    16,    72,    72,     8,    21,    98,   177,   178,
     179,    70,     8,   173,   175,     8,    29,   133,    16,    74,
      78,    70,    11,    12,    13,    14,    28,   128,   129,   131,
     132,   134,    70,     8,    16,   112,   109,   111,     8,   111,
      71,   115,    23,   125,   126,   127,    22,   103,   104,    80,
     180,    16,    73,   178,    76,     8,    73,   173,    74,    70,
      75,     9,   119,   120,   122,   123,    74,    74,    74,    74,
      74,    73,   131,   132,    76,   115,    71,    16,     8,    73,
     127,     8,    73,   104,    16,    16,     8,    16,    19,   181,
      79,   174,    70,     8,    70,    71,    75,    80,   121,     8,
     133,     8,     8,     8,    16,   115,     8,   135,   111,    71,
      72,   115,    72,   115,    81,    70,     8,    70,    71,   120,
      79,   118,    81,    79,   124,     8,    75,    75,    71,    71,
      75,    74,    70,    16,   128,   125,     8,     8,    72,   116,
       8,    15,    16,    70,    70,    16,     8,   130,    75,    75,
      73,    73,    74,     8,    16,    19,    21,    41,    42,    43,
      44,    45,    46,    47,    48,    66,    67,    70,    72,    74,
      85,    86,    87,    88,    91,    92,   138,   139,   140,   144,
     147,   148,   149,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   169,   170,
     182,   115,    75,    74,    71,    79,   136,    75,    16,     8,
     146,   148,    70,    70,   144,    74,     8,    74,    74,   163,
     163,   138,   148,    73,   144,    70,    70,    71,    61,    82,
      60,    83,    84,    85,    68,    69,    62,    63,    77,    78,
      64,    65,    86,    87,    88,    89,    90,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    76,   150,   162,
     163,    66,    67,    74,    80,    93,     8,    74,   141,   142,
     143,    70,    19,    16,     9,    10,   137,   171,    75,    16,
      70,    48,   140,   145,   148,    70,   148,   148,    73,    75,
     149,   153,   148,   154,   155,   156,   157,   158,   158,   159,
     159,   159,   159,   160,   160,   161,   161,   162,   162,   162,
     149,    75,   149,   166,   148,     8,   143,    71,    74,    76,
      80,    71,    75,   172,   172,    71,    74,    70,    75,    75,
      79,    71,    75,    81,    75,   142,    75,    72,   149,   167,
      16,    81,    19,    70,   171,   148,   146,   144,   144,   151,
     149,   167,   168,    81,    71,    75,    70,    49,    71,    73,
      19,    70,   146,   144,    73,   167,    71,    75,    19,   144,
      75
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
		std::string returnVariable	=(yyvsp[(8) - (9)]).strs[1];
		ostringstream shaderCode;
		ostringstream extraDeclarations;
		ostringstream finalCode;
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
					string sem=(type+"_")+m.name;
					if(m.semantic.length())
						sem=(sem+"_")+m.semantic;
					if(m.semantic==string("gl_VertexID"))
						sem=m.semantic;
					//shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
					shaderCode<<"in "<<it->storage<<' '<<m.type<<' '<<sem<<";"<<endl;
					extraDeclarations<<structInstanceName<<"."<<m.name<<"="<<sem<<";\n";
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
		// Add the return variable.
		if(returnType!=string("void"))
		{
			map<string,Struct*>::const_iterator u=gEffect->m_structs.find(returnType);
			if(u==gEffect->m_structs.end())
			{
				// if we're returning a simple type, we declare it as an output.
				shaderCode<<"out "<<returnType<<" "<<returnVariable<<"_out;\n";
				finalCode<<returnVariable<<"_out="<<returnVariable<<";"<<endl;
			}
			else
			{
				// if we're returning a struct, we declare outputs for each of its members,
				// then fill in them all.
				const Struct *s=u->second;
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					string sem=(returnType+"_")+m.name;
					if(m.semantic.length())
						sem=(sem+"_")+m.semantic;
					shaderCode<<"out "<<m.type<<' '<<sem<<";"<<endl;
					finalCode<<sem<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
			}
		}
		// Add definition and code
		shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
		shaderCode<<"void main()\n{\n";
		if(extraDeclarations.str().length())
			shaderCode<<extraDeclarations.str()<<"\n";
		shaderCode<<"#line "<<content_linenumber<<" "<<current_filenumber<<endl;
		shaderCode<<shaderContent<<"\n"<<finalCode.str()<<"\n}\n";
		gEffect->m_shaderLayouts[shaderName]	=currentCsLayout;
		gEffect->m_shaders[shaderName]			=shaderCode.str();
		// now we must put a #line directive in the shared code, because we've just snipped out a bunch of what was there:
		
		gEffect->m_sharedCode<<"#line "<<(glfxget_lineno()+(last_linenumber-global_linenumber))<<" "<<current_filenumber<<endl;
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 356 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 361 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 364 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 367 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 374 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 380 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 385 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 390 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 395 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 400 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 32:
/* Line 1792 of yacc.c  */
#line 411 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 415 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 418 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 422 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_techniques[(yyvsp[(3) - (7)]).strs[0]] = (yyvsp[(5) - (7)]).tech;
	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 426 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 430 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 435 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 439 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 443 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 447 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 451 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 456 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		   }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 461 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 465 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 469 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 475 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
    gLexPassthrough=false;
}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 481 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 485 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 492 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 498 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 501 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 504 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 54:
/* Line 1792 of yacc.c  */
#line 516 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 55:
/* Line 1792 of yacc.c  */
#line 527 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 532 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 57:
/* Line 1792 of yacc.c  */
#line 563 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="[]";
				}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 567 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 572 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (3)]).strs[0];
		string type		=(yyvsp[(2) - (3)]).strs[0];
		string id		=(yyvsp[(3) - (3)]).strs[0];
		(yyval).strs[0]		= storage	;
		(yyval).strs[1]		= type		;
		(yyval).strs[2]		= id		;
	}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 581 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 585 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 589 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 594 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 599 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 604 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 610 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 617 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 68:
/* Line 1792 of yacc.c  */
#line 628 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 69:
/* Line 1792 of yacc.c  */
#line 642 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable = (yyvsp[(1) - (5)]).boolean;
	(yyval).prog = (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0] = (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 649 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders));
    delete (yyvsp[(1) - (1)]).shaders;
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 655 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 72:
/* Line 1792 of yacc.c  */
#line 665 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 73:
/* Line 1792 of yacc.c  */
#line 678 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 694 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 703 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 707 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
			 }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 712 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 719 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 80:
/* Line 1792 of yacc.c  */
#line 768 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 81:
/* Line 1792 of yacc.c  */
#line 829 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string compiledShaderName	=(yyvsp[(1) - (1)]).strs[0];
			(yyval).strs[0]					=compiledShaderName;
			(yyval).num						=0;
			(yyval).lineno					=(yyvsp[(1) - (1)]).lineno;
		}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 836 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

			CompiledShader *compiledShader					=gEffect->m_compiledShaders[compiledShaderName];

			gEffect->m_compiledShaders[compiledShaderName]	=compiledShader=new CompiledShader;
			compiledShader->m_functionName					=(yyvsp[(5) - (8)]).strs[0];
			compiledShader->shaderType						=(yyvsp[(1) - (8)]).sType;
			compiledShader->version							=(yyval).num=version_num;
		}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 862 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 873 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 879 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 883 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 887 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 892 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 897 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 901 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 910 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 916 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 921 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 94:
/* Line 1792 of yacc.c  */
#line 934 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+" ";
			(yyval).strs[0]+=(yyvsp[(2) - (2)]).strs[0];
		}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 939 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 943 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 947 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 951 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 955 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 959 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 963 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 967 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 971 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 975 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
				}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 980 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 984 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 988 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 992 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 996 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1000 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1004 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1008 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0];
				}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1012 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1016 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1020 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1024 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
				(yyval).strs[1]=(yyvsp[(2) - (3)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (3)]).lineno;
			}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1030 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1035 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1039 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1043 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1046 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1050 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1055 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1060 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1064 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1068 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1072 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1076 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1089 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1093 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1097 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
	}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1102 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1106 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1110 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1114 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1118 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1122 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1126 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1130 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1134 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1138 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1143 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1147 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1155 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1159 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1163 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1167 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1171 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1175 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1179 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1183 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1187 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1191 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1195 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1199 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1203 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1207 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1211 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1215 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1219 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1223 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1227 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1231 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1235 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1239 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1243 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1251 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1255 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1259 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1263 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1267 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1271 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1275 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1280 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1287 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1294 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1298 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1305 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1309 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1313 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1317 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1321 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1325 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1333 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1341 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1345 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 203:
/* Line 1792 of yacc.c  */
#line 1357 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1361 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1365 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1370 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1374 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1377 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1381 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1386 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1390 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 212:
/* Line 1792 of yacc.c  */
#line 1499 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1504 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1510 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1515 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1519 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1524 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1529 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1534 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 4128 "src/glfxLALRParser.cpp"
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
#line 1537 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
