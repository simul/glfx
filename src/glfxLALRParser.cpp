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
		std::map<std::string,CompilableShader*> compilableShaders;

/* Line 371 of yacc.c  */
#line 209 "src/glfxLALRParser.cpp"

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
     SV_VERTEXID = 273,
     NUM = 274,
     INCLUDE = 275,
     SAMPLER = 276,
     FLOAT = 277,
     LAYOUT = 278,
     LINE = 279,
     TECHNIQUE = 280,
     PASS = 281,
     GROUP = 282,
     RENDER_STATE_DECL = 283,
     QUOTED_STRING = 284,
     SHADER_LINE = 285,
     SHADER_TYPE = 286,
     COMPILE_SHADER = 287,
     CONSTRUCT_GS_WITH_SO = 288,
     STRUCT = 289,
     DEFINE = 290,
     MACRO_DEFINITION = 291,
     EOL = 292,
     DECL_SHADER = 293,
     PROFILE = 294,
     RW_TEXTURE2D = 295,
     RW_TEXTURE3D = 296,
     RW_TEXTURE2DARRAY = 297,
     RW_TEXTURE3D_FLOAT4 = 298,
     TEXTURE2DMS = 299,
     IMAGE3D = 300,
     KNOWN_TYPE = 301,
     STRUCTUREDBUFFER = 302,
     RW_STRUCTUREDBUFFER = 303,
     RETURN = 304,
     BREAK = 305,
     CONTINUE = 306,
     DO = 307,
     FOR = 308,
     GOTO = 309,
     IF = 310,
     WHILE = 311,
     ELSE = 312,
     TIMES_EQUALS = 313,
     OVER_EQUALS = 314,
     PERCENT_EQUALS = 315,
     PLUS_EQUALS = 316,
     MINUS_EQUALS = 317,
     LEFT_SHIFT_EQUALS = 318,
     RIGHT_SHIFT_EQUALS = 319,
     AND_EQUALS = 320,
     XOR_EQUALS = 321,
     OR_EQUALS = 322,
     AND = 323,
     OR = 324,
     LESS_EQ = 325,
     GRTR_EQ = 326,
     LEFT_SHIFT = 327,
     RIGHT_SHIFT = 328,
     PLUS_PLUS = 329,
     MINUS_MINUS = 330,
     EQ_EQ = 331,
     NOT_EQ = 332,
     SA_MAXVERTEXCOUNT = 333,
     SA_NUMTHREADS = 334,
     CS_LAYOUT = 335
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
#line 355 "src/glfxLALRParser.cpp"

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
#define YYLAST   547

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  105
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  92
/* YYNRULES -- Number of rules.  */
#define YYNRULES  234
/* YYNRULES -- Number of states.  */
#define YYNSTATES  488

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   335

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   103,     2,     2,     2,   101,    96,     2,
      83,    84,    99,    97,    86,    98,   104,   100,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    92,    81,
      90,    89,    91,    93,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    82,     2,    85,    95,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    87,    94,    88,   102,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    24,    30,
      35,    37,    44,    55,    60,    63,    67,    71,    75,    82,
      87,    94,   100,   105,   115,   123,   125,   133,   139,   143,
     146,   148,   150,   152,   154,   156,   158,   160,   164,   165,
     173,   176,   178,   184,   192,   196,   200,   204,   206,   208,
     210,   216,   220,   222,   224,   225,   226,   227,   231,   232,
     235,   236,   240,   242,   243,   247,   251,   252,   254,   255,
     260,   262,   263,   265,   267,   269,   271,   274,   277,   280,
     281,   283,   286,   288,   294,   296,   299,   301,   304,   306,
     317,   323,   331,   341,   346,   352,   354,   361,   370,   375,
     380,   381,   384,   385,   389,   391,   394,   396,   397,   401,
     404,   406,   410,   412,   416,   418,   422,   427,   431,   435,
     438,   440,   443,   445,   451,   459,   465,   473,   483,   487,
     490,   493,   497,   499,   501,   503,   504,   506,   507,   511,
     513,   517,   519,   523,   525,   527,   529,   531,   533,   535,
     537,   539,   541,   543,   545,   547,   553,   555,   559,   561,
     565,   567,   571,   573,   577,   579,   583,   585,   589,   593,
     595,   599,   603,   607,   611,   613,   617,   621,   623,   627,
     631,   633,   637,   641,   645,   647,   649,   652,   655,   658,
     660,   662,   664,   666,   668,   670,   672,   677,   682,   686,
     690,   693,   696,   700,   702,   704,   708,   713,   715,   719,
     721,   723,   727,   729,   731,   734,   737,   738,   743,   746,
     747,   750,   752,   756,   757,   760,   762,   767,   769,   772,
     776,   777,   779,   781,   783
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     106,     0,    -1,   106,   107,    -1,    -1,     7,   125,     8,
     129,    81,   127,    -1,    37,    -1,   108,    -1,     4,   111,
     113,     8,    81,    -1,     4,   112,   113,     8,    81,    -1,
       4,     8,     8,    81,    -1,    80,    -1,    82,    78,    83,
      19,    84,    85,    -1,    82,    79,    83,    19,    86,    19,
      86,    19,    84,    85,    -1,    23,   118,     8,    81,    -1,
      23,   119,    -1,    43,     8,    81,    -1,    43,     8,    86,
      -1,    35,    36,    37,    -1,    34,     8,    87,   189,    88,
      81,    -1,    28,     8,   190,    81,    -1,    39,     8,    83,
      19,    84,    81,    -1,    38,     8,    89,   147,    81,    -1,
      23,   125,   114,   127,    -1,   110,     8,     8,    83,   131,
      84,   130,   128,   127,    -1,     6,   125,     8,    87,   142,
      88,   127,    -1,   117,    -1,    27,   125,     8,    87,   115,
      88,   127,    -1,    24,   125,    19,    19,   127,    -1,    24,
      19,    19,    -1,     5,   126,    -1,    44,    -1,    45,    -1,
      40,    -1,    41,    -1,    42,    -1,    47,    -1,    48,    -1,
      90,     8,    91,    -1,    -1,    83,    19,    86,    19,    86,
      19,    84,    -1,   115,   116,    -1,   116,    -1,    25,     8,
      87,   139,    88,    -1,    25,   125,     8,    87,   139,    88,
     127,    -1,    83,   122,    84,    -1,    83,   120,    84,    -1,
     120,    86,   121,    -1,   121,    -1,   123,    -1,     8,    -1,
     123,    86,   123,    86,   123,    -1,     8,    89,   124,    -1,
       8,    -1,    19,    -1,    -1,    -1,    -1,    87,   152,    88,
      -1,    -1,    92,     8,    -1,    -1,   131,    86,   132,    -1,
     132,    -1,    -1,   135,   133,   138,    -1,    82,   134,    85,
      -1,    -1,    19,    -1,    -1,   136,     8,   113,     8,    -1,
       9,    -1,    -1,    15,    -1,    17,    -1,    16,    -1,    18,
      -1,    92,    19,    -1,    92,   137,    -1,    92,     8,    -1,
      -1,   140,    -1,   140,   141,    -1,   141,    -1,    26,     8,
      87,   142,    88,    -1,   143,    -1,   143,   146,    -1,   146,
      -1,   143,   145,    -1,   145,    -1,     8,    83,    22,    86,
      22,    86,    22,    86,    22,    84,    -1,    12,    83,     8,
      84,    81,    -1,    13,    83,     8,    86,    19,    84,    81,
      -1,    14,    83,     8,    86,   144,    86,    19,    84,    81,
      -1,   148,    89,   149,    81,    -1,    11,    83,   147,    84,
      81,    -1,     8,    -1,    33,    83,     8,    86,    29,    84,
      -1,    32,    83,     8,    86,     8,    83,    84,    84,    -1,
      31,    83,    19,    84,    -1,     8,    83,    84,   150,    -1,
      -1,    92,   151,    -1,    -1,   151,    86,   185,    -1,   185,
      -1,   152,   158,    -1,   158,    -1,    -1,    24,    19,    19,
      -1,   196,   155,    -1,   156,    -1,   155,    86,   156,    -1,
     157,    -1,   157,    89,   181,    -1,     8,    -1,    83,   157,
      84,    -1,   157,    82,    19,    85,    -1,   157,    82,    85,
      -1,   157,    83,    84,    -1,   162,    81,    -1,    81,    -1,
     154,    81,    -1,   161,    -1,    55,    83,   162,    84,   158,
      -1,    55,    83,   162,    84,   158,    57,   158,    -1,    56,
      83,   162,    84,   158,    -1,    52,   158,    56,    83,   162,
      84,    81,    -1,    53,    83,   159,    81,   160,    81,   160,
      84,   158,    -1,    54,     8,    81,    -1,    51,    81,    -1,
      50,    81,    -1,    49,   160,    81,    -1,   153,    -1,   162,
      -1,   154,    -1,    -1,   162,    -1,    -1,    87,   152,    88,
      -1,   163,    -1,   162,    86,   163,    -1,   165,    -1,   177,
     164,   163,    -1,    89,    -1,    58,    -1,    59,    -1,    60,
      -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,
      -1,    66,    -1,    67,    -1,   166,    -1,   166,    93,   162,
      92,   165,    -1,   167,    -1,   166,    69,   167,    -1,   168,
      -1,   167,    68,   168,    -1,   169,    -1,   168,    94,   169,
      -1,   170,    -1,   169,    95,   170,    -1,   171,    -1,   170,
      96,   171,    -1,   172,    -1,   171,    76,   172,    -1,   171,
      77,   172,    -1,   173,    -1,   172,    90,   173,    -1,   172,
      91,   173,    -1,   172,    70,   173,    -1,   172,    71,   173,
      -1,   174,    -1,   173,    72,   174,    -1,   173,    73,   174,
      -1,   175,    -1,   174,    97,   175,    -1,   174,    98,   175,
      -1,   176,    -1,   175,    99,   176,    -1,   175,   100,   176,
      -1,   175,   101,   176,    -1,   177,    -1,   179,    -1,    74,
     177,    -1,    75,   177,    -1,   178,   176,    -1,    96,    -1,
      99,    -1,    97,    -1,    98,    -1,   102,    -1,   103,    -1,
     183,    -1,   179,    82,   162,    85,    -1,   179,    83,   180,
      84,    -1,   179,    83,    84,    -1,   179,   104,     8,    -1,
     179,    74,    -1,   179,    75,    -1,   180,    86,   163,    -1,
     163,    -1,   163,    -1,    87,   182,    88,    -1,    87,   182,
      86,    88,    -1,   181,    -1,   182,    86,   181,    -1,     8,
      -1,   184,    -1,    83,   162,    84,    -1,    19,    -1,    22,
      -1,     9,   186,    -1,    10,   186,    -1,    -1,     8,     8,
     188,    81,    -1,    92,     8,    -1,    -1,   189,   187,    -1,
     187,    -1,    87,   191,    88,    -1,    -1,   191,   192,    -1,
     192,    -1,   193,    89,   195,    81,    -1,   109,    -1,     8,
     194,    -1,    82,    19,    85,    -1,    -1,     8,    -1,    19,
      -1,    22,    -1,     8,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   150,   150,   151,   155,   159,   162,   165,   195,   211,
     217,   221,   225,   232,   240,   246,   252,   258,   261,   279,
     319,   329,   346,   353,   372,   377,   380,   388,   395,   401,
     406,   406,   406,   406,   406,   412,   412,   418,   424,   428,
     439,   443,   446,   450,   460,   464,   469,   473,   477,   481,
     485,   490,   495,   499,   504,   510,   516,   520,   527,   532,
     536,   538,   550,   562,   566,   598,   604,   608,   614,   618,
     630,   635,   638,   643,   648,   653,   658,   663,   669,   675,
     680,   687,   699,   713,   722,   728,   738,   751,   759,   767,
     776,   780,   786,   794,   845,   912,   919,   938,   972,   983,
     990,   993,   998,  1002,  1007,  1011,  1020,  1027,  1031,  1044,
    1053,  1057,  1061,  1065,  1103,  1107,  1111,  1116,  1120,  1124,
    1129,  1133,  1137,  1142,  1146,  1150,  1154,  1158,  1163,  1167,
    1171,  1175,  1190,  1195,  1199,  1204,  1206,  1211,  1215,  1221,
    1225,  1229,  1233,  1237,  1241,  1242,  1243,  1244,  1245,  1246,
    1247,  1248,  1249,  1250,  1254,  1258,  1263,  1267,  1271,  1275,
    1279,  1283,  1287,  1291,  1295,  1299,  1304,  1308,  1312,  1316,
    1320,  1324,  1328,  1332,  1336,  1340,  1344,  1348,  1352,  1356,
    1360,  1364,  1368,  1372,  1376,  1380,  1384,  1388,  1392,  1396,
    1396,  1396,  1396,  1396,  1396,  1400,  1404,  1408,  1412,  1416,
    1422,  1426,  1430,  1434,  1438,  1443,  1450,  1457,  1464,  1471,
    1475,  1479,  1483,  1487,  1491,  1499,  1508,  1511,  1523,  1528,
    1531,  1536,  1540,  1544,  1547,  1552,  1556,  1665,  1670,  1676,
    1682,  1685,  1690,  1695,  1700
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
  "SV_GROUPID", "SV_VERTEXID", "NUM", "INCLUDE", "SAMPLER", "FLOAT",
  "LAYOUT", "LINE", "TECHNIQUE", "PASS", "GROUP", "RENDER_STATE_DECL",
  "QUOTED_STRING", "SHADER_LINE", "SHADER_TYPE", "COMPILE_SHADER",
  "CONSTRUCT_GS_WITH_SO", "STRUCT", "DEFINE", "MACRO_DEFINITION", "EOL",
  "DECL_SHADER", "PROFILE", "RW_TEXTURE2D", "RW_TEXTURE3D",
  "RW_TEXTURE2DARRAY", "RW_TEXTURE3D_FLOAT4", "TEXTURE2DMS", "IMAGE3D",
  "KNOWN_TYPE", "STRUCTUREDBUFFER", "RW_STRUCTUREDBUFFER", "RETURN",
  "BREAK", "CONTINUE", "DO", "FOR", "GOTO", "IF", "WHILE", "ELSE",
  "TIMES_EQUALS", "OVER_EQUALS", "PERCENT_EQUALS", "PLUS_EQUALS",
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
  "optional_return_semantic", "param_declaration_list",
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,    59,    91,    40,    41,    93,    44,   123,   125,    61,
      60,    62,    58,    63,   124,    94,    38,    43,    45,    42,
      47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   105,   106,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   108,   109,   110,
     111,   111,   111,   111,   111,   112,   112,   113,   113,   114,
     115,   115,   116,   117,   118,   119,   120,   120,   121,   121,
     122,   123,   124,   124,   125,   126,   127,   128,   129,   130,
     130,   131,   131,   131,   132,   133,   133,   134,   134,   135,
     136,   136,   137,   137,   137,   137,   138,   138,   138,   138,
     139,   140,   140,   141,   142,   143,   143,   143,   143,   144,
     145,   145,   145,   146,   146,   147,   147,   147,   148,   149,
     149,   150,   150,   151,   151,   152,   152,   152,   153,   154,
     155,   155,   156,   156,   157,   157,   157,   157,   157,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   159,   159,   159,   160,   160,   161,   162,
     162,   163,   163,   164,   164,   164,   164,   164,   164,   164,
     164,   164,   164,   164,   165,   165,   166,   166,   167,   167,
     168,   168,   169,   169,   170,   170,   171,   171,   171,   172,
     172,   172,   172,   172,   173,   173,   173,   174,   174,   174,
     175,   175,   175,   175,   176,   177,   177,   177,   177,   178,
     178,   178,   178,   178,   178,   179,   179,   179,   179,   179,
     179,   179,   180,   180,   181,   181,   181,   182,   182,   183,
     183,   183,   184,   184,   185,   185,   186,   187,   188,   188,
     189,   189,   190,   190,   191,   191,   192,   192,   193,   194,
     194,   195,   195,   195,   196
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     5,     5,     4,
       1,     6,    10,     4,     2,     3,     3,     3,     6,     4,
       6,     5,     4,     9,     7,     1,     7,     5,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     7,
       2,     1,     5,     7,     3,     3,     3,     1,     1,     1,
       5,     3,     1,     1,     0,     0,     0,     3,     0,     2,
       0,     3,     1,     0,     3,     3,     0,     1,     0,     4,
       1,     0,     1,     1,     1,     1,     2,     2,     2,     0,
       1,     2,     1,     5,     1,     2,     1,     2,     1,    10,
       5,     7,     9,     4,     5,     1,     6,     8,     4,     4,
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
       3,     0,     1,     0,    55,    54,    54,     0,    54,    54,
      54,     0,     0,     0,     5,     0,     0,     0,    10,     0,
       2,     6,     0,    25,     0,    32,    33,    34,    30,    31,
      35,    36,    38,    38,    29,     0,     0,     0,     0,    14,
       0,     0,     0,     0,   223,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    58,    49,
       0,    47,     0,    48,     0,     0,    56,     0,     0,     0,
       0,     0,     0,    17,     0,     0,    15,    16,     0,     0,
       0,     9,     0,     0,     0,     0,     0,     0,    45,     0,
      44,     0,    13,     0,    22,    56,     0,     0,   230,     0,
     227,     0,   225,     0,    19,     0,   221,     0,    95,     0,
       0,     0,     0,     0,     0,    63,    37,     7,     8,     0,
       0,     0,     0,     0,     0,    84,    88,    86,     0,    56,
      52,    53,    51,    46,    48,     0,     0,     0,    27,     0,
       0,    80,    82,     0,     0,    41,     0,   228,     0,   222,
     224,     0,   219,     0,   220,     0,     0,    21,     0,     0,
       0,    70,     0,    62,    66,     0,     0,     0,     0,     0,
       0,    56,    87,    85,   100,     4,     0,     0,     0,    56,
      81,     0,    56,    40,     0,    28,   231,   232,   233,     0,
       0,     0,    18,     0,     0,    20,    11,     0,    60,    71,
      68,    79,    38,     0,     0,     0,     0,     0,    24,     0,
       0,    50,     0,     0,    43,     0,    26,   229,   226,   218,
     217,     0,     0,     0,     0,     0,    61,    67,     0,     0,
      64,     0,     0,     0,     0,     0,    98,     0,    93,     0,
       0,     0,     0,     0,     0,    59,   107,    56,    65,    78,
      72,    74,    73,    75,    76,    77,    69,    94,    90,     0,
       0,     0,   102,    39,    83,    42,     0,    96,     0,   209,
     212,   213,     0,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   120,     0,   107,   189,   191,   192,   190,
     193,   194,     0,   132,     0,   106,   122,     0,   139,   141,
     154,   156,   158,   160,   162,   164,   166,   169,   174,   177,
     180,   184,     0,   185,   195,   210,     0,    23,     0,     0,
       0,     0,    99,     0,    12,     0,   209,     0,   136,   130,
     129,     0,   135,     0,     0,     0,   186,   187,     0,     0,
      57,   105,   121,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   143,     0,   188,   184,   200,   201,
       0,     0,     0,   114,     0,   109,   110,   112,    91,     0,
       0,   216,   216,   101,   104,    97,   108,   131,     0,   134,
       0,   133,   128,     0,     0,   211,   138,   140,   157,     0,
     159,   161,   163,   165,   167,   168,   172,   173,   170,   171,
     175,   176,   178,   179,   181,   182,   183,   142,     0,   198,
     203,     0,   199,     0,     0,     0,     0,     0,     0,     0,
     214,   215,     0,     0,   137,     0,     0,     0,   196,   197,
       0,   115,   111,     0,   117,   118,     0,   204,   113,     0,
      92,   103,     0,     0,   123,   125,   155,   202,   116,   207,
       0,     0,     0,   137,     0,     0,   205,     0,   126,     0,
     124,   206,   208,     0,     0,     0,   127,    89
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    20,    21,   100,    22,    32,    33,    55,    66,
     144,   145,    23,    38,    39,    60,    61,    62,    63,   132,
      35,    34,    94,   247,    86,   225,   162,   163,   201,   228,
     164,   165,   255,   230,   140,   141,   142,   124,   125,   261,
     126,   127,   111,   128,   210,   322,   393,   292,   293,   294,
     385,   386,   387,   295,   400,   327,   296,   297,   298,   375,
     299,   300,   301,   302,   303,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   431,   458,   470,   314,   315,
     394,   440,   106,   191,   107,    71,   101,   102,   103,   147,
     189,   316
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -448
static const yytype_int16 yypact[] =
{
    -448,   414,  -448,   152,  -448,  -448,  -448,   -42,  -448,  -448,
    -448,    36,    43,    21,  -448,    64,    74,   101,  -448,    46,
    -448,  -448,   104,  -448,   122,  -448,  -448,  -448,  -448,  -448,
    -448,  -448,    13,    13,  -448,   126,   132,   144,   164,  -448,
      66,   156,   187,   199,   124,   170,   204,   169,   179,   -66,
     180,   181,   257,   185,   261,   263,   264,   190,  -448,   189,
     -18,  -448,   195,   196,   202,   265,  -448,   266,   200,   201,
       5,   205,   285,  -448,    -1,   275,  -448,  -448,   279,   280,
     227,  -448,   221,   232,   233,   150,   234,     4,  -448,   144,
    -448,   308,  -448,   231,  -448,  -448,   292,   294,   239,   303,
    -448,    19,  -448,   235,  -448,   319,  -448,    14,  -448,   245,
     246,   249,   247,   252,   253,   107,  -448,  -448,  -448,   250,
     254,   259,   260,   262,   256,   150,  -448,  -448,   267,  -448,
    -448,  -448,  -448,  -448,  -448,   189,   271,   316,  -448,   332,
     258,   292,  -448,   343,   -19,  -448,   339,  -448,   340,  -448,
    -448,    28,   268,   281,  -448,   353,   357,  -448,   286,   283,
     347,  -448,    -9,  -448,   287,   362,    -1,   363,   366,   369,
     359,  -448,  -448,  -448,   371,  -448,   308,   295,   293,  -448,
    -448,   296,  -448,  -448,   297,  -448,  -448,  -448,  -448,   309,
     381,   312,  -448,   310,   315,  -448,  -448,   320,   302,   386,
     383,   313,    13,   325,   326,   327,   329,   328,  -448,   334,
     330,  -448,   403,   150,  -448,   292,  -448,  -448,  -448,  -448,
    -448,   415,   395,   406,   418,   341,  -448,  -448,   342,   211,
    -448,   425,   364,   365,   421,   426,  -448,   360,  -448,   370,
     355,   367,   373,   384,   385,  -448,   251,  -448,  -448,  -448,
    -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,   387,
     389,   361,   358,  -448,  -448,  -448,   390,  -448,   388,   462,
    -448,  -448,   456,   301,   396,   397,   251,   393,   471,   398,
     399,   301,   301,  -448,   301,   251,  -448,  -448,  -448,  -448,
    -448,  -448,   135,  -448,   402,  -448,  -448,   -44,  -448,  -448,
     -58,   412,   391,   392,   394,   129,   -17,   141,   123,    37,
    -448,   400,   301,   -49,  -448,  -448,    -4,  -448,   405,   466,
     465,   215,  -448,   407,  -448,   473,  -448,   416,   409,  -448,
    -448,   437,   333,   417,   301,   301,  -448,  -448,    -6,   193,
    -448,  -448,  -448,  -448,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,   301,   301,   301,   301,   301,   301,
     301,   301,   301,   301,  -448,  -448,  -448,  -448,  -448,  -448,
    -448,  -448,  -448,  -448,  -448,   301,  -448,  -448,  -448,  -448,
     301,   289,   491,  -448,    -4,   419,  -448,    59,  -448,   420,
     423,  -448,  -448,   422,  -448,  -448,  -448,  -448,   427,  -448,
     428,   409,  -448,    35,    69,  -448,  -448,  -448,   412,   -46,
     391,   392,   394,   129,   -17,   -17,   141,   141,   141,   141,
     123,   123,    37,    37,  -448,  -448,  -448,  -448,   154,  -448,
    -448,    72,  -448,    95,    -4,   -14,   429,    48,   478,   430,
    -448,  -448,   215,   301,   301,   251,   251,   301,  -448,  -448,
     301,  -448,  -448,   431,  -448,  -448,    48,  -448,  -448,   432,
    -448,  -448,    96,   433,   444,  -448,  -448,  -448,  -448,  -448,
     116,   480,   434,   301,   251,    30,  -448,   435,  -448,   436,
    -448,  -448,  -448,   481,   251,   438,  -448,  -448
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -448,  -448,  -448,  -448,  -448,  -448,  -448,  -448,   -31,  -448,
    -448,   368,  -448,  -448,  -448,  -448,   439,  -448,   -70,  -448,
     244,  -448,   -71,  -448,  -448,  -448,  -448,   305,  -448,  -448,
    -448,  -448,  -448,  -448,   304,  -448,   376,   311,  -448,  -448,
     401,   404,   372,  -448,  -448,  -448,  -448,   238,  -448,   198,
    -448,    91,   143,  -276,  -448,  -443,  -448,  -270,  -336,  -448,
      84,  -448,   188,   192,   184,   186,   191,  -116,  -188,  -102,
     -99,  -302,  -264,  -448,  -448,  -448,  -447,  -448,  -448,  -448,
      92,   145,   440,  -448,  -448,  -448,  -448,   441,  -448,  -448,
    -448,  -448
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -235
static const yytype_int16 yytable[] =
{
     331,   463,    56,   328,   383,   453,   143,   108,   407,   469,
     376,   345,   130,    98,   338,    76,   341,   336,   337,   134,
      77,   136,   105,   131,   138,   378,   379,    98,   482,    99,
     479,   109,   110,   380,   381,   346,   186,   343,   326,   427,
     344,    37,   344,    99,    44,   430,   447,   187,   377,   270,
     188,    45,   271,   353,   354,   382,   326,    46,   175,   424,
     425,   426,   401,   341,   403,   404,    88,   270,    89,   182,
     271,   454,    47,   355,   356,   198,   409,   199,   405,   384,
     344,   377,    48,   377,   377,   377,   377,   377,   377,   377,
     377,   377,   377,   377,   377,   377,   377,   377,   377,   377,
     208,   457,   153,    54,   281,   282,   211,   149,   214,    49,
     428,   216,    52,   284,   467,   -71,   161,   456,   481,   445,
     457,   344,   281,   282,    50,    51,   286,   287,   288,   289,
      53,   284,   290,   291,    57,   456,   361,   362,   363,   457,
      58,   435,   436,   269,   286,   287,   288,   289,   437,    65,
     290,   291,    59,   446,   270,   344,   449,   271,   450,   272,
      24,   119,   120,   121,   122,   416,   417,   418,   419,   464,
     465,   231,    64,   462,   328,    67,   317,   435,   436,   451,
     472,   123,   344,   377,   273,   274,   275,   276,   277,   278,
     279,   280,    25,    26,    27,    68,    28,    29,   480,    30,
      31,   269,   475,   328,   476,   351,   352,    69,   486,   281,
     282,    70,   270,   357,   358,   271,   283,   272,   284,   249,
     359,   360,   285,   340,   391,   392,   250,   251,   252,   253,
     254,   286,   287,   288,   289,   414,   415,   290,   291,   448,
     344,    73,   273,   274,   275,   276,   277,   278,   279,   280,
      36,    40,    41,    42,    43,   420,   421,    72,    74,   269,
     422,   423,    75,    78,    79,    80,    81,   281,   282,    82,
     270,    83,    84,   271,   283,   272,   284,    85,    87,    90,
     285,   406,    91,    92,    93,    95,   104,    96,    97,   286,
     287,   288,   289,   105,   112,   290,   291,   326,   113,   114,
     273,   274,   275,   276,   277,   278,   279,   280,   270,   326,
     115,   271,   116,   117,   118,   129,   135,   137,   139,   143,
     270,   146,   148,   271,   151,   281,   282,   152,   155,   156,
     157,   158,   283,   166,   284,   177,   159,   167,   285,   160,
     178,   269,   168,   169,   171,   170,   179,   286,   287,   288,
     289,   181,   270,   290,   291,   271,   174,   176,   184,   185,
     190,   193,   192,   281,   282,   194,   197,   195,   196,   200,
     202,   204,   284,   429,   205,   281,   282,   206,   207,   209,
     213,   212,   217,   215,   284,   286,   287,   288,   289,   219,
     218,   290,   291,   220,   224,   161,   221,   286,   287,   288,
     289,   222,   227,   290,   291,   229,   223,   281,   282,   232,
     233,   238,   236,   234,     2,   235,   284,   237,     3,     4,
       5,     6,   239,   242,   243,   244,   245,   248,   246,   286,
     287,   288,   289,   256,   260,   290,   291,     7,     8,     9,
     259,    10,    11,   264,   262,   257,   258,   320,    12,    13,
     321,    14,    15,    16,   263,   265,   266,    17,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   267,   268,
    -234,   318,   319,   324,   323,   325,   332,   329,   330,   333,
     347,   334,   335,   342,   390,   348,   388,   349,   389,   374,
     350,   395,   396,   398,    18,   344,    19,   397,   402,   432,
     459,   474,   477,   485,   226,   434,   438,   439,   442,   444,
     443,   460,   183,   455,   473,   478,   468,   180,   471,   241,
     484,   483,   487,   339,   240,   452,   172,   433,   133,   173,
     399,   466,   411,   408,   461,   412,     0,   441,   203,   410,
       0,   413,   150,     0,     0,     0,     0,   154
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-448)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     276,   444,    33,   273,     8,    19,    25,     8,   344,   456,
     312,    69,     8,     8,   284,    81,   292,   281,   282,    89,
      86,    91,     8,    19,    95,    74,    75,     8,   475,    24,
     473,    32,    33,    82,    83,    93,     8,    81,     8,   375,
      86,    83,    86,    24,     8,   381,    92,    19,   312,    19,
      22,     8,    22,    70,    71,   104,     8,    36,   129,   361,
     362,   363,   332,   339,   334,   335,    84,    19,    86,    88,
      22,    85,     8,    90,    91,    84,   346,    86,    84,    83,
      86,   345,     8,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     171,   437,    88,    90,    74,    75,   176,    88,   179,     8,
     380,   182,     8,    83,   450,     8,     9,    87,    88,    84,
     456,    86,    74,    75,    78,    79,    96,    97,    98,    99,
       8,    83,   102,   103,     8,    87,    99,   100,   101,   475,
       8,    82,    83,     8,    96,    97,    98,    99,    89,    83,
     102,   103,     8,    84,    19,    86,    84,    22,    86,    24,
       8,    11,    12,    13,    14,   353,   354,   355,   356,   445,
     446,   202,     8,   443,   444,    19,   247,    82,    83,    84,
      84,    31,    86,   447,    49,    50,    51,    52,    53,    54,
      55,    56,    40,    41,    42,     8,    44,    45,   474,    47,
      48,     8,    86,   473,    88,    76,    77,     8,   484,    74,
      75,    87,    19,    72,    73,    22,    81,    24,    83,     8,
      97,    98,    87,    88,     9,    10,    15,    16,    17,    18,
      19,    96,    97,    98,    99,   351,   352,   102,   103,    85,
      86,    37,    49,    50,    51,    52,    53,    54,    55,    56,
       6,     7,     8,     9,    10,   357,   358,    87,    89,     8,
     359,   360,    83,    83,    83,     8,    81,    74,    75,     8,
      19,     8,     8,    22,    81,    24,    83,    87,    89,    84,
      87,    88,    86,    81,    19,    19,    81,    87,    87,    96,
      97,    98,    99,     8,    19,   102,   103,     8,    19,    19,
      49,    50,    51,    52,    53,    54,    55,    56,    19,     8,
      83,    22,    91,    81,    81,    81,     8,    86,    26,    25,
      19,    82,    19,    22,    89,    74,    75,     8,    83,    83,
      81,    84,    81,    83,    83,    19,    84,    83,    87,    86,
       8,     8,    83,    83,    88,    83,    88,    96,    97,    98,
      99,     8,    19,   102,   103,    22,    89,    86,    19,    19,
      92,     8,    81,    74,    75,     8,    19,    81,    85,    82,
       8,     8,    83,    84,     8,    74,    75,     8,    19,     8,
      87,    86,    85,    87,    83,    96,    97,    98,    99,     8,
      81,   102,   103,    81,    92,     9,    86,    96,    97,    98,
      99,    86,    19,   102,   103,    92,    86,    74,    75,    84,
      84,    81,    84,    86,     0,    86,    83,    83,     4,     5,
       6,     7,    19,     8,    29,    19,     8,    85,    87,    96,
      97,    98,    99,     8,     8,   102,   103,    23,    24,    25,
      19,    27,    28,    88,    84,    81,    81,    86,    34,    35,
      92,    37,    38,    39,    84,    88,    83,    43,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    84,    84,
       8,    84,    83,    85,    84,    19,    83,    81,    81,     8,
      68,    83,    83,    81,    19,    94,    81,    95,    22,    89,
      96,    84,    19,    56,    80,    86,    82,    81,    81,     8,
      22,    57,    22,    22,   199,    86,    86,    84,    86,    81,
      83,    81,   144,    84,    81,    81,    85,   141,    86,   215,
      84,    86,    84,   285,   213,   434,   125,   384,    89,   125,
     332,   447,   348,   345,   442,   349,    -1,   392,   166,   347,
      -1,   350,   101,    -1,    -1,    -1,    -1,   107
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   106,     0,     4,     5,     6,     7,    23,    24,    25,
      27,    28,    34,    35,    37,    38,    39,    43,    80,    82,
     107,   108,   110,   117,     8,    40,    41,    42,    44,    45,
      47,    48,   111,   112,   126,   125,   125,    83,   118,   119,
     125,   125,   125,   125,     8,     8,    36,     8,     8,     8,
      78,    79,     8,     8,    90,   113,   113,     8,     8,     8,
     120,   121,   122,   123,     8,    83,   114,    19,     8,     8,
      87,   190,    87,    37,    89,    83,    81,    86,    83,    83,
       8,    81,     8,     8,     8,    87,   129,    89,    84,    86,
      84,    86,    81,    19,   127,    19,    87,    87,     8,    24,
     109,   191,   192,   193,    81,     8,   187,   189,     8,    32,
      33,   147,    19,    19,    19,    83,    91,    81,    81,    11,
      12,    13,    14,    31,   142,   143,   145,   146,   148,    81,
       8,    19,   124,   121,   123,     8,   123,    86,   127,    26,
     139,   140,   141,    25,   115,   116,    82,   194,    19,    88,
     192,    89,     8,    88,   187,    83,    83,    81,    84,    84,
      86,     9,   131,   132,   135,   136,    83,    83,    83,    83,
      83,    88,   145,   146,    89,   127,    86,    19,     8,    88,
     141,     8,    88,   116,    19,    19,     8,    19,    22,   195,
      92,   188,    81,     8,     8,    81,    85,    19,    84,    86,
      82,   133,     8,   147,     8,     8,     8,    19,   127,     8,
     149,   123,    86,    87,   127,    87,   127,    85,    81,     8,
      81,    86,    86,    86,    92,   130,   132,    19,   134,    92,
     138,   113,    84,    84,    86,    86,    84,    83,    81,    19,
     142,   139,     8,    29,    19,     8,    87,   128,    85,     8,
      15,    16,    17,    18,    19,   137,     8,    81,    81,    19,
       8,   144,    84,    84,    88,    88,    83,    84,    84,     8,
      19,    22,    24,    49,    50,    51,    52,    53,    54,    55,
      56,    74,    75,    81,    83,    87,    96,    97,    98,    99,
     102,   103,   152,   153,   154,   158,   161,   162,   163,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   183,   184,   196,   127,    84,    83,
      86,    92,   150,    84,    85,    19,     8,   160,   162,    81,
      81,   158,    83,     8,    83,    83,   177,   177,   162,   152,
      88,   158,    81,    81,    86,    69,    93,    68,    94,    95,
      96,    76,    77,    70,    71,    90,    91,    72,    73,    97,
      98,    99,   100,   101,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    89,   164,   176,   177,    74,    75,
      82,    83,   104,     8,    83,   155,   156,   157,    81,    22,
      19,     9,    10,   151,   185,    84,    19,    81,    56,   154,
     159,   162,    81,   162,   162,    84,    88,   163,   167,   162,
     168,   169,   170,   171,   172,   172,   173,   173,   173,   173,
     174,   174,   175,   175,   176,   176,   176,   163,   162,    84,
     163,   180,     8,   157,    86,    82,    83,    89,    86,    84,
     186,   186,    86,    83,    81,    84,    84,    92,    85,    84,
      86,    84,   156,    19,    85,    84,    87,   163,   181,    22,
      81,   185,   162,   160,   158,   158,   165,   163,    85,   181,
     182,    86,    84,    81,    57,    86,    88,    22,    81,   160,
     158,    88,   181,    86,    84,    22,   158,    84
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
#line 151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 156 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 163 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 166 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
		decl<<layout<<"uniform "<<GetEquivalentGLTextureType(texture_type,template_type)<<" "<<texture_name<<";\n";
		gEffect->m_sharedCode<<decl.str();
		if(compute_only)
			gEffect->m_sharedCode<<"#endif\n";
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 196 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 212 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 218 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 222 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 226 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="layout(local_size_x=%1,local_size_y=%2,local_size_z=%3) in;";
		stringReplaceAll(currentCsLayout,"%1",(yyvsp[(4) - (10)]).strs[0]);
		stringReplaceAll(currentCsLayout,"%2",(yyvsp[(6) - (10)]).strs[0]);
		stringReplaceAll(currentCsLayout,"%3",(yyvsp[(8) - (10)]).strs[0]);
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 233 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 241 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 253 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 259 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 262 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 19:
/* Line 1792 of yacc.c  */
#line 280 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 20:
/* Line 1792 of yacc.c  */
#line 320 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 21:
/* Line 1792 of yacc.c  */
#line 330 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 22:
/* Line 1792 of yacc.c  */
#line 347 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout="";
		currentCsLayout+=(yyvsp[(1) - (4)]).strs[0];
		currentCsLayout+=(yyvsp[(3) - (4)]).strs[0];
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 354 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
		delete (yyvsp[(5) - (9)]).vars;
		
		gEffect->m_sharedCode<<"#line "<<(glfxget_lineno()+(last_linenumber-global_linenumber))<<" "<<current_filenumber<<endl;
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 373 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 378 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 381 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string groupName=(yyvsp[(3) - (7)]).strs[0];
		if(gEffect->m_techniqueGroups.find(groupName)==gEffect->m_techniqueGroups.end())
			gEffect->m_techniqueGroups[groupName]=new TechniqueGroup;
		*(gEffect->m_techniqueGroups[groupName])=buildTechniqueGroup;
		buildTechniqueGroup.m_techniques.clear();
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 389 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 396 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 402 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 407 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 413 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 419 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 424 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 429 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 40:
/* Line 1792 of yacc.c  */
#line 440 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 444 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 447 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 451 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 44:
/* Line 1792 of yacc.c  */
#line 461 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 465 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 470 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 474 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 478 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 482 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	   }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 486 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 491 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		   }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 496 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 500 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 504 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 510 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
    gLexPassthrough=false;
}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 516 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 520 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 527 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 533 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 536 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
 }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 539 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 62:
/* Line 1792 of yacc.c  */
#line 551 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 63:
/* Line 1792 of yacc.c  */
#line 562 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 567 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 65:
/* Line 1792 of yacc.c  */
#line 599 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 604 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 609 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
			}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 614 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
			}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 619 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (4)]).strs[0];
		string type		=(yyvsp[(2) - (4)]).strs[0];
		string template_=(yyvsp[(3) - (4)]).strs[0];
		if(template_.length())
			type+=string("<")+template_+string(">");
		string id		=(yyvsp[(4) - (4)]).strs[0];
		(yyval).strs[0]		= storage	;
		(yyval).strs[1]		= type		;
		(yyval).strs[2]		= id		;
	}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 631 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 635 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 639 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 644 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 649 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 654 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 659 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 664 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 670 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 675 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 681 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 688 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 82:
/* Line 1792 of yacc.c  */
#line 700 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 83:
/* Line 1792 of yacc.c  */
#line 714 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable = (yyvsp[(1) - (5)]).boolean;
	(yyval).prog = (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0] = (yyvsp[(2) - (5)]).strs[0];
	(yyval).prog->passState=buildPassState;
	buildPassState=PassState();
}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 723 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders));
    delete (yyvsp[(1) - (1)]).shaders;
}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 729 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 86:
/* Line 1792 of yacc.c  */
#line 739 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 87:
/* Line 1792 of yacc.c  */
#line 752 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 760 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 768 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 777 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 781 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 787 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 795 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 94:
/* Line 1792 of yacc.c  */
#line 846 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 95:
/* Line 1792 of yacc.c  */
#line 913 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string compiledShaderName	=(yyvsp[(1) - (1)]).strs[0];
			(yyval).strs[0]					=compiledShaderName;
			(yyval).num						=0;
			(yyval).lineno					=(yyvsp[(1) - (1)]).lineno;
		}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 920 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 97:
/* Line 1792 of yacc.c  */
#line 939 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 98:
/* Line 1792 of yacc.c  */
#line 973 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 984 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 990 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 994 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 998 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1003 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1008 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1012 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1021 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1027 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1032 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 109:
/* Line 1792 of yacc.c  */
#line 1045 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			stringReplaceAll(init_declarator_list,type_spec+type_spec,type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1054 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1058 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1062 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1066 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 114:
/* Line 1792 of yacc.c  */
#line 1104 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1108 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1112 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1117 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1121 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1125 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1130 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1134 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1138 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
				}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1143 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1147 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1155 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+(yyvsp[(7) - (7)]).strs[0];
				}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1159 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
				}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1164 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1168 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1172 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1176 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 132:
/* Line 1792 of yacc.c  */
#line 1191 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1196 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1200 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1204 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1207 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1211 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1216 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1222 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1226 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1230 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1234 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1238 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1251 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1255 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1259 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
	}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1264 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1268 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1272 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1276 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1280 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1284 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1288 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 163:
/* Line 1792 of yacc.c  */
#line 1292 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 164:
/* Line 1792 of yacc.c  */
#line 1296 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 165:
/* Line 1792 of yacc.c  */
#line 1300 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 166:
/* Line 1792 of yacc.c  */
#line 1305 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1309 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1313 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1317 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1321 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1325 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1329 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1333 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1337 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1341 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1345 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1349 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1353 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1357 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1361 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1365 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1369 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1373 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1377 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1381 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1385 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1389 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1393 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1397 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1401 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1405 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1409 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
					}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1413 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1417 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1423 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1427 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1431 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1435 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1439 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1444 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1451 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1458 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1465 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1472 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1476 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1480 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1484 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1488 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1492 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1500 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1508 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1512 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 218:
/* Line 1792 of yacc.c  */
#line 1524 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1528 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1532 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1537 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1541 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1544 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1548 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1553 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1557 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 227:
/* Line 1792 of yacc.c  */
#line 1666 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1671 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1677 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1682 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1691 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1696 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1701 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 4379 "src/glfxLALRParser.cpp"
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
#line 1704 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
