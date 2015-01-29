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
    #include <algorithm>
    
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
			return "layout(rgba32f)";
		}
		if(s==string("float"))
		{
			return "layout(r32f)";
		}
		return "";
	}
	void stringReplaceAll(std::string& str, const std::string& from, const std::string& to)
	{
		if(from.empty())
			return;
		size_t start_pos = 0;
		while((start_pos = str.find(from, start_pos)) != std::string::npos)
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}
	string getGLInputSemantic(int s);

/* Line 371 of yacc.c  */
#line 178 "src/glfxLALRParser.cpp"

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
     STRUCT = 287,
     DEFINE = 288,
     MACRO_DEFINITION = 289,
     EOL = 290,
     DECL_SHADER = 291,
     PROFILE = 292,
     CS_LAYOUT = 293,
     RW_TEXTURE2D = 294,
     RW_TEXTURE3D = 295,
     RW_TEXTURE3D_FLOAT4 = 296,
     TEXTURE2DMS = 297,
     IMAGE3D = 298,
     KNOWN_TYPE = 299,
     RETURN = 300,
     BREAK = 301,
     CONTINUE = 302,
     DO = 303,
     FOR = 304,
     GOTO = 305,
     IF = 306,
     WHILE = 307,
     ELSE = 308,
     TIMES_EQUALS = 309,
     OVER_EQUALS = 310,
     PERCENT_EQUALS = 311,
     PLUS_EQUALS = 312,
     MINUS_EQUALS = 313,
     LEFT_SHIFT_EQUALS = 314,
     RIGHT_SHIFT_EQUALS = 315,
     AND_EQUALS = 316,
     XOR_EQUALS = 317,
     OR_EQUALS = 318,
     AND = 319,
     OR = 320,
     LESS_EQ = 321,
     GRTR_EQ = 322,
     LEFT_SHIFT = 323,
     RIGHT_SHIFT = 324,
     PLUS_PLUS = 325,
     MINUS_MINUS = 326,
     EQ_EQ = 327,
     NOT_EQ = 328
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
#line 317 "src/glfxLALRParser.cpp"

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
#define YYLAST   525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  90
/* YYNRULES -- Number of rules.  */
#define YYNRULES  224
/* YYNRULES -- Number of states.  */
#define YYNSTATES  456

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   328

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    96,     2,     2,     2,    94,    89,     2,
      78,    79,    92,    90,    75,    91,    97,    93,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    83,    74,
      81,    80,    82,    86,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    84,     2,    85,    88,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,    87,    77,    95,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    24,    29,
      31,    36,    39,    43,    47,    51,    58,    63,    70,    76,
      81,    91,    99,   101,   109,   115,   119,   122,   124,   126,
     128,   130,   134,   135,   143,   146,   148,   154,   162,   166,
     170,   174,   176,   178,   180,   186,   190,   192,   194,   195,
     196,   197,   201,   202,   205,   206,   210,   212,   213,   217,
     220,   221,   225,   227,   228,   230,   232,   234,   237,   240,
     243,   244,   246,   249,   251,   257,   259,   262,   264,   267,
     269,   280,   286,   294,   304,   309,   315,   317,   326,   331,
     336,   337,   340,   341,   345,   347,   350,   352,   353,   357,
     360,   362,   366,   368,   372,   374,   378,   383,   387,   391,
     394,   396,   399,   401,   407,   415,   421,   429,   439,   443,
     446,   449,   453,   455,   457,   459,   460,   462,   463,   467,
     469,   473,   475,   479,   481,   483,   485,   487,   489,   491,
     493,   495,   497,   499,   501,   503,   509,   511,   515,   517,
     521,   523,   527,   529,   533,   535,   539,   541,   545,   549,
     551,   555,   559,   563,   567,   569,   573,   577,   579,   583,
     587,   589,   593,   597,   601,   603,   605,   608,   611,   614,
     616,   618,   620,   622,   624,   626,   628,   633,   638,   642,
     646,   649,   652,   656,   658,   660,   664,   669,   671,   675,
     677,   679,   683,   685,   687,   690,   693,   694,   699,   702,
     703,   706,   708,   712,   713,   716,   718,   723,   725,   728,
     732,   733,   735,   737,   739
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      99,     0,    -1,    99,   100,    -1,    -1,     7,   117,     8,
     121,    74,   119,    -1,    35,    -1,   101,    -1,     4,   104,
     105,     8,    74,    -1,     4,     8,     8,    74,    -1,    38,
      -1,    22,   110,     8,    74,    -1,    22,   111,    -1,    41,
       8,    74,    -1,    41,     8,    75,    -1,    33,    34,    35,
      -1,    32,     8,    76,   180,    77,    74,    -1,    27,     8,
     181,    74,    -1,    37,     8,    78,    18,    79,    74,    -1,
      36,     8,    80,   138,    74,    -1,    22,   117,   106,   119,
      -1,   103,     8,     8,    78,   123,    79,   122,   120,   119,
      -1,     6,   117,     8,    76,   133,    77,   119,    -1,   109,
      -1,    26,   117,     8,    76,   107,    77,   119,    -1,    23,
     117,    18,    18,   119,    -1,    23,    18,    18,    -1,     5,
     118,    -1,    42,    -1,    43,    -1,    39,    -1,    40,    -1,
      81,     8,    82,    -1,    -1,    78,    18,    75,    18,    75,
      18,    79,    -1,   107,   108,    -1,   108,    -1,    24,     8,
      76,   130,    77,    -1,    24,   117,     8,    76,   130,    77,
     119,    -1,    78,   114,    79,    -1,    78,   112,    79,    -1,
     112,    75,   113,    -1,   113,    -1,   115,    -1,     8,    -1,
     115,    75,   115,    75,   115,    -1,     8,    80,   116,    -1,
       8,    -1,    18,    -1,    -1,    -1,    -1,    76,   143,    77,
      -1,    -1,    83,     8,    -1,    -1,   123,    75,   124,    -1,
     124,    -1,    -1,   126,   125,   129,    -1,    84,    85,    -1,
      -1,   127,     8,     8,    -1,     9,    -1,    -1,    15,    -1,
      17,    -1,    16,    -1,    83,    18,    -1,    83,   128,    -1,
      83,     8,    -1,    -1,   131,    -1,   131,   132,    -1,   132,
      -1,    25,     8,    76,   133,    77,    -1,   134,    -1,   134,
     137,    -1,   137,    -1,   134,   136,    -1,   136,    -1,     8,
      78,    21,    75,    21,    75,    21,    75,    21,    79,    -1,
      12,    78,     8,    79,    74,    -1,    13,    78,     8,    75,
      18,    79,    74,    -1,    14,    78,     8,    75,   135,    75,
      18,    79,    74,    -1,   139,    80,   140,    74,    -1,    11,
      78,   138,    79,    74,    -1,     8,    -1,    31,    78,     8,
      75,     8,    78,    79,    79,    -1,    30,    78,    18,    79,
      -1,     8,    78,    79,   141,    -1,    -1,    83,   142,    -1,
      -1,   142,    75,   176,    -1,   176,    -1,   143,   149,    -1,
     149,    -1,    -1,    23,    18,    18,    -1,   187,   146,    -1,
     147,    -1,   146,    75,   147,    -1,   148,    -1,   148,    80,
     172,    -1,     8,    -1,    78,   148,    79,    -1,   148,    84,
      18,    85,    -1,   148,    84,    85,    -1,   148,    78,    79,
      -1,   153,    74,    -1,    74,    -1,   145,    74,    -1,   152,
      -1,    51,    78,   153,    79,   149,    -1,    51,    78,   153,
      79,   149,    53,   149,    -1,    52,    78,   153,    79,   149,
      -1,    48,   149,    52,    78,   153,    79,    74,    -1,    49,
      78,   150,    74,   151,    74,   151,    79,   149,    -1,    50,
       8,    74,    -1,    47,    74,    -1,    46,    74,    -1,    45,
     151,    74,    -1,   144,    -1,   153,    -1,   145,    -1,    -1,
     153,    -1,    -1,    76,   143,    77,    -1,   154,    -1,   153,
      75,   154,    -1,   156,    -1,   168,   155,   154,    -1,    80,
      -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,
      -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,   157,    -1,   157,    86,   153,    83,   156,    -1,   158,
      -1,   157,    65,   158,    -1,   159,    -1,   158,    64,   159,
      -1,   160,    -1,   159,    87,   160,    -1,   161,    -1,   160,
      88,   161,    -1,   162,    -1,   161,    89,   162,    -1,   163,
      -1,   162,    72,   163,    -1,   162,    73,   163,    -1,   164,
      -1,   163,    81,   164,    -1,   163,    82,   164,    -1,   163,
      66,   164,    -1,   163,    67,   164,    -1,   165,    -1,   164,
      68,   165,    -1,   164,    69,   165,    -1,   166,    -1,   165,
      90,   166,    -1,   165,    91,   166,    -1,   167,    -1,   166,
      92,   167,    -1,   166,    93,   167,    -1,   166,    94,   167,
      -1,   168,    -1,   170,    -1,    70,   168,    -1,    71,   168,
      -1,   169,   167,    -1,    89,    -1,    92,    -1,    90,    -1,
      91,    -1,    95,    -1,    96,    -1,   174,    -1,   170,    84,
     153,    85,    -1,   170,    78,   171,    79,    -1,   170,    78,
      79,    -1,   170,    97,     8,    -1,   170,    70,    -1,   170,
      71,    -1,   171,    75,   154,    -1,   154,    -1,   154,    -1,
      76,   173,    77,    -1,    76,   173,    75,    77,    -1,   172,
      -1,   173,    75,   172,    -1,     8,    -1,   175,    -1,    78,
     153,    79,    -1,    18,    -1,    21,    -1,     9,   177,    -1,
      10,   177,    -1,    -1,     8,     8,   179,    74,    -1,    83,
       8,    -1,    -1,   180,   178,    -1,   178,    -1,    76,   182,
      77,    -1,    -1,   182,   183,    -1,   183,    -1,   184,    80,
     186,    74,    -1,   102,    -1,     8,   185,    -1,    84,    18,
      85,    -1,    -1,     8,    -1,    18,    -1,    21,    -1,     8,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   120,   124,   128,   131,   134,   150,   156,
     160,   168,   174,   180,   186,   189,   207,   247,   257,   274,
     281,   377,   382,   385,   388,   395,   401,   406,   406,   406,
     406,   411,   417,   421,   432,   436,   439,   443,   447,   451,
     456,   460,   464,   468,   472,   477,   482,   486,   491,   497,
     503,   507,   514,   519,   523,   525,   537,   549,   553,   584,
     589,   593,   602,   607,   610,   615,   620,   625,   630,   636,
     642,   647,   654,   665,   679,   686,   692,   702,   715,   723,
     731,   740,   744,   749,   756,   805,   866,   873,   899,   910,
     917,   920,   925,   929,   934,   938,   947,   954,   958,   971,
     979,   983,   987,   991,  1029,  1033,  1037,  1042,  1046,  1050,
    1055,  1059,  1063,  1068,  1072,  1076,  1080,  1084,  1089,  1093,
    1097,  1101,  1116,  1121,  1125,  1130,  1132,  1137,  1141,  1147,
    1151,  1155,  1159,  1163,  1167,  1168,  1169,  1170,  1171,  1172,
    1173,  1174,  1175,  1176,  1180,  1184,  1189,  1193,  1197,  1201,
    1205,  1209,  1213,  1217,  1221,  1225,  1230,  1234,  1238,  1242,
    1246,  1250,  1254,  1258,  1262,  1266,  1270,  1274,  1278,  1282,
    1286,  1290,  1294,  1298,  1302,  1306,  1310,  1314,  1318,  1322,
    1322,  1322,  1322,  1322,  1322,  1326,  1330,  1334,  1338,  1342,
    1346,  1350,  1354,  1358,  1362,  1367,  1374,  1381,  1388,  1395,
    1399,  1403,  1407,  1411,  1415,  1423,  1432,  1435,  1447,  1452,
    1455,  1460,  1464,  1468,  1471,  1476,  1480,  1589,  1594,  1600,
    1606,  1609,  1614,  1619,  1624
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
  "SET_BLEND_COMMAND", "SV_DISPATCHTHREADID", "SV_GROUPTHREADID",
  "SV_GROUPID", "NUM", "INCLUDE", "SAMPLER", "FLOAT", "LAYOUT", "LINE",
  "TECHNIQUE", "PASS", "GROUP", "RENDER_STATE_DECL", "QUOTED_STRING",
  "SHADER_LINE", "SHADER_TYPE", "COMPILE_SHADER", "STRUCT", "DEFINE",
  "MACRO_DEFINITION", "EOL", "DECL_SHADER", "PROFILE", "CS_LAYOUT",
  "RW_TEXTURE2D", "RW_TEXTURE3D", "RW_TEXTURE3D_FLOAT4", "TEXTURE2DMS",
  "IMAGE3D", "KNOWN_TYPE", "RETURN", "BREAK", "CONTINUE", "DO", "FOR",
  "GOTO", "IF", "WHILE", "ELSE", "TIMES_EQUALS", "OVER_EQUALS",
  "PERCENT_EQUALS", "PLUS_EQUALS", "MINUS_EQUALS", "LEFT_SHIFT_EQUALS",
  "RIGHT_SHIFT_EQUALS", "AND_EQUALS", "XOR_EQUALS", "OR_EQUALS", "AND",
  "OR", "LESS_EQ", "GRTR_EQ", "LEFT_SHIFT", "RIGHT_SHIFT", "PLUS_PLUS",
  "MINUS_MINUS", "EQ_EQ", "NOT_EQ", "';'", "','", "'{'", "'}'", "'('",
  "')'", "'='", "'<'", "'>'", "':'", "'['", "']'", "'?'", "'|'", "'^'",
  "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'!'", "'.'", "$accept",
  "prog", "tok", "line_statement", "ignore_line_statement",
  "shader_and_layout", "texture_type", "optional_templateval",
  "layout_params", "technique_decls", "group_technique_decl",
  "technique_decl", "cs_layout_spec", "normal_layout_spec", "tx_layout",
  "layout_s", "cs_layout", "layout_el", "layout_def", "lex_fx",
  "shader_fx", "lex_passthrough", "function_content", "read_block",
  "optional_return_semantic", "param_declaration_list",
  "param_declaration", "opt_sq", "param", "opt_storage", "input_semantic",
  "location", "tech_def", "pass_list", "pass_def", "prog_def",
  "shaders_list", "vec4", "shader_fn", "shader_def", "shader_compile",
  "shader_lvalue", "shader_rvalue", "shader_layout", "shader_layout_list",
  "statement_list", "line_statement_in_shader", "declaration",
  "init_declarator_list", "init_declarator", "declarator", "statement",
  "for_init_statement", "optional_expression", "compound_statement",
  "expression", "assignment_exp", "assignment_operator", "conditional_exp",
  "logical_or_exp", "logical_and_exp", "inclusive_or_exp",
  "exclusive_or_exp", "and_exp", "equality_exp", "relational_exp",
  "shift_expression", "additive_exp", "mult_exp", "cast_exp", "unary_exp",
  "unary_operator", "postfix_exp", "argument_exp_list", "initializer",
  "initializer_list", "primary_exp", "const", "layout", "read_parenthesis",
  "struct_member", "optional_semantic", "struct_members",
  "optional_render_state_list", "render_state_list",
  "render_state_command", "render_state_identifier", "optional_index",
  "render_state_rvalue", "type_spec", YY_NULL
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
     325,   326,   327,   328,    59,    44,   123,   125,    40,    41,
      61,    60,    62,    58,    91,    93,    63,   124,    94,    38,
      43,    45,    42,    47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,    99,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   101,   102,   103,   104,   104,   104,
     104,   105,   105,   106,   107,   107,   108,   109,   110,   111,
     112,   112,   113,   113,   114,   115,   116,   116,   117,   118,
     119,   120,   121,   122,   122,   123,   123,   123,   124,   125,
     125,   126,   127,   127,   128,   128,   128,   129,   129,   129,
     129,   130,   131,   131,   132,   133,   134,   134,   134,   134,
     135,   136,   136,   136,   137,   137,   138,   138,   139,   140,
     140,   141,   141,   142,   142,   143,   143,   143,   144,   145,
     146,   146,   147,   147,   148,   148,   148,   148,   148,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   150,   150,   150,   151,   151,   152,   153,
     153,   154,   154,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   156,   156,   157,   157,   158,   158,
     159,   159,   160,   160,   161,   161,   162,   162,   162,   163,
     163,   163,   163,   163,   164,   164,   164,   165,   165,   165,
     166,   166,   166,   166,   167,   168,   168,   168,   168,   169,
     169,   169,   169,   169,   169,   170,   170,   170,   170,   170,
     170,   170,   171,   171,   172,   172,   172,   173,   173,   174,
     174,   174,   175,   175,   176,   176,   177,   178,   179,   179,
     180,   180,   181,   181,   182,   182,   183,   183,   184,   185,
     185,   186,   186,   186,   187
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     5,     4,     1,
       4,     2,     3,     3,     3,     6,     4,     6,     5,     4,
       9,     7,     1,     7,     5,     3,     2,     1,     1,     1,
       1,     3,     0,     7,     2,     1,     5,     7,     3,     3,
       3,     1,     1,     1,     5,     3,     1,     1,     0,     0,
       0,     3,     0,     2,     0,     3,     1,     0,     3,     2,
       0,     3,     1,     0,     1,     1,     1,     2,     2,     2,
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
       3,     0,     1,     0,    49,    48,    48,     0,    48,    48,
      48,     0,     0,     0,     5,     0,     0,     9,     0,     2,
       6,     0,    22,     0,    29,    30,    27,    28,    32,    26,
       0,     0,     0,     0,    11,     0,     0,     0,     0,   213,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    43,     0,    41,     0,    42,     0,     0,    50,     0,
       0,     0,     0,     0,     0,    14,     0,     0,    12,    13,
       0,     8,     0,     0,     0,     0,     0,     0,    39,    38,
       0,    10,     0,    19,    50,     0,     0,   220,     0,   217,
       0,   215,     0,    16,     0,   211,     0,    86,     0,     0,
       0,    57,    31,     7,     0,     0,     0,     0,     0,     0,
      75,    79,    77,     0,    50,    46,    47,    45,    40,    42,
       0,     0,     0,    24,     0,     0,    71,    73,     0,     0,
      35,     0,   218,     0,   212,   214,     0,   209,     0,   210,
       0,    18,     0,    62,     0,    56,    60,     0,     0,     0,
       0,     0,     0,    50,    78,    76,    90,     4,     0,     0,
       0,    50,    72,     0,    50,    34,     0,    25,   221,   222,
     223,     0,     0,     0,    15,     0,    17,    63,    54,     0,
      70,     0,     0,     0,     0,     0,     0,    21,     0,     0,
      44,     0,     0,    37,     0,    23,   219,   216,   208,   207,
       0,    55,     0,     0,    59,     0,    58,    61,     0,     0,
       0,     0,    88,     0,    84,     0,     0,     0,     0,    53,
      97,    50,    69,    64,    66,    65,    67,    68,    85,    81,
       0,     0,     0,    92,    33,    74,    36,     0,   199,   202,
     203,     0,   127,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,    97,     0,   179,   181,   182,   180,   183,
     184,     0,   122,     0,    96,   112,     0,   129,   131,   144,
     146,   148,   150,   152,   154,   156,   159,   164,   167,   170,
     174,     0,   175,   185,   200,     0,    20,     0,     0,     0,
       0,    89,     0,     0,   199,     0,   126,   120,   119,     0,
     125,     0,     0,     0,   176,   177,     0,     0,    51,    95,
     111,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   133,     0,   178,   174,   190,   191,     0,     0,
       0,   104,     0,    99,   100,   102,    82,     0,     0,   206,
     206,    91,    94,    87,    98,   121,     0,   124,     0,   123,
     118,     0,     0,   128,   201,   130,   147,     0,   149,   151,
     153,   155,   157,   158,   162,   163,   160,   161,   165,   166,
     168,   169,   171,   172,   173,   132,   188,   193,     0,     0,
     189,     0,     0,     0,     0,     0,     0,     0,   204,   205,
       0,     0,   127,     0,     0,     0,     0,   187,   186,   105,
     101,   108,     0,   194,   103,     0,   107,     0,    83,    93,
       0,     0,   113,   115,   145,   192,   197,     0,   106,     0,
       0,   127,     0,     0,   195,     0,   116,     0,   114,   196,
     198,     0,     0,     0,   117,    80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    89,    21,    28,    48,    58,   129,
     130,    22,    33,    34,    52,    53,    54,    55,   117,    30,
      29,    83,   221,    75,   203,   144,   145,   180,   146,   147,
     227,   206,   125,   126,   127,   109,   110,   232,   111,   112,
      99,   113,   189,   291,   361,   261,   262,   263,   353,   354,
     355,   264,   368,   295,   265,   266,   267,   343,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   398,   424,   437,   283,   284,   362,   408,
      95,   173,    96,    63,    90,    91,    92,   132,   171,   285
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -406
static const yytype_int16 yypact[] =
{
    -406,   378,  -406,    14,  -406,  -406,  -406,   -68,  -406,  -406,
    -406,    13,    25,    -6,  -406,    30,    51,  -406,    61,  -406,
    -406,    93,  -406,    95,  -406,  -406,  -406,  -406,    45,  -406,
     136,   149,   151,   157,  -406,    89,   155,   171,   205,   100,
     122,   180,   154,   142,    42,   218,   164,   220,   237,   194,
    -406,   198,    68,  -406,   195,   207,   202,   267,  -406,   269,
     213,   228,     3,   231,   302,  -406,     1,   297,  -406,  -406,
     238,  -406,   235,   244,    34,   245,    22,   151,  -406,  -406,
     312,  -406,   247,  -406,  -406,   298,   305,   246,   315,  -406,
      -4,  -406,   254,  -406,   329,  -406,    -7,  -406,   260,   266,
     263,   175,  -406,  -406,   261,   268,   270,   271,   274,   276,
      34,  -406,  -406,   264,  -406,  -406,  -406,  -406,  -406,  -406,
     198,   272,   327,  -406,   351,   286,   298,  -406,   354,    20,
    -406,   346,  -406,   347,  -406,  -406,    90,   283,   293,  -406,
     360,  -406,   306,  -406,    85,  -406,   295,   369,     1,   379,
     380,   381,   368,  -406,  -406,  -406,   382,  -406,   312,   316,
     320,  -406,  -406,   321,  -406,  -406,   318,  -406,  -406,  -406,
    -406,   332,   399,   334,  -406,   337,  -406,   400,   335,   336,
     339,   409,   341,   344,   349,   350,   348,  -406,   352,   355,
    -406,   408,    34,  -406,   298,  -406,  -406,  -406,  -406,  -406,
     420,  -406,   423,   356,  -406,   115,  -406,  -406,   359,   361,
     416,   428,  -406,   358,  -406,   362,   363,   365,   366,  -406,
     201,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,
     364,   367,   371,   370,  -406,  -406,  -406,   372,   430,  -406,
    -406,   421,   280,   373,   374,   201,   376,   441,   377,   383,
     280,   280,  -406,   201,   280,  -406,  -406,  -406,  -406,  -406,
    -406,   104,  -406,   384,  -406,  -406,   168,  -406,  -406,   -57,
     386,   375,   385,   387,   183,    33,   200,   190,   147,  -406,
     204,   280,   -47,  -406,  -406,    -2,  -406,   389,   431,   438,
     285,  -406,   388,   439,  -406,   390,   391,  -406,  -406,   407,
     303,   394,   280,   280,  -406,  -406,   140,    91,  -406,  -406,
    -406,  -406,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   280,   280,   280,   280,   280,   280,   280,
     280,   280,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,
    -406,  -406,  -406,   280,  -406,  -406,  -406,  -406,    50,   280,
     452,  -406,    -2,   395,  -406,    26,  -406,   396,   393,  -406,
    -406,   402,  -406,  -406,  -406,  -406,   397,  -406,   404,   391,
    -406,   133,   146,  -406,  -406,  -406,   386,   -48,   375,   385,
     387,   183,    33,    33,   200,   200,   200,   200,   190,   190,
     147,   147,  -406,  -406,  -406,  -406,  -406,  -406,   148,   -33,
    -406,    40,    -2,   401,   265,   -13,   444,   405,  -406,  -406,
     285,   280,   280,   201,   201,   280,   280,  -406,  -406,  -406,
    -406,  -406,   265,  -406,  -406,   398,  -406,   406,  -406,  -406,
     158,   410,   429,  -406,  -406,  -406,  -406,   -26,  -406,   448,
     411,   280,   201,   236,  -406,   412,  -406,   413,  -406,  -406,
    -406,   453,   201,   414,  -406,  -406
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,  -406,
     357,  -406,  -406,  -406,  -406,   417,  -406,   -62,  -406,   196,
    -406,   -59,  -406,  -406,  -406,  -406,   311,  -406,  -406,  -406,
    -406,  -406,   296,  -406,   392,   299,  -406,  -406,   403,   415,
     353,  -406,  -406,  -406,  -406,   242,  -406,   189,  -406,    94,
     145,  -245,  -406,  -405,  -406,  -240,  -309,  -406,    83,  -406,
     186,   185,   187,   188,   184,   -20,  -186,   -23,   -19,  -264,
    -238,  -406,  -406,  -406,  -402,  -406,  -406,  -406,    96,   144,
     418,  -406,  -406,  -406,  -406,   419,  -406,  -406,  -406,  -406
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -225
static const yytype_int16 yytable[] =
{
     299,    94,   296,   375,    87,   425,   351,   431,   313,    97,
      32,    87,   304,   305,   307,   119,   309,   344,   121,    88,
     436,    39,    23,   346,   347,   123,    88,   312,    41,   314,
     115,   348,    98,    40,   395,   415,   447,   349,    42,   397,
     116,   450,   312,   345,   128,   104,   105,   106,   107,   443,
     350,   444,   418,    24,    25,   157,    26,    27,   294,    43,
     369,   309,   371,   372,   108,   392,   393,   394,   239,    44,
     138,   240,   426,   134,   377,   345,   352,   345,   345,   345,
     345,   345,   345,   345,   345,   345,   345,   345,   345,   345,
     345,   345,   345,   345,   187,   423,   190,   164,   168,   321,
     322,    45,   193,    46,   403,   195,   404,   435,   169,   399,
     405,   170,   238,   423,   323,   324,    68,    69,   403,   419,
     250,   251,   239,   222,   405,   240,    47,   241,   254,   396,
     223,   224,   225,   226,   423,   384,   385,   386,   387,   255,
     256,   257,   258,    77,    49,   259,   260,    78,   238,   242,
     243,   244,   245,   246,   247,   248,   249,    50,   239,    51,
     177,   240,   286,   241,   178,    56,   312,    57,   432,   433,
     374,   430,   296,    59,   250,   251,    62,   345,   252,    60,
     253,   308,   254,   -63,   143,   242,   243,   244,   245,   246,
     247,   248,   249,   255,   256,   257,   258,   448,    64,   259,
     260,   296,    31,    35,    36,    37,    38,   454,   312,   238,
     250,   251,   413,    61,   252,    65,   253,   373,   254,   239,
      67,   312,   240,   416,   241,   414,    70,   417,    72,   255,
     256,   257,   258,   312,    66,   259,   260,   440,    71,   329,
     330,   331,   311,   312,   294,    73,   242,   243,   244,   245,
     246,   247,   248,   249,   239,   319,   320,   240,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   325,   326,
      74,   250,   251,   294,    79,   252,    81,   253,    76,   254,
     327,   328,    80,   239,   342,    82,   240,    84,   294,    85,
     255,   256,   257,   258,   359,   360,   259,   260,   239,   382,
     383,   240,   388,   389,    86,    93,   250,   251,   390,   391,
      94,   238,   422,   449,   254,   100,   101,   102,   103,   114,
     120,   239,   122,   124,   240,   255,   256,   257,   258,   128,
     131,   259,   260,   133,   136,   250,   251,   137,   140,   148,
     141,   422,   142,   254,   156,   159,   149,   158,   150,   151,
     250,   251,   152,   153,   255,   256,   257,   258,   254,   160,
     259,   260,   163,   161,   166,   167,   172,   174,   175,   255,
     256,   257,   258,   250,   251,   259,   260,   181,     2,   179,
     176,   254,     3,     4,     5,     6,   186,   183,   184,   185,
     188,   191,   255,   256,   257,   258,   192,   194,   259,   260,
       7,     8,     9,   196,    10,    11,   197,   198,   199,   143,
      12,    13,   200,    14,    15,    16,    17,   207,   202,    18,
     208,   204,   205,   209,   210,   211,   215,   212,   218,   214,
     213,   219,   220,   228,   230,   229,   231,   233,  -224,   293,
     235,   234,   236,   287,   237,   288,   289,   297,   298,   301,
     315,   292,   357,   290,   300,   302,   358,   364,   310,   366,
     400,   303,   316,   356,   365,   427,   312,   363,   370,   445,
     402,   406,   407,   317,   453,   411,   318,   410,   412,   428,
     421,   439,   442,   438,   441,   446,   165,   451,   201,   367,
     217,   216,   452,   455,   118,   306,   420,   401,   434,   376,
     378,   182,   381,   379,   409,   380,   429,     0,     0,   135,
       0,     0,     0,   154,   139,     0,     0,     0,   162,     0,
       0,     0,     0,     0,     0,   155
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-406)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     245,     8,   242,   312,     8,    18,     8,   412,    65,     8,
      78,     8,   250,   251,   254,    77,   261,   281,    80,    23,
     422,     8,     8,    70,    71,    84,    23,    75,    34,    86,
       8,    78,    31,     8,   343,    83,   441,    84,     8,   348,
      18,   443,    75,   281,    24,    11,    12,    13,    14,    75,
      97,    77,    85,    39,    40,   114,    42,    43,     8,     8,
     300,   306,   302,   303,    30,   329,   330,   331,    18,     8,
      77,    21,    85,    77,   314,   313,    78,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   153,   404,   158,    77,     8,    66,
      67,     8,   161,     8,    78,   164,    80,   416,    18,   349,
      84,    21,     8,   422,    81,    82,    74,    75,    78,    79,
      70,    71,    18,     8,    84,    21,    81,    23,    78,    79,
      15,    16,    17,    18,   443,   321,   322,   323,   324,    89,
      90,    91,    92,    75,     8,    95,    96,    79,     8,    45,
      46,    47,    48,    49,    50,    51,    52,     8,    18,     8,
      75,    21,   221,    23,    79,     8,    75,    78,   413,   414,
      79,   411,   412,    18,    70,    71,    76,   415,    74,     8,
      76,    77,    78,     8,     9,    45,    46,    47,    48,    49,
      50,    51,    52,    89,    90,    91,    92,   442,    76,    95,
      96,   441,     6,     7,     8,     9,    10,   452,    75,     8,
      70,    71,    79,     8,    74,    35,    76,    77,    78,    18,
      78,    75,    21,    75,    23,    79,     8,    79,     8,    89,
      90,    91,    92,    75,    80,    95,    96,    79,    74,    92,
      93,    94,    74,    75,     8,     8,    45,    46,    47,    48,
      49,    50,    51,    52,    18,    72,    73,    21,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    68,    69,
      76,    70,    71,     8,    79,    74,    74,    76,    80,    78,
      90,    91,    75,    18,    80,    18,    21,    18,     8,    76,
      89,    90,    91,    92,     9,    10,    95,    96,    18,   319,
     320,    21,   325,   326,    76,    74,    70,    71,   327,   328,
       8,     8,    76,    77,    78,    18,    78,    82,    74,    74,
       8,    18,    75,    25,    21,    89,    90,    91,    92,    24,
      84,    95,    96,    18,    80,    70,    71,     8,    78,    78,
      74,    76,    79,    78,    80,    18,    78,    75,    78,    78,
      70,    71,    78,    77,    89,    90,    91,    92,    78,     8,
      95,    96,     8,    77,    18,    18,    83,    74,     8,    89,
      90,    91,    92,    70,    71,    95,    96,     8,     0,    84,
      74,    78,     4,     5,     6,     7,    18,     8,     8,     8,
       8,    75,    89,    90,    91,    92,    76,    76,    95,    96,
      22,    23,    24,    85,    26,    27,    74,     8,    74,     9,
      32,    33,    75,    35,    36,    37,    38,     8,    83,    41,
      79,    85,    83,    79,    75,    75,    18,    79,     8,    74,
      78,     8,    76,    74,    18,    74,     8,    79,     8,    18,
      77,    79,    77,    79,    78,    78,    75,    74,    74,     8,
      64,    79,    21,    83,    78,    78,    18,    18,    74,    52,
       8,    78,    87,    74,    74,    21,    75,    79,    74,    21,
      75,    75,    79,    88,    21,    78,    89,    75,    74,    74,
      79,    75,    53,    85,    74,    74,   129,    75,   177,   300,
     194,   192,    79,    79,    77,   253,   402,   352,   415,   313,
     315,   148,   318,   316,   360,   317,   410,    -1,    -1,    90,
      -1,    -1,    -1,   110,    96,    -1,    -1,    -1,   126,    -1,
      -1,    -1,    -1,    -1,    -1,   110
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    99,     0,     4,     5,     6,     7,    22,    23,    24,
      26,    27,    32,    33,    35,    36,    37,    38,    41,   100,
     101,   103,   109,     8,    39,    40,    42,    43,   104,   118,
     117,   117,    78,   110,   111,   117,   117,   117,   117,     8,
       8,    34,     8,     8,     8,     8,     8,    81,   105,     8,
       8,     8,   112,   113,   114,   115,     8,    78,   106,    18,
       8,     8,    76,   181,    76,    35,    80,    78,    74,    75,
       8,    74,     8,     8,    76,   121,    80,    75,    79,    79,
      75,    74,    18,   119,    18,    76,    76,     8,    23,   102,
     182,   183,   184,    74,     8,   178,   180,     8,    31,   138,
      18,    78,    82,    74,    11,    12,    13,    14,    30,   133,
     134,   136,   137,   139,    74,     8,    18,   116,   113,   115,
       8,   115,    75,   119,    25,   130,   131,   132,    24,   107,
     108,    84,   185,    18,    77,   183,    80,     8,    77,   178,
      78,    74,    79,     9,   123,   124,   126,   127,    78,    78,
      78,    78,    78,    77,   136,   137,    80,   119,    75,    18,
       8,    77,   132,     8,    77,   108,    18,    18,     8,    18,
      21,   186,    83,   179,    74,     8,    74,    75,    79,    84,
     125,     8,   138,     8,     8,     8,    18,   119,     8,   140,
     115,    75,    76,   119,    76,   119,    85,    74,     8,    74,
      75,   124,    83,   122,    85,    83,   129,     8,    79,    79,
      75,    75,    79,    78,    74,    18,   133,   130,     8,     8,
      76,   120,     8,    15,    16,    17,    18,   128,    74,    74,
      18,     8,   135,    79,    79,    77,    77,    78,     8,    18,
      21,    23,    45,    46,    47,    48,    49,    50,    51,    52,
      70,    71,    74,    76,    78,    89,    90,    91,    92,    95,
      96,   143,   144,   145,   149,   152,   153,   154,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   174,   175,   187,   119,    79,    78,    75,
      83,   141,    79,    18,     8,   151,   153,    74,    74,   149,
      78,     8,    78,    78,   168,   168,   143,   153,    77,   149,
      74,    74,    75,    65,    86,    64,    87,    88,    89,    72,
      73,    66,    67,    81,    82,    68,    69,    90,    91,    92,
      93,    94,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    80,   155,   167,   168,    70,    71,    78,    84,
      97,     8,    78,   146,   147,   148,    74,    21,    18,     9,
      10,   142,   176,    79,    18,    74,    52,   145,   150,   153,
      74,   153,   153,    77,    79,   154,   158,   153,   159,   160,
     161,   162,   163,   163,   164,   164,   164,   164,   165,   165,
     166,   166,   167,   167,   167,   154,    79,   154,   171,   153,
       8,   148,    75,    78,    80,    84,    75,    79,   177,   177,
      75,    78,    74,    79,    79,    83,    75,    79,    85,    79,
     147,    79,    76,   154,   172,    18,    85,    21,    74,   176,
     153,   151,   149,   149,   156,   154,   172,   173,    85,    75,
      79,    74,    53,    75,    77,    21,    74,   151,   149,    77,
     172,    75,    79,    21,   149,    79
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
#line 120 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 125 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 129 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 132 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 135 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string texture_type=(yyvsp[(2) - (5)]).strs[0];
		bool compute_only=(texture_type==string("image3D"))||(texture_type.substr(0,2)==string("RW"));
		
		stringReplaceAll(texture_type,"RWTexture","image");
		ostringstream decl;
		if(compute_only)
			gEffect->m_sharedCode<<"#ifdef IN_COMPUTE_SHADER\n";
		string template_type=(yyvsp[(3) - (5)]).strs[0];
		string texture_name=(yyvsp[(4) - (5)]).strs[0];
		decl<<GetLayoutForTemplateType(template_type)<<" uniform "<<texture_type<<" "<<texture_name<<";\n";
		gEffect->m_sharedCode<<decl.str();
		if(compute_only)
			gEffect->m_sharedCode<<"#endif\n";
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 157 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 161 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 169 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 175 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 181 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 187 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 190 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 208 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 248 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 258 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 275 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 282 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
				extraDeclarations<<it->type<<" "<<structInstanceName<<"="<<it->semantic<<";\n"<<endl;
//				shaderCode<<"#define "<<it->identifier<<" "<<it->semantic<<endl;
			}
			else
			{
			// First put #line in to make sure that all our definitions produce correct-looking warnings/errors.
				shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
				shaderCode<<it->storage<<' '<<type<<' '<<it->identifier<<';\n'<<endl;
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
#line 378 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 383 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 386 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 389 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 396 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 402 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 407 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 412 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 417 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 422 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 34:
/* Line 1792 of yacc.c  */
#line 433 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 437 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 440 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 444 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_techniques[(yyvsp[(3) - (7)]).strs[0]] = (yyvsp[(5) - (7)]).tech;
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 448 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 452 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 457 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 461 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 465 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 469 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 473 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 478 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		   }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 483 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 487 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 491 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 497 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
    gLexPassthrough=false;
}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 503 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 507 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 514 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 520 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 523 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 526 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 56:
/* Line 1792 of yacc.c  */
#line 538 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 57:
/* Line 1792 of yacc.c  */
#line 549 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 554 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
		semantic=getGLInputSemantic((yyvsp[(3) - (3)]).num);//strs[0];
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

  case 59:
/* Line 1792 of yacc.c  */
#line 585 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="[]";
				}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 589 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 594 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (3)]).strs[0];
		string type		=(yyvsp[(2) - (3)]).strs[0];
		string id		=(yyvsp[(3) - (3)]).strs[0];
		(yyval).strs[0]		= storage	;
		(yyval).strs[1]		= type		;
		(yyval).strs[2]		= id		;
	}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 603 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 607 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 611 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 616 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 621 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 626 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 631 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 637 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 642 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 648 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 655 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 73:
/* Line 1792 of yacc.c  */
#line 666 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 74:
/* Line 1792 of yacc.c  */
#line 680 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable = (yyvsp[(1) - (5)]).boolean;
	(yyval).prog = (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0] = (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 687 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders));
    delete (yyvsp[(1) - (1)]).shaders;
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 693 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 77:
/* Line 1792 of yacc.c  */
#line 703 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 78:
/* Line 1792 of yacc.c  */
#line 716 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 724 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 732 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 741 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 745 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
			 }
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 750 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 757 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
						theShader<<"#define IN_COMPUTE_SHADER 1"<<endl;
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

  case 85:
/* Line 1792 of yacc.c  */
#line 806 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
						theShader<<"#define IN_COMPUTE_SHADER 1"<<endl;
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

  case 86:
/* Line 1792 of yacc.c  */
#line 867 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string compiledShaderName	=(yyvsp[(1) - (1)]).strs[0];
			(yyval).strs[0]					=compiledShaderName;
			(yyval).num						=0;
			(yyval).lineno					=(yyvsp[(1) - (1)]).lineno;
		}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 874 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 88:
/* Line 1792 of yacc.c  */
#line 900 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 911 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 917 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 921 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 925 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 930 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 935 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 939 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 948 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 954 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 959 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 99:
/* Line 1792 of yacc.c  */
#line 972 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 980 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 984 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 988 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 992 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			// An expression of the form vec2 c=....;
			// Pass-through normally, but most GLSL compilers cannot handle array initializers.
			string initializer=(yyvsp[(3) - (3)]).strs[0];
			if((yyvsp[(3) - (3)]).children.size()<=1)
			{
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+initializer;
			}
			else
			{
				ostringstream declare_lines;
				declare_lines<<(yyvsp[(1) - (3)]).strs[0]<<";\n";
				/* Here we convert an expression of the form 
										vec2 poss[2]=
										{
											{ 1.0,-1.0},
											{ 1.0, 1.0},
										};
				to the form:
										vec2 poss[2];
										poss[0]=vec2(1.0,-1.0);
										poss[1]=vec2(1.0, 1.0);
				Only trouble is, we don't yet have the "vec2" or whatever the type is. So we will insert a special %type% wildcard for now.
										*/
				string name=(yyvsp[(1) - (3)]).strs[0];
				int sq_pos=name.find("[");
				name=name.substr(0,sq_pos);
				for(int i=0;i<(yyvsp[(3) - (3)]).children.size();i++)
				{
					string c=(yyvsp[(3) - (3)]).children[i].strs[0];
					std::replace( c.begin(), c.end(), '{', '('); 
					std::replace( c.begin(), c.end(), '}', ')'); 
					declare_lines<<"\t"<<name<<"["<<i<<"]=%type%"<<c<<";\n";
				}
				(yyval).strs[0]=declare_lines.str();
			}
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1030 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1034 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1038 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1043 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1047 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1051 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
				}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1056 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1060 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1064 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
				}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1069 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1073 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1077 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1081 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1085 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1090 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1094 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1098 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1102 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				string optional_expression=(yyvsp[(2) - (3)]).strs[0];
				if(optional_expression.length()>0)
				{
					(yyval).strs[0]="";
					(yyval).strs[1]=optional_expression;
				}
				else
				{
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
				(yyval).lineno=(yyvsp[(1) - (3)]).lineno;
			}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1117 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1122 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1126 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1130 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1133 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1137 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1142 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1148 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1152 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1156 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1164 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1177 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1181 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1185 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
	}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1190 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1194 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1198 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1202 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1206 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1210 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1214 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1218 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1222 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1226 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1231 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1235 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1239 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1243 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1251 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1255 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1259 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1263 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1267 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1271 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1275 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1279 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1283 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1287 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1291 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1295 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1299 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1303 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1307 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1311 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1315 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1319 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1323 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1327 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1331 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1335 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1339 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1343 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1347 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1351 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1355 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1359 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1363 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1368 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1375 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1382 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1389 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1396 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1400 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1404 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1408 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1412 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1416 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1424 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1432 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1436 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 208:
/* Line 1792 of yacc.c  */
#line 1448 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1452 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1456 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1461 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1465 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1468 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1472 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1477 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1481 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 217:
/* Line 1792 of yacc.c  */
#line 1590 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1595 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1601 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1606 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1610 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1615 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1620 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1625 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 4245 "src/glfxLALRParser.cpp"
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
#line 1628 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


	string getGLInputSemantic(int s)
	{
		switch(s)
		{
		case SV_DISPATCHTHREADID:
			return "gl_GlobalInvocationID";
		case SV_GROUPTHREADID:
			return "gl_LocalInvocationID";
		case SV_GROUPID:
			return "gl_WorkGroupID";
		break;
		};
		return "";
	}
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
