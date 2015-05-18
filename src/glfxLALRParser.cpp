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
    #include "StringFunctions.h"

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
	int maxVertexCount			=0;
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
		if(s==string("uint"))
		{
			return "layout(r32ui)";
		}
		if(s==string("int"))
		{
			return "layout(r32i)";
		}
		return "";
	}
	static string GetEquivalentGLTextureType(string texture_type,string template_type)
	{
		stringReplaceAll(texture_type,"RWTexture","image");
		stringReplaceAll(texture_type,"Texture","sampler");
		if(template_type.find("uint")<template_type.length())
		{
			texture_type=string("u")+texture_type;
		}
		else if(template_type.find("int")<template_type.length())
		{
			texture_type=string("i")+texture_type;
		}
		return texture_type;
	}
	string getGLInputSemantic(int s);
	map<std::string,CompilableShader*> compilableShaders;
	map<std::string,Function*> functions;
	map<string,DeclaredTexture> declaredTextures;
	Function buildFunction;

/* Line 371 of yacc.c  */
#line 213 "src/glfxLALRParser.cpp"

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
     DEFINE = 292,
     UNDEF = 293,
     MACRO_DEFINITION = 294,
     EOL = 295,
     DECL_SHADER = 296,
     PROFILE = 297,
     RW_TEXTURE2D = 298,
     RW_TEXTURE3D = 299,
     RW_TEXTURE2DARRAY = 300,
     RW_TEXTURE3D_FLOAT4 = 301,
     TEXTURE2DMS = 302,
     TEXTURE2D = 303,
     TEXTURE3D = 304,
     IMAGE3D = 305,
     KNOWN_TYPE = 306,
     STRUCTUREDBUFFER = 307,
     RW_STRUCTUREDBUFFER = 308,
     RETURN = 309,
     BREAK = 310,
     CONTINUE = 311,
     DO = 312,
     FOR = 313,
     GOTO = 314,
     IF = 315,
     WHILE = 316,
     ELSE = 317,
     TIMES_EQUALS = 318,
     OVER_EQUALS = 319,
     PERCENT_EQUALS = 320,
     PLUS_EQUALS = 321,
     MINUS_EQUALS = 322,
     LEFT_SHIFT_EQUALS = 323,
     RIGHT_SHIFT_EQUALS = 324,
     AND_EQUALS = 325,
     XOR_EQUALS = 326,
     OR_EQUALS = 327,
     AND = 328,
     OR = 329,
     LESS_EQ = 330,
     GRTR_EQ = 331,
     LEFT_SHIFT = 332,
     RIGHT_SHIFT = 333,
     PLUS_PLUS = 334,
     MINUS_MINUS = 335,
     EQ_EQ = 336,
     NOT_EQ = 337,
     SA_MAXVERTEXCOUNT = 338,
     SA_NUMTHREADS = 339,
     CS_LAYOUT = 340
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
#line 364 "src/glfxLALRParser.cpp"

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
#define YYLAST   599

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  110
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  96
/* YYNRULES -- Number of rules.  */
#define YYNRULES  247
/* YYNRULES -- Number of states.  */
#define YYNSTATES  522

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   108,     2,     2,     2,   106,   101,     2,
      88,    89,   104,   102,    91,   103,   109,   105,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,    86,
      95,    94,    96,    98,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    87,     2,    90,   100,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    92,    99,    93,   107,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    24,    30,
      35,    37,    44,    55,    60,    63,    67,    71,    75,    79,
      86,    91,    98,   104,   109,   116,   125,   135,   143,   145,
     153,   159,   163,   166,   168,   170,   172,   174,   176,   178,
     180,   182,   184,   188,   189,   197,   200,   202,   208,   216,
     220,   224,   228,   230,   232,   234,   240,   244,   246,   248,
     249,   250,   251,   255,   256,   259,   260,   264,   267,   269,
     274,   276,   277,   281,   283,   284,   288,   292,   293,   295,
     296,   301,   303,   304,   306,   308,   310,   312,   315,   318,
     321,   322,   324,   327,   329,   335,   337,   340,   342,   345,
     347,   358,   364,   372,   382,   387,   393,   395,   402,   411,
     416,   421,   422,   425,   426,   430,   432,   435,   437,   438,
     442,   445,   447,   451,   453,   457,   459,   463,   468,   472,
     476,   479,   481,   484,   486,   492,   500,   506,   514,   524,
     528,   531,   534,   538,   540,   542,   544,   545,   547,   548,
     552,   554,   558,   560,   564,   566,   568,   570,   572,   574,
     576,   578,   580,   582,   584,   586,   588,   594,   596,   600,
     602,   606,   608,   612,   614,   618,   620,   624,   626,   630,
     634,   636,   640,   644,   648,   652,   654,   658,   662,   664,
     668,   672,   674,   678,   682,   686,   688,   690,   693,   696,
     699,   701,   703,   705,   707,   709,   711,   715,   717,   722,
     727,   732,   736,   740,   743,   746,   750,   752,   754,   758,
     763,   765,   769,   771,   773,   777,   779,   781,   784,   787,
     788,   793,   796,   797,   800,   802,   806,   807,   810,   812,
     817,   819,   822,   826,   827,   829,   831,   833
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     111,     0,    -1,   111,   112,    -1,    -1,     8,   130,     9,
     134,    86,   132,    -1,    40,    -1,   113,    -1,     4,   116,
     118,     9,    86,    -1,     4,   117,   118,     9,    86,    -1,
       4,     9,     9,    86,    -1,    85,    -1,    87,    83,    88,
      21,    89,    90,    -1,    87,    84,    88,    21,    91,    21,
      91,    21,    89,    90,    -1,    25,   123,     9,    86,    -1,
      25,   124,    -1,    46,     9,    86,    -1,    46,     9,    91,
      -1,    37,    39,    40,    -1,    38,     9,    40,    -1,    36,
       9,    92,   198,    93,    86,    -1,    30,     9,   199,    86,
      -1,    42,     9,    88,    21,    89,    86,    -1,    41,     9,
      94,   156,    86,    -1,    25,   130,   119,   132,    -1,     6,
       9,   131,   136,    86,   132,    -1,     9,     9,    88,   140,
      89,   131,   133,   132,    -1,   115,     9,     9,    88,   140,
      89,   135,   133,   132,    -1,     7,   130,     9,    92,   151,
      93,   132,    -1,   122,    -1,    29,   130,     9,    92,   120,
      93,   132,    -1,    26,   130,    21,    21,   132,    -1,    26,
      21,    21,    -1,     5,   131,    -1,    48,    -1,    49,    -1,
      47,    -1,    50,    -1,    43,    -1,    44,    -1,    45,    -1,
      52,    -1,    53,    -1,    95,     9,    96,    -1,    -1,    88,
      21,    91,    21,    91,    21,    89,    -1,   120,   121,    -1,
     121,    -1,    27,     9,    92,   148,    93,    -1,    27,   130,
       9,    92,   148,    93,   132,    -1,    88,   127,    89,    -1,
      88,   125,    89,    -1,   125,    91,   126,    -1,   126,    -1,
     128,    -1,     9,    -1,   128,    91,   128,    91,   128,    -1,
       9,    94,   129,    -1,     9,    -1,    21,    -1,    -1,    -1,
      -1,    92,   161,    93,    -1,    -1,    97,     9,    -1,    -1,
      92,   137,    93,    -1,   137,   138,    -1,   138,    -1,   139,
       9,     9,    86,    -1,     4,    -1,    -1,   140,    91,   141,
      -1,   141,    -1,    -1,   144,   142,   147,    -1,    87,   143,
      90,    -1,    -1,    21,    -1,    -1,   145,     9,   118,     9,
      -1,    11,    -1,    -1,    17,    -1,    19,    -1,    18,    -1,
      20,    -1,    97,    21,    -1,    97,   146,    -1,    97,     9,
      -1,    -1,   149,    -1,   149,   150,    -1,   150,    -1,    28,
       9,    92,   151,    93,    -1,   152,    -1,   152,   155,    -1,
     155,    -1,   152,   154,    -1,   154,    -1,     9,    88,    24,
      91,    24,    91,    24,    91,    24,    89,    -1,    14,    88,
       9,    89,    86,    -1,    15,    88,     9,    91,    21,    89,
      86,    -1,    16,    88,     9,    91,   153,    91,    21,    89,
      86,    -1,   157,    94,   158,    86,    -1,    13,    88,   156,
      89,    86,    -1,     9,    -1,    35,    88,     9,    91,    31,
      89,    -1,    34,    88,     9,    91,     9,    88,    89,    89,
      -1,    33,    88,    21,    89,    -1,     9,    88,    89,   159,
      -1,    -1,    97,   160,    -1,    -1,   160,    91,   195,    -1,
     195,    -1,   161,   167,    -1,   167,    -1,    -1,    26,    21,
      21,    -1,   205,   164,    -1,   165,    -1,   164,    91,   165,
      -1,   166,    -1,   166,    94,   191,    -1,     9,    -1,    88,
     166,    89,    -1,   166,    87,    21,    90,    -1,   166,    87,
      90,    -1,   166,    88,    89,    -1,   171,    86,    -1,    86,
      -1,   163,    86,    -1,   170,    -1,    60,    88,   171,    89,
     167,    -1,    60,    88,   171,    89,   167,    62,   167,    -1,
      61,    88,   171,    89,   167,    -1,    57,   167,    61,    88,
     171,    89,    86,    -1,    58,    88,   168,    86,   169,    86,
     169,    89,   167,    -1,    59,     9,    86,    -1,    56,    86,
      -1,    55,    86,    -1,    54,   169,    86,    -1,   162,    -1,
     171,    -1,   163,    -1,    -1,   171,    -1,    -1,    92,   161,
      93,    -1,   172,    -1,   171,    91,   172,    -1,   174,    -1,
     186,   173,   172,    -1,    94,    -1,    63,    -1,    64,    -1,
      65,    -1,    66,    -1,    67,    -1,    68,    -1,    69,    -1,
      70,    -1,    71,    -1,    72,    -1,   175,    -1,   175,    98,
     171,    97,   174,    -1,   176,    -1,   175,    74,   176,    -1,
     177,    -1,   176,    73,   177,    -1,   178,    -1,   177,    99,
     178,    -1,   179,    -1,   178,   100,   179,    -1,   180,    -1,
     179,   101,   180,    -1,   181,    -1,   180,    81,   181,    -1,
     180,    82,   181,    -1,   182,    -1,   181,    95,   182,    -1,
     181,    96,   182,    -1,   181,    75,   182,    -1,   181,    76,
     182,    -1,   183,    -1,   182,    77,   183,    -1,   182,    78,
     183,    -1,   184,    -1,   183,   102,   184,    -1,   183,   103,
     184,    -1,   185,    -1,   184,   104,   185,    -1,   184,   105,
     185,    -1,   184,   106,   185,    -1,   186,    -1,   189,    -1,
      79,   186,    -1,    80,   186,    -1,   187,   185,    -1,   101,
      -1,   104,    -1,   102,    -1,   103,    -1,   107,    -1,   108,
      -1,   189,   109,    10,    -1,   193,    -1,   189,    87,   171,
      90,    -1,   188,    88,   190,    89,    -1,   189,    88,   190,
      89,    -1,   189,    88,    89,    -1,   189,   109,     9,    -1,
     189,    79,    -1,   189,    80,    -1,   190,    91,   172,    -1,
     172,    -1,   172,    -1,    92,   192,    93,    -1,    92,   192,
      91,    93,    -1,   191,    -1,   192,    91,   191,    -1,     9,
      -1,   194,    -1,    88,   171,    89,    -1,    21,    -1,    24,
      -1,    11,   196,    -1,    12,   196,    -1,    -1,     9,     9,
     197,    86,    -1,    97,     9,    -1,    -1,   198,   138,    -1,
     138,    -1,    92,   200,    93,    -1,    -1,   200,   201,    -1,
     201,    -1,   202,    94,   204,    86,    -1,   114,    -1,     9,
     203,    -1,    87,    21,    90,    -1,    -1,     9,    -1,    21,
      -1,    24,    -1,     9,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   154,   154,   155,   159,   163,   166,   169,   201,   217,
     223,   227,   231,   238,   246,   252,   258,   264,   268,   274,
     292,   332,   342,   359,   365,   378,   445,   481,   486,   489,
     497,   504,   510,   515,   515,   515,   515,   515,   515,   515,
     521,   521,   527,   533,   537,   548,   552,   555,   559,   569,
     573,   578,   582,   586,   590,   594,   599,   604,   608,   613,
     619,   625,   629,   636,   641,   646,   649,   654,   658,   662,
     666,   671,   674,   687,   701,   706,   739,   745,   749,   755,
     759,   773,   778,   781,   786,   791,   796,   801,   806,   812,
     818,   823,   830,   842,   856,   865,   871,   881,   894,   902,
     910,   919,   923,   929,   937,   988,  1055,  1062,  1081,  1115,
    1126,  1133,  1136,  1141,  1145,  1150,  1154,  1163,  1170,  1174,
    1187,  1196,  1200,  1204,  1208,  1246,  1250,  1254,  1259,  1263,
    1267,  1272,  1276,  1280,  1285,  1289,  1300,  1304,  1308,  1313,
    1317,  1321,  1325,  1340,  1345,  1349,  1354,  1356,  1361,  1365,
    1371,  1375,  1379,  1383,  1387,  1391,  1392,  1393,  1394,  1395,
    1396,  1397,  1398,  1399,  1400,  1404,  1408,  1413,  1417,  1421,
    1425,  1429,  1433,  1437,  1441,  1445,  1449,  1454,  1458,  1462,
    1466,  1470,  1474,  1478,  1482,  1486,  1490,  1494,  1498,  1502,
    1506,  1510,  1514,  1518,  1522,  1526,  1530,  1534,  1538,  1542,
    1546,  1546,  1546,  1546,  1546,  1546,  1550,  1561,  1565,  1569,
    1614,  1622,  1626,  1632,  1636,  1640,  1644,  1648,  1653,  1660,
    1667,  1674,  1681,  1685,  1689,  1693,  1697,  1701,  1709,  1718,
    1721,  1733,  1738,  1741,  1746,  1750,  1754,  1757,  1762,  1766,
    1875,  1880,  1886,  1892,  1895,  1900,  1905,  1910
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHITESPACE", "UNIFORM", "SHADER",
  "CONSTANT_BUFFER", "PROGRAM", "INTERFACE", "IDENTIFIER",
  "SAMPLING_COMMAND", "STORAGEQ", "GL_FRAGDEPTH", "SHADER_COMMAND",
  "SET_RASTERIZER_COMMAND", "SET_DEPTH_COMMAND", "SET_BLEND_COMMAND",
  "SV_DISPATCHTHREADID", "SV_GROUPTHREADID", "SV_GROUPID", "SV_VERTEXID",
  "NUM", "INCLUDE", "SAMPLER", "FLOAT", "LAYOUT", "LINE", "TECHNIQUE",
  "PASS", "GROUP", "RENDER_STATE_DECL", "QUOTED_STRING", "SHADER_LINE",
  "SHADER_TYPE", "COMPILE_SHADER", "CONSTRUCT_GS_WITH_SO", "STRUCT",
  "DEFINE", "UNDEF", "MACRO_DEFINITION", "EOL", "DECL_SHADER", "PROFILE",
  "RW_TEXTURE2D", "RW_TEXTURE3D", "RW_TEXTURE2DARRAY",
  "RW_TEXTURE3D_FLOAT4", "TEXTURE2DMS", "TEXTURE2D", "TEXTURE3D",
  "IMAGE3D", "KNOWN_TYPE", "STRUCTUREDBUFFER", "RW_STRUCTUREDBUFFER",
  "RETURN", "BREAK", "CONTINUE", "DO", "FOR", "GOTO", "IF", "WHILE",
  "ELSE", "TIMES_EQUALS", "OVER_EQUALS", "PERCENT_EQUALS", "PLUS_EQUALS",
  "MINUS_EQUALS", "LEFT_SHIFT_EQUALS", "RIGHT_SHIFT_EQUALS", "AND_EQUALS",
  "XOR_EQUALS", "OR_EQUALS", "AND", "OR", "LESS_EQ", "GRTR_EQ",
  "LEFT_SHIFT", "RIGHT_SHIFT", "PLUS_PLUS", "MINUS_MINUS", "EQ_EQ",
  "NOT_EQ", "SA_MAXVERTEXCOUNT", "SA_NUMTHREADS", "CS_LAYOUT", "';'",
  "'['", "'('", "')'", "']'", "','", "'{'", "'}'", "'='", "'<'", "'>'",
  "':'", "'?'", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'~'", "'!'", "'.'", "$accept", "prog", "tok", "line_statement",
  "ignore_line_statement", "shader_and_layout", "texture_type",
  "buffer_type", "optional_templateval", "layout_params",
  "technique_decls", "group_technique_decl", "technique_decl",
  "cs_layout_spec", "normal_layout_spec", "tx_layout", "layout_s",
  "cs_layout", "layout_el", "layout_def", "lex_fx", "shader_fx",
  "lex_passthrough", "function_content", "read_block",
  "optional_return_semantic", "struct_definition", "struct_member_list",
  "struct_member", "optional_uniform", "param_declaration_list",
  "param_declaration", "opt_sq", "opt_num", "param", "opt_storage",
  "input_semantic", "location", "tech_def", "pass_list", "pass_def",
  "prog_def", "shaders_list", "vec4", "shader_fn", "shader_def",
  "shader_compile", "shader_lvalue", "shader_rvalue", "shader_layout",
  "shader_layout_list", "statement_list", "line_statement_in_shader",
  "declaration", "init_declarator_list", "init_declarator", "declarator",
  "statement", "for_init_statement", "optional_expression",
  "compound_statement", "expression", "assignment_exp",
  "assignment_operator", "conditional_exp", "logical_or_exp",
  "logical_and_exp", "inclusive_or_exp", "exclusive_or_exp", "and_exp",
  "equality_exp", "relational_exp", "shift_expression", "additive_exp",
  "mult_exp", "cast_exp", "unary_exp", "unary_operator", "sampling_exp",
  "postfix_exp", "argument_exp_list", "initializer", "initializer_list",
  "primary_exp", "const", "layout", "read_parenthesis",
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,    59,    91,    40,    41,
      93,    44,   123,   125,    61,    60,    62,    58,    63,   124,
      94,    38,    43,    45,    42,    47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     113,   114,   115,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   118,   118,   119,   120,   120,   121,   122,   123,
     124,   125,   125,   126,   126,   127,   128,   129,   129,   130,
     131,   132,   133,   134,   135,   135,   136,   137,   137,   138,
     139,   139,   140,   140,   140,   141,   142,   142,   143,   143,
     144,   145,   145,   146,   146,   146,   146,   147,   147,   147,
     147,   148,   149,   149,   150,   151,   152,   152,   152,   152,
     153,   154,   154,   154,   155,   155,   156,   156,   156,   157,
     158,   158,   159,   159,   160,   160,   161,   161,   161,   162,
     163,   164,   164,   165,   165,   166,   166,   166,   166,   166,
     167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
     167,   167,   167,   167,   168,   168,   168,   169,   169,   170,
     171,   171,   172,   172,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   174,   174,   175,   175,   176,
     176,   177,   177,   178,   178,   179,   179,   180,   180,   180,
     181,   181,   181,   181,   181,   182,   182,   182,   183,   183,
     183,   184,   184,   184,   184,   185,   186,   186,   186,   186,
     187,   187,   187,   187,   187,   187,   188,   189,   189,   189,
     189,   189,   189,   189,   189,   190,   190,   191,   191,   191,
     192,   192,   193,   193,   193,   194,   194,   195,   195,   196,
     138,   197,   197,   198,   198,   199,   199,   200,   200,   201,
     201,   202,   203,   203,   204,   204,   204,   205
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     5,     5,     4,
       1,     6,    10,     4,     2,     3,     3,     3,     3,     6,
       4,     6,     5,     4,     6,     8,     9,     7,     1,     7,
       5,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     7,     2,     1,     5,     7,     3,
       3,     3,     1,     1,     1,     5,     3,     1,     1,     0,
       0,     0,     3,     0,     2,     0,     3,     2,     1,     4,
       1,     0,     3,     1,     0,     3,     3,     0,     1,     0,
       4,     1,     0,     1,     1,     1,     1,     2,     2,     2,
       0,     1,     2,     1,     5,     1,     2,     1,     2,     1,
      10,     5,     7,     9,     4,     5,     1,     6,     8,     4,
       4,     0,     2,     0,     3,     1,     2,     1,     0,     3,
       2,     1,     3,     1,     3,     1,     3,     4,     3,     3,
       2,     1,     2,     1,     5,     7,     5,     7,     9,     3,
       2,     2,     3,     1,     1,     1,     0,     1,     0,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     1,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     3,     1,     4,     4,
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
       3,     0,     1,     0,    60,     0,    59,    59,     0,     0,
      59,    59,    59,     0,     0,     0,     0,     5,     0,     0,
       0,    10,     0,     2,     6,     0,    28,     0,    37,    38,
      39,    35,    33,    34,    36,    40,    41,    43,    43,    32,
      60,     0,     0,     0,     0,     0,    14,     0,     0,     0,
       0,   236,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    63,    74,    54,
       0,    52,     0,    53,     0,     0,    61,     0,     0,     0,
       0,     0,     0,    17,    18,     0,     0,    15,    16,     0,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     0,
      81,     0,    73,    77,     0,     0,    50,     0,    49,     0,
      13,     0,    23,    61,     0,     0,   243,     0,   240,     0,
     238,     0,    20,    70,     0,   234,     0,     0,   106,     0,
       0,     0,     0,     0,     0,    74,    42,     7,     8,     0,
      68,    61,     0,     0,     0,     0,     0,     0,    95,    99,
      97,     0,    61,    60,    82,    79,    90,    43,    57,    58,
      56,    51,    53,     0,     0,     0,    30,     0,     0,    91,
      93,     0,     0,    46,     0,   241,     0,   235,   237,     0,
     232,     0,     0,   233,     0,     0,    22,     0,     0,     0,
       0,    66,    67,    24,     0,     0,     0,     0,     0,    61,
      98,    96,   111,     4,     0,    72,    78,     0,     0,    75,
       0,     0,     0,     0,    61,    92,     0,    61,    45,     0,
      31,   244,   245,   246,     0,     0,     0,     0,    19,     0,
       0,    21,    11,     0,    65,     0,     0,     0,     0,     0,
      27,     0,     0,   118,    61,    76,    89,    83,    85,    84,
      86,    87,    88,    80,    55,     0,     0,    48,     0,    29,
     242,   239,   231,   230,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   109,     0,   104,   222,   225,   226,
       0,   148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   131,     0,   118,   200,   202,   203,   201,   204,   205,
       0,   143,     0,   117,   133,     0,   150,   152,   165,   167,
     169,   171,   173,   175,   177,   180,   185,   188,   191,   195,
       0,     0,   196,   207,   223,     0,    25,     0,     0,     0,
       0,     0,     0,    64,    61,   105,   101,     0,     0,     0,
     113,     0,   222,     0,   147,   141,   140,     0,   146,     0,
       0,     0,   197,   198,     0,     0,    62,   116,   132,   130,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     154,     0,   199,   195,     0,   213,   214,     0,     0,     0,
     125,     0,   120,   121,   123,    44,    94,    47,     0,   107,
       0,    26,     0,     0,     0,     0,   110,   119,   142,     0,
     145,     0,   144,   139,     0,     0,   224,   149,   151,   168,
       0,   170,   172,   174,   176,   178,   179,   183,   184,   181,
     182,   186,   187,   189,   190,   192,   193,   194,   153,   216,
       0,     0,   211,     0,   212,   206,     0,     0,     0,     0,
       0,     0,    12,   102,     0,     0,   229,   229,   112,   115,
       0,   148,     0,     0,     0,   209,     0,   208,   210,   126,
     122,     0,   128,   129,     0,   217,   124,   108,     0,     0,
     227,   228,     0,     0,     0,   134,   136,   166,   215,   127,
     220,     0,     0,   103,   114,     0,   148,     0,     0,   218,
       0,   137,     0,   135,   219,   221,     0,     0,     0,   138,
       0,   100
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   118,    25,    37,    38,    63,    76,
     172,   173,    26,    45,    46,    70,    71,    72,    73,   160,
      41,    39,   112,   244,    99,   269,    97,   139,   125,   126,
     101,   102,   156,   207,   103,   104,   252,   209,   168,   169,
     170,   147,   148,   339,   149,   150,   131,   151,   242,   416,
     468,   300,   301,   302,   402,   403,   404,   303,   421,   343,
     304,   305,   306,   391,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     450,   486,   501,   323,   324,   469,   490,   226,   127,    81,
     119,   120,   121,   175,   224,   325
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -457
static const yytype_int16 yypact[] =
{
    -457,    39,  -457,   227,  -457,    11,  -457,  -457,    52,   -54,
    -457,  -457,  -457,    69,   100,    35,   114,  -457,   141,   159,
     178,  -457,   -53,  -457,  -457,   202,  -457,   222,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,    22,    22,  -457,
    -457,   226,   228,   158,   231,   264,  -457,   190,   273,   276,
     288,   211,   216,   258,   272,   233,   247,    65,   249,   254,
     334,   259,   338,   340,   341,   261,   262,  -457,    12,   257,
      38,  -457,   266,   269,   279,   348,  -457,   351,   281,   282,
      32,   289,   121,  -457,  -457,     2,   355,  -457,  -457,   356,
     357,   295,  -457,   291,   298,   302,   121,   303,   181,   304,
    -457,    80,  -457,   305,   382,    46,  -457,   231,  -457,   384,
    -457,   307,  -457,  -457,   366,   368,   312,   379,  -457,     0,
    -457,   308,  -457,  -457,   392,  -457,   394,     3,  -457,   316,
     318,   321,   319,   320,   322,    12,  -457,  -457,  -457,     6,
    -457,  -457,   323,   324,   328,   329,   352,   353,   181,  -457,
    -457,   347,  -457,  -457,   399,   401,   350,    22,  -457,  -457,
    -457,  -457,  -457,   257,   354,   423,  -457,   439,   358,   366,
    -457,   440,    -5,  -457,   429,  -457,   431,  -457,  -457,    73,
     359,   444,   369,  -457,   445,   449,  -457,   373,   370,   441,
     152,  -457,  -457,  -457,     2,   452,   454,   455,   446,  -457,
    -457,  -457,   456,  -457,   374,  -457,  -457,   378,    94,  -457,
     460,   384,   380,   381,  -457,  -457,   383,  -457,  -457,   386,
    -457,  -457,  -457,  -457,   388,   461,   391,   393,  -457,   387,
     389,  -457,  -457,   390,   375,   395,   396,   397,   398,   402,
    -457,   404,   400,   260,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,  -457,  -457,  -457,  -457,   462,   181,  -457,   366,  -457,
    -457,  -457,  -457,  -457,  -457,   473,   459,   466,   484,   374,
     408,   409,   475,   488,  -457,   410,  -457,   489,  -457,  -457,
     479,   317,   415,   416,   260,   417,   494,   418,   419,   317,
     317,  -457,   317,   260,  -457,  -457,  -457,  -457,  -457,  -457,
     146,  -457,   422,  -457,  -457,    75,  -457,  -457,   -47,   436,
     405,   411,   412,    19,    84,    87,    55,   104,  -457,   363,
     317,   424,   -55,  -457,  -457,     4,  -457,   421,   425,   426,
     427,   428,   432,  -457,  -457,  -457,  -457,   433,   435,   434,
     430,   493,  -457,   438,   437,  -457,  -457,   465,   335,   443,
     317,   317,  -457,  -457,   176,   203,  -457,  -457,  -457,  -457,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,
    -457,   317,  -457,  -457,   317,  -457,  -457,   317,    74,   164,
    -457,     4,   442,  -457,   -31,  -457,  -457,  -457,   447,  -457,
     448,  -457,   451,   492,   499,   179,  -457,  -457,  -457,   453,
    -457,   457,   437,  -457,   177,   199,  -457,  -457,  -457,   436,
      25,   405,   411,   412,    19,    84,    84,    87,    87,    87,
      87,    55,    55,   104,   104,  -457,  -457,  -457,  -457,  -457,
     241,   108,  -457,   242,  -457,  -457,   132,     4,    -4,   450,
     221,   458,  -457,  -457,   463,   464,  -457,  -457,   467,  -457,
     317,   317,   260,   260,   317,  -457,   317,  -457,  -457,  -457,
    -457,   469,  -457,  -457,   221,  -457,  -457,  -457,   506,   470,
    -457,  -457,   179,   245,   471,   472,  -457,  -457,  -457,  -457,
    -457,    -2,   474,  -457,  -457,   476,   317,   260,   278,  -457,
     507,  -457,   477,  -457,  -457,  -457,   478,   260,   508,  -457,
     481,  -457
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -457,  -457,  -457,  -457,  -457,  -457,  -457,  -457,   -36,  -457,
    -457,   372,  -457,  -457,  -457,  -457,   468,  -457,  -101,  -457,
     206,   -35,  -112,   271,  -457,  -457,  -457,  -457,   -77,  -457,
     407,   406,  -457,  -457,  -457,  -457,  -457,  -457,   277,  -457,
     376,   290,  -457,  -457,   403,   413,   361,  -457,  -457,  -457,
    -457,   255,  -457,   201,  -457,    93,   151,  -284,  -457,  -453,
    -457,  -278,  -356,  -457,    89,  -457,   207,   204,   200,   208,
     205,  -116,  -186,  -118,   -83,  -271,  -230,  -457,  -457,  -457,
     174,  -456,  -457,  -457,  -457,    82,   109,  -457,  -457,  -457,
    -457,   480,  -457,  -457,  -457,  -457
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -248
static const yytype_int16 yytable[] =
{
     347,   166,    64,   344,   428,    65,   162,   123,   164,   116,
     123,   128,   124,   400,   354,   124,   357,   481,   494,   140,
      40,   -82,   171,   100,   395,   396,   117,   361,   500,   193,
      58,    59,   397,   398,    44,   448,   129,   130,   449,     2,
     203,   116,   449,     3,     4,     5,     6,     7,     8,   392,
     183,   362,   515,   512,   399,   158,   458,   459,   117,   352,
     353,    43,   192,   460,     9,    10,    11,   159,    12,    13,
     422,   357,   424,   425,    53,    14,    15,    16,    51,    17,
      18,    19,   221,   342,   430,    20,   482,   240,   217,   508,
     393,   509,   401,   177,   222,   278,   182,   223,   279,   191,
     367,   368,   257,   246,   485,   259,   445,   446,   447,    52,
     254,   247,   248,   249,   250,   251,   360,    62,   204,   451,
     498,   210,   474,    54,    21,   123,    22,   106,   485,   107,
     124,   393,   326,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
      55,    87,   485,   289,   290,   277,    88,   375,   376,   369,
     370,   359,   292,   452,   373,   374,   360,   278,    56,   153,
     279,   154,   280,   454,   455,   294,   295,   296,   297,   371,
     372,   298,   299,   437,   438,   439,   440,    57,   495,   496,
     466,   467,   493,   344,   142,   143,   144,   145,   477,   360,
     281,   282,   283,   284,   285,   286,   287,   288,   377,   378,
     379,    60,   277,    42,   146,    47,    48,    49,    50,   458,
     459,   479,   411,   513,   278,   289,   290,   279,   344,   280,
     342,    61,   291,   519,   292,    66,    27,    67,   293,   356,
      69,   234,   278,   154,   393,   279,    68,   294,   295,   296,
     297,   435,   436,   298,   299,   441,   442,   281,   282,   283,
     284,   285,   286,   287,   288,   426,   472,   360,   360,   277,
      28,    29,    30,    74,    31,    32,    33,    34,    75,    35,
      36,   278,   289,   290,   279,    78,   280,   342,   473,   291,
     360,   292,   443,   444,    77,   293,   427,    79,    83,   278,
     289,   290,   279,    80,   294,   295,   296,   297,    82,   292,
     298,   299,    84,   484,   281,   282,   283,   284,   285,   286,
     287,   288,   294,   295,   296,   297,   342,    85,   298,   299,
     475,   478,   476,   476,   505,    86,   360,    89,   278,   289,
     290,   279,    90,    91,   277,    92,   291,    93,   292,    94,
      95,   105,   293,    96,    98,   108,   278,   289,   290,   279,
     109,   294,   295,   296,   297,   110,   292,   298,   299,   111,
     484,   514,   113,   114,   115,   122,   132,   133,   134,   294,
     295,   296,   297,   135,   137,   298,   299,   136,   138,   141,
     152,   157,   155,   163,   167,   171,   289,   290,   165,   174,
     176,   180,   179,   181,   184,   292,   185,   186,   187,   188,
     100,   194,   195,   189,   289,   290,   196,   197,   294,   295,
     296,   297,   206,   292,   298,   299,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   294,   295,   296,   297,
     198,   202,   298,   299,   212,   211,   199,   208,   213,   216,
     219,   214,   220,   227,   229,   228,   225,   390,   230,   231,
     232,   236,   233,   237,   238,   241,   243,   239,   245,   253,
     262,   255,   268,   256,   261,   258,   260,   263,   265,   264,
     266,   267,   330,   327,   270,   271,   276,   332,   272,   273,
     331,   274,   275,   333,   335,   336,   337,   338,  -247,   340,
     341,   345,   346,   349,   364,   348,   350,   351,   358,   363,
     405,   365,   394,   366,   417,   408,   464,   409,   406,   407,
     465,   410,   412,   413,   418,   414,   419,   415,   360,   423,
     502,   516,   520,   457,   507,   329,   461,   463,   462,   483,
     334,   470,   190,   471,   218,   215,   328,   487,   355,   420,
     480,   200,   456,   489,   488,   235,   503,   506,   492,   499,
     205,   201,   511,   497,   432,   510,   517,   431,   429,   518,
     521,   434,   453,   433,   504,   161,   491,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   178
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-457)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     284,   113,    38,   281,   360,    40,   107,     4,   109,     9,
       4,     9,     9,     9,   292,     9,   300,    21,   471,    96,
       9,     9,    27,    11,    79,    80,    26,    74,   484,   141,
      83,    84,    87,    88,    88,   391,    34,    35,   394,     0,
     152,     9,   398,     4,     5,     6,     7,     8,     9,   320,
     127,    98,   508,   506,   109,     9,    87,    88,    26,   289,
     290,     9,   139,    94,    25,    26,    27,    21,    29,    30,
     348,   355,   350,   351,    39,    36,    37,    38,     9,    40,
      41,    42,     9,     9,   362,    46,    90,   199,    93,    91,
     320,    93,    88,    93,    21,    21,    93,    24,    24,    93,
      81,    82,   214,     9,   460,   217,   377,   378,   379,     9,
     211,    17,    18,    19,    20,    21,    91,    95,   153,   397,
     476,   157,    97,     9,    85,     4,    87,    89,   484,    91,
       9,   361,   244,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
       9,    86,   508,    79,    80,     9,    91,   102,   103,    75,
      76,    86,    88,    89,    77,    78,    91,    21,     9,    89,
      24,    91,    26,     9,    10,   101,   102,   103,   104,    95,
      96,   107,   108,   369,   370,   371,   372,     9,   472,   473,
      11,    12,   470,   471,    13,    14,    15,    16,    90,    91,
      54,    55,    56,    57,    58,    59,    60,    61,   104,   105,
     106,     9,     9,     7,    33,     9,    10,    11,    12,    87,
      88,    89,   334,   507,    21,    79,    80,    24,   506,    26,
       9,     9,    86,   517,    88,     9,     9,     9,    92,    93,
       9,    89,    21,    91,   474,    24,    88,   101,   102,   103,
     104,   367,   368,   107,   108,   373,   374,    54,    55,    56,
      57,    58,    59,    60,    61,    89,    89,    91,    91,     9,
      43,    44,    45,     9,    47,    48,    49,    50,    88,    52,
      53,    21,    79,    80,    24,     9,    26,     9,    89,    86,
      91,    88,   375,   376,    21,    92,    93,     9,    40,    21,
      79,    80,    24,    92,   101,   102,   103,   104,    92,    88,
     107,   108,    40,    92,    54,    55,    56,    57,    58,    59,
      60,    61,   101,   102,   103,   104,     9,    94,   107,   108,
      89,    89,    91,    91,    89,    88,    91,    88,    21,    79,
      80,    24,    88,     9,     9,    86,    86,     9,    88,     9,
       9,    94,    92,    92,    92,    89,    21,    79,    80,    24,
      91,   101,   102,   103,   104,    86,    88,   107,   108,    21,
      92,    93,    21,    92,    92,    86,    21,    21,    21,   101,
     102,   103,   104,    88,    86,   107,   108,    96,    86,    86,
      86,     9,    87,     9,    28,    27,    79,    80,    91,    87,
      21,     9,    94,     9,    88,    88,    88,    86,    89,    89,
      11,    88,    88,    91,    79,    80,    88,    88,   101,   102,
     103,   104,    21,    88,   107,   108,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,   101,   102,   103,   104,
      88,    94,   107,   108,    21,    91,    93,    97,     9,     9,
      21,    93,    21,     9,     9,    86,    97,    94,     9,    86,
      90,     9,    21,     9,     9,     9,    92,    21,    90,     9,
       9,    91,    97,    92,    86,    92,    90,    86,    91,    86,
      91,    91,     9,    21,    89,    89,    86,    21,    91,    91,
      31,    89,    88,     9,    86,    86,    21,     9,     9,    89,
      21,    86,    86,     9,    99,    88,    88,    88,    86,    73,
      89,   100,    88,   101,    21,    88,    24,    89,    93,    93,
      21,    89,    89,    88,    86,    91,    61,    97,    91,    86,
      24,    24,    24,    91,    62,   258,    89,    86,    90,    89,
     269,    88,   135,    86,   172,   169,   256,    89,   293,   348,
     457,   148,   401,    89,    91,   194,    86,    86,    91,    90,
     154,   148,    86,   474,   364,    91,    89,   363,   361,    91,
      89,   366,   398,   365,   492,   107,   467,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   111,     0,     4,     5,     6,     7,     8,     9,    25,
      26,    27,    29,    30,    36,    37,    38,    40,    41,    42,
      46,    85,    87,   112,   113,   115,   122,     9,    43,    44,
      45,    47,    48,    49,    50,    52,    53,   116,   117,   131,
       9,   130,   130,     9,    88,   123,   124,   130,   130,   130,
     130,     9,     9,    39,     9,     9,     9,     9,    83,    84,
       9,     9,    95,   118,   118,   131,     9,     9,    88,     9,
     125,   126,   127,   128,     9,    88,   119,    21,     9,     9,
      92,   199,    92,    40,    40,    94,    88,    86,    91,    88,
      88,     9,    86,     9,     9,     9,    92,   136,    92,   134,
      11,   140,   141,   144,   145,    94,    89,    91,    89,    91,
      86,    21,   132,    21,    92,    92,     9,    26,   114,   200,
     201,   202,    86,     4,     9,   138,   139,   198,     9,    34,
      35,   156,    21,    21,    21,    88,    96,    86,    86,   137,
     138,    86,    13,    14,    15,    16,    33,   151,   152,   154,
     155,   157,    86,    89,    91,    87,   142,     9,     9,    21,
     129,   126,   128,     9,   128,    91,   132,    28,   148,   149,
     150,    27,   120,   121,    87,   203,    21,    93,   201,    94,
       9,     9,    93,   138,    88,    88,    86,    89,    89,    91,
     140,    93,   138,   132,    88,    88,    88,    88,    88,    93,
     154,   155,    94,   132,   131,   141,    21,   143,    97,   147,
     118,    91,    21,     9,    93,   150,     9,    93,   121,    21,
      21,     9,    21,    24,   204,    97,   197,     9,    86,     9,
       9,    86,    90,    21,    89,   156,     9,     9,     9,    21,
     132,     9,   158,    92,   133,    90,     9,    17,    18,    19,
      20,    21,   146,     9,   128,    91,    92,   132,    92,   132,
      90,    86,     9,    86,    86,    91,    91,    91,    97,   135,
      89,    89,    91,    91,    89,    88,    86,     9,    21,    24,
      26,    54,    55,    56,    57,    58,    59,    60,    61,    79,
      80,    86,    88,    92,   101,   102,   103,   104,   107,   108,
     161,   162,   163,   167,   170,   171,   172,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   193,   194,   205,   132,    21,   151,   148,
       9,    31,    21,     9,   133,    86,    86,    21,     9,   153,
      89,    21,     9,   169,   171,    86,    86,   167,    88,     9,
      88,    88,   186,   186,   171,   161,    93,   167,    86,    86,
      91,    74,    98,    73,    99,   100,   101,    81,    82,    75,
      76,    95,    96,    77,    78,   102,   103,   104,   105,   106,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      94,   173,   185,   186,    88,    79,    80,    87,    88,   109,
       9,    88,   164,   165,   166,    89,    93,    93,    88,    89,
      89,   132,    89,    88,    91,    97,   159,    21,    86,    61,
     163,   168,   171,    86,   171,   171,    89,    93,   172,   176,
     171,   177,   178,   179,   180,   181,   181,   182,   182,   182,
     182,   183,   183,   184,   184,   185,   185,   185,   172,   172,
     190,   171,    89,   190,     9,    10,   166,    91,    87,    88,
      94,    89,    90,    86,    24,    21,    11,    12,   160,   195,
      88,    86,    89,    89,    97,    89,    91,    90,    89,    89,
     165,    21,    90,    89,    92,   172,   191,    89,    91,    89,
     196,   196,    91,   171,   169,   167,   167,   174,   172,    90,
     191,   192,    24,    86,   195,    89,    86,    62,    91,    93,
      91,    86,   169,   167,    93,   191,    24,    89,    91,   167,
      24,    89
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
#line 155 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 164 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 167 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 170 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string texture_type=(yyvsp[(2) - (5)]).strs[0];
		int typed_id=(yyvsp[(2) - (5)]).token;
		bool compute_only=(texture_type==string("image3D"))||(texture_type.substr(0,2)==string("RW"));
		
		stringReplaceAll(texture_type,"RWTexture","image");
		ostringstream decl;
		if(compute_only)
			gEffect->m_sharedCode<<"#ifdef IN_COMPUTE_SHADER\n";
		string template_type=(yyvsp[(3) - (5)]).strs[0];
		string texture_name=(yyvsp[(4) - (5)]).strs[0];
		string layout;
		if(compute_only)
			layout=GetLayoutForTemplateType(template_type)+" ";
		string type=GetEquivalentGLTextureType(texture_type,template_type);
		decl<<layout<<"uniform "<<type<<" "<<texture_name<<";\n";
		declaredTextures[texture_name].type=type;
		gEffect->m_sharedCode<<decl.str();
		if(compute_only)
			gEffect->m_sharedCode<<"#endif\n";
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 202 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 218 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 224 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 228 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 232 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="layout(local_size_x=%1,local_size_y=%2,local_size_z=%3) in;";
		stringReplaceAll(currentCsLayout,"%1",(yyvsp[(4) - (10)]).strs[0]);
		stringReplaceAll(currentCsLayout,"%2",(yyvsp[(6) - (10)]).strs[0]);
		stringReplaceAll(currentCsLayout,"%3",(yyvsp[(8) - (10)]).strs[0]);
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 239 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(2) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(4) - (4)]).strs[0];
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 253 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 259 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 265 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name					=(yyvsp[(2) - (3)]).strs[0];
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 269 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name		=(yyvsp[(2) - (3)]).strs[0];
		string str		=string("#undef ")+name+"\n";
		glfxWrite(str.c_str()); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 275 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 20:
/* Line 1792 of yacc.c  */
#line 293 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 21:
/* Line 1792 of yacc.c  */
#line 333 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 22:
/* Line 1792 of yacc.c  */
#line 343 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 23:
/* Line 1792 of yacc.c  */
#line 360 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 366 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string bufferName	=(yyvsp[(2) - (6)]).strs[0];
		string def			=(yyvsp[(4) - (6)]).strs[0];

		ostringstream str;
		WriteLineNumber(str,current_filenumber,(yyvsp[(1) - (6)]).lineno+(last_linenumber-global_linenumber));
		str<< "constant_buffer"<<" "<<(yyvsp[(2) - (6)]).strs[0]<<(yyvsp[(4) - (6)]).strs[0]<<";\n";
		WriteLineNumber(str,current_filenumber,glfxget_lineno()+(last_linenumber-global_linenumber));

		glfxWrite(str.str().c_str());
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 379 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string functionName		=(yyvsp[(2) - (8)]).strs[0];
		Function *f				=new Function;
		functions[functionName]	=f;
		f->returnType			=(yyvsp[(1) - (8)]).strs[0];
		f->content				=(yyvsp[(7) - (8)]).strs[0];
		string returnable		=(yyvsp[(8) - (8)]).strs[1];
		f->content+="\nreturn ";
		f->content+=returnable+";";
		f->parameters			=*(yyvsp[(4) - (8)]).vars;
		delete (yyvsp[(4) - (8)]).vars;

		// Now we must reorganize any texture parameters. Look at buildFunction:
		for(std::map<std::string,TextureSampler*>::const_iterator i=buildFunction.textureSamplers.begin();i!=buildFunction.textureSamplers.end();i++)
		{
			string tsname=i->first;
			string texture_name=i->second->textureName;
			string sampler_state_name=i->second->samplerState;
		}
		
		ostringstream str;
		ostringstream params;
		bool start=true;
		for(vector<glfxstype::variable>::iterator j=f->parameters.begin();j!=f->parameters.end();j++)
		{
			string type=j->type;
			// We SHOULD check the type but don't yet.
			string name=j->identifier;
			// Is this one of the textures in the textureSampler list?
			auto u=buildFunction.textureSamplersByTexture.find(name);
			if(u!=buildFunction.textureSamplersByTexture.end())
			{
				// the type remains the same.
				for(auto v=u->second.begin();v!=u->second.end();v++)
				{
					if(start)
						start=false;
					else
						params<<", ";
					TextureSampler *ts=*v;
					params<<j->storage<<" "<<j->type<<" "<<ts->textureName<<"_"<<ts->samplerState;
					if(j->semantic.size())
						params<<": "<<j->semantic;
				}
			}
			else
			{
				if(start)
					start=false;
				else
					params<<", ";
				params<<j->storage<<" "<<j->type<<" "<<j->identifier;
				if(j->semantic.size())
					params<<": "<<j->semantic;
			}
		}

		WriteLineNumber(str,current_filenumber,(yyvsp[(1) - (8)]).lineno+(last_linenumber-global_linenumber));
		str<< f->returnType<<" "<<functionName<<"("<<params.str()<<")"<<"\n{"<<f->content<<"\n}\n";
		WriteLineNumber(str,current_filenumber,glfxget_lineno()+(last_linenumber-global_linenumber));

		glfxWrite(str.str().c_str());

		buildFunction.clear();
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 446 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		CompilableShader &sh=*(compilableShaders[(yyvsp[(3) - (9)]).strs[0]]=new CompilableShader);
		sh.shaderName			=(yyvsp[(3) - (9)]).strs[0];
		sh.returnType			=(yyvsp[(2) - (9)]).strs[0];
		sh.shaderContent		=(yyvsp[(8) - (9)]).strs[0];
		sh.returnable			=(yyvsp[(8) - (9)]).strs[1];
		sh.main_linenumber		=(yyvsp[(1) - (9)]).lineno+(last_linenumber-global_linenumber);
		sh.content_linenumber	=(yyvsp[(8) - (9)]).lineno+(last_linenumber-global_linenumber);
		sh.current_filenumber	=current_filenumber;
		sh.csLayout				=currentCsLayout;
		ostringstream shaderCode;
		ostringstream extraDeclarations;
		ostringstream finalCode;
		sh.vars=*(yyvsp[(5) - (9)]).vars;

		ostringstream str;
		for(std::map<std::string,TextureSampler*>::const_iterator i=buildFunction.textureSamplers.begin();i!=buildFunction.textureSamplers.end();i++)
		{
			string tsname=i->first;
			string texture_name=i->second->textureName;
			if(declaredTextures.find(texture_name)!=declaredTextures.end())
			{
				string sampler_type=declaredTextures[texture_name].type;
				str<<sampler_type<<" "<<tsname;
			}
			else
				errSem(string("Can't find texture declaration for ")+texture_name);
		}
		gEffect->m_sharedCode<<str.str();

		buildFunction.clear();
		delete (yyvsp[(5) - (9)]).vars;
		
		gEffect->m_sharedCode<<"#line "<<(glfxget_lineno()+(last_linenumber-global_linenumber))<<" "<<current_filenumber<<endl;
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 482 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 487 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 490 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string groupName=(yyvsp[(3) - (7)]).strs[0];
		if(gEffect->m_techniqueGroups.find(groupName)==gEffect->m_techniqueGroups.end())
			gEffect->m_techniqueGroups[groupName]=new TechniqueGroup;
		*(gEffect->m_techniqueGroups[groupName])=buildTechniqueGroup;
		buildTechniqueGroup.m_techniques.clear();
	}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 498 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 505 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 511 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 516 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 522 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 528 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 533 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 538 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 45:
/* Line 1792 of yacc.c  */
#line 549 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 553 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 556 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 560 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 49:
/* Line 1792 of yacc.c  */
#line 570 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 574 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 579 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 583 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 587 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 591 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 595 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 600 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		   }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 605 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 609 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 613 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 619 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
    gLexPassthrough=false;
}
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 625 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 629 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 636 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 642 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
 }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 646 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
 }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 650 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="{\n";
	(yyval).strs[0]+=((yyvsp[(2) - (3)]).strs[0]+"\n}\n");
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 655 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=((yyvsp[(1) - (2)]).strs[0]+"\n")+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 659 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 663 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(((yyvsp[(1) - (4)]).strs[0]+" ")+(yyvsp[(2) - (4)]).strs[0]+" ")+(yyvsp[(3) - (4)]).strs[0]+";";
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 667 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="uniform";
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 671 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 675 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars		=(yyvsp[(1) - (3)]).vars;
		(yyval).strs[0]	=((yyvsp[(1) - (3)]).strs[0]+",")+(yyvsp[(3) - (3)]).strs[0];

		YYSTYPE::variable var;
		var.storage		=(yyvsp[(3) - (3)]).strs[1];
		var.type		=(yyvsp[(3) - (3)]).strs[2];
		var.identifier	=(yyvsp[(3) - (3)]).strs[3];
		var.semantic	=(yyvsp[(3) - (3)]).strs[4];
    
		(yyval).vars->push_back(var);
	}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 688 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		YYSTYPE::variable var;
		string s1	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).strs[0]	=s1;
		var.storage=(yyvsp[(1) - (1)]).strs[1];
		var.type=(yyvsp[(1) - (1)]).strs[2];
		var.identifier=(yyvsp[(1) - (1)]).strs[3];
		var.semantic=(yyvsp[(1) - (1)]).strs[4];
    
		(yyval).vars = new vector<YYSTYPE::variable>;
		(yyval).vars->push_back(var);
	}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 701 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 707 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    ostringstream prepend;
	string semantic;
	string location		=(yyvsp[(3) - (3)]).strs[1];
    switch((yyvsp[(3) - (3)]).rType)
	{
    case REGISTER_INT:
        prepend<<"layout(location="<<(yyvsp[(3) - (3)]).num<<") ";
        break;
    case REGISTER_NAME:
        prepend<<"layout(location="<<(yyvsp[(3) - (3)]).strs[0]<<") ";
        break;
    case SEMANTIC:
		semantic=getGLInputSemantic((yyvsp[(3) - (3)]).num);
        break;
    }
    prepend<<(yyvsp[(1) - (3)]).strs[1];

	string storage	=prepend.str();
	string type		=(yyvsp[(1) - (3)]).strs[2];
	string id		=(yyvsp[(1) - (3)]).strs[3]+(yyvsp[(2) - (3)]).strs[0];
	string all		=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
    (yyval).strs[0]=all;
    (yyval).strs[1]=storage;
    (yyval).strs[2]=type;
    (yyval).strs[3]=id;

   // $$.strs[3]=$2.strs[0];
    //$$.strs[3]+=$3.strs[0];
    (yyval).strs[4]=semantic;
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 740 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 745 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 750 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
			}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 755 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
			}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 760 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (4)]).strs[0];
		string type		=(yyvsp[(2) - (4)]).strs[0];
		string template_=(yyvsp[(3) - (4)]).strs[0];
		if(template_.length())
			type+=string("<")+template_+string(">");
		string id		=(yyvsp[(4) - (4)]).strs[0];
		string all		=(((yyvsp[(1) - (4)]).strs[0]+" ")+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+" ")+(yyvsp[(4) - (4)]).strs[0];
		(yyval).strs[0]		= all	;
		(yyval).strs[1]		= storage	;
		(yyval).strs[2]		= type		;
		(yyval).strs[3]		= id		;
	}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 774 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 778 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 782 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 787 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 792 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 797 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 802 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 807 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 813 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 818 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 824 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 831 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 93:
/* Line 1792 of yacc.c  */
#line 843 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 94:
/* Line 1792 of yacc.c  */
#line 857 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable = (yyvsp[(1) - (5)]).boolean;
	(yyval).prog = (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0] = (yyvsp[(2) - (5)]).strs[0];
	(yyval).prog->passState=buildPassState;
	buildPassState=PassState();
}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 866 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders));
    delete (yyvsp[(1) - (1)]).shaders;
}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 872 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 97:
/* Line 1792 of yacc.c  */
#line 882 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 98:
/* Line 1792 of yacc.c  */
#line 895 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 903 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 911 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 920 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 924 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 930 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 938 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 105:
/* Line 1792 of yacc.c  */
#line 989 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 106:
/* Line 1792 of yacc.c  */
#line 1056 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string compiledShaderName	=(yyvsp[(1) - (1)]).strs[0];
			(yyval).strs[0]					=compiledShaderName;
			(yyval).num						=0;
			(yyval).lineno					=(yyvsp[(1) - (1)]).lineno;
		}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1063 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).lineno				=(yyvsp[(5) - (6)]).lineno;
			string gsName			=(yyvsp[(3) - (6)]).strs[0];
			string definition		=(yyvsp[(5) - (6)]).strs[0];
			CompiledShaderMap::iterator i=gEffect->m_compiledShaders.find(gsName);
			if(i==gEffect->m_compiledShaders.end())
			{
				ostringstream msg;
				msg<<"Compiled shader "<<gsName<<" not found for streamout"<<endl;
				errSem(msg.str().c_str());
			}
			else
			{
				// gl doesn't really care.
			//	gEffect->m_compiledShaders[]=i->second;
			}
			(yyval).strs[0]										=gsName;
		}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1082 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).lineno								=(yyvsp[(5) - (8)]).lineno;
			string profileName						=(yyvsp[(3) - (8)]).strs[0];
			ProfileMap::iterator i					=gEffect->m_profileToVersion.find(profileName);
			int version_num							=0;
			if(i==gEffect->m_profileToVersion.end())
			{
				ostringstream msg;
				msg<<"Profile "<<profileName<<" not found."<<endl;
				errSem(msg.str().c_str());
			}
			else
				version_num=i->second;


			string shaderName=(yyvsp[(5) - (8)]).strs[0];
			CompilableShader &sh=*(compilableShaders[shaderName]);
			gEffect->m_shaderLayouts[shaderName]	=sh.csLayout;
			gEffect->m_shaders[shaderName]			=Compile((yyvsp[(1) - (8)]).sType,sh);


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

  case 109:
/* Line 1792 of yacc.c  */
#line 1116 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1127 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1133 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1137 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1141 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1146 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1155 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1164 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1170 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1175 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 120:
/* Line 1792 of yacc.c  */
#line 1188 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			stringReplaceAll(init_declarator_list,type_spec+type_spec,type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1197 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1201 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1205 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1209 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 125:
/* Line 1792 of yacc.c  */
#line 1247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1251 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1255 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1260 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1264 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1268 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
				}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1273 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1277 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1281 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
				}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1286 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1290 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string s1=(yyvsp[(1) - (7)]).strs[0];
					string s2=(yyvsp[(2) - (7)]).strs[0];
					string s3=(yyvsp[(3) - (7)]).strs[0];
					string s4=(yyvsp[(4) - (7)]).strs[0];
					string s5=(yyvsp[(5) - (7)]).strs[0];
					string s6=(yyvsp[(6) - (7)]).strs[0];
					string s7=(yyvsp[(7) - (7)]).strs[0];
					(yyval).strs[0]=(s1+s2+s3+s4+s5+s6+"\n")+s7;
				}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1301 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1305 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1309 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
				}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1314 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1318 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1322 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1326 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 143:
/* Line 1792 of yacc.c  */
#line 1341 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1346 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1350 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1354 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1357 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1361 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1366 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1372 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1376 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1380 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1384 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1388 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1401 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1405 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1409 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
	}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1414 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1418 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1422 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1426 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1430 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1434 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1438 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1442 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1446 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1450 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1455 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1459 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1463 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1467 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1471 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1475 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1479 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1483 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1487 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1491 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1495 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1499 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1503 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1507 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1511 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1515 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1519 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1523 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1527 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1531 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1535 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1539 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1543 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1547 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1551 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
						// Put the thing we're sampling into strs[1]
						(yyval).strs[1]=expr1;
						// We put the command into strs[2]
						(yyval).strs[2]=expr3;
					}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1562 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1566 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1570 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (4)]).strs[0];
						string textureName=(yyvsp[(1) - (4)]).strs[1];
						string command=(yyvsp[(1) - (4)]).strs[2];
						string expr2=(yyvsp[(2) - (4)]).strs[0];
						string expr3=(yyvsp[(3) - (4)]).strs[0];
						string expr4=(yyvsp[(4) - (4)]).strs[0];
						vector<string> args=split(expr3,',');
						// The first argument is the sampler state, the second is the texcoords, the third if present is the lod.
						// So: to translate this to GLSL, an expression like
						//			mainTexture.Sample(samplerState1,texcoords)
						// becomes:
						//			texture(mainTexture&samplerState1,texcoords)
						// and we will map the string "mainTexture&samplerState1" to mainTexture and samplerState1.

						// Later, if we call the function, we will insert it into the shader code.
						// each Texture parameter must be replaced by a list of all the texture-sampler combinations that use it.
						// each SamplerState parameter must be replaced by a list of the texture-sampler combinations that use it.
						// This might lead to some doubling-up.
						TextureSampler *ts=new TextureSampler;
						ts->textureName=textureName;
						ts->samplerState=args[0];
						string textureSamplerName=(ts->textureName+"_")+ts->samplerState;
						buildFunction.textureSamplers[textureSamplerName]=(ts);
						buildFunction.textureSamplersByTexture[textureName].push_back(ts);
						string full_expr=string("texture(")+(textureSamplerName+",")+args[1]+")";
						(yyval).strs[0]=full_expr;

						// There are four possibilities for each sampling command:
						// 1. both the texture and the sampler are declared globally.
						// 2. The texture is a function parameter and the sampler is declared globally.
						// 3. The texture is declared globally and the sampler is a function parameter.
						// 4. The texture and the sampler are function parameters.

						// In case 1., we insert the textureSampler declaration at the top, and in C++ apply that sampler to the texture.

						// In case 2., we replace the texture parameter with as many textureSampler parameters as needed.
						//				In the calls to this function we replace the texture parameter with the textureSamplers.
						// In case 3., we replace the sampler parameter with as many textureSampler parameters as needed.
						//				In the calls to this function we replace the sampler parameter with the textureSamplers.
						// In case 4., we replace the texture with as many textureSampler parameters as needed, and remove the sampler parameters.

						// Initially we will only implement cases 1 and 2.
					}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1615 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (4)]).strs[0];
						string expr2=(yyvsp[(2) - (4)]).strs[0];
						string expr3=(yyvsp[(3) - (4)]).strs[0];
						string expr4=(yyvsp[(4) - (4)]).strs[0];
						(yyval).strs[0]=expr1+expr2+expr3+expr4;
					}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1623 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1627 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1633 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1637 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1641 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1645 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1649 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1654 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1661 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1668 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1675 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1682 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1690 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1694 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1698 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1702 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1710 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1718 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1722 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 231:
/* Line 1792 of yacc.c  */
#line 1734 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1738 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1742 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1747 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1751 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1754 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1758 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1763 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1767 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 240:
/* Line 1792 of yacc.c  */
#line 1876 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1881 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 1887 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 1892 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 1896 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 1901 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 1906 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 1911 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 4670 "src/glfxLALRParser.cpp"
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
#line 1914 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
		case SV_VERTEXID:
			return "gl_VertexID";
		default:
		break;
		};
		return "";
	}
void glfxWarning(const char* e)
{
    ostringstream errMsg;
	int lex_linenumber=glfxget_lineno();
	int true_linenumber=lex_linenumber+last_linenumber-global_linenumber;
    errMsg<<current_filenumber<<"("<< true_linenumber<<") : glfx warning: \""<<glfxget_text()<<"\" "<<e<<std::endl;
	gEffect->Log()<<errMsg.str();
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

void resetGlfxParse()
{
	buildFunction.clear();
	functions.clear();
	declaredTextures.clear();
}
