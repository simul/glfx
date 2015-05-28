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
	ComputeLayout currentCsLayout;
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
	string GetTypeOfParameter(const vector<glfxstype::variable> &parameters,const string &name)
	{
		for(vector<glfxstype::variable>::const_iterator j=parameters.begin();j!=parameters.end();j++)
		{
			if(name==j->identifier)
				return j->type;
		}
		return "";
	}
	int GetIndexOfParameter(const vector<glfxstype::variable> &parameters,const string &name)
	{
		for(int i=0;i<parameters.size();i++)
		{
			if(name==parameters[i].identifier)
				return i;
		}
		return -1;
	}
	string getGLInputSemantic(int s);
	map<std::string,CompilableShader*> compilableShaders;
	map<std::string,Function*> functions;
	map<string,DeclaredTexture> declaredTextures;
	map<string,DeclaredTexture> additionalTextureDeclarations;
	
	void DeclareTextureSampler(const TextureSampler *ts)
	{
		auto i=additionalTextureDeclarations.find(ts->textureSamplerName());
		if(i!=additionalTextureDeclarations.end())
			return;

		string tsname		=ts->textureSamplerName();
		string texture_name=ts->textureName;
		if(declaredTextures.find(texture_name)!=declaredTextures.end())
		{
			string sampler_type=declaredTextures[texture_name].type;
			//str<<"uniform "<<sampler_type<<" "<<tsname<<";\n";
			additionalTextureDeclarations[tsname].type=sampler_type;
			// We know that this texture-sampler combo will be used in this shader.
		}
		else
			errSem(string("Can't find texture declaration for ")+texture_name);
	}
	Function buildFunction;
	TextureSampler *AddTextureSampler(string textureName,string samplerStateName)
	{
		auto i=buildFunction.textureSamplers.find((textureName+"_")+samplerStateName);
		if(i!=buildFunction.textureSamplers.end())
		{
			return i->second;
		}
		TextureSampler *ts=new TextureSampler;
		ts->textureName			=textureName;
		ts->samplerStateName	=samplerStateName;
		ts->global				=false;
		buildFunction.textureSamplers[ts->textureSamplerName()]=(ts);
		buildFunction.textureSamplersByTexture[textureName].insert(ts);
		buildFunction.textureSamplersBySampler[ts->samplerStateName].insert(ts);
		return ts;
	}
	string ComputeLayout::text()
	{
		string tt=stringFormat("layout(local_size_x=%d,local_size_y=%d,local_size_z=%d) in;",x,y,z);
		return tt;
	}
	string ShaderTypeToString(ShaderType s)
	{
		switch(s)
		{
		case VERTEX_SHADER:
		return "Vertex";
		case TESSELATION_CONTROL_SHADER:		//= Hull shader
		return "Hull (TC)";
		case TESSELATION_EVALUATION_SHADER:	//= Domain Shader
		return "Domain (TE)";
		case GEOMETRY_SHADER:
		return "Geometry";
		case FRAGMENT_SHADER:
		return "Pixel (Fragment)";
		case COMPUTE_SHADER:
		return "Compute";
		default:
		return "Unknown";
		}
	};

/* Line 371 of yacc.c  */
#line 292 "src/glfxLALRParser.cpp"

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
     SAMPLE = 265,
     SAMPLE_LOD = 266,
     STORAGEQ = 267,
     GL_FRAGDEPTH = 268,
     SHADER_COMMAND = 269,
     SET_RASTERIZER_COMMAND = 270,
     SET_DEPTH_COMMAND = 271,
     SET_BLEND_COMMAND = 272,
     SV_DISPATCHTHREADID = 273,
     SV_GROUPTHREADID = 274,
     SV_GROUPID = 275,
     SV_VERTEXID = 276,
     NUM = 277,
     INCLUDE = 278,
     SAMPLER = 279,
     FLOAT = 280,
     LAYOUT = 281,
     LINE = 282,
     TECHNIQUE = 283,
     PASS = 284,
     GROUP = 285,
     RENDER_STATE_DECL = 286,
     QUOTED_STRING = 287,
     SHADER_LINE = 288,
     SHADER_TYPE = 289,
     COMPILE_SHADER = 290,
     CONSTRUCT_GS_WITH_SO = 291,
     STRUCT = 292,
     PRAGMA = 293,
     DEFINE = 294,
     UNDEF = 295,
     MACRO_DEFINITION = 296,
     EOL = 297,
     DECL_SHADER = 298,
     PROFILE = 299,
     WARNING = 300,
     DEF = 301,
     MESSAGE = 302,
     PACK_MATRIX = 303,
     RW_TEXTURE2D = 304,
     RW_TEXTURE3D = 305,
     RW_TEXTURE2DARRAY = 306,
     RW_TEXTURE3D_FLOAT4 = 307,
     TEXTURE2DMS = 308,
     TEXTURE2D = 309,
     TEXTURE3D = 310,
     IMAGE3D = 311,
     KNOWN_TYPE = 312,
     STRUCTUREDBUFFER = 313,
     RW_STRUCTUREDBUFFER = 314,
     RETURN = 315,
     BREAK = 316,
     CONTINUE = 317,
     DO = 318,
     FOR = 319,
     GOTO = 320,
     IF = 321,
     WHILE = 322,
     ELSE = 323,
     TIMES_EQUALS = 324,
     OVER_EQUALS = 325,
     PERCENT_EQUALS = 326,
     PLUS_EQUALS = 327,
     MINUS_EQUALS = 328,
     LEFT_SHIFT_EQUALS = 329,
     RIGHT_SHIFT_EQUALS = 330,
     AND_EQUALS = 331,
     XOR_EQUALS = 332,
     OR_EQUALS = 333,
     AND = 334,
     OR = 335,
     LESS_EQ = 336,
     GRTR_EQ = 337,
     LEFT_SHIFT = 338,
     RIGHT_SHIFT = 339,
     PLUS_PLUS = 340,
     MINUS_MINUS = 341,
     EQ_EQ = 342,
     NOT_EQ = 343,
     SA_MAXVERTEXCOUNT = 344,
     SA_NUMTHREADS = 345,
     SHADER_PROFILE = 346
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
#line 449 "src/glfxLALRParser.cpp"

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
#define YYLAST   620

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  116
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  98
/* YYNRULES -- Number of rules.  */
#define YYNRULES  249
/* YYNRULES -- Number of states.  */
#define YYNSTATES  528

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   346

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   114,     2,     2,     2,   112,   107,     2,
      93,    95,   110,   108,    98,   109,   115,   111,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    94,    92,
     102,    99,   103,   104,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    96,     2,    97,   106,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   100,   105,   101,   113,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    26,    32,
      38,    43,    50,    61,    66,    69,    73,    77,    81,    85,
      90,    95,   102,   108,   113,   120,   129,   139,   147,   149,
     157,   163,   167,   170,   172,   174,   176,   178,   180,   182,
     184,   186,   188,   192,   193,   201,   203,   205,   208,   210,
     216,   224,   228,   232,   236,   238,   240,   242,   248,   252,
     254,   256,   257,   258,   259,   260,   264,   265,   268,   269,
     273,   276,   278,   285,   287,   288,   292,   294,   295,   299,
     303,   304,   306,   307,   312,   314,   315,   317,   319,   321,
     323,   326,   329,   332,   333,   335,   338,   340,   346,   348,
     351,   353,   356,   358,   369,   375,   383,   393,   398,   404,
     406,   413,   422,   427,   432,   433,   436,   437,   441,   443,
     446,   448,   449,   453,   456,   458,   462,   464,   468,   470,
     474,   479,   483,   487,   490,   492,   495,   497,   503,   511,
     517,   525,   535,   539,   542,   545,   549,   551,   553,   555,
     556,   558,   559,   563,   565,   569,   571,   575,   577,   579,
     581,   583,   585,   587,   589,   591,   593,   595,   597,   599,
     605,   607,   611,   613,   617,   619,   623,   625,   629,   631,
     635,   637,   641,   645,   647,   651,   655,   659,   663,   665,
     669,   673,   675,   679,   683,   685,   689,   693,   697,   699,
     701,   704,   707,   710,   712,   714,   716,   718,   720,   722,
     724,   726,   730,   732,   737,   744,   749,   753,   757,   760,
     763,   767,   769,   771,   775,   780,   782,   786,   788,   790,
     794,   796,   798,   801,   804,   805,   808,   809,   813,   814,
     817,   819,   824,   826,   829,   833,   834,   836,   838,   840
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     117,     0,    -1,   117,   118,    -1,    -1,     8,   137,     9,
     142,    92,   140,    -1,    42,    -1,   119,    -1,    38,    45,
      93,   126,    94,    22,    95,    -1,     4,   122,   124,     9,
      92,    -1,     4,   123,   124,     9,    92,    -1,     4,     9,
       9,    92,    -1,    96,    89,    93,    22,    95,    97,    -1,
      96,    90,    93,    22,    98,    22,    98,    22,    95,    97,
      -1,    26,   130,     9,    92,    -1,    26,   131,    -1,    52,
       9,    92,    -1,    52,     9,    98,    -1,    39,    41,    42,
      -1,    40,     9,    42,    -1,    37,     9,   144,    92,    -1,
      31,     9,   207,    92,    -1,    44,    91,    93,    22,    95,
      92,    -1,    43,     9,    99,   164,    92,    -1,    26,   137,
     125,   140,    -1,     6,     9,   138,   144,    92,   140,    -1,
       9,     9,    93,   148,    95,   139,   141,   140,    -1,   121,
       9,     9,    93,   148,    95,   143,   141,   140,    -1,     7,
     137,     9,   100,   159,   101,   140,    -1,   129,    -1,    30,
     137,     9,   100,   127,   101,   140,    -1,    27,   137,    22,
      22,   140,    -1,    27,    22,    22,    -1,     5,   138,    -1,
      54,    -1,    55,    -1,    53,    -1,    56,    -1,    49,    -1,
      50,    -1,    51,    -1,    58,    -1,    59,    -1,   102,     9,
     103,    -1,    -1,    93,    22,    98,    22,    98,    22,    95,
      -1,     9,    -1,    22,    -1,   127,   128,    -1,   128,    -1,
      28,     9,   100,   156,   101,    -1,    28,   137,     9,   100,
     156,   101,   140,    -1,    93,   134,    95,    -1,    93,   132,
      95,    -1,   132,    98,   133,    -1,   133,    -1,   135,    -1,
       9,    -1,   135,    98,   135,    98,   135,    -1,     9,    99,
     136,    -1,     9,    -1,    22,    -1,    -1,    -1,    -1,    -1,
     100,   169,   101,    -1,    -1,    94,     9,    -1,    -1,   100,
     145,   101,    -1,   145,   146,    -1,   146,    -1,   147,     9,
       9,   150,   206,    92,    -1,     4,    -1,    -1,   148,    98,
     149,    -1,   149,    -1,    -1,   152,   150,   155,    -1,    96,
     151,    97,    -1,    -1,    22,    -1,    -1,   153,     9,   124,
       9,    -1,    12,    -1,    -1,    18,    -1,    20,    -1,    19,
      -1,    21,    -1,    94,    22,    -1,    94,   154,    -1,    94,
       9,    -1,    -1,   157,    -1,   157,   158,    -1,   158,    -1,
      29,     9,   100,   159,   101,    -1,   160,    -1,   160,   163,
      -1,   163,    -1,   160,   162,    -1,   162,    -1,     9,    93,
      25,    98,    25,    98,    25,    98,    25,    95,    -1,    15,
      93,     9,    95,    92,    -1,    16,    93,     9,    98,    22,
      95,    92,    -1,    17,    93,     9,    98,   161,    98,    22,
      95,    92,    -1,   165,    99,   166,    92,    -1,    14,    93,
     164,    95,    92,    -1,     9,    -1,    36,    93,     9,    98,
      32,    95,    -1,    35,    93,    91,    98,     9,    93,    95,
      95,    -1,    34,    93,    22,    95,    -1,     9,    93,    95,
     167,    -1,    -1,    94,   168,    -1,    -1,   168,    98,   204,
      -1,   204,    -1,   169,   175,    -1,   175,    -1,    -1,    27,
      22,    22,    -1,   213,   172,    -1,   173,    -1,   172,    98,
     173,    -1,   174,    -1,   174,    99,   200,    -1,     9,    -1,
      93,   174,    95,    -1,   174,    96,    22,    97,    -1,   174,
      96,    97,    -1,   174,    93,    95,    -1,   179,    92,    -1,
      92,    -1,   171,    92,    -1,   178,    -1,    66,    93,   179,
      95,   175,    -1,    66,    93,   179,    95,   175,    68,   175,
      -1,    67,    93,   179,    95,   175,    -1,    63,   175,    67,
      93,   179,    95,    92,    -1,    64,    93,   176,    92,   177,
      92,   177,    95,   175,    -1,    65,     9,    92,    -1,    62,
      92,    -1,    61,    92,    -1,    60,   177,    92,    -1,   170,
      -1,   179,    -1,   171,    -1,    -1,   179,    -1,    -1,   100,
     169,   101,    -1,   180,    -1,   179,    98,   180,    -1,   182,
      -1,   194,   181,   180,    -1,    99,    -1,    69,    -1,    70,
      -1,    71,    -1,    72,    -1,    73,    -1,    74,    -1,    75,
      -1,    76,    -1,    77,    -1,    78,    -1,   183,    -1,   183,
     104,   179,    94,   182,    -1,   184,    -1,   183,    80,   184,
      -1,   185,    -1,   184,    79,   185,    -1,   186,    -1,   185,
     105,   186,    -1,   187,    -1,   186,   106,   187,    -1,   188,
      -1,   187,   107,   188,    -1,   189,    -1,   188,    87,   189,
      -1,   188,    88,   189,    -1,   190,    -1,   189,   102,   190,
      -1,   189,   103,   190,    -1,   189,    81,   190,    -1,   189,
      82,   190,    -1,   191,    -1,   190,    83,   191,    -1,   190,
      84,   191,    -1,   192,    -1,   191,   108,   192,    -1,   191,
     109,   192,    -1,   193,    -1,   192,   110,   193,    -1,   192,
     111,   193,    -1,   192,   112,   193,    -1,   194,    -1,   198,
      -1,    85,   194,    -1,    86,   194,    -1,   195,   193,    -1,
     107,    -1,   110,    -1,   108,    -1,   109,    -1,   113,    -1,
     114,    -1,    10,    -1,    11,    -1,   198,   115,   196,    -1,
     202,    -1,   198,    96,   179,    97,    -1,   197,    93,   180,
      98,   199,    95,    -1,   198,    93,   199,    95,    -1,   198,
      93,    95,    -1,   198,   115,     9,    -1,   198,    85,    -1,
     198,    86,    -1,   199,    98,   180,    -1,   180,    -1,   180,
      -1,   100,   201,   101,    -1,   100,   201,    98,   101,    -1,
     200,    -1,   201,    98,   200,    -1,     9,    -1,   203,    -1,
      93,   179,    95,    -1,    22,    -1,    25,    -1,    12,   205,
      -1,    13,   205,    -1,    -1,    94,     9,    -1,    -1,   100,
     208,   101,    -1,    -1,   208,   209,    -1,   209,    -1,   210,
      99,   212,    92,    -1,   120,    -1,     9,   211,    -1,    96,
      22,    97,    -1,    -1,     9,    -1,    22,    -1,    25,    -1,
       9,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   236,   236,   237,   241,   245,   248,   251,   254,   286,
     302,   308,   312,   318,   321,   327,   333,   339,   343,   349,
     366,   406,   416,   435,   438,   453,   567,   601,   606,   609,
     617,   624,   630,   635,   635,   635,   635,   635,   635,   635,
     641,   641,   647,   653,   657,   671,   674,   677,   681,   684,
     688,   698,   702,   707,   711,   715,   719,   723,   731,   737,
     741,   746,   753,   760,   767,   771,   778,   783,   788,   791,
     796,   802,   807,   826,   831,   834,   847,   861,   866,   899,
     905,   909,   915,   919,   933,   938,   941,   946,   951,   956,
     961,   966,   972,   978,   983,   990,  1002,  1016,  1023,  1030,
    1040,  1053,  1061,  1069,  1078,  1082,  1088,  1096,  1101,  1175,
    1187,  1207,  1243,  1254,  1261,  1264,  1269,  1273,  1278,  1282,
    1291,  1298,  1302,  1315,  1324,  1328,  1332,  1336,  1374,  1378,
    1382,  1387,  1391,  1395,  1400,  1404,  1408,  1413,  1417,  1428,
    1432,  1436,  1441,  1445,  1449,  1453,  1468,  1473,  1477,  1482,
    1484,  1489,  1493,  1499,  1503,  1507,  1511,  1515,  1519,  1520,
    1521,  1522,  1523,  1524,  1525,  1526,  1527,  1528,  1532,  1536,
    1541,  1545,  1549,  1553,  1557,  1561,  1565,  1569,  1573,  1577,
    1582,  1586,  1590,  1594,  1598,  1602,  1606,  1610,  1614,  1618,
    1622,  1626,  1630,  1634,  1638,  1642,  1646,  1650,  1654,  1658,
    1662,  1666,  1670,  1674,  1674,  1674,  1674,  1674,  1674,  1678,
    1682,  1686,  1697,  1702,  1707,  1744,  1809,  1815,  1822,  1826,
    1830,  1838,  1846,  1851,  1858,  1865,  1872,  1879,  1883,  1887,
    1891,  1895,  1899,  1907,  1916,  1919,  1924,  1927,  1931,  1934,
    1939,  1943,  2052,  2057,  2063,  2069,  2072,  2077,  2082,  2087
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHITESPACE", "UNIFORM", "SHADER",
  "CONSTANT_BUFFER", "PROGRAM", "INTERFACE", "IDENTIFIER", "SAMPLE",
  "SAMPLE_LOD", "STORAGEQ", "GL_FRAGDEPTH", "SHADER_COMMAND",
  "SET_RASTERIZER_COMMAND", "SET_DEPTH_COMMAND", "SET_BLEND_COMMAND",
  "SV_DISPATCHTHREADID", "SV_GROUPTHREADID", "SV_GROUPID", "SV_VERTEXID",
  "NUM", "INCLUDE", "SAMPLER", "FLOAT", "LAYOUT", "LINE", "TECHNIQUE",
  "PASS", "GROUP", "RENDER_STATE_DECL", "QUOTED_STRING", "SHADER_LINE",
  "SHADER_TYPE", "COMPILE_SHADER", "CONSTRUCT_GS_WITH_SO", "STRUCT",
  "PRAGMA", "DEFINE", "UNDEF", "MACRO_DEFINITION", "EOL", "DECL_SHADER",
  "PROFILE", "WARNING", "DEF", "MESSAGE", "PACK_MATRIX", "RW_TEXTURE2D",
  "RW_TEXTURE3D", "RW_TEXTURE2DARRAY", "RW_TEXTURE3D_FLOAT4",
  "TEXTURE2DMS", "TEXTURE2D", "TEXTURE3D", "IMAGE3D", "KNOWN_TYPE",
  "STRUCTUREDBUFFER", "RW_STRUCTUREDBUFFER", "RETURN", "BREAK", "CONTINUE",
  "DO", "FOR", "GOTO", "IF", "WHILE", "ELSE", "TIMES_EQUALS",
  "OVER_EQUALS", "PERCENT_EQUALS", "PLUS_EQUALS", "MINUS_EQUALS",
  "LEFT_SHIFT_EQUALS", "RIGHT_SHIFT_EQUALS", "AND_EQUALS", "XOR_EQUALS",
  "OR_EQUALS", "AND", "OR", "LESS_EQ", "GRTR_EQ", "LEFT_SHIFT",
  "RIGHT_SHIFT", "PLUS_PLUS", "MINUS_MINUS", "EQ_EQ", "NOT_EQ",
  "SA_MAXVERTEXCOUNT", "SA_NUMTHREADS", "SHADER_PROFILE", "';'", "'('",
  "':'", "')'", "'['", "']'", "','", "'='", "'{'", "'}'", "'<'", "'>'",
  "'?'", "'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'",
  "'!'", "'.'", "$accept", "prog", "tok", "line_statement",
  "ignore_line_statement", "shader_and_layout", "texture_type",
  "buffer_type", "optional_templateval", "layout_params",
  "warning-specifier", "technique_decls", "group_technique_decl",
  "technique_decl", "cs_layout_spec", "normal_layout_spec", "tx_layout",
  "layout_s", "cs_layout", "layout_el", "layout_def", "lex_fx",
  "shader_fx", "function_fx", "lex_passthrough", "function_content",
  "read_block", "optional_return_semantic", "struct_definition",
  "struct_member_list", "struct_memb", "optional_uniform",
  "param_declaration_list", "param_declaration", "opt_sq", "opt_num",
  "param", "opt_storage", "input_semantic", "location", "tech_def",
  "pass_list", "pass_def", "prog_def", "shaders_list", "vec4", "shader_fn",
  "shader_def", "shader_compile", "shader_lvalue", "shader_rvalue",
  "shader_layout", "shader_layout_list", "statement_list",
  "line_statement_in_shader", "declaration", "init_declarator_list",
  "init_declarator", "declarator", "statement", "for_init_statement",
  "optional_expression", "compound_statement", "expression",
  "assignment_exp", "assignment_operator", "conditional_exp",
  "logical_or_exp", "logical_and_exp", "inclusive_or_exp",
  "exclusive_or_exp", "and_exp", "equality_exp", "relational_exp",
  "shift_expression", "additive_exp", "mult_exp", "cast_exp", "unary_exp",
  "unary_operator", "sampling_command", "sampling_exp", "postfix_exp",
  "argument_exp_list", "initializer", "initializer_list", "primary_exp",
  "const", "layout", "read_parenthesis", "optional_semantic",
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,    59,    40,    58,    41,    91,    93,    44,    61,
     123,   125,    60,    62,    63,   124,    94,    38,    43,    45,
      42,    47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   116,   117,   117,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     119,   120,   121,   122,   122,   122,   122,   122,   122,   122,
     123,   123,   124,   124,   125,   126,   126,   127,   127,   128,
     129,   130,   131,   132,   132,   133,   133,   134,   135,   136,
     136,   137,   138,   139,   140,   141,   142,   143,   143,   144,
     145,   145,   146,   147,   147,   148,   148,   148,   149,   150,
     150,   151,   151,   152,   153,   153,   154,   154,   154,   154,
     155,   155,   155,   155,   156,   157,   157,   158,   159,   160,
     160,   160,   160,   161,   162,   162,   162,   163,   163,   164,
     164,   164,   165,   166,   166,   167,   167,   168,   168,   169,
     169,   169,   170,   171,   172,   172,   173,   173,   174,   174,
     174,   174,   174,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   176,   176,   176,
     177,   177,   178,   179,   179,   180,   180,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   182,   182,
     183,   183,   184,   184,   185,   185,   186,   186,   187,   187,
     188,   188,   188,   189,   189,   189,   189,   189,   190,   190,
     190,   191,   191,   191,   192,   192,   192,   192,   193,   194,
     194,   194,   194,   195,   195,   195,   195,   195,   195,   196,
     196,   197,   198,   198,   198,   198,   198,   198,   198,   198,
     199,   199,   200,   200,   200,   201,   201,   202,   202,   202,
     203,   203,   204,   204,   205,   206,   206,   207,   207,   208,
     208,   209,   209,   210,   211,   211,   212,   212,   212,   213
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     7,     5,     5,
       4,     6,    10,     4,     2,     3,     3,     3,     3,     4,
       4,     6,     5,     4,     6,     8,     9,     7,     1,     7,
       5,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     7,     1,     1,     2,     1,     5,
       7,     3,     3,     3,     1,     1,     1,     5,     3,     1,
       1,     0,     0,     0,     0,     3,     0,     2,     0,     3,
       2,     1,     6,     1,     0,     3,     1,     0,     3,     3,
       0,     1,     0,     4,     1,     0,     1,     1,     1,     1,
       2,     2,     2,     0,     1,     2,     1,     5,     1,     2,
       1,     2,     1,    10,     5,     7,     9,     4,     5,     1,
       6,     8,     4,     4,     0,     2,     0,     3,     1,     2,
       1,     0,     3,     2,     1,     3,     1,     3,     1,     3,
       4,     3,     3,     2,     1,     2,     1,     5,     7,     5,
       7,     9,     3,     2,     2,     3,     1,     1,     1,     0,
       1,     0,     3,     1,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     1,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     4,     6,     4,     3,     3,     2,     2,
       3,     1,     1,     3,     4,     1,     3,     1,     1,     3,
       1,     1,     2,     2,     0,     2,     0,     3,     0,     2,
       1,     4,     1,     2,     3,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,    62,     0,    61,    61,     0,     0,
      61,    61,    61,     0,     0,     0,     0,     0,     5,     0,
       0,     0,     0,     2,     6,     0,    28,     0,    37,    38,
      39,    35,    33,    34,    36,    40,    41,    43,    43,    32,
      62,     0,     0,     0,     0,     0,    14,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,    77,
      56,     0,    54,     0,    55,     0,     0,    64,     0,     0,
       0,     0,     0,    74,     0,     0,    17,    18,     0,     0,
      15,    16,     0,     0,     0,    10,     0,     0,     0,     0,
       0,     0,    84,     0,    76,    80,     0,     0,    52,     0,
      51,     0,    13,     0,    23,    64,     0,     0,   245,     0,
     242,     0,   240,     0,    20,    73,    74,    71,     0,    19,
      45,    46,     0,   109,     0,     0,     0,     0,     0,     0,
      77,    42,     8,     9,    64,     0,     0,     0,     0,     0,
       0,    98,   102,   100,     0,    64,    63,    85,    82,    93,
      43,    59,    60,    58,    53,    55,     0,     0,     0,    30,
       0,     0,    94,    96,     0,     0,    48,     0,   243,     0,
     237,   239,     0,    69,    70,     0,     0,     0,     0,    22,
       0,     0,     0,     0,    24,     0,     0,     0,     0,     0,
      64,   101,    99,   114,     4,     0,    75,    81,     0,     0,
      78,     0,     0,     0,     0,    64,    95,     0,    64,    47,
       0,    31,   246,   247,   248,     0,    80,     0,     0,     0,
      21,    11,     0,    68,     0,     0,     0,     0,     0,    27,
       0,     0,   121,    64,    79,    92,    86,    88,    87,    89,
      90,    91,    83,    57,     0,     0,    50,     0,    29,   244,
     241,   236,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,     0,   107,   227,   230,   231,     0,   151,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   134,
       0,   121,   203,   205,   206,   204,   207,   208,     0,   146,
       0,   120,   136,     0,   153,   155,   168,   170,   172,   174,
     176,   178,   180,   183,   188,   191,   194,   198,     0,     0,
     199,   212,   228,     0,    25,     0,     0,     0,     0,     0,
       0,     0,     0,    67,    64,   108,   104,     0,     0,     0,
     116,     0,   227,     0,   150,   144,   143,     0,   149,     0,
       0,     0,   200,   201,     0,     0,    65,   119,   135,   133,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     157,     0,   202,   198,     0,   218,   219,     0,     0,     0,
     128,     0,   123,   124,   126,    44,    97,    49,   235,    72,
       0,   110,     0,    26,     0,     0,     0,     0,   113,   122,
     145,     0,   148,     0,   147,   142,     0,     0,   229,   152,
     154,   171,     0,   173,   175,   177,   179,   181,   182,   186,
     187,   184,   185,   189,   190,   192,   193,   195,   196,   197,
     156,     0,   216,   221,     0,     0,   217,   209,   210,   211,
       0,     0,     0,     0,     0,     0,    12,   105,     0,     0,
     234,   234,   115,   118,     0,   151,     0,     0,     0,     0,
     215,     0,   213,   129,   125,   132,     0,   131,     0,   222,
     127,   111,     0,     0,   232,   233,     0,     0,     0,   137,
     139,   169,     0,   220,   130,   225,     0,     0,   106,   117,
       0,   151,     0,   214,     0,   223,     0,   140,     0,   138,
     224,   226,     0,     0,     0,   141,     0,   103
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   120,    25,    37,    38,    64,    77,
     132,   175,   176,    26,    45,    46,    71,    72,    73,    74,
     163,    41,    39,   205,   114,   243,   101,   267,    84,   126,
     127,   128,   103,   104,   159,   208,   105,   106,   251,   210,
     171,   172,   173,   150,   151,   339,   152,   153,   136,   154,
     241,   418,   472,   298,   299,   300,   402,   403,   404,   301,
     423,   343,   302,   303,   304,   391,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     459,   319,   320,   454,   490,   506,   321,   322,   473,   494,
     329,    82,   121,   122,   123,   178,   225,   323
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -469
static const yytype_int16 yypact[] =
{
    -469,   407,  -469,    10,  -469,    23,  -469,  -469,    27,   -46,
    -469,  -469,  -469,    42,    46,    48,    66,   147,  -469,   153,
      24,   163,    30,  -469,  -469,   187,  -469,   194,  -469,  -469,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,    26,    26,  -469,
    -469,   213,   227,    76,   240,   258,  -469,   175,   247,   261,
     262,   172,   173,   181,   242,   243,   184,   195,   -36,   196,
     197,   278,   199,   283,   284,   285,   173,   198,  -469,   112,
     204,    59,  -469,   200,   208,   205,   288,  -469,   289,   214,
     217,    16,   228,   309,   238,    31,  -469,  -469,     9,   297,
    -469,  -469,   310,   311,   252,  -469,   232,   239,   254,   255,
     136,   260,  -469,    81,  -469,   257,   347,    45,  -469,   240,
    -469,   348,  -469,   263,  -469,  -469,   329,   331,   264,   342,
    -469,     0,  -469,   266,  -469,  -469,    -3,  -469,   357,  -469,
    -469,  -469,   273,  -469,   275,   281,   279,   280,   293,   294,
     112,  -469,  -469,  -469,  -469,   286,   290,   300,   305,   306,
     301,   136,  -469,  -469,   318,  -469,  -469,   364,   356,   314,
      26,  -469,  -469,  -469,  -469,  -469,   204,   330,   408,  -469,
     420,   335,   329,  -469,   422,   -17,  -469,   410,  -469,   417,
    -469,  -469,    12,  -469,  -469,   431,   419,   351,   434,  -469,
     360,   358,   432,   102,  -469,     9,   444,   447,   448,   436,
    -469,  -469,  -469,   451,  -469,   361,  -469,  -469,   365,   171,
    -469,   454,   348,   366,   367,  -469,  -469,   368,  -469,  -469,
     369,  -469,  -469,  -469,  -469,   373,   257,   374,   372,   375,
    -469,  -469,   376,   377,   380,   381,   379,   382,   383,  -469,
     386,   389,   277,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,  -469,  -469,  -469,   450,   136,  -469,   329,  -469,  -469,
    -469,   388,  -469,   474,   452,   463,   477,   361,   395,   396,
     467,   481,  -469,   397,  -469,   482,  -469,  -469,   471,   287,
     402,   403,   277,   404,   487,   405,   406,   287,   287,  -469,
     287,   277,  -469,  -469,  -469,  -469,  -469,  -469,   146,  -469,
     409,  -469,  -469,    18,  -469,  -469,   -65,   421,   399,   400,
     398,    90,   -32,   145,    77,   115,  -469,   349,   287,   414,
     -63,  -469,  -469,    -2,  -469,   413,   401,   411,   500,   418,
     423,   416,   424,  -469,  -469,  -469,  -469,   425,   428,   415,
     429,   492,  -469,   426,   427,  -469,  -469,   455,   296,   435,
     287,   287,  -469,  -469,   106,   215,  -469,  -469,  -469,  -469,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,
    -469,   287,  -469,  -469,   287,  -469,  -469,   241,   287,   234,
    -469,    -2,   430,  -469,     7,  -469,  -469,  -469,  -469,  -469,
     437,  -469,   433,  -469,   439,   490,   495,   221,  -469,  -469,
    -469,   440,  -469,   442,   427,  -469,   107,   119,  -469,  -469,
    -469,   421,   -70,   399,   400,   398,    90,   -32,   -32,   145,
     145,   145,   145,    77,    77,   115,   115,  -469,  -469,  -469,
    -469,   438,  -469,  -469,   120,   160,  -469,  -469,  -469,  -469,
      -1,    -2,   443,   -12,     4,   445,  -469,  -469,   441,   446,
    -469,  -469,   449,  -469,   287,   287,   277,   277,   287,   287,
    -469,   287,  -469,  -469,  -469,  -469,   453,  -469,     4,  -469,
    -469,  -469,   499,   456,  -469,  -469,   221,   121,   457,   458,
    -469,  -469,   125,  -469,  -469,  -469,    28,   459,  -469,  -469,
     460,   287,   277,  -469,    74,  -469,   504,  -469,   461,  -469,
    -469,  -469,   462,   277,   510,  -469,   464,  -469
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -469,  -469,  -469,  -469,  -469,  -469,  -469,  -469,   -33,  -469,
    -469,  -469,   362,  -469,  -469,  -469,  -469,   465,  -469,  -103,
    -469,   154,   502,  -469,  -113,   276,  -469,  -469,   478,  -469,
     466,  -469,   468,   394,   319,  -469,  -469,  -469,  -469,  -469,
     298,  -469,   390,   291,  -469,  -469,   412,   469,   359,  -469,
    -469,  -469,  -469,   267,  -469,   216,  -469,    92,   164,  -282,
    -469,  -463,  -469,  -276,  -356,  -469,    83,  -469,   206,   203,
     207,   210,   202,  -116,  -290,  -112,  -111,  -301,  -230,  -469,
    -469,  -469,  -469,    91,  -468,  -469,  -469,  -469,    73,   101,
    -469,  -469,  -469,   470,  -469,  -469,  -469,  -469
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -250
static const yytype_int16 yytable[] =
{
     347,   125,   169,   344,   430,    65,   165,   400,   167,   118,
     486,   174,   498,   342,   354,   361,   357,   392,   133,    27,
     505,   222,   395,   396,   478,   118,   276,   119,   360,   277,
     397,   194,    40,   398,   223,   450,    43,   224,   451,   362,
     130,   453,   204,   119,   134,   135,   521,    44,   518,   369,
     370,    51,   399,   131,   161,    52,    90,   352,   353,    28,
      29,    30,    91,    31,    32,    33,    34,   162,    35,    36,
     371,   372,   424,   357,   426,   427,   447,   448,   449,   439,
     440,   441,   442,   342,   218,   487,   432,   239,   393,   287,
     288,   401,   462,    53,   483,   463,   276,   290,   183,   277,
     462,   180,   256,   463,   488,   258,   464,    54,   489,   253,
     359,   292,   293,   294,   295,    57,   360,   296,   297,    59,
      60,   -85,   455,   453,   102,   503,   514,   211,    63,   515,
     324,   393,   489,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     145,   146,   147,   148,   108,   275,    55,   109,   489,   287,
     288,    42,    56,    47,    48,    49,    50,   290,   276,    69,
     149,   277,    58,   278,   488,   520,   156,   367,   368,   157,
     245,   292,   293,   294,   295,   375,   376,   296,   297,   246,
     247,   248,   249,   250,   499,   500,    61,   233,   497,   344,
     157,   428,   476,    62,   360,   360,   279,   280,   281,   282,
     283,   284,   285,   286,   477,   480,   510,   360,   481,   360,
     513,   413,    67,   481,   275,   377,   378,   379,   373,   374,
     519,   287,   288,   470,   471,   344,    68,   276,   289,   290,
     277,   525,   278,   456,   457,   458,   291,   356,   393,    70,
     342,   437,   438,   292,   293,   294,   295,   482,   360,   296,
     297,   443,   444,   276,   445,   446,   277,    75,    76,    78,
      79,    80,    81,    83,    85,   279,   280,   281,   282,   283,
     284,   285,   286,    88,    86,    87,   275,    94,    89,    92,
      93,    95,    96,    97,    98,   110,   342,   112,   100,   276,
     287,   288,   277,   107,   278,   275,   111,   289,   290,   276,
     113,   115,   277,   125,   116,   291,   429,   117,   276,   137,
     124,   277,   292,   293,   294,   295,   287,   288,   296,   297,
     129,   142,   138,   139,   290,   141,   452,   279,   280,   281,
     282,   283,   284,   285,   286,   140,   143,   144,   292,   293,
     294,   295,   155,   158,   296,   297,   160,   166,   170,   174,
     177,   168,   287,   288,   179,   182,   185,   186,   187,   289,
     290,   189,   287,   288,   188,   190,   102,   291,   207,   195,
     290,   287,   288,   196,   292,   293,   294,   295,   191,   290,
     296,   297,   192,   197,   292,   293,   294,   295,   198,   199,
     296,   297,   200,   292,   293,   294,   295,     2,   209,   296,
     297,     3,     4,     5,     6,     7,     8,   203,   380,   381,
     382,   383,   384,   385,   386,   387,   388,   389,   212,   214,
     213,   217,   220,     9,    10,    11,   215,    12,    13,   221,
     226,   227,   228,   229,    14,    15,    16,    17,   390,    18,
      19,    20,   230,   235,   232,   231,   236,   237,   238,    21,
     240,   242,   244,   252,   254,   260,   259,   255,   257,   262,
     263,   266,   325,   264,   265,   268,   269,   270,   272,   273,
     271,   274,   328,   330,   331,   332,   333,   335,   336,   337,
     338,  -249,   340,   341,   345,   346,   349,   348,   350,   351,
     363,   358,   406,    22,   364,   366,   365,   394,   405,   408,
     409,   411,   407,   416,   419,   468,   410,   469,   420,   412,
     414,   415,   421,   417,   507,   360,   512,   425,   461,   522,
     466,   467,   465,   474,   475,   526,   479,   219,   485,   492,
     491,   493,    66,   334,    99,   261,   326,   496,   508,   511,
     504,   206,   517,   484,   234,   327,   523,   516,   355,   527,
     524,   501,   216,   201,   422,   460,   433,   431,   436,   509,
     502,   434,   495,     0,   164,   435,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   181,   184,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   193,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     202
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-469)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     282,     4,   115,   279,   360,    38,   109,     9,   111,     9,
      22,    28,   475,     9,   290,    80,   298,   318,     9,     9,
     488,     9,    85,    86,    94,     9,    22,    27,    98,    25,
      93,   144,     9,    96,    22,   391,     9,    25,   394,   104,
       9,   397,   155,    27,    35,    36,   514,    93,   511,    81,
      82,     9,   115,    22,     9,     9,    92,   287,   288,    49,
      50,    51,    98,    53,    54,    55,    56,    22,    58,    59,
     102,   103,   348,   355,   350,   351,   377,   378,   379,   369,
     370,   371,   372,     9,   101,    97,   362,   200,   318,    85,
      86,    93,    93,    45,    95,    96,    22,    93,   101,    25,
      93,   101,   215,    96,   100,   218,    99,    41,   464,   212,
      92,   107,   108,   109,   110,    91,    98,   113,   114,    89,
      90,     9,   398,   479,    12,   481,    98,   160,   102,   101,
     243,   361,   488,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   378,   379,
      14,    15,    16,    17,    95,     9,     9,    98,   514,    85,
      86,     7,     9,     9,    10,    11,    12,    93,    22,    93,
      34,    25,     9,    27,   100,   101,    95,    87,    88,    98,
       9,   107,   108,   109,   110,   108,   109,   113,   114,    18,
      19,    20,    21,    22,   476,   477,     9,    95,   474,   475,
      98,    95,    95,     9,    98,    98,    60,    61,    62,    63,
      64,    65,    66,    67,    95,    95,    95,    98,    98,    98,
      95,   334,     9,    98,     9,   110,   111,   112,    83,    84,
     512,    85,    86,    12,    13,   511,     9,    22,    92,    93,
      25,   523,    27,     9,    10,    11,   100,   101,   478,     9,
       9,   367,   368,   107,   108,   109,   110,    97,    98,   113,
     114,   373,   374,    22,   375,   376,    25,     9,    93,    22,
       9,     9,   100,   100,    93,    60,    61,    62,    63,    64,
      65,    66,    67,    99,    42,    42,     9,     9,    93,    93,
      93,    92,     9,     9,     9,    95,     9,    92,   100,    22,
      85,    86,    25,    99,    27,     9,    98,    92,    93,    22,
      22,    22,    25,     4,   100,   100,   101,   100,    22,    22,
      92,    25,   107,   108,   109,   110,    85,    86,   113,   114,
      92,    92,    22,    22,    93,   103,    95,    60,    61,    62,
      63,    64,    65,    66,    67,    93,    92,    92,   107,   108,
     109,   110,    92,    96,   113,   114,     9,     9,    29,    28,
      96,    98,    85,    86,    22,    99,     9,    94,    93,    92,
      93,    92,    85,    86,    93,    95,    12,   100,    22,    93,
      93,    85,    86,    93,   107,   108,   109,   110,    95,    93,
     113,   114,    98,    93,   107,   108,   109,   110,    93,    93,
     113,   114,   101,   107,   108,   109,   110,     0,    94,   113,
     114,     4,     5,     6,     7,     8,     9,    99,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    98,     9,
      22,     9,    22,    26,    27,    28,   101,    30,    31,    22,
       9,    22,    91,     9,    37,    38,    39,    40,    99,    42,
      43,    44,    92,     9,    22,    97,     9,     9,    22,    52,
       9,   100,    97,     9,    98,    92,    97,   100,   100,    95,
      98,    94,    22,    98,    98,    95,    95,    98,    95,    93,
      98,    92,    94,     9,    32,    22,     9,    92,    92,    22,
       9,     9,    95,    22,    92,    92,     9,    93,    93,    93,
      79,    92,   101,    96,   105,   107,   106,    93,    95,     9,
      92,    95,   101,    98,    22,    25,    93,    22,    92,    95,
      95,    93,    67,    94,    25,    98,    68,    92,    98,    25,
      97,    92,    95,    93,    92,    25,    98,   175,    95,    98,
      95,    95,    40,   267,    66,   226,   255,    98,    92,    92,
      97,   157,    92,   461,   195,   257,    95,    98,   291,    95,
      98,   478,   172,   151,   348,   401,   363,   361,   366,   496,
     479,   364,   471,    -1,   109,   365,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   121,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   117,     0,     4,     5,     6,     7,     8,     9,    26,
      27,    28,    30,    31,    37,    38,    39,    40,    42,    43,
      44,    52,    96,   118,   119,   121,   129,     9,    49,    50,
      51,    53,    54,    55,    56,    58,    59,   122,   123,   138,
       9,   137,   137,     9,    93,   130,   131,   137,   137,   137,
     137,     9,     9,    45,    41,     9,     9,    91,     9,    89,
      90,     9,     9,   102,   124,   124,   138,     9,     9,    93,
       9,   132,   133,   134,   135,     9,    93,   125,    22,     9,
       9,   100,   207,   100,   144,    93,    42,    42,    99,    93,
      92,    98,    93,    93,     9,    92,     9,     9,     9,   144,
     100,   142,    12,   148,   149,   152,   153,    99,    95,    98,
      95,    98,    92,    22,   140,    22,   100,   100,     9,    27,
     120,   208,   209,   210,    92,     4,   145,   146,   147,    92,
       9,    22,   126,     9,    35,    36,   164,    22,    22,    22,
      93,   103,    92,    92,    92,    14,    15,    16,    17,    34,
     159,   160,   162,   163,   165,    92,    95,    98,    96,   150,
       9,     9,    22,   136,   133,   135,     9,   135,    98,   140,
      29,   156,   157,   158,    28,   127,   128,    96,   211,    22,
     101,   209,    99,   101,   146,     9,    94,    93,    93,    92,
      95,    95,    98,   148,   140,    93,    93,    93,    93,    93,
     101,   162,   163,    99,   140,   139,   149,    22,   151,    94,
     155,   124,    98,    22,     9,   101,   158,     9,   101,   128,
      22,    22,     9,    22,    25,   212,     9,    22,    91,     9,
      92,    97,    22,    95,   164,     9,     9,     9,    22,   140,
       9,   166,   100,   141,    97,     9,    18,    19,    20,    21,
      22,   154,     9,   135,    98,   100,   140,   100,   140,    97,
      92,   150,    95,    98,    98,    98,    94,   143,    95,    95,
      98,    98,    95,    93,    92,     9,    22,    25,    27,    60,
      61,    62,    63,    64,    65,    66,    67,    85,    86,    92,
      93,   100,   107,   108,   109,   110,   113,   114,   169,   170,
     171,   175,   178,   179,   180,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   197,
     198,   202,   203,   213,   140,    22,   159,   156,    94,   206,
       9,    32,    22,     9,   141,    92,    92,    22,     9,   161,
      95,    22,     9,   177,   179,    92,    92,   175,    93,     9,
      93,    93,   194,   194,   179,   169,   101,   175,    92,    92,
      98,    80,   104,    79,   105,   106,   107,    87,    88,    81,
      82,   102,   103,    83,    84,   108,   109,   110,   111,   112,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      99,   181,   193,   194,    93,    85,    86,    93,    96,   115,
       9,    93,   172,   173,   174,    95,   101,   101,     9,    92,
      93,    95,    95,   140,    95,    93,    98,    94,   167,    22,
      92,    67,   171,   176,   179,    92,   179,   179,    95,   101,
     180,   184,   179,   185,   186,   187,   188,   189,   189,   190,
     190,   190,   190,   191,   191,   192,   192,   193,   193,   193,
     180,   180,    95,   180,   199,   179,     9,    10,    11,   196,
     174,    98,    93,    96,    99,    95,    97,    92,    25,    22,
      12,    13,   168,   204,    93,    92,    95,    95,    94,    98,
      95,    98,    97,    95,   173,    95,    22,    97,   100,   180,
     200,    95,    98,    95,   205,   205,    98,   179,   177,   175,
     175,   182,   199,   180,    97,   200,   201,    25,    92,   204,
      95,    92,    68,    95,    98,   101,    98,    92,   177,   175,
     101,   200,    25,    95,    98,   175,    25,    95
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
#line 237 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 242 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 246 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 249 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 252 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 255 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 9:
/* Line 1792 of yacc.c  */
#line 287 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 10:
/* Line 1792 of yacc.c  */
#line 303 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 309 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 313 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout.x=(yyvsp[(4) - (10)]).num;
		currentCsLayout.y=(yyvsp[(6) - (10)]).num;
		currentCsLayout.z=(yyvsp[(8) - (10)]).num;
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 319 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 322 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 328 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 334 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 340 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name					=(yyvsp[(2) - (3)]).strs[0];
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 344 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name		=(yyvsp[(2) - (3)]).strs[0];
		string str		=string("#undef ")+name+"\n";
		glfxWrite(str.c_str()); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 350 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		Struct *rs					=new Struct;
		*rs							=buildStruct;
		string name					=(yyvsp[(2) - (4)]).strs[0];
		gEffect->m_structs[name]	=rs;
		gEffect->m_sharedCode<<"struct "<<(yyvsp[(2) - (4)]).strs[0]<<"\n{\n";
		for(int i=0;i<(int)rs->m_structMembers.size();i++)
		{
			const StructMember &m=rs->m_structMembers[i];
			gEffect->m_sharedCode<<m.type<<" "<<m.name<<";\n";
		}
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,(yyvsp[(4) - (4)]).lineno+last_linenumber-global_linenumber);
		gEffect->m_sharedCode<<"};";
		// Set to default:
		buildStruct					=Struct();
	}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 367 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 407 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 417 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
		if((yyvsp[(1) - (5)]).sType!=(yyvsp[(4) - (5)]).sType)
			errSem((((string("Shader type mismatch for ")+compiledShaderName+" - can't assign ")+ShaderTypeToString((yyvsp[(4) - (5)]).sType)+" shader to ")+ShaderTypeToString((yyvsp[(1) - (5)]).sType)+" shader").c_str());
		gEffect->m_compiledShaders[compiledShaderName]=compiledShader=cs;
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 436 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 439 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string bufferName	=(yyvsp[(2) - (6)]).strs[0];
		string def			=(yyvsp[(4) - (6)]).strs[0];

		ostringstream str;
		WriteLineNumber(str,current_filenumber,(yyvsp[(1) - (6)]).lineno+(last_linenumber-global_linenumber));
		str<< "constant_buffer"<<" "<<(yyvsp[(2) - (6)]).strs[0]<<(yyvsp[(4) - (6)]).strs[0]<<";\n";
		WriteLineNumber(str,current_filenumber,glfxget_lineno()+(last_linenumber-global_linenumber));

		glfxWrite(str.str().c_str());
		// Set to default:
		buildStruct					=Struct();
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 454 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string functionName		=(yyvsp[(2) - (8)]).strs[0];
		Function *f				=new Function;
		*f						=buildFunction;
		if(buildFunction.textureSamplers.size())
		{
	//		std::cout<<"ts: "<<functionName.c_str()<<std::endl;
		}
		functions[functionName]	=f;
		f->returnType			=(yyvsp[(1) - (8)]).strs[0];
		f->content				=(yyvsp[(7) - (8)]).strs[0];
		
		f->parameters			=*(yyvsp[(4) - (8)]).vars;
		delete (yyvsp[(4) - (8)]).vars;
		
		ostringstream params;
		bool start=true;
		set<string> usedSamplerStates;
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
					usedSamplerStates.insert(ts->samplerStateName);
					params<<j->storage<<" "<<j->type<<" "<<ts->textureSamplerName();
					if(j->semantic.size())
						params<<": "<<j->semantic;
					glfxstype::variable p;
					p.storage		=j->storage;
					p.type			=j->type;
					p.identifier	=(ts->textureName+"_")+ts->samplerStateName;
					p.semantic		=j->semantic;
					f->expanded_parameters.push_back(p);
					buildFunction.removeTextureSampler(ts->textureSamplerName());
				}
			}
			else
			{
				auto a=usedSamplerStates.find(name);
				if(a!=usedSamplerStates.end())
					continue;
				u=buildFunction.textureSamplersBySampler.find(name);
				if(u!=buildFunction.textureSamplersBySampler.end())
				{
					// the type must become sampler2D, sampler3D etc. EITHER
					// the type is declared for the texture in the vars list, OR it is
					// in declaredTextures.
					for(auto v=u->second.begin();v!=u->second.end();v++)
					{
						if(start)
							start=false;
						else
							params<<", ";
						TextureSampler *ts=*v;
						string type=GetTypeOfParameter(f->parameters,ts->textureName);
						if(type.length()==0)
							type=declaredTextures[ts->textureName].type;
						params<<j->storage<<" "<<type<<" "<<ts->textureName<<"_"<<ts->samplerStateName;
						if(j->semantic.size())
							params<<": "<<j->semantic;
						glfxstype::variable p;
						p.storage			=j->storage;
						p.type				=type;
						p.identifier		=ts->textureSamplerName();
						p.semantic			=j->semantic;
						f->expanded_parameters.push_back(p);
						buildFunction.removeTextureSampler(ts->textureSamplerName());
					}
				}
				else
				{
					f->expanded_parameters.push_back(*j);
					if(start)
						start=false;
					else
						params<<", ";
					params<<j->storage<<" "<<j->type<<" "<<j->identifier;
					if(j->semantic.size())
						params<<": "<<j->semantic;
				}
			}
		}
		ostringstream str;
		// Any textureSamplers not passed up the line are added to the effect's list of global textureSamplers.
		// Note: This is only temporary until we stop including unused functions in the shared code.
		for(std::map<std::string,TextureSampler*>::const_iterator i=buildFunction.textureSamplers.begin();i!=buildFunction.textureSamplers.end();i++)
		{
			TextureSampler *ts=i->second;
			ts->global=true;
			DeclareTextureSampler(i->second);
		}
		
		WriteLineNumber(str,current_filenumber,(yyvsp[(1) - (8)]).lineno+(last_linenumber-global_linenumber));
		str<< f->returnType<<" "<<functionName<<"("<<params.str()<<")"<<"\n{\n"<<f->content<<"\n}\n";
		WriteLineNumber(str,current_filenumber,glfxget_lineno()+(last_linenumber-global_linenumber));

		glfxWrite(str.str().c_str());

		buildFunction.clear();
	}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 568 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		CompilableShader &sh=*(compilableShaders[(yyvsp[(3) - (9)]).strs[0]]=new CompilableShader);
		sh.shaderName			=(yyvsp[(3) - (9)]).strs[0];
		sh.function.returnType	=(yyvsp[(2) - (9)]).strs[0];
		sh.function.content		=(yyvsp[(8) - (9)]).strs[0];
		sh.returnable			=(yyvsp[(8) - (9)]).strs[1];
		sh.main_linenumber		=(yyvsp[(1) - (9)]).lineno+(last_linenumber-global_linenumber);
		sh.content_linenumber	=(yyvsp[(8) - (9)]).lineno+(last_linenumber-global_linenumber);
		sh.current_filenumber	=current_filenumber;
		sh.csLayout				=currentCsLayout;
		ostringstream shaderCode;
		ostringstream extraDeclarations;
		ostringstream finalCode;
		sh.function.parameters	=*(yyvsp[(5) - (9)]).vars;

		ostringstream str;
		sh.function.textureSamplers					=buildFunction.textureSamplers;
		sh.function.textureSamplersByTexture		=buildFunction.textureSamplersByTexture;
		sh.function.textureSamplersBySampler		=buildFunction.textureSamplersBySampler;
		buildFunction.textureSamplers.clear();	// so the pointers won't be freed later.


		for(std::map<std::string,TextureSampler*>::const_iterator i=sh.function.textureSamplers.begin();i!=sh.function.textureSamplers.end();i++)
		{
			DeclareTextureSampler(i->second);
		}
		gEffect->m_sharedCode<<str.str();

		buildFunction.clear();
		delete (yyvsp[(5) - (9)]).vars;
		
		gEffect->m_sharedCode<<"#line "<<(glfxget_lineno()+(last_linenumber-global_linenumber))<<" "<<current_filenumber<<endl;
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 602 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 607 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 610 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 618 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 625 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 631 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 636 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 642 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 648 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 653 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 658 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	std::string ret="(";
	ret+=(yyvsp[(2) - (7)]).strs[0];
	ret+=",";
	ret+=(yyvsp[(4) - (7)]).strs[0];
	ret+=",";
	ret+=(yyvsp[(6) - (7)]).strs[0];
	ret+=")";
	(yyval).strs[0]=ret;
	currentCsLayout.x=(yyvsp[(2) - (7)]).num;
	currentCsLayout.y=(yyvsp[(4) - (7)]).num;
	currentCsLayout.z=(yyvsp[(6) - (7)]).num;
}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 672 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 675 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 678 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 682 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 685 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 689 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 51:
/* Line 1792 of yacc.c  */
#line 699 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 703 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 708 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 712 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 716 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 720 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 724 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				currentCsLayout.x=(yyvsp[(1) - (5)]).num;
				currentCsLayout.y=(yyvsp[(3) - (5)]).num;
				currentCsLayout.z=(yyvsp[(5) - (5)]).num;
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 732 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				(yyval).num=(yyvsp[(3) - (3)]).num;
		   }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 738 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 742 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 746 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 753 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 760 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_function=true;
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 767 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 771 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 778 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 784 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
 }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 788 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
 }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 792 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="{\n";
	(yyval).strs[0]+=((yyvsp[(2) - (3)]).strs[0]+"\n}\n");
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 797 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string list			=(yyvsp[(1) - (2)]).strs[0];
	string new_member	=(yyvsp[(2) - (2)]).strs[0];
    (yyval).strs[0]=(list+"\n")+new_member;
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 803 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string member	=(yyvsp[(1) - (1)]).strs[0];
    (yyval).strs[0]=member;
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 808 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).lineno		=(yyvsp[(4) - (6)]).lineno;
	string unif		=(yyvsp[(1) - (6)]).strs[0];
	string type		=(yyvsp[(2) - (6)]).strs[0];
	string name		=(yyvsp[(3) - (6)]).strs[0];
	string sq		=(yyvsp[(4) - (6)]).strs[0];
	string sem		=(yyvsp[(5) - (6)]).strs[0];
	StructMember s;
	s.type		=type;
	s.semantic	=sem;
	s.name		=name;
	buildStruct.m_structMembers.push_back(s);
	(yyval).strs[0]=(unif.length()?(unif+" "):"");
    (yyval).strs[0]+=(type+" ")+name;
	(yyval).strs[0]+=sq;
	(yyval).strs[0]+=sem.length()?(string(": ")+sem):"";
	(yyval).strs[0]+=";";
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 827 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="uniform";
}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 831 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 835 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 76:
/* Line 1792 of yacc.c  */
#line 848 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 77:
/* Line 1792 of yacc.c  */
#line 861 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 867 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 79:
/* Line 1792 of yacc.c  */
#line 900 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 905 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 910 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
			}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 915 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
			}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 920 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 84:
/* Line 1792 of yacc.c  */
#line 934 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 938 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 942 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 947 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 952 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 957 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 962 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 967 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 973 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 978 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 984 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 991 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 96:
/* Line 1792 of yacc.c  */
#line 1003 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 97:
/* Line 1792 of yacc.c  */
#line 1017 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable	= (yyvsp[(1) - (5)]).boolean;
	(yyval).prog					= (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0]				= (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1024 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders),buildPassState,gEffect->textureSamplersByShader);
    delete (yyvsp[(1) - (1)]).shaders;
	buildPassState			=PassState();
}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 1031 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 100:
/* Line 1792 of yacc.c  */
#line 1041 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 101:
/* Line 1792 of yacc.c  */
#line 1054 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1062 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1070 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1079 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1083 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1089 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1097 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				errSem("Pass definitions like vs(430)=vs_main are no longer supported. Please use SetVertexShader() etc.");
			}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1102 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[1]="";
				(yyval).strs[0]="";
				(yyval).sType	=(yyvsp[(1) - (5)]).sType;//(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
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
					if((yyval).sType!=(yyvsp[(3) - (5)]).sType)
						errSem((((string("Shader type mismatch for ")+compiledShaderName+" - can't call ")+(yyvsp[(1) - (5)]).strs[0]+" with ")+ShaderTypeToString((yyvsp[(3) - (5)]).sType)+" shader as input.").c_str());

					ostringstream theShader;
					theShader << "#version " << compiledShader->version << endl;
					glfxParser::ShaderCommand shaderCommand=(yyvsp[(1) - (5)]).sCommand;
					// Because there's no such thing in GLSL:
					theShader<<"#define SamplerState int\n";
					for(map<std::string,SamplerState*>::const_iterator i=gEffect->m_samplerStates.begin();i!=gEffect->m_samplerStates.end();i++)
					{
						theShader<<"int "<<i->first<<"=0;\n";
					}
					for(auto i=additionalTextureDeclarations.begin();i!=additionalTextureDeclarations.end();i++)
					{
						theShader<<"uniform "<<i->second.type<<" "<<i->first<<";\n";
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
									theShader<<gEffect->m_shaderLayouts[shaderName].text()<<"\n";
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

  case 109:
/* Line 1792 of yacc.c  */
#line 1176 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string compiledShaderName	=(yyvsp[(1) - (1)]).strs[0];
			CompiledShaderMap::iterator i=gEffect->m_compiledShaders.find(compiledShaderName);
			if(i!=gEffect->m_compiledShaders.end())
				(yyval).sType				=i->second->shaderType;
			else
				(yyval).sType				=NUM_OF_SHADER_TYPES;
			(yyval).strs[0]					=compiledShaderName;
			(yyval).num						=0;
			(yyval).lineno					=(yyvsp[(1) - (1)]).lineno;
		}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1188 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).lineno				=(yyvsp[(5) - (6)]).lineno;
			(yyval).sType				=GEOMETRY_SHADER;
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

  case 111:
/* Line 1792 of yacc.c  */
#line 1208 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).lineno								=(yyvsp[(5) - (8)]).lineno;
			(yyval).sType								=(yyvsp[(3) - (8)]).sType;
			string profileName						=(yyvsp[(3) - (8)]).strs[0];
			(yyval).token								=(yyvsp[(3) - (8)]).token;
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
			// "Compile" the shader - in the sense of "concatenate the strings and prepare it as GLSL source":
			gEffect->m_shaders[shaderName]			=Compile((yyvsp[(1) - (8)]).sType,sh);

			gEffect->MergeTextureSamplers(sh.function.textureSamplers,shaderName);

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

  case 112:
/* Line 1792 of yacc.c  */
#line 1244 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1255 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1261 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1265 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1269 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1274 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1279 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1283 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1292 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1298 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1303 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 123:
/* Line 1792 of yacc.c  */
#line 1316 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			stringReplaceAll(init_declarator_list,type_spec+type_spec,type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1325 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1329 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1333 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1337 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 128:
/* Line 1792 of yacc.c  */
#line 1375 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1379 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1383 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1388 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1392 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1396 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
				}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1401 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=";\n";
				}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1405 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
				}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1409 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
				}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1414 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1418 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 139:
/* Line 1792 of yacc.c  */
#line 1429 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1433 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+";\n";
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1437 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
				}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1442 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+";\n";
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1446 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1450 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
				}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1454 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				string optional_expression=(yyvsp[(2) - (3)]).strs[0];
				if(read_shader&&optional_expression.length()>0)
				{
					(yyval).strs[0]="";
					(yyval).strs[1]=optional_expression;
				}
				else
				{
					(yyval).strs[0]=((yyvsp[(1) - (3)]).strs[0]+" ")+optional_expression+";\n";
					(yyval).strs[1]=optional_expression;
				}
				(yyval).lineno=(yyvsp[(1) - (3)]).lineno;
			}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1469 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1474 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1478 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1482 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1485 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1489 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1494 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1500 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1504 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1508 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1512 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1516 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 167:
/* Line 1792 of yacc.c  */
#line 1529 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 168:
/* Line 1792 of yacc.c  */
#line 1533 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1537 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
	}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1542 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1546 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1550 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1554 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1558 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1562 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1566 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1570 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1574 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1578 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1583 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1587 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1591 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1595 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1599 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1603 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1607 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1611 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1615 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1619 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1623 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1627 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1631 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1635 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1639 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1643 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1647 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1651 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1655 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1659 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1663 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1667 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1671 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1675 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 209:
/* Line 1792 of yacc.c  */
#line 1679 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texture";
}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1683 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="textureLod";
}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1687 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string texture=(yyvsp[(1) - (3)]).strs[0];
						string command=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[0]=texture+(yyvsp[(2) - (3)]).strs[0]+command;
						// Put the thing we're sampling into strs[1]
						(yyval).strs[1]=texture;
						// We put the command into strs[2]
						(yyval).strs[2]=command;
					}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1698 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[0];			//Command
					}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1703 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (4)]).strs[2];			//Command
					}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1708 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName		=(yyvsp[(1) - (6)]).strs[1];
						string command			=(yyvsp[(1) - (6)]).strs[2];
						string samplerStateName	=(yyvsp[(3) - (6)]).strs[0];
						string otherParams		=(yyvsp[(5) - (6)]).strs[0];
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
						TextureSampler *ts=AddTextureSampler(textureName,samplerStateName);
						string full_expr=(command+"(")+(ts->textureSamplerName()+",")+otherParams+")";
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

  case 215:
/* Line 1792 of yacc.c  */
#line 1745 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (4)]).strs[0];
						string expr2=(yyvsp[(2) - (4)]).strs[0];
						string params;
						auto vars=*((yyvsp[(3) - (4)]).vars);
						delete (yyvsp[(3) - (4)]).vars;
						string expr4=(yyvsp[(4) - (4)]).strs[0];
						// ok this could be a function call.
						string command=(yyvsp[(1) - (4)]).strs[2];
						auto j=functions.find(command);
						if(j==functions.end())
						{
							params=(yyvsp[(3) - (4)]).strs[0];
						}
						else
						{
							const Function &f=*(j->second);
							// If it's a known function, there may need to be a mapping from the texture and sampler parameters.
							// We figure out this mapping by looking at the vars list of the function we're calling.
							//	this is the unmodified list, so it corresponds to the call we're making.
							for(vector<glfxstype::variable>::const_iterator i=f.expanded_parameters.begin();i!=f.expanded_parameters.end();i++)
							{
								string declared_name=i->identifier;
								// That's how the parameter was declared. Is it in the original list?
								int index=GetIndexOfParameter(f.parameters,declared_name);
								// If so we pass the corresponding parameter from the call.
								if(index>=0)
								{
									const glfxstype::variable &p=vars[index];
									if(params.size())
										params+=",";
									params+=p.identifier;
								}
								else // could be a textureSampler...
								{
									auto u=f.textureSamplers.find(declared_name);
									if(u!=f.textureSamplers.end())
									{
										TextureSampler *ts		=u->second;
										int t					=GetIndexOfParameter(f.parameters,ts->textureName);
										int s					=GetIndexOfParameter(f.parameters,ts->samplerStateName);
										string textureName		=ts->textureName;
										string samplerStateName	=ts->samplerStateName;
										if(t>=0)
											textureName			=(vars[t]).identifier;
										if(s>=0)
											samplerStateName	=(vars[s]).identifier;
										TextureSampler *ts_new=AddTextureSampler(textureName,samplerStateName);
										if(params.size())
											params+=",";
										params+=ts_new->textureSamplerName();
										
									}
								}
							}
							for(auto j=f.textureSamplers.begin();j!=f.textureSamplers.end();j++)
							{
								TextureSampler *ts		=j->second;
								if(ts->global)
									AddTextureSampler(ts->textureName,ts->samplerStateName)->global=true;
							}
						}
						(yyval).strs[0]=expr1+expr2+params+expr4;
					}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1810 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						// ok this could be a function call.
						string command=(yyvsp[(1) - (3)]).strs[2];
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1816 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[2]=expr3;			//Command
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1823 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1827 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1831 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars=(yyvsp[(1) - (3)]).vars;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1839 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars = new vector<YYSTYPE::variable>;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1847 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1852 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1859 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1866 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1873 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1880 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1884 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1888 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 1892 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 1896 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 1900 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 1908 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 1916 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 1920 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 1924 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 1928 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 1931 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 1935 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 1940 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 1944 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 242:
/* Line 1792 of yacc.c  */
#line 2053 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2058 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2064 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2069 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 2073 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 2078 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2083 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 2088 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 4868 "src/glfxLALRParser.cpp"
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
#line 2091 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
	buildStruct					=Struct();
	declaredTextures.clear();
	read_shader=false;
	read_function=false;
}
