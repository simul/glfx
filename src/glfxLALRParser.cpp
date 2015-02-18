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
	PassState buildPassState;
	BlendState buildBlendState;
	DepthStencilState buildDepthStencilState;
	SamplerState buildSamplerState;
	TechniqueGroup buildTechniqueGroup;
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
		if(s==string("uchar4"))
		{
			return "layout(rgba8)";
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
#line 185 "src/glfxLALRParser.cpp"

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
     STRUCTUREDBUFFER = 300,
     RW_STRUCTUREDBUFFER = 301,
     RETURN = 302,
     BREAK = 303,
     CONTINUE = 304,
     DO = 305,
     FOR = 306,
     GOTO = 307,
     IF = 308,
     WHILE = 309,
     ELSE = 310,
     TIMES_EQUALS = 311,
     OVER_EQUALS = 312,
     PERCENT_EQUALS = 313,
     PLUS_EQUALS = 314,
     MINUS_EQUALS = 315,
     LEFT_SHIFT_EQUALS = 316,
     RIGHT_SHIFT_EQUALS = 317,
     AND_EQUALS = 318,
     XOR_EQUALS = 319,
     OR_EQUALS = 320,
     AND = 321,
     OR = 322,
     LESS_EQ = 323,
     GRTR_EQ = 324,
     LEFT_SHIFT = 325,
     RIGHT_SHIFT = 326,
     PLUS_PLUS = 327,
     MINUS_MINUS = 328,
     EQ_EQ = 329,
     NOT_EQ = 330
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
#line 326 "src/glfxLALRParser.cpp"

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
#define YYLAST   518

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  91
/* YYNRULES -- Number of rules.  */
#define YYNRULES  227
/* YYNRULES -- Number of states.  */
#define YYNSTATES  462

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    98,     2,     2,     2,    96,    91,     2,
      80,    81,    94,    92,    77,    93,    99,    95,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    85,    76,
      83,    82,    84,    88,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    86,     2,    87,    90,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    78,    89,    79,    97,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    24,    30,
      35,    37,    42,    45,    49,    53,    57,    64,    69,    76,
      82,    87,    97,   105,   107,   115,   121,   125,   128,   130,
     132,   134,   136,   138,   140,   144,   145,   153,   156,   158,
     164,   172,   176,   180,   184,   186,   188,   190,   196,   200,
     202,   204,   205,   206,   207,   211,   212,   215,   216,   220,
     222,   223,   227,   230,   231,   235,   237,   238,   240,   242,
     244,   247,   250,   253,   254,   256,   259,   261,   267,   269,
     272,   274,   277,   279,   290,   296,   304,   314,   319,   325,
     327,   336,   341,   346,   347,   350,   351,   355,   357,   360,
     362,   363,   367,   370,   372,   376,   378,   382,   384,   388,
     393,   397,   401,   404,   406,   409,   411,   417,   425,   431,
     439,   449,   453,   456,   459,   463,   465,   467,   469,   470,
     472,   473,   477,   479,   483,   485,   489,   491,   493,   495,
     497,   499,   501,   503,   505,   507,   509,   511,   513,   519,
     521,   525,   527,   531,   533,   537,   539,   543,   545,   549,
     551,   555,   559,   561,   565,   569,   573,   577,   579,   583,
     587,   589,   593,   597,   599,   603,   607,   611,   613,   615,
     618,   621,   624,   626,   628,   630,   632,   634,   636,   638,
     643,   648,   652,   656,   659,   662,   666,   668,   670,   674,
     679,   681,   685,   687,   689,   693,   695,   697,   700,   703,
     704,   709,   712,   713,   716,   718,   722,   723,   726,   728,
     733,   735,   738,   742,   743,   745,   747,   749
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     101,     0,    -1,   101,   102,    -1,    -1,     7,   120,     8,
     124,    76,   122,    -1,    35,    -1,   103,    -1,     4,   106,
     108,     8,    76,    -1,     4,   107,   108,     8,    76,    -1,
       4,     8,     8,    76,    -1,    38,    -1,    22,   113,     8,
      76,    -1,    22,   114,    -1,    41,     8,    76,    -1,    41,
       8,    77,    -1,    33,    34,    35,    -1,    32,     8,    78,
     183,    79,    76,    -1,    27,     8,   184,    76,    -1,    37,
       8,    80,    18,    81,    76,    -1,    36,     8,    82,   141,
      76,    -1,    22,   120,   109,   122,    -1,   105,     8,     8,
      80,   126,    81,   125,   123,   122,    -1,     6,   120,     8,
      78,   136,    79,   122,    -1,   112,    -1,    26,   120,     8,
      78,   110,    79,   122,    -1,    23,   120,    18,    18,   122,
      -1,    23,    18,    18,    -1,     5,   121,    -1,    42,    -1,
      43,    -1,    39,    -1,    40,    -1,    45,    -1,    46,    -1,
      83,     8,    84,    -1,    -1,    80,    18,    77,    18,    77,
      18,    81,    -1,   110,   111,    -1,   111,    -1,    24,     8,
      78,   133,    79,    -1,    24,   120,     8,    78,   133,    79,
     122,    -1,    80,   117,    81,    -1,    80,   115,    81,    -1,
     115,    77,   116,    -1,   116,    -1,   118,    -1,     8,    -1,
     118,    77,   118,    77,   118,    -1,     8,    82,   119,    -1,
       8,    -1,    18,    -1,    -1,    -1,    -1,    78,   146,    79,
      -1,    -1,    85,     8,    -1,    -1,   126,    77,   127,    -1,
     127,    -1,    -1,   129,   128,   132,    -1,    86,    87,    -1,
      -1,   130,     8,     8,    -1,     9,    -1,    -1,    15,    -1,
      17,    -1,    16,    -1,    85,    18,    -1,    85,   131,    -1,
      85,     8,    -1,    -1,   134,    -1,   134,   135,    -1,   135,
      -1,    25,     8,    78,   136,    79,    -1,   137,    -1,   137,
     140,    -1,   140,    -1,   137,   139,    -1,   139,    -1,     8,
      80,    21,    77,    21,    77,    21,    77,    21,    81,    -1,
      12,    80,     8,    81,    76,    -1,    13,    80,     8,    77,
      18,    81,    76,    -1,    14,    80,     8,    77,   138,    77,
      18,    81,    76,    -1,   142,    82,   143,    76,    -1,    11,
      80,   141,    81,    76,    -1,     8,    -1,    31,    80,     8,
      77,     8,    80,    81,    81,    -1,    30,    80,    18,    81,
      -1,     8,    80,    81,   144,    -1,    -1,    85,   145,    -1,
      -1,   145,    77,   179,    -1,   179,    -1,   146,   152,    -1,
     152,    -1,    -1,    23,    18,    18,    -1,   190,   149,    -1,
     150,    -1,   149,    77,   150,    -1,   151,    -1,   151,    82,
     175,    -1,     8,    -1,    80,   151,    81,    -1,   151,    86,
      18,    87,    -1,   151,    86,    87,    -1,   151,    80,    81,
      -1,   156,    76,    -1,    76,    -1,   148,    76,    -1,   155,
      -1,    53,    80,   156,    81,   152,    -1,    53,    80,   156,
      81,   152,    55,   152,    -1,    54,    80,   156,    81,   152,
      -1,    50,   152,    54,    80,   156,    81,    76,    -1,    51,
      80,   153,    76,   154,    76,   154,    81,   152,    -1,    52,
       8,    76,    -1,    49,    76,    -1,    48,    76,    -1,    47,
     154,    76,    -1,   147,    -1,   156,    -1,   148,    -1,    -1,
     156,    -1,    -1,    78,   146,    79,    -1,   157,    -1,   156,
      77,   157,    -1,   159,    -1,   171,   158,   157,    -1,    82,
      -1,    56,    -1,    57,    -1,    58,    -1,    59,    -1,    60,
      -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,
      -1,   160,    -1,   160,    88,   156,    85,   159,    -1,   161,
      -1,   160,    67,   161,    -1,   162,    -1,   161,    66,   162,
      -1,   163,    -1,   162,    89,   163,    -1,   164,    -1,   163,
      90,   164,    -1,   165,    -1,   164,    91,   165,    -1,   166,
      -1,   165,    74,   166,    -1,   165,    75,   166,    -1,   167,
      -1,   166,    83,   167,    -1,   166,    84,   167,    -1,   166,
      68,   167,    -1,   166,    69,   167,    -1,   168,    -1,   167,
      70,   168,    -1,   167,    71,   168,    -1,   169,    -1,   168,
      92,   169,    -1,   168,    93,   169,    -1,   170,    -1,   169,
      94,   170,    -1,   169,    95,   170,    -1,   169,    96,   170,
      -1,   171,    -1,   173,    -1,    72,   171,    -1,    73,   171,
      -1,   172,   170,    -1,    91,    -1,    94,    -1,    92,    -1,
      93,    -1,    97,    -1,    98,    -1,   177,    -1,   173,    86,
     156,    87,    -1,   173,    80,   174,    81,    -1,   173,    80,
      81,    -1,   173,    99,     8,    -1,   173,    72,    -1,   173,
      73,    -1,   174,    77,   157,    -1,   157,    -1,   157,    -1,
      78,   176,    79,    -1,    78,   176,    77,    79,    -1,   175,
      -1,   176,    77,   175,    -1,     8,    -1,   178,    -1,    80,
     156,    81,    -1,    18,    -1,    21,    -1,     9,   180,    -1,
      10,   180,    -1,    -1,     8,     8,   182,    76,    -1,    85,
       8,    -1,    -1,   183,   181,    -1,   181,    -1,    78,   185,
      79,    -1,    -1,   185,   186,    -1,   186,    -1,   187,    82,
     189,    76,    -1,   104,    -1,     8,   188,    -1,    86,    18,
      87,    -1,    -1,     8,    -1,    18,    -1,    21,    -1,     8,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   126,   126,   127,   131,   135,   138,   141,   167,   183,
     189,   193,   201,   207,   213,   219,   222,   240,   280,   290,
     307,   314,   432,   437,   440,   448,   455,   461,   466,   466,
     466,   466,   472,   472,   478,   484,   488,   499,   503,   506,
     510,   520,   524,   529,   533,   537,   541,   545,   550,   555,
     559,   564,   570,   576,   580,   587,   592,   596,   598,   610,
     622,   626,   657,   662,   666,   675,   680,   683,   688,   693,
     698,   703,   709,   715,   720,   727,   739,   753,   762,   768,
     778,   791,   799,   807,   816,   820,   826,   834,   885,   952,
     959,   985,   996,  1003,  1006,  1011,  1015,  1020,  1024,  1033,
    1040,  1044,  1057,  1066,  1070,  1074,  1078,  1116,  1120,  1124,
    1129,  1133,  1137,  1142,  1146,  1150,  1155,  1159,  1163,  1167,
    1171,  1176,  1180,  1184,  1188,  1203,  1208,  1212,  1217,  1219,
    1224,  1228,  1234,  1238,  1242,  1246,  1250,  1254,  1255,  1256,
    1257,  1258,  1259,  1260,  1261,  1262,  1263,  1267,  1271,  1276,
    1280,  1284,  1288,  1292,  1296,  1300,  1304,  1308,  1312,  1317,
    1321,  1325,  1329,  1333,  1337,  1341,  1345,  1349,  1353,  1357,
    1361,  1365,  1369,  1373,  1377,  1381,  1385,  1389,  1393,  1397,
    1401,  1405,  1409,  1409,  1409,  1409,  1409,  1409,  1413,  1417,
    1421,  1425,  1429,  1433,  1437,  1441,  1445,  1449,  1454,  1461,
    1468,  1475,  1482,  1486,  1490,  1494,  1498,  1502,  1510,  1519,
    1522,  1534,  1539,  1542,  1547,  1551,  1555,  1558,  1563,  1567,
    1676,  1681,  1687,  1693,  1696,  1701,  1706,  1711
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
  "IMAGE3D", "KNOWN_TYPE", "STRUCTUREDBUFFER", "RW_STRUCTUREDBUFFER",
  "RETURN", "BREAK", "CONTINUE", "DO", "FOR", "GOTO", "IF", "WHILE",
  "ELSE", "TIMES_EQUALS", "OVER_EQUALS", "PERCENT_EQUALS", "PLUS_EQUALS",
  "MINUS_EQUALS", "LEFT_SHIFT_EQUALS", "RIGHT_SHIFT_EQUALS", "AND_EQUALS",
  "XOR_EQUALS", "OR_EQUALS", "AND", "OR", "LESS_EQ", "GRTR_EQ",
  "LEFT_SHIFT", "RIGHT_SHIFT", "PLUS_PLUS", "MINUS_MINUS", "EQ_EQ",
  "NOT_EQ", "';'", "','", "'{'", "'}'", "'('", "')'", "'='", "'<'", "'>'",
  "':'", "'['", "']'", "'?'", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "'~'", "'!'", "'.'", "$accept", "prog", "tok",
  "line_statement", "ignore_line_statement", "shader_and_layout",
  "texture_type", "buffer_type", "optional_templateval", "layout_params",
  "technique_decls", "group_technique_decl", "technique_decl",
  "cs_layout_spec", "normal_layout_spec", "tx_layout", "layout_s",
  "cs_layout", "layout_el", "layout_def", "lex_fx", "shader_fx",
  "lex_passthrough", "function_content", "read_block",
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
     325,   326,   327,   328,   329,   330,    59,    44,   123,   125,
      40,    41,    61,    60,    62,    58,    91,    93,    63,   124,
      94,    38,    43,    45,    42,    47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   103,   104,   105,   106,   106,
     106,   106,   107,   107,   108,   108,   109,   110,   110,   111,
     112,   113,   114,   115,   115,   116,   116,   117,   118,   119,
     119,   120,   121,   122,   123,   124,   125,   125,   126,   126,
     126,   127,   128,   128,   129,   130,   130,   131,   131,   131,
     132,   132,   132,   132,   133,   134,   134,   135,   136,   137,
     137,   137,   137,   138,   139,   139,   139,   140,   140,   141,
     141,   142,   143,   143,   144,   144,   145,   145,   146,   146,
     146,   147,   148,   149,   149,   150,   150,   151,   151,   151,
     151,   151,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   153,   153,   153,   154,
     154,   155,   156,   156,   157,   157,   158,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   159,   159,   160,
     160,   161,   161,   162,   162,   163,   163,   164,   164,   165,
     165,   165,   166,   166,   166,   166,   166,   167,   167,   167,
     168,   168,   168,   169,   169,   169,   169,   170,   171,   171,
     171,   171,   172,   172,   172,   172,   172,   172,   173,   173,
     173,   173,   173,   173,   173,   174,   174,   175,   175,   175,
     176,   176,   177,   177,   177,   178,   178,   179,   179,   180,
     181,   182,   182,   183,   183,   184,   184,   185,   185,   186,
     186,   187,   188,   188,   189,   189,   189,   190
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     5,     5,     4,
       1,     4,     2,     3,     3,     3,     6,     4,     6,     5,
       4,     9,     7,     1,     7,     5,     3,     2,     1,     1,
       1,     1,     1,     1,     3,     0,     7,     2,     1,     5,
       7,     3,     3,     3,     1,     1,     1,     5,     3,     1,
       1,     0,     0,     0,     3,     0,     2,     0,     3,     1,
       0,     3,     2,     0,     3,     1,     0,     1,     1,     1,
       2,     2,     2,     0,     1,     2,     1,     5,     1,     2,
       1,     2,     1,    10,     5,     7,     9,     4,     5,     1,
       8,     4,     4,     0,     2,     0,     3,     1,     2,     1,
       0,     3,     2,     1,     3,     1,     3,     1,     3,     4,
       3,     3,     2,     1,     2,     1,     5,     7,     5,     7,
       9,     3,     2,     2,     3,     1,     1,     1,     0,     1,
       0,     3,     1,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     1,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     3,     3,     2,     2,     3,     1,     1,     3,     4,
       1,     3,     1,     1,     3,     1,     1,     2,     2,     0,
       4,     2,     0,     2,     1,     3,     0,     2,     1,     4,
       1,     2,     3,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,    52,    51,    51,     0,    51,    51,
      51,     0,     0,     0,     5,     0,     0,    10,     0,     2,
       6,     0,    23,     0,    30,    31,    28,    29,    32,    33,
      35,    35,    27,     0,     0,     0,     0,    12,     0,     0,
       0,     0,   216,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    46,     0,    44,     0,    45,
       0,     0,    53,     0,     0,     0,     0,     0,     0,    15,
       0,     0,    13,    14,     0,     9,     0,     0,     0,     0,
       0,     0,     0,    42,    41,     0,    11,     0,    20,    53,
       0,     0,   223,     0,   220,     0,   218,     0,    17,     0,
     214,     0,    89,     0,     0,     0,    60,    34,     7,     8,
       0,     0,     0,     0,     0,     0,    78,    82,    80,     0,
      53,    49,    50,    48,    43,    45,     0,     0,     0,    25,
       0,     0,    74,    76,     0,     0,    38,     0,   221,     0,
     215,   217,     0,   212,     0,   213,     0,    19,     0,    65,
       0,    59,    63,     0,     0,     0,     0,     0,     0,    53,
      81,    79,    93,     4,     0,     0,     0,    53,    75,     0,
      53,    37,     0,    26,   224,   225,   226,     0,     0,     0,
      16,     0,    18,    66,    57,     0,    73,     0,     0,     0,
       0,     0,     0,    22,     0,     0,    47,     0,     0,    40,
       0,    24,   222,   219,   211,   210,     0,    58,     0,     0,
      62,     0,    61,    64,     0,     0,     0,     0,    91,     0,
      87,     0,     0,     0,     0,    56,   100,    53,    72,    67,
      69,    68,    70,    71,    88,    84,     0,     0,     0,    95,
      36,    77,    39,     0,   202,   205,   206,     0,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   100,
       0,   182,   184,   185,   183,   186,   187,     0,   125,     0,
      99,   115,     0,   132,   134,   147,   149,   151,   153,   155,
     157,   159,   162,   167,   170,   173,   177,     0,   178,   188,
     203,     0,    21,     0,     0,     0,     0,    92,     0,     0,
     202,     0,   129,   123,   122,     0,   128,     0,     0,     0,
     179,   180,     0,     0,    54,    98,   114,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   136,     0,
     181,   177,   193,   194,     0,     0,     0,   107,     0,   102,
     103,   105,    85,     0,     0,   209,   209,    94,    97,    90,
     101,   124,     0,   127,     0,   126,   121,     0,     0,   131,
     204,   133,   150,     0,   152,   154,   156,   158,   160,   161,
     165,   166,   163,   164,   168,   169,   171,   172,   174,   175,
     176,   135,   191,   196,     0,     0,   192,     0,     0,     0,
       0,     0,     0,     0,   207,   208,     0,     0,   130,     0,
       0,     0,     0,   190,   189,   108,   104,   111,     0,   197,
     106,     0,   110,     0,    86,    96,     0,     0,   116,   118,
     148,   195,   200,     0,   109,     0,     0,   130,     0,     0,
     198,     0,   119,     0,   117,   199,   201,     0,     0,     0,
     120,    83
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    19,    20,    94,    21,    30,    31,    51,    62,
     135,   136,    22,    36,    37,    56,    57,    58,    59,   123,
      33,    32,    88,   227,    80,   209,   150,   151,   186,   152,
     153,   233,   212,   131,   132,   133,   115,   116,   238,   117,
     118,   104,   119,   195,   297,   367,   267,   268,   269,   359,
     360,   361,   270,   374,   301,   271,   272,   273,   349,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   404,   430,   443,   289,   290,   368,
     414,   100,   179,   101,    67,    95,    96,    97,   138,   177,
     291
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -418
static const yytype_int16 yypact[] =
{
    -418,   409,  -418,     2,  -418,  -418,  -418,   -63,  -418,  -418,
    -418,    13,    25,     6,  -418,    38,    50,  -418,    63,  -418,
    -418,    98,  -418,   104,  -418,  -418,  -418,  -418,  -418,  -418,
      62,    62,  -418,   150,   168,   171,   176,  -418,    90,   172,
     184,   190,   157,   164,   212,   187,   170,    84,   258,   194,
     263,   264,   266,   206,  -418,   203,    -9,  -418,   207,   210,
     213,   272,  -418,   273,   214,   215,    42,   218,   287,  -418,
       0,   278,  -418,  -418,   217,  -418,   219,   222,   223,   103,
     229,     1,   171,  -418,  -418,   299,  -418,   232,  -418,  -418,
     285,   289,   225,   296,  -418,    -3,  -418,   234,  -418,   310,
    -418,    17,  -418,   243,   248,   247,    18,  -418,  -418,  -418,
     249,   251,   252,   253,   254,   256,   103,  -418,  -418,   257,
    -418,  -418,  -418,  -418,  -418,  -418,   203,   259,   323,  -418,
     334,   268,   285,  -418,   335,   -20,  -418,   326,  -418,   330,
    -418,  -418,    48,   267,   275,  -418,   341,  -418,   279,  -418,
      27,  -418,   274,   346,     0,   353,   356,   357,   350,  -418,
    -418,  -418,   361,  -418,   299,   293,   295,  -418,  -418,   297,
    -418,  -418,   284,  -418,  -418,  -418,  -418,   300,   369,   302,
    -418,   303,  -418,   370,   298,   306,   305,   376,   313,   314,
     319,   320,   317,  -418,   328,   342,  -418,   381,   103,  -418,
     285,  -418,  -418,  -418,  -418,  -418,   402,  -418,   403,   339,
    -418,   149,  -418,  -418,   343,   344,   404,   413,  -418,   347,
    -418,   358,   348,   355,   360,  -418,   228,  -418,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,   362,   368,   372,   352,
    -418,  -418,  -418,   371,   430,  -418,  -418,   433,   309,   377,
     378,   228,   375,   448,   379,   380,   309,   309,  -418,   228,
     309,  -418,  -418,  -418,  -418,  -418,  -418,   102,  -418,   382,
    -418,  -418,   144,  -418,  -418,   -60,   391,   373,   374,   383,
     178,   -31,   169,   162,   138,  -418,   166,   309,   -50,  -418,
    -418,    -7,  -418,   385,   442,   447,   109,  -418,   386,   450,
    -418,   390,   392,  -418,  -418,   416,   332,   395,   309,   309,
    -418,  -418,   165,    58,  -418,  -418,  -418,  -418,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,  -418,  -418,
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,   309,
    -418,  -418,  -418,  -418,   265,   309,   464,  -418,    -7,   396,
    -418,    44,  -418,   398,   397,  -418,  -418,   399,  -418,  -418,
    -418,  -418,   400,  -418,   401,   392,  -418,    67,    82,  -418,
    -418,  -418,   391,    26,   373,   374,   383,   178,   -31,   -31,
     169,   169,   169,   169,   162,   162,   138,   138,  -418,  -418,
    -418,  -418,  -418,  -418,   108,   -23,  -418,    51,    -7,   405,
     294,    11,   458,   406,  -418,  -418,   109,   309,   309,   228,
     228,   309,   309,  -418,  -418,  -418,  -418,  -418,   294,  -418,
    -418,   394,  -418,   407,  -418,  -418,   110,   411,   428,  -418,
    -418,  -418,  -418,    59,  -418,   467,   414,   309,   228,    49,
    -418,   408,  -418,   410,  -418,  -418,  -418,   468,   228,   412,
    -418,  -418
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -418,  -418,  -418,  -418,  -418,  -418,  -418,  -418,   461,  -418,
    -418,   359,  -418,  -418,  -418,  -418,   415,  -418,   -67,  -418,
     196,  -418,   -65,  -418,  -418,  -418,  -418,   312,  -418,  -418,
    -418,  -418,  -418,   301,  -418,   364,   304,  -418,  -418,   384,
     387,   345,  -418,  -418,  -418,  -418,   239,  -418,   198,  -418,
      97,   148,  -251,  -418,  -412,  -418,  -246,  -315,  -418,    86,
    -418,   189,   188,   191,   192,   186,   -61,  -119,   -71,   -66,
    -236,  -244,  -418,  -418,  -418,  -417,  -418,  -418,  -418,    95,
     146,   417,  -418,  -418,  -418,  -418,   419,  -418,  -418,  -418,
    -418
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -228
static const yytype_int16 yytable[] =
{
     305,   357,   302,   381,   134,    92,   437,   319,   102,   121,
      23,   442,   310,   311,   313,   125,   315,    35,   127,   122,
      93,    42,   352,   353,   129,    99,   -66,   149,   320,   431,
     354,   103,   456,    43,   401,   453,   355,   327,   328,   403,
      44,    24,    25,   351,    26,    27,    45,    28,    29,   356,
      92,   350,   329,   330,   318,   163,   174,   300,    46,   170,
     375,   315,   377,   378,   424,    93,   175,   245,    82,   176,
     246,    47,    83,   358,   383,   351,   140,   351,   351,   351,
     351,   351,   351,   351,   351,   351,   351,   351,   351,   351,
     351,   351,   351,   351,   193,   429,   144,   196,   432,   398,
     399,   400,   199,   318,   183,   201,    48,   441,   184,   405,
     244,   421,    49,   429,   110,   111,   112,   113,   365,   366,
     245,   256,   257,   246,   409,   247,   410,   428,   455,   260,
     411,   409,   425,   114,   429,   318,   449,   411,   450,   380,
     261,   262,   263,   264,   318,    50,   265,   266,   419,   248,
     249,   250,   251,   252,   253,   254,   255,   228,    53,   318,
      72,    73,   292,   420,   229,   230,   231,   232,   438,   439,
      61,   436,   302,   244,   256,   257,    54,   351,   258,    55,
     259,   314,   260,   245,    60,   422,   246,   318,   247,   423,
      63,   446,    64,   261,   262,   263,   264,   454,    65,   265,
     266,   302,    34,    38,    39,    40,    41,   460,   390,   391,
     392,   393,   248,   249,   250,   251,   252,   253,   254,   255,
     317,   318,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   335,   336,   337,    66,   244,   256,   257,   331,
     332,   258,    68,   259,   379,   260,   245,    69,   348,   246,
      71,   247,   325,   326,   333,   334,   261,   262,   263,   264,
     394,   395,   265,   266,   388,   389,    74,   396,   397,    70,
      75,    76,    77,   300,    78,   248,   249,   250,   251,   252,
     253,   254,   255,   245,    79,    81,   246,    85,    84,    86,
      87,    89,    90,    91,    98,    99,   105,   106,   108,   109,
     256,   257,   300,   107,   258,   120,   259,   126,   260,   128,
     130,   137,   245,   134,   139,   246,   142,   300,   143,   261,
     262,   263,   264,   146,   147,   265,   266,   245,   148,   154,
     246,   155,   156,   157,   158,   159,   164,   256,   257,   162,
     244,   165,   166,   169,   172,   260,   402,   167,   173,   181,
     245,   180,   178,   246,   187,   182,   261,   262,   263,   264,
     185,   189,   265,   266,   190,   191,   256,   257,   192,   194,
     197,   202,   428,   198,   260,   200,   203,   204,   205,   149,
     206,   256,   257,   208,   213,   261,   262,   263,   264,   260,
     211,   265,   266,   210,   214,   215,   216,   217,   218,   221,
     261,   262,   263,   264,   256,   257,   265,   266,   219,     2,
     224,   225,   260,     3,     4,     5,     6,   226,   220,   234,
     235,   237,   236,   261,   262,   263,   264,   241,   239,   265,
     266,     7,     8,     9,   242,    10,    11,   296,  -227,   240,
     243,    12,    13,   293,    14,    15,    16,    17,   294,   295,
      18,   299,   298,   303,   304,   306,   307,   321,   316,   308,
     309,   362,   322,   363,   323,   364,   371,   369,   370,   318,
     372,   376,   406,   408,   324,   412,   416,   418,   413,   433,
     417,   444,   434,   448,   445,   457,   427,   447,   451,   459,
     452,   458,    52,   461,   171,   207,   168,   124,   312,   188,
     160,   223,   222,   161,   373,   426,   407,   440,   382,   384,
     387,   435,   415,   385,   141,   386,     0,     0,   145
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-418)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     251,     8,   248,   318,    24,     8,   418,    67,     8,     8,
       8,   428,   256,   257,   260,    82,   267,    80,    85,    18,
      23,     8,    72,    73,    89,     8,     8,     9,    88,    18,
      80,    31,   449,     8,   349,   447,    86,    68,    69,   354,
      34,    39,    40,   287,    42,    43,     8,    45,    46,    99,
       8,   287,    83,    84,    77,   120,     8,     8,     8,    79,
     306,   312,   308,   309,    87,    23,    18,    18,    77,    21,
      21,     8,    81,    80,   320,   319,    79,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   159,   410,    79,   164,    87,   335,
     336,   337,   167,    77,    77,   170,     8,   422,    81,   355,
       8,    85,     8,   428,    11,    12,    13,    14,     9,    10,
      18,    72,    73,    21,    80,    23,    82,    78,    79,    80,
      86,    80,    81,    30,   449,    77,    77,    86,    79,    81,
      91,    92,    93,    94,    77,    83,    97,    98,    81,    47,
      48,    49,    50,    51,    52,    53,    54,     8,     8,    77,
      76,    77,   227,    81,    15,    16,    17,    18,   419,   420,
      80,   417,   418,     8,    72,    73,     8,   421,    76,     8,
      78,    79,    80,    18,     8,    77,    21,    77,    23,    81,
      18,    81,     8,    91,    92,    93,    94,   448,     8,    97,
      98,   447,     6,     7,     8,     9,    10,   458,   327,   328,
     329,   330,    47,    48,    49,    50,    51,    52,    53,    54,
      76,    77,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    94,    95,    96,    78,     8,    72,    73,    70,
      71,    76,    78,    78,    79,    80,    18,    35,    82,    21,
      80,    23,    74,    75,    92,    93,    91,    92,    93,    94,
     331,   332,    97,    98,   325,   326,     8,   333,   334,    82,
      76,     8,     8,     8,     8,    47,    48,    49,    50,    51,
      52,    53,    54,    18,    78,    82,    21,    77,    81,    76,
      18,    18,    78,    78,    76,     8,    18,    80,    76,    76,
      72,    73,     8,    84,    76,    76,    78,     8,    80,    77,
      25,    86,    18,    24,    18,    21,    82,     8,     8,    91,
      92,    93,    94,    80,    76,    97,    98,    18,    81,    80,
      21,    80,    80,    80,    80,    79,    77,    72,    73,    82,
       8,    18,     8,     8,    18,    80,    81,    79,    18,     8,
      18,    76,    85,    21,     8,    76,    91,    92,    93,    94,
      86,     8,    97,    98,     8,     8,    72,    73,    18,     8,
      77,    87,    78,    78,    80,    78,    76,     8,    76,     9,
      77,    72,    73,    85,     8,    91,    92,    93,    94,    80,
      85,    97,    98,    87,    81,    81,    77,    77,    81,    18,
      91,    92,    93,    94,    72,    73,    97,    98,    80,     0,
       8,     8,    80,     4,     5,     6,     7,    78,    76,    76,
      76,     8,    18,    91,    92,    93,    94,    79,    81,    97,
      98,    22,    23,    24,    79,    26,    27,    85,     8,    81,
      80,    32,    33,    81,    35,    36,    37,    38,    80,    77,
      41,    18,    81,    76,    76,    80,     8,    66,    76,    80,
      80,    76,    89,    21,    90,    18,    76,    81,    18,    77,
      54,    76,     8,    77,    91,    77,    77,    76,    81,    21,
      80,    87,    76,    55,    77,    77,    81,    76,    21,    21,
      76,    81,    31,    81,   135,   183,   132,    82,   259,   154,
     116,   200,   198,   116,   306,   408,   358,   421,   319,   321,
     324,   416,   366,   322,    95,   323,    -1,    -1,   101
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   101,     0,     4,     5,     6,     7,    22,    23,    24,
      26,    27,    32,    33,    35,    36,    37,    38,    41,   102,
     103,   105,   112,     8,    39,    40,    42,    43,    45,    46,
     106,   107,   121,   120,   120,    80,   113,   114,   120,   120,
     120,   120,     8,     8,    34,     8,     8,     8,     8,     8,
      83,   108,   108,     8,     8,     8,   115,   116,   117,   118,
       8,    80,   109,    18,     8,     8,    78,   184,    78,    35,
      82,    80,    76,    77,     8,    76,     8,     8,     8,    78,
     124,    82,    77,    81,    81,    77,    76,    18,   122,    18,
      78,    78,     8,    23,   104,   185,   186,   187,    76,     8,
     181,   183,     8,    31,   141,    18,    80,    84,    76,    76,
      11,    12,    13,    14,    30,   136,   137,   139,   140,   142,
      76,     8,    18,   119,   116,   118,     8,   118,    77,   122,
      25,   133,   134,   135,    24,   110,   111,    86,   188,    18,
      79,   186,    82,     8,    79,   181,    80,    76,    81,     9,
     126,   127,   129,   130,    80,    80,    80,    80,    80,    79,
     139,   140,    82,   122,    77,    18,     8,    79,   135,     8,
      79,   111,    18,    18,     8,    18,    21,   189,    85,   182,
      76,     8,    76,    77,    81,    86,   128,     8,   141,     8,
       8,     8,    18,   122,     8,   143,   118,    77,    78,   122,
      78,   122,    87,    76,     8,    76,    77,   127,    85,   125,
      87,    85,   132,     8,    81,    81,    77,    77,    81,    80,
      76,    18,   136,   133,     8,     8,    78,   123,     8,    15,
      16,    17,    18,   131,    76,    76,    18,     8,   138,    81,
      81,    79,    79,    80,     8,    18,    21,    23,    47,    48,
      49,    50,    51,    52,    53,    54,    72,    73,    76,    78,
      80,    91,    92,    93,    94,    97,    98,   146,   147,   148,
     152,   155,   156,   157,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   177,
     178,   190,   122,    81,    80,    77,    85,   144,    81,    18,
       8,   154,   156,    76,    76,   152,    80,     8,    80,    80,
     171,   171,   146,   156,    79,   152,    76,    76,    77,    67,
      88,    66,    89,    90,    91,    74,    75,    68,    69,    83,
      84,    70,    71,    92,    93,    94,    95,    96,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    82,   158,
     170,   171,    72,    73,    80,    86,    99,     8,    80,   149,
     150,   151,    76,    21,    18,     9,    10,   145,   179,    81,
      18,    76,    54,   148,   153,   156,    76,   156,   156,    79,
      81,   157,   161,   156,   162,   163,   164,   165,   166,   166,
     167,   167,   167,   167,   168,   168,   169,   169,   170,   170,
     170,   157,    81,   157,   174,   156,     8,   151,    77,    80,
      82,    86,    77,    81,   180,   180,    77,    80,    76,    81,
      81,    85,    77,    81,    87,    81,   150,    81,    78,   157,
     175,    18,    87,    21,    76,   179,   156,   154,   152,   152,
     159,   157,   175,   176,    87,    77,    81,    76,    55,    77,
      79,    21,    76,   154,   152,    79,   175,    77,    81,    21,
     152,    81
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
#line 127 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 132 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 136 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 139 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 142 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 168 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string buffer_type=(yyvsp[(2) - (5)]).strs[0];
		bool compute_only=true;
		ostringstream decl;
		if(compute_only)
			gEffect->m_sharedCode<<"#ifdef IN_COMPUTE_SHADER\n";
		string template_type=(yyvsp[(3) - (5)]).strs[0];
		string buffer_name=(yyvsp[(4) - (5)]).strs[0];
		decl<<"layout(std430) buffer "<<buffer_name<<"_\n{\n\t";
		decl<<template_type<<" "<<buffer_name<<"[];\n";
		decl<<"};\n";
		gEffect->m_sharedCode<<decl.str();
		if(compute_only)
			gEffect->m_sharedCode<<"#endif\n";
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 184 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 190 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 194 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(2) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(4) - (4)]).strs[0];
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 202 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 208 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 214 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 220 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 223 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 17:
/* Line 1792 of yacc.c  */
#line 241 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 18:
/* Line 1792 of yacc.c  */
#line 281 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 19:
/* Line 1792 of yacc.c  */
#line 291 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 20:
/* Line 1792 of yacc.c  */
#line 308 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 315 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		std::string shaderName		=(yyvsp[(3) - (9)]).strs[0];
		std::string returnType		=(yyvsp[(2) - (9)]).strs[0];
		std::string shaderContent	=(yyvsp[(8) - (9)]).strs[0];
		std::string returnable		=(yyvsp[(8) - (9)]).strs[1];
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
				string returnVariable="returnVariable";
				// if we're returning a simple type, we declare it as an output.
				shaderCode<<"out "<<returnType<<" "<<returnVariable<<";\n";
				finalCode<<returnVariable<<"="<<returnable<<";"<<endl;
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
					// Special outputs:
					if(m.semantic==string("gl_VertexID")||m.semantic==string("SV_POSITION"))
					{
						string builtin_name="gl_Position";
						shaderCode<<"out "<<m.type<<' '<<builtin_name<<";"<<endl;
						finalCode<<builtin_name<<"="<<returnable<<"."<<m.name<<";"<<endl;
					}
					if(m.semantic.substr(0,9)==string("SV_TARGET"))
					{
						string numstr=m.semantic.substr(9,m.semantic.length()-9);
						int num=0;
						 char * pEnd;
						num=strtol(numstr.c_str(),&pEnd,10);
						if(num>=0)
							shaderCode<<"layout(location = "<<num<<") ";
					}
					if(m.semantic.substr(0,9)==string("SV_DEPTH"))
					{
						sem="gl_FragDepth";
					}
					//out float gl_FragDepth;
					shaderCode<<"out "<<m.type<<' '<<sem<<";"<<endl;
					finalCode<<sem<<"="<<returnable<<"."<<m.name<<";"<<endl;
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

  case 22:
/* Line 1792 of yacc.c  */
#line 433 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 438 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 441 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string groupName=(yyvsp[(3) - (7)]).strs[0];
		if(gEffect->m_techniqueGroups.find(groupName)==gEffect->m_techniqueGroups.end())
			gEffect->m_techniqueGroups[groupName]=new TechniqueGroup;
		*(gEffect->m_techniqueGroups[groupName])=buildTechniqueGroup;
		buildTechniqueGroup.m_techniques.clear();
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 449 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 456 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 462 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 467 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 473 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 479 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 484 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 489 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 37:
/* Line 1792 of yacc.c  */
#line 500 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 504 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 507 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 511 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		if(gEffect->m_techniqueGroups.find("")==gEffect->m_techniqueGroups.end())
		{
			gEffect->m_techniqueGroups[""]=new TechniqueGroup;
		}
		TechniqueGroup *g=gEffect->m_techniqueGroups[""];
		string techname=(yyvsp[(3) - (7)]).strs[0];
		g->m_techniques[techname] = (yyvsp[(5) - (7)]).tech;
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 521 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 525 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 530 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 534 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 538 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 542 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 546 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 551 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		   }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 556 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 560 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 564 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 570 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
    gLexPassthrough=false;
}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 576 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 580 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 587 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 593 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 596 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 599 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 59:
/* Line 1792 of yacc.c  */
#line 611 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 60:
/* Line 1792 of yacc.c  */
#line 622 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 627 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 62:
/* Line 1792 of yacc.c  */
#line 658 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="[]";
				}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 662 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 667 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (3)]).strs[0];
		string type		=(yyvsp[(2) - (3)]).strs[0];
		string id		=(yyvsp[(3) - (3)]).strs[0];
		(yyval).strs[0]		= storage	;
		(yyval).strs[1]		= type		;
		(yyval).strs[2]		= id		;
	}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 676 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 680 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 684 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 689 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 694 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 699 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 704 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 710 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 715 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 721 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 728 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).passes				=((yyvsp[(1) - (2)]).passes);
	map<string,Program> &passes=*(yyval).passes;
	string name			=(yyvsp[(2) - (2)]).strs[0];
	Program *p			=(yyvsp[(2) - (2)]).prog;
	if(p)
	{
		passes[name]	=*(p);
	}
	delete (yyvsp[(2) - (2)]).prog;
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 740 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	map<string,Program> *m=new map<string,Program>;
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

  case 77:
/* Line 1792 of yacc.c  */
#line 754 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable = (yyvsp[(1) - (5)]).boolean;
	(yyval).prog = (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0] = (yyvsp[(2) - (5)]).strs[0];
	(yyval).prog->passState=buildPassState;
	buildPassState=PassState();
}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 763 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders));
    delete (yyvsp[(1) - (1)]).shaders;
}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 769 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 80:
/* Line 1792 of yacc.c  */
#line 779 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 81:
/* Line 1792 of yacc.c  */
#line 792 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 800 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 808 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 817 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 821 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 827 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 835 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
					// Because there's no such thing in GLSL:
					theShader<<"#define SamplerState int\n";
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

  case 88:
/* Line 1792 of yacc.c  */
#line 886 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
					// Because there's no such thing in GLSL:
					theShader<<"#define SamplerState int\n";
					for(map<std::string,SamplerState*>::const_iterator i=gEffect->m_samplerStates.begin();i!=gEffect->m_samplerStates.end();i++)
					{
						theShader<<"int "<<i->first<<"=0;\n";
					}
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

  case 89:
/* Line 1792 of yacc.c  */
#line 953 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string compiledShaderName	=(yyvsp[(1) - (1)]).strs[0];
			(yyval).strs[0]					=compiledShaderName;
			(yyval).num						=0;
			(yyval).lineno					=(yyvsp[(1) - (1)]).lineno;
		}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 960 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 91:
/* Line 1792 of yacc.c  */
#line 986 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 997 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1003 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1007 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1011 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1016 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1021 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1025 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 1034 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 1040 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1045 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 102:
/* Line 1792 of yacc.c  */
#line 1058 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			stringReplaceAll(init_declarator_list,type_spec+type_spec,type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1067 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1071 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1075 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1079 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
				int sq_pos=(int)name.find("[");
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

  case 107:
/* Line 1792 of yacc.c  */
#line 1117 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1121 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1125 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1130 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1134 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1138 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
				}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1143 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1147 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1156 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1164 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1168 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1172 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1177 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1181 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1185 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1189 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 125:
/* Line 1792 of yacc.c  */
#line 1204 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1209 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1213 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1217 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1220 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1224 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1229 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1235 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1239 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1243 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1251 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1264 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1268 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1272 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
	}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1277 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1281 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1285 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1289 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1293 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1297 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1301 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1305 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1309 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1313 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1318 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1322 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1326 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1330 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1334 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1338 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1342 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1346 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1350 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1354 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1358 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1362 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1366 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1370 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1374 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1378 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1382 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1386 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1390 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1394 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1398 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1402 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1406 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1410 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1414 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1418 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1422 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1426 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1430 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1434 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1438 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1442 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1446 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1450 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1455 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1462 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1469 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1476 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1483 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1487 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1491 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1495 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1499 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1503 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1511 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1519 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1523 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 211:
/* Line 1792 of yacc.c  */
#line 1535 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1539 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1543 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1548 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1552 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1555 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1559 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1564 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1568 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 220:
/* Line 1792 of yacc.c  */
#line 1677 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1682 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1688 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1693 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1697 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1702 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1707 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1712 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 4338 "src/glfxLALRParser.cpp"
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
#line 1715 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
