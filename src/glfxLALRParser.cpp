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
	map<string,DeclaredTexture> additionalTextureDeclarations;
	
	void DeclareTextureSampler(const TextureSampler *ts)
	{
		auto i=additionalTextureDeclarations.find(ts->textureSamplerName());
		if(i!=additionalTextureDeclarations.end())
			return;

		string tsname		=ts->textureSamplerName();
		string texture_name	=ts->textureName;
		if (gEffect->declaredTextures.find(texture_name) != gEffect->declaredTextures.end())
		{
			string sampler_type = gEffect->declaredTextures[texture_name].type;
			//str<<"uniform "<<sampler_type<<" "<<tsname<<";\n";
			additionalTextureDeclarations[tsname].type		=sampler_type;
			additionalTextureDeclarations[tsname].type_enum = gEffect->declaredTextures[texture_name].type_enum;
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
	int GetTextureType(const Function &function,const string &textureName)
	{
		for(vector<glfxstype::variable>::const_iterator i=function.parameters.begin();i!=function.parameters.end();i++)
		{
			if(textureName==i->identifier)
				return i->type_enum;
		}
		auto j = gEffect->declaredTextures.find(textureName);
		if (j != gEffect->declaredTextures.end())
			return j->second.type_enum;
		return 0;
	}
	GLTextureType ToGLTextureType(int t);
	
	string GetSizeFunction(string textureName,string x,string y,string z)
	{
		int glTextureType	=(GetTextureType(buildFunction,textureName));
		bool lod_param=false;
		switch(glTextureType)
		{
			case gsampler1D:
			case gsampler2D:
			case gsampler3D:
			case gsamplerCube:
			case sampler1DShadow:
			case sampler2DShadow:
			case samplerCubeShadow:
			case gsamplerCubeArray:
			case gsampler1DArray:
			case gsampler2DArray:
			case sampler1DArrayShadow:
			case sampler2DArrayShadow:
				lod_param=true;
			default:
				break;
		}
		int return_size=2;
		switch(glTextureType)
		{
		case gsampler1D:
		case sampler1DShadow:
		case gsamplerBuffer:
			return_size=1;
			break;
		case gsampler3D:
		case gsamplerCubeArray:
		case samplerCubeArrayShadow:
		case gsampler2DArray:
		case gsampler2DMSArray:
		case sampler2DArrayShadow:
			return_size=3;
			break;
		default:
			break;
		}
		ostringstream full_expr;
		// NOTE the spaces around the textureName. We might need to replace it with a sampler name, so we make sure we can find it
		// as a whole word easily.
		full_expr<<"{ivec"<<return_size<<" iv=textureSize( "<<textureName<<" ";
		if(lod_param)
			full_expr<<",0";
		full_expr<<"); "<<x<<"=iv.x;";
		if(return_size>1&&y.size()>0)
			full_expr<<y<<"=iv.y;";
		if(return_size>2&&z.size()>0)
			full_expr<<z<<"=iv.z;";
		full_expr<<"}\n";
		return full_expr.str();
	}
	bool IsDeclared(string name)
	{
		if(gEffect->IsDeclared(name))
			return true;
		for(auto i=buildFunction.parameters.begin();i!=buildFunction.parameters.end();i++)
		{
			if(i->identifier==name)
				return true;
		}
		return false;
	}

/* Line 371 of yacc.c  */
#line 372 "src/glfxLALRParser.cpp"

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
     TEXTURECUBE = 313,
     IMAGE3D = 314,
     KNOWN_TYPE = 315,
     STRUCTUREDBUFFER = 316,
     RW_STRUCTUREDBUFFER = 317,
     RETURN = 318,
     BREAK = 319,
     CONTINUE = 320,
     DO = 321,
     FOR = 322,
     GOTO = 323,
     IF = 324,
     WHILE = 325,
     ELSE = 326,
     TIMES_EQUALS = 327,
     OVER_EQUALS = 328,
     PERCENT_EQUALS = 329,
     PLUS_EQUALS = 330,
     MINUS_EQUALS = 331,
     LEFT_SHIFT_EQUALS = 332,
     RIGHT_SHIFT_EQUALS = 333,
     AND_EQUALS = 334,
     XOR_EQUALS = 335,
     OR_EQUALS = 336,
     AND = 337,
     OR = 338,
     LESS_EQ = 339,
     GRTR_EQ = 340,
     LEFT_SHIFT = 341,
     RIGHT_SHIFT = 342,
     PLUS_PLUS = 343,
     MINUS_MINUS = 344,
     EQ_EQ = 345,
     NOT_EQ = 346,
     SA_MAXVERTEXCOUNT = 347,
     SA_NUMTHREADS = 348,
     SHADER_PROFILE = 349
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
#line 532 "src/glfxLALRParser.cpp"

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
#define YYLAST   670

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  119
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  257
/* YYNRULES -- Number of states.  */
#define YYNSTATES  547

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   349

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   117,     2,     2,     2,   115,   110,     2,
      96,    98,   113,   111,   101,   112,   118,   114,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    97,    95,
     105,   102,   106,   107,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    99,     2,   100,   109,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   103,   108,   104,   116,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    26,    32,
      38,    43,    50,    61,    66,    69,    73,    77,    81,    85,
      90,    96,   103,   109,   114,   121,   130,   140,   148,   150,
     158,   164,   168,   171,   173,   175,   177,   179,   181,   183,
     185,   187,   189,   191,   195,   196,   204,   206,   208,   211,
     213,   219,   227,   231,   235,   239,   241,   243,   245,   251,
     255,   257,   259,   260,   261,   262,   263,   267,   268,   271,
     272,   276,   279,   281,   288,   290,   291,   295,   297,   298,
     302,   306,   307,   309,   310,   315,   317,   319,   321,   322,
     324,   326,   328,   330,   333,   336,   339,   340,   342,   345,
     347,   353,   355,   358,   360,   363,   365,   376,   382,   390,
     400,   405,   411,   413,   420,   429,   434,   439,   440,   443,
     444,   448,   450,   453,   455,   456,   460,   463,   465,   469,
     471,   475,   477,   481,   486,   490,   494,   497,   499,   502,
     504,   510,   518,   524,   532,   542,   546,   549,   552,   556,
     558,   560,   562,   563,   565,   566,   570,   572,   576,   578,
     582,   584,   586,   588,   590,   592,   594,   596,   598,   600,
     602,   604,   606,   612,   614,   618,   620,   624,   626,   630,
     632,   636,   638,   642,   644,   648,   652,   654,   658,   662,
     666,   670,   672,   676,   680,   682,   686,   690,   692,   696,
     700,   704,   706,   708,   711,   714,   717,   719,   721,   723,
     725,   727,   729,   731,   733,   737,   741,   743,   748,   755,
     764,   771,   776,   780,   784,   787,   790,   794,   796,   798,
     802,   807,   809,   813,   815,   817,   821,   823,   825,   828,
     831,   832,   838,   839,   842,   843,   847,   848,   851,   853,
     858,   860,   863,   867,   868,   870,   872,   874
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     120,     0,    -1,   120,   121,    -1,    -1,     9,   140,    10,
     145,    95,   143,    -1,    44,    -1,   122,    -1,    40,    47,
      96,   129,    97,    24,    98,    -1,     4,   125,   127,    10,
      95,    -1,     4,   126,   127,    10,    95,    -1,     4,    10,
      10,    95,    -1,    99,    92,    96,    24,    98,   100,    -1,
      99,    93,    96,    24,   101,    24,   101,    24,    98,   100,
      -1,    28,   133,    10,    95,    -1,    28,   134,    -1,    54,
      10,    95,    -1,    54,    10,   101,    -1,    41,    43,    44,
      -1,    42,    10,    44,    -1,    39,    10,   147,    95,    -1,
      33,    10,   211,   213,    95,    -1,    46,    94,    96,    24,
      98,    95,    -1,    45,    10,   102,   168,    95,    -1,    28,
     140,   128,   143,    -1,     7,    10,   141,   147,    95,   143,
      -1,    10,    10,    96,   151,    98,   142,   144,   143,    -1,
     124,    10,    10,    96,   151,    98,   146,   144,   143,    -1,
       8,   140,    10,   103,   163,   104,   143,    -1,   132,    -1,
      32,   140,    10,   103,   130,   104,   143,    -1,    29,   140,
      24,    24,   143,    -1,    29,    24,    24,    -1,     6,   141,
      -1,    56,    -1,    57,    -1,    55,    -1,    59,    -1,    51,
      -1,    52,    -1,    53,    -1,    58,    -1,    61,    -1,    62,
      -1,   105,    10,   106,    -1,    -1,    96,    24,   101,    24,
     101,    24,    98,    -1,    10,    -1,    24,    -1,   130,   131,
      -1,   131,    -1,    30,    10,   103,   160,   104,    -1,    30,
     140,    10,   103,   160,   104,   143,    -1,    96,   137,    98,
      -1,    96,   135,    98,    -1,   135,   101,   136,    -1,   136,
      -1,   138,    -1,    10,    -1,   138,   101,   138,   101,   138,
      -1,    10,   102,   139,    -1,    10,    -1,    24,    -1,    -1,
      -1,    -1,    -1,   103,   173,   104,    -1,    -1,    97,    10,
      -1,    -1,   103,   148,   104,    -1,   148,   149,    -1,   149,
      -1,   150,    10,    10,   153,   212,    95,    -1,     4,    -1,
      -1,   151,   101,   152,    -1,   152,    -1,    -1,   155,   153,
     159,    -1,    99,   154,   100,    -1,    -1,    24,    -1,    -1,
     157,   156,   127,    10,    -1,    10,    -1,   125,    -1,    14,
      -1,    -1,    20,    -1,    22,    -1,    21,    -1,    23,    -1,
      97,    24,    -1,    97,   158,    -1,    97,    10,    -1,    -1,
     161,    -1,   161,   162,    -1,   162,    -1,    31,    10,   103,
     163,   104,    -1,   164,    -1,   164,   167,    -1,   167,    -1,
     164,   166,    -1,   166,    -1,    10,    96,    27,   101,    27,
     101,    27,   101,    27,    98,    -1,    17,    96,    10,    98,
      95,    -1,    18,    96,    10,   101,    24,    98,    95,    -1,
      19,    96,    10,   101,   165,   101,    24,    98,    95,    -1,
     169,   102,   170,    95,    -1,    16,    96,   168,    98,    95,
      -1,    10,    -1,    38,    96,    10,   101,    34,    98,    -1,
      37,    96,    94,   101,    10,    96,    98,    98,    -1,    36,
      96,    24,    98,    -1,    10,    96,    98,   171,    -1,    -1,
      97,   172,    -1,    -1,   172,   101,   209,    -1,   209,    -1,
     173,   179,    -1,   179,    -1,    -1,    29,    24,    24,    -1,
     219,   176,    -1,   177,    -1,   176,   101,   177,    -1,   178,
      -1,   178,   102,   205,    -1,    10,    -1,    96,   178,    98,
      -1,   178,    99,    24,   100,    -1,   178,    99,   100,    -1,
     178,    96,    98,    -1,   183,    95,    -1,    95,    -1,   175,
      95,    -1,   182,    -1,    69,    96,   183,    98,   179,    -1,
      69,    96,   183,    98,   179,    71,   179,    -1,    70,    96,
     183,    98,   179,    -1,    66,   179,    70,    96,   183,    98,
      95,    -1,    67,    96,   180,    95,   181,    95,   181,    98,
     179,    -1,    68,    10,    95,    -1,    65,    95,    -1,    64,
      95,    -1,    63,   181,    95,    -1,   174,    -1,   183,    -1,
     175,    -1,    -1,   183,    -1,    -1,   103,   173,   104,    -1,
     184,    -1,   183,   101,   184,    -1,   186,    -1,   198,   185,
     184,    -1,   102,    -1,    72,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,
      80,    -1,    81,    -1,   187,    -1,   187,   107,   183,    97,
     186,    -1,   188,    -1,   187,    83,   188,    -1,   189,    -1,
     188,    82,   189,    -1,   190,    -1,   189,   108,   190,    -1,
     191,    -1,   190,   109,   191,    -1,   192,    -1,   191,   110,
     192,    -1,   193,    -1,   192,    90,   193,    -1,   192,    91,
     193,    -1,   194,    -1,   193,   105,   194,    -1,   193,   106,
     194,    -1,   193,    84,   194,    -1,   193,    85,   194,    -1,
     195,    -1,   194,    86,   195,    -1,   194,    87,   195,    -1,
     196,    -1,   195,   111,   196,    -1,   195,   112,   196,    -1,
     197,    -1,   196,   113,   197,    -1,   196,   114,   197,    -1,
     196,   115,   197,    -1,   198,    -1,   203,    -1,    88,   198,
      -1,    89,   198,    -1,   199,   197,    -1,   110,    -1,   113,
      -1,   111,    -1,   112,    -1,   116,    -1,   117,    -1,    11,
      -1,    12,    -1,   203,   118,   200,    -1,   203,   118,    13,
      -1,   207,    -1,   203,    99,   183,   100,    -1,   202,    96,
     184,   101,   184,    98,    -1,   202,    96,   184,   101,   184,
     101,   184,    98,    -1,   201,    96,   184,   101,   204,    98,
      -1,   203,    96,   204,    98,    -1,   203,    96,    98,    -1,
     203,   118,    10,    -1,   203,    88,    -1,   203,    89,    -1,
     204,   101,   184,    -1,   184,    -1,   184,    -1,   103,   206,
     104,    -1,   103,   206,   101,   104,    -1,   205,    -1,   206,
     101,   205,    -1,    10,    -1,   208,    -1,    96,   183,    98,
      -1,    24,    -1,    27,    -1,    14,   210,    -1,    15,   210,
      -1,    -1,    97,     5,    96,    10,    98,    -1,    -1,    97,
      10,    -1,    -1,   103,   214,   104,    -1,    -1,   214,   215,
      -1,   215,    -1,   216,   102,   218,    95,    -1,   123,    -1,
      10,   217,    -1,    99,    24,   100,    -1,    -1,    10,    -1,
      24,    -1,    27,    -1,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   316,   316,   317,   321,   325,   328,   331,   334,   367,
     383,   389,   393,   399,   402,   408,   414,   420,   424,   430,
     447,   487,   497,   516,   519,   534,   658,   692,   697,   700,
     708,   715,   721,   726,   726,   726,   726,   726,   726,   726,
     726,   732,   732,   738,   744,   748,   762,   765,   768,   772,
     775,   779,   789,   793,   798,   802,   806,   810,   814,   822,
     828,   832,   837,   844,   851,   858,   862,   869,   874,   879,
     882,   887,   893,   898,   917,   922,   925,   939,   955,   960,
     991,   997,  1001,  1007,  1011,  1026,  1031,  1036,  1041,  1044,
    1049,  1054,  1059,  1064,  1069,  1075,  1081,  1086,  1093,  1105,
    1119,  1126,  1133,  1143,  1156,  1164,  1172,  1181,  1185,  1191,
    1199,  1204,  1278,  1290,  1310,  1346,  1357,  1364,  1367,  1372,
    1376,  1381,  1385,  1394,  1401,  1405,  1418,  1427,  1431,  1435,
    1439,  1477,  1481,  1485,  1490,  1494,  1498,  1504,  1509,  1514,
    1520,  1525,  1537,  1542,  1547,  1553,  1558,  1563,  1568,  1583,
    1589,  1593,  1598,  1600,  1605,  1609,  1615,  1619,  1623,  1627,
    1631,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,
    1644,  1648,  1652,  1657,  1661,  1665,  1669,  1673,  1677,  1681,
    1685,  1689,  1693,  1698,  1702,  1706,  1710,  1714,  1718,  1722,
    1726,  1730,  1734,  1738,  1742,  1746,  1750,  1754,  1758,  1762,
    1766,  1770,  1774,  1778,  1782,  1786,  1790,  1790,  1790,  1790,
    1790,  1790,  1794,  1798,  1802,  1812,  1822,  1827,  1832,  1840,
    1848,  1891,  1956,  1962,  1969,  1973,  1977,  1985,  1993,  1998,
    2005,  2012,  2019,  2026,  2030,  2034,  2038,  2042,  2046,  2054,
    2063,  2066,  2072,  2075,  2080,  2083,  2087,  2090,  2095,  2099,
    2208,  2213,  2219,  2225,  2228,  2233,  2238,  2243
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHITESPACE", "UNIFORM", "REGISTER",
  "SHADER", "CONSTANT_BUFFER", "PROGRAM", "INTERFACE", "IDENTIFIER",
  "SAMPLE", "SAMPLE_LOD", "GET_DIMS", "STORAGEQ", "GL_FRAGDEPTH",
  "SHADER_COMMAND", "SET_RASTERIZER_COMMAND", "SET_DEPTH_COMMAND",
  "SET_BLEND_COMMAND", "SV_DISPATCHTHREADID", "SV_GROUPTHREADID",
  "SV_GROUPID", "SV_VERTEXID", "NUM", "INCLUDE", "SAMPLER", "FLOAT",
  "LAYOUT", "LINE", "TECHNIQUE", "PASS", "GROUP", "RENDER_STATE_DECL",
  "QUOTED_STRING", "SHADER_LINE", "SHADER_TYPE", "COMPILE_SHADER",
  "CONSTRUCT_GS_WITH_SO", "STRUCT", "PRAGMA", "DEFINE", "UNDEF",
  "MACRO_DEFINITION", "EOL", "DECL_SHADER", "PROFILE", "WARNING", "DEF",
  "MESSAGE", "PACK_MATRIX", "RW_TEXTURE2D", "RW_TEXTURE3D",
  "RW_TEXTURE2DARRAY", "RW_TEXTURE3D_FLOAT4", "TEXTURE2DMS", "TEXTURE2D",
  "TEXTURE3D", "TEXTURECUBE", "IMAGE3D", "KNOWN_TYPE", "STRUCTUREDBUFFER",
  "RW_STRUCTUREDBUFFER", "RETURN", "BREAK", "CONTINUE", "DO", "FOR",
  "GOTO", "IF", "WHILE", "ELSE", "TIMES_EQUALS", "OVER_EQUALS",
  "PERCENT_EQUALS", "PLUS_EQUALS", "MINUS_EQUALS", "LEFT_SHIFT_EQUALS",
  "RIGHT_SHIFT_EQUALS", "AND_EQUALS", "XOR_EQUALS", "OR_EQUALS", "AND",
  "OR", "LESS_EQ", "GRTR_EQ", "LEFT_SHIFT", "RIGHT_SHIFT", "PLUS_PLUS",
  "MINUS_MINUS", "EQ_EQ", "NOT_EQ", "SA_MAXVERTEXCOUNT", "SA_NUMTHREADS",
  "SHADER_PROFILE", "';'", "'('", "':'", "')'", "'['", "']'", "','", "'='",
  "'{'", "'}'", "'<'", "'>'", "'?'", "'|'", "'^'", "'&'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'~'", "'!'", "'.'", "$accept", "prog", "tok",
  "line_statement", "ignore_line_statement", "shader_and_layout",
  "texture_type", "buffer_type", "optional_templateval", "layout_params",
  "warning-specifier", "technique_decls", "group_technique_decl",
  "technique_decl", "cs_layout_spec", "normal_layout_spec", "tx_layout",
  "layout_s", "cs_layout", "layout_el", "layout_def", "lex_fx",
  "shader_fx", "function_fx", "lex_passthrough", "function_content",
  "read_block", "optional_return_semantic", "struct_definition",
  "struct_member_list", "struct_memb", "optional_uniform",
  "param_declaration_list", "param_declaration", "opt_sq", "opt_num",
  "param", "type_name", "opt_storage", "input_semantic", "location",
  "tech_def", "pass_list", "pass_def", "prog_def", "shaders_list", "vec4",
  "shader_fn", "shader_def", "shader_compile", "shader_lvalue",
  "shader_rvalue", "shader_layout", "shader_layout_list", "statement_list",
  "line_statement_in_shader", "declaration", "init_declarator_list",
  "init_declarator", "declarator", "statement", "for_init_statement",
  "optional_expression", "compound_statement", "expression",
  "assignment_exp", "assignment_operator", "conditional_exp",
  "logical_or_exp", "logical_and_exp", "inclusive_or_exp",
  "exclusive_or_exp", "and_exp", "equality_exp", "relational_exp",
  "shift_expression", "additive_exp", "mult_exp", "cast_exp", "unary_exp",
  "unary_operator", "sampling_command", "sampling_exp", "get_dims_exp",
  "postfix_exp", "argument_exp_list", "initializer", "initializer_list",
  "primary_exp", "const", "layout", "read_parenthesis",
  "optional_object_semantic", "optional_semantic",
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
     345,   346,   347,   348,   349,    59,    40,    58,    41,    91,
      93,    44,    61,   123,   125,    60,    62,    63,   124,    94,
      38,    43,    45,    42,    47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   119,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   123,   124,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   126,   127,   127,   128,   129,   129,   130,   130,
     131,   132,   133,   134,   135,   135,   136,   136,   137,   138,
     139,   139,   140,   141,   142,   143,   144,   145,   146,   146,
     147,   148,   148,   149,   150,   150,   151,   151,   151,   152,
     153,   153,   154,   154,   155,   156,   156,   157,   157,   158,
     158,   158,   158,   159,   159,   159,   159,   160,   161,   161,
     162,   163,   164,   164,   164,   164,   165,   166,   166,   166,
     167,   167,   168,   168,   168,   169,   170,   170,   171,   171,
     172,   172,   173,   173,   173,   174,   175,   176,   176,   177,
     177,   178,   178,   178,   178,   178,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     180,   180,   180,   181,   181,   182,   183,   183,   184,   184,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     185,   186,   186,   187,   187,   188,   188,   189,   189,   190,
     190,   191,   191,   192,   192,   192,   193,   193,   193,   193,
     193,   194,   194,   194,   195,   195,   195,   196,   196,   196,
     196,   197,   198,   198,   198,   198,   199,   199,   199,   199,
     199,   199,   200,   200,   201,   202,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   204,   204,   205,   205,
     205,   206,   206,   207,   207,   207,   208,   208,   209,   209,
     210,   211,   211,   212,   212,   213,   213,   214,   214,   215,
     215,   216,   217,   217,   218,   218,   218,   219
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     7,     5,     5,
       4,     6,    10,     4,     2,     3,     3,     3,     3,     4,
       5,     6,     5,     4,     6,     8,     9,     7,     1,     7,
       5,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     7,     1,     1,     2,     1,
       5,     7,     3,     3,     3,     1,     1,     1,     5,     3,
       1,     1,     0,     0,     0,     0,     3,     0,     2,     0,
       3,     2,     1,     6,     1,     0,     3,     1,     0,     3,
       3,     0,     1,     0,     4,     1,     1,     1,     0,     1,
       1,     1,     1,     2,     2,     2,     0,     1,     2,     1,
       5,     1,     2,     1,     2,     1,    10,     5,     7,     9,
       4,     5,     1,     6,     8,     4,     4,     0,     2,     0,
       3,     1,     2,     1,     0,     3,     2,     1,     3,     1,
       3,     1,     3,     4,     3,     3,     2,     1,     2,     1,
       5,     7,     5,     7,     9,     3,     2,     2,     3,     1,
       1,     1,     0,     1,     0,     3,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     1,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     4,     6,     8,
       6,     4,     3,     3,     2,     2,     3,     1,     1,     3,
       4,     1,     3,     1,     1,     3,     1,     1,     2,     2,
       0,     5,     0,     2,     0,     3,     0,     2,     1,     4,
       1,     2,     3,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     1,     0,    63,     0,    62,    62,     0,     0,
      62,    62,    62,     0,     0,     0,     0,     0,     5,     0,
       0,     0,     0,     2,     6,     0,    28,     0,    37,    38,
      39,    35,    33,    34,    40,    36,    41,    42,    44,    44,
      32,    63,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,   242,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    67,
      88,    57,     0,    55,     0,    56,     0,     0,    65,     0,
       0,     0,     0,   246,    75,     0,     0,    17,    18,     0,
       0,    15,    16,     0,     0,     0,    10,     0,     0,     0,
       0,     0,     0,    87,     0,    77,    81,     0,     0,    53,
       0,    52,     0,    13,     0,    23,    65,     0,     0,     0,
       0,     0,    74,    75,    72,     0,    19,    46,    47,     0,
     112,     0,     0,     0,     0,     0,     0,    88,    43,     8,
       9,    65,     0,     0,     0,     0,     0,     0,   101,   105,
     103,     0,    65,    64,    88,    83,    96,    85,    86,    44,
      60,    61,    59,    54,    56,     0,     0,     0,    30,     0,
       0,    97,    99,     0,     0,    49,     0,   253,     0,   250,
       0,   248,     0,    20,    70,    71,     0,     0,     0,     0,
      22,     0,     0,     0,     0,    24,     0,     0,     0,     0,
       0,    65,   104,   102,   117,     4,     0,    76,    82,     0,
       0,    79,     0,     0,     0,     0,    65,    98,     0,    65,
      48,     0,     0,   251,     0,   245,   247,     0,    81,     0,
       0,     0,    21,    11,     0,    69,     0,     0,     0,     0,
       0,    27,     0,     0,   124,    65,    80,    95,    89,    91,
      90,    92,    93,    94,    84,    58,     0,     0,    51,     0,
      29,   241,     0,    31,   254,   255,   256,     0,   244,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
       0,   110,   233,   236,   237,     0,   154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   137,     0,   124,   206,
     208,   209,   207,   210,   211,     0,   149,     0,   123,   139,
       0,   156,   158,   171,   173,   175,   177,   179,   181,   183,
     186,   191,   194,   197,   201,     0,     0,     0,   202,   216,
     234,     0,    25,     0,     0,     0,   252,   249,     0,     0,
       0,     0,     0,    68,    65,   111,   107,     0,     0,     0,
     119,     0,   233,     0,   153,   147,   146,     0,   152,     0,
       0,     0,   203,   204,     0,     0,    66,   122,   138,   136,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     160,     0,   205,   201,     0,     0,   224,   225,     0,     0,
       0,   131,     0,   126,   127,   129,    45,   100,    50,   243,
      73,     0,   113,     0,    26,     0,     0,     0,     0,   116,
     125,   148,     0,   151,     0,   150,   145,     0,     0,   235,
     155,   157,   174,     0,   176,   178,   180,   182,   184,   185,
     189,   190,   187,   188,   192,   193,   195,   196,   198,   199,
     200,   159,     0,     0,   222,   227,     0,     0,   223,   212,
     213,   215,   214,     0,     0,     0,     0,     0,     0,    12,
     108,     0,     0,   240,   240,   118,   121,     0,   154,     0,
       0,     0,     0,     0,   221,     0,   217,   132,   128,   135,
       0,   134,     0,   228,   130,   114,     0,     0,   238,   239,
       0,     0,     0,   140,   142,   172,     0,     0,   226,   133,
     231,     0,     0,   109,   120,     0,   154,     0,   220,   218,
       0,     0,   229,     0,   143,     0,   141,     0,   230,   232,
       0,     0,   219,     0,   144,     0,   106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   179,    25,    38,    39,    65,    78,
     129,   174,   175,    26,    46,    47,    72,    73,    74,    75,
     162,    42,    40,   206,   115,   245,   102,   274,    85,   123,
     124,   125,   104,   105,   156,   209,   106,   159,   107,   253,
     211,   170,   171,   172,   147,   148,   349,   149,   150,   133,
     151,   243,   429,   485,   305,   306,   307,   413,   414,   415,
     308,   434,   353,   309,   310,   311,   401,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   472,   326,   327,   328,   466,   504,   521,   329,   330,
     486,   508,    83,   339,   121,   180,   181,   182,   223,   267,
     331
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -491
static const yytype_int16 yypact[] =
{
    -491,   395,  -491,     5,  -491,     3,  -491,  -491,    21,   -54,
    -491,  -491,  -491,    34,    63,    80,    38,    84,  -491,   121,
      52,   154,    92,  -491,  -491,   160,  -491,   185,  -491,  -491,
    -491,  -491,  -491,  -491,  -491,  -491,  -491,  -491,    48,    48,
    -491,  -491,   192,   198,   125,   220,   222,  -491,   141,   229,
     245,   257,   177,   174,   182,   235,   242,   188,   191,   -71,
     195,   196,   283,   199,   285,   289,   290,   174,   204,  -491,
      -8,   200,    31,  -491,   210,   211,   216,   291,  -491,   292,
     214,   215,   308,   224,   325,   239,    10,  -491,  -491,     8,
     306,  -491,  -491,   311,   312,   241,  -491,   232,   246,   248,
     251,   118,   252,  -491,    40,  -491,   240,   400,    12,  -491,
     220,  -491,   338,  -491,   249,  -491,  -491,   318,   323,   262,
      58,   270,  -491,    -2,  -491,   361,  -491,  -491,  -491,   277,
    -491,   279,   280,   284,   282,   296,   281,    -8,  -491,  -491,
    -491,  -491,   287,   293,   300,   301,   302,   303,   118,  -491,
    -491,   286,  -491,  -491,   392,   384,   314,  -491,  -491,    48,
    -491,  -491,  -491,  -491,  -491,   200,   317,   385,  -491,   402,
     309,   318,  -491,   409,   -20,  -491,   412,   327,   405,  -491,
      -6,  -491,   328,  -491,  -491,  -491,   421,   408,   339,   428,
    -491,   349,   345,   422,    47,  -491,     8,   437,   438,   444,
     436,  -491,  -491,  -491,   451,  -491,   359,  -491,  -491,   363,
     159,  -491,   458,   338,   368,   369,  -491,  -491,   380,  -491,
    -491,   386,   461,  -491,   462,  -491,  -491,    11,   240,   389,
     387,   388,  -491,  -491,   390,   393,   394,   397,   396,   398,
     403,  -491,   404,   407,   256,  -491,  -491,  -491,  -491,  -491,
    -491,  -491,  -491,  -491,  -491,  -491,   469,   118,  -491,   318,
    -491,  -491,   406,  -491,  -491,  -491,  -491,   410,   399,  -491,
     488,   470,   483,   498,   359,   414,   415,   487,   502,  -491,
     416,  -491,   503,  -491,  -491,   491,   304,   423,   424,   256,
     420,   507,   425,   426,   304,   304,  -491,   304,   256,  -491,
    -491,  -491,  -491,  -491,  -491,   123,  -491,   429,  -491,  -491,
     -21,  -491,  -491,   -64,   441,   417,   411,   418,   124,   -52,
     137,   136,    42,  -491,   401,   304,   430,   431,   -49,  -491,
    -491,    -1,  -491,   432,   427,   433,  -491,  -491,   519,   439,
     440,   434,   435,  -491,  -491,  -491,  -491,   442,   443,   445,
     446,   511,  -491,   447,   448,  -491,  -491,   468,   354,   449,
     304,   304,  -491,  -491,   108,   193,  -491,  -491,  -491,  -491,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
    -491,  -491,  -491,  -491,  -491,  -491,  -491,  -491,  -491,  -491,
    -491,   304,  -491,  -491,   304,   304,  -491,  -491,   244,   304,
     150,  -491,    -1,   450,  -491,   -11,  -491,  -491,  -491,  -491,
    -491,   452,  -491,   453,  -491,   457,   514,   521,   236,  -491,
    -491,  -491,   459,  -491,   463,   448,  -491,   109,   115,  -491,
    -491,  -491,   441,    -5,   417,   411,   418,   124,   -52,   -52,
     137,   137,   137,   137,   136,   136,    42,    42,  -491,  -491,
    -491,  -491,   455,   456,  -491,  -491,   130,   164,  -491,  -491,
    -491,  -491,  -491,     1,    -1,   464,   -17,   274,   465,  -491,
    -491,   460,   466,  -491,  -491,   467,  -491,   304,   304,   256,
     256,   304,   304,   304,  -491,   304,  -491,  -491,  -491,  -491,
     454,  -491,   274,  -491,  -491,  -491,   520,   471,  -491,  -491,
     236,   143,   472,   477,  -491,  -491,   144,   148,  -491,  -491,
    -491,     2,   473,  -491,  -491,   474,   304,   256,  -491,  -491,
     304,    55,  -491,   532,  -491,   475,  -491,   478,  -491,  -491,
     476,   256,  -491,   533,  -491,   480,  -491
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -491,  -491,  -491,  -491,  -491,  -491,   479,  -491,   -34,  -491,
    -491,  -491,   391,  -491,  -491,  -491,  -491,   481,  -491,   -85,
    -491,   187,   529,  -491,  -115,   297,  -491,  -491,   505,  -491,
     482,  -491,   484,   485,   347,  -491,  -491,  -491,  -491,  -491,
    -491,   320,  -491,   413,   324,  -491,  -491,   486,   489,   419,
    -491,  -491,  -491,  -491,   294,  -491,   225,  -491,   106,   170,
    -289,  -491,  -477,  -491,  -283,  -353,  -491,    94,  -491,   217,
     221,   213,   218,   219,  -108,  -206,  -111,  -110,  -317,  -266,
    -491,  -491,  -491,  -491,  -491,    97,  -490,  -491,  -491,  -491,
      86,   113,  -491,  -491,  -491,  -491,   490,  -491,  -491,  -491,
    -491
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -258
static const yytype_int16 yytable[] =
{
     357,   168,   122,   354,   177,    66,   103,   500,   402,   411,
     173,   512,   520,    41,   364,    27,   367,   441,   130,   371,
     127,   264,   160,   178,    91,   164,   195,   166,   362,   363,
      92,    44,   379,   380,   128,   265,   161,   205,   266,   406,
     407,   539,    45,   372,    52,   131,   132,   408,   461,   535,
     409,   462,   463,   381,   382,   465,    28,    29,    30,   403,
      31,    32,    33,    34,    35,   352,    36,    37,   177,   410,
     458,   459,   460,    53,   369,   435,   367,   437,   438,   283,
     370,    55,   284,   501,   219,   475,   241,   178,   476,   443,
     -78,   477,   491,   -78,    56,   412,   370,   475,   225,   497,
     476,   258,   184,   531,   260,   403,   532,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   403,   403,   403,   403,
     403,   403,   403,   403,   503,   212,   467,    54,   255,   109,
     332,    57,   110,   282,   142,   143,   144,   145,   153,   465,
     517,   154,   518,   294,   295,   235,    58,   283,   154,   503,
     284,   297,   285,    64,   146,   387,   388,   389,   502,   538,
     468,   469,   470,   471,    59,   299,   300,   301,   302,   247,
      62,   303,   304,   450,   451,   452,   453,   537,   503,   248,
     249,   250,   251,   252,    60,    61,   286,   287,   288,   289,
     290,   291,   292,   293,    43,    63,    48,    49,    50,    51,
     513,   514,    68,   282,   511,   354,   439,   489,    69,   370,
     370,   294,   295,   490,   377,   378,   370,   283,   296,   297,
     284,    70,   285,   383,   384,   403,   298,   366,   494,   424,
      71,   495,    76,   299,   300,   301,   302,    77,   536,   303,
     304,   525,   528,   354,   370,   495,   529,   385,   386,   530,
     483,   484,   544,    79,   352,    80,   286,   287,   288,   289,
     290,   291,   292,   293,   496,   370,   282,    81,   283,   448,
     449,   284,   454,   455,    82,   456,   457,    84,    86,    87,
     283,   294,   295,   284,   352,   285,    88,    90,   296,   297,
      89,    93,    94,    95,    96,    97,   298,   440,   283,    98,
      99,   284,   108,   299,   300,   301,   302,   101,   111,   303,
     304,   113,   112,   119,   352,   114,   116,   117,   118,   286,
     287,   288,   289,   290,   291,   292,   293,   120,   283,   122,
     134,   284,   294,   295,   126,   135,   136,   137,   138,   155,
     297,   139,   464,   140,   294,   295,   141,   152,   165,   169,
     167,   296,   297,   173,   299,   300,   301,   302,   176,   298,
     303,   304,   294,   295,   282,   183,   299,   300,   301,   302,
     297,   186,   303,   304,   187,   188,   189,   502,   283,   190,
     191,   284,   193,   196,   299,   300,   301,   302,   204,   197,
     303,   304,   294,   295,   192,     2,   198,   199,   200,     3,
     297,     4,     5,     6,     7,     8,   103,   201,   208,   214,
     157,   210,   215,   216,   299,   300,   301,   302,   213,   218,
     303,   304,   221,     9,    10,    11,   222,    12,    13,   224,
     227,   228,   229,   230,    14,    15,    16,    17,   231,    18,
      19,    20,   294,   295,   232,   233,   234,   237,   238,    21,
     297,    28,    29,    30,   239,    31,    32,    33,    34,    35,
     240,   242,   244,   246,   299,   300,   301,   302,   254,   256,
     303,   304,   257,   390,   391,   392,   393,   394,   395,   396,
     397,   398,   399,   259,   261,   262,   263,   269,   270,   271,
     273,   272,   275,   333,    22,   276,   338,   277,   340,   278,
     280,   279,   281,   400,   341,   337,   336,   342,   343,   345,
     346,   347,   348,  -257,   350,   351,   358,   359,   355,   356,
     375,   360,   361,   373,   368,   374,   404,   405,   376,   419,
     416,   417,   422,   423,   420,   430,   421,   418,   432,   426,
     425,   481,   431,   428,   436,   482,   427,   522,   527,   370,
     478,   474,   480,   479,   519,   487,   492,   493,   488,   540,
     545,   506,   499,   505,   507,   220,   523,   526,   510,   534,
      67,   344,   100,   541,   533,   268,   542,   543,   546,   335,
     498,   334,   473,   433,   217,   515,   158,   445,   442,   516,
       0,   163,   365,   446,   444,   447,   524,   509,     0,     0,
       0,     0,     0,     0,     0,   185,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   236,     0,     0,     0,     0,
       0,   194,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,   203,     0,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     226
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-491)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     289,   116,     4,   286,    10,    39,    14,    24,   325,    10,
      30,   488,   502,    10,   297,    10,   305,   370,    10,    83,
      10,    10,    10,    29,    95,   110,   141,   112,   294,   295,
     101,    10,    84,    85,    24,    24,    24,   152,    27,    88,
      89,   531,    96,   107,    10,    37,    38,    96,   401,   526,
      99,   404,   405,   105,   106,   408,    51,    52,    53,   325,
      55,    56,    57,    58,    59,    10,    61,    62,    10,   118,
     387,   388,   389,    10,    95,   358,   365,   360,   361,    24,
     101,    43,    27,   100,   104,    96,   201,    29,    99,   372,
      98,   102,    97,   101,    10,    96,   101,    96,   104,    98,
      99,   216,   104,   101,   219,   371,   104,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   477,   159,   409,    47,   213,    98,
     245,    10,   101,    10,    16,    17,    18,    19,    98,   492,
     493,   101,   495,    88,    89,    98,    94,    24,   101,   502,
      27,    96,    29,   105,    36,   113,   114,   115,   103,   104,
      10,    11,    12,    13,    10,   110,   111,   112,   113,    10,
      10,   116,   117,   379,   380,   381,   382,   530,   531,    20,
      21,    22,    23,    24,    92,    93,    63,    64,    65,    66,
      67,    68,    69,    70,     7,    10,     9,    10,    11,    12,
     489,   490,    10,    10,   487,   488,    98,    98,    10,   101,
     101,    88,    89,    98,    90,    91,   101,    24,    95,    96,
      27,    96,    29,    86,    87,   491,   103,   104,    98,   344,
      10,   101,    10,   110,   111,   112,   113,    96,   527,   116,
     117,    98,    98,   526,   101,   101,    98,   111,   112,   101,
      14,    15,   541,    24,    10,    10,    63,    64,    65,    66,
      67,    68,    69,    70,   100,   101,    10,    10,    24,   377,
     378,    27,   383,   384,    97,   385,   386,   103,    96,    44,
      24,    88,    89,    27,    10,    29,    44,    96,    95,    96,
     102,    96,    96,    10,    95,    10,   103,   104,    24,    10,
      10,    27,   102,   110,   111,   112,   113,   103,    98,   116,
     117,    95,   101,     5,    10,    24,    24,   103,   103,    63,
      64,    65,    66,    67,    68,    69,    70,   103,    24,     4,
      24,    27,    88,    89,    95,    24,    24,    96,   106,    99,
      96,    95,    98,    95,    88,    89,    95,    95,    10,    31,
     101,    95,    96,    30,   110,   111,   112,   113,    96,   103,
     116,   117,    88,    89,    10,    95,   110,   111,   112,   113,
      96,    10,   116,   117,    97,    96,    96,   103,    24,    95,
      98,    27,   101,    96,   110,   111,   112,   113,   102,    96,
     116,   117,    88,    89,    98,     0,    96,    96,    96,     4,
      96,     6,     7,     8,     9,    10,    14,   104,    24,    24,
      10,    97,    10,   104,   110,   111,   112,   113,   101,    10,
     116,   117,    10,    28,    29,    30,    99,    32,    33,    24,
     102,    10,    24,    94,    39,    40,    41,    42,    10,    44,
      45,    46,    88,    89,    95,   100,    24,    10,    10,    54,
      96,    51,    52,    53,    10,    55,    56,    57,    58,    59,
      24,    10,   103,   100,   110,   111,   112,   113,    10,   101,
     116,   117,   103,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,   103,    98,    24,    24,    98,   101,   101,
      97,   101,    98,    24,    99,    98,    97,   101,    10,   101,
      96,    98,    95,   102,    34,    95,   100,    24,    10,    95,
      95,    24,    10,    10,    98,    24,    96,    10,    95,    95,
     109,    96,    96,    82,    95,   108,    96,    96,   110,    10,
      98,   104,    98,    98,    95,    24,    96,   104,    70,    96,
      98,    27,    95,    97,    95,    24,   101,    27,    71,   101,
      98,   101,    95,   100,   100,    96,   101,   101,    95,    27,
      27,   101,    98,    98,    98,   174,    95,    95,   101,    95,
      41,   274,    67,    98,   101,   228,    98,   101,    98,   259,
     474,   257,   412,   358,   171,   491,   107,   374,   371,   492,
      -1,   110,   298,   375,   373,   376,   510,   484,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,    -1,
      -1,   137,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   148,    -1,    -1,   148,    -1,   154,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     180
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   120,     0,     4,     6,     7,     8,     9,    10,    28,
      29,    30,    32,    33,    39,    40,    41,    42,    44,    45,
      46,    54,    99,   121,   122,   124,   132,    10,    51,    52,
      53,    55,    56,    57,    58,    59,    61,    62,   125,   126,
     141,    10,   140,   140,    10,    96,   133,   134,   140,   140,
     140,   140,    10,    10,    47,    43,    10,    10,    94,    10,
      92,    93,    10,    10,   105,   127,   127,   141,    10,    10,
      96,    10,   135,   136,   137,   138,    10,    96,   128,    24,
      10,    10,    97,   211,   103,   147,    96,    44,    44,   102,
      96,    95,   101,    96,    96,    10,    95,    10,    10,    10,
     147,   103,   145,    14,   151,   152,   155,   157,   102,    98,
     101,    98,   101,    95,    24,   143,    24,   103,   103,     5,
     103,   213,     4,   148,   149,   150,    95,    10,    24,   129,
      10,    37,    38,   168,    24,    24,    24,    96,   106,    95,
      95,    95,    16,    17,    18,    19,    36,   163,   164,   166,
     167,   169,    95,    98,   101,    99,   153,    10,   125,   156,
      10,    24,   139,   136,   138,    10,   138,   101,   143,    31,
     160,   161,   162,    30,   130,   131,    96,    10,    29,   123,
     214,   215,   216,    95,   104,   149,    10,    97,    96,    96,
      95,    98,    98,   101,   151,   143,    96,    96,    96,    96,
      96,   104,   166,   167,   102,   143,   142,   152,    24,   154,
      97,   159,   127,   101,    24,    10,   104,   162,    10,   104,
     131,    10,    99,   217,    24,   104,   215,   102,    10,    24,
      94,    10,    95,   100,    24,    98,   168,    10,    10,    10,
      24,   143,    10,   170,   103,   144,   100,    10,    20,    21,
      22,    23,    24,   158,    10,   138,   101,   103,   143,   103,
     143,    98,    24,    24,    10,    24,    27,   218,   153,    98,
     101,   101,   101,    97,   146,    98,    98,   101,   101,    98,
      96,    95,    10,    24,    27,    29,    63,    64,    65,    66,
      67,    68,    69,    70,    88,    89,    95,    96,   103,   110,
     111,   112,   113,   116,   117,   173,   174,   175,   179,   182,
     183,   184,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   201,   202,   203,   207,
     208,   219,   143,    24,   163,   160,   100,    95,    97,   212,
      10,    34,    24,    10,   144,    95,    95,    24,    10,   165,
      98,    24,    10,   181,   183,    95,    95,   179,    96,    10,
      96,    96,   198,   198,   183,   173,   104,   179,    95,    95,
     101,    83,   107,    82,   108,   109,   110,    90,    91,    84,
      85,   105,   106,    86,    87,   111,   112,   113,   114,   115,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
     102,   185,   197,   198,    96,    96,    88,    89,    96,    99,
     118,    10,    96,   176,   177,   178,    98,   104,   104,    10,
      95,    96,    98,    98,   143,    98,    96,   101,    97,   171,
      24,    95,    70,   175,   180,   183,    95,   183,   183,    98,
     104,   184,   188,   183,   189,   190,   191,   192,   193,   193,
     194,   194,   194,   194,   195,   195,   196,   196,   197,   197,
     197,   184,   184,   184,    98,   184,   204,   183,    10,    11,
      12,    13,   200,   178,   101,    96,    99,   102,    98,   100,
      95,    27,    24,    14,    15,   172,   209,    96,    95,    98,
      98,    97,   101,   101,    98,   101,   100,    98,   177,    98,
      24,   100,   103,   184,   205,    98,   101,    98,   210,   210,
     101,   183,   181,   179,   179,   186,   204,   184,   184,   100,
     205,   206,    27,    95,   209,    98,    95,    71,    98,    98,
     101,   101,   104,   101,    95,   181,   179,   184,   104,   205,
      27,    98,    98,   101,   179,    27,    98
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
#line 317 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 322 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 326 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 329 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 332 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 335 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string texture_type=(yyvsp[(2) - (5)]).strs[0];
		GLTextureType type_enum = ToGLTextureType((yyvsp[(2) - (5)]).token);
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
		gEffect->declaredTextures[texture_name].type = type;
		gEffect->declaredTextures[texture_name].type_enum = type_enum;
		gEffect->m_sharedCode << decl.str(); 
		if(compute_only)
			gEffect->m_sharedCode<<"#endif\n";
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 368 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 384 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 390 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 394 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout.x=(yyvsp[(4) - (10)]).num;
		currentCsLayout.y=(yyvsp[(6) - (10)]).num;
		currentCsLayout.z=(yyvsp[(8) - (10)]).num;
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 400 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 403 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 409 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 415 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 421 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name					=(yyvsp[(2) - (3)]).strs[0];
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 425 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name		=(yyvsp[(2) - (3)]).strs[0];
		string str		=string("#undef ")+name+"\n";
		glfxWrite(str.c_str()); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 431 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 448 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).lineno		=(yyvsp[(4) - (5)]).lineno;
		RenderState t=renderState;
		string name=(yyvsp[(2) - (5)]).strs[0];
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
		int true_linenumber=(yyvsp[(4) - (5)]).lineno+(last_linenumber-global_linenumber);
	//	WriteLineNumber(true_linenumber);
	}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 488 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 498 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 517 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 520 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 535 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
		for(auto p=buildFunction.textureSamplersByTexture.begin();p!=buildFunction.textureSamplersByTexture.end();p++)
		{
			auto q=p->second.begin();
			if(q!=p->second.end())
			{
				string t=string(" ")+(*q)->textureName+" ";
				find_and_replace(f->content,t,(*q)->textureSamplerName());
			}
		}
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
							type = gEffect->declaredTextures[ts->textureName].type;
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
			// use the one in the stored function, which is permanent, not buildFunction, which is temporary.
			TextureSampler *ts=f->textureSamplers[i->first];
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
#line 659 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

		//ostringstream str;
		sh.function.textureSamplers					=buildFunction.textureSamplers;
		sh.function.textureSamplersByTexture		=buildFunction.textureSamplersByTexture;
		sh.function.textureSamplersBySampler		=buildFunction.textureSamplersBySampler;
		buildFunction.textureSamplers.clear();	// so the pointers won't be freed later.


		for(std::map<std::string,TextureSampler*>::const_iterator i=sh.function.textureSamplers.begin();i!=sh.function.textureSamplers.end();i++)
		{
			DeclareTextureSampler(i->second);
		}
		//gEffect->m_sharedCode<<str.str();

		buildFunction.clear();
		delete (yyvsp[(5) - (9)]).vars;
		
		gEffect->m_sharedCode<<"#line "<<(glfxget_lineno()+(last_linenumber-global_linenumber))<<" "<<current_filenumber<<endl;
	}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 693 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 698 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 701 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 709 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 716 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 722 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 727 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 733 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 739 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 744 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 749 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 46:
/* Line 1792 of yacc.c  */
#line 763 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 766 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 769 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 773 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 776 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 780 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 52:
/* Line 1792 of yacc.c  */
#line 790 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 794 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 799 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 803 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 807 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 811 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 815 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				currentCsLayout.x=(yyvsp[(1) - (5)]).num;
				currentCsLayout.y=(yyvsp[(3) - (5)]).num;
				currentCsLayout.z=(yyvsp[(5) - (5)]).num;
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 823 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				(yyval).num=(yyvsp[(3) - (3)]).num;
		   }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 829 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 833 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 837 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 844 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 851 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_function=true;
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 858 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 862 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 869 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 875 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
 }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 879 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
 }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 883 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="{\n";
	(yyval).strs[0]+=((yyvsp[(2) - (3)]).strs[0]+"\n}\n");
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 888 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string list			=(yyvsp[(1) - (2)]).strs[0];
	string new_member	=(yyvsp[(2) - (2)]).strs[0];
    (yyval).strs[0]=(list+"\n")+new_member;
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 894 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string member	=(yyvsp[(1) - (1)]).strs[0];
    (yyval).strs[0]=member;
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 899 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 74:
/* Line 1792 of yacc.c  */
#line 918 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="uniform";
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 922 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 926 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars		=(yyvsp[(1) - (3)]).vars;
		(yyval).strs[0]	=((yyvsp[(1) - (3)]).strs[0]+",")+(yyvsp[(3) - (3)]).strs[0];

		YYSTYPE::variable var;
		var.storage		=(yyvsp[(3) - (3)]).strs[1];
		var.type		=(yyvsp[(3) - (3)]).strs[2];
		var.identifier	=(yyvsp[(3) - (3)]).strs[3];
		var.semantic	=(yyvsp[(3) - (3)]).strs[4];
		var.type_enum = ToGLTextureType((yyvsp[(3) - (3)]).token);
		(yyval).vars->push_back(var);
		buildFunction.parameters.push_back(var);
	}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 940 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		YYSTYPE::variable var;
		string s1	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).strs[0]	=s1;
		var.storage		=(yyvsp[(1) - (1)]).strs[1];
		var.type		=(yyvsp[(1) - (1)]).strs[2];
		var.identifier	=(yyvsp[(1) - (1)]).strs[3];
		var.semantic	=(yyvsp[(1) - (1)]).strs[4];
		var.type_enum = ToGLTextureType((yyvsp[(1) - (1)]).token);
    
		(yyval).vars = new vector<YYSTYPE::variable>;
		(yyval).vars->push_back(var);
		buildFunction.parameters.push_back(var);
	}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 955 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 961 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
    (yyval).strs[0]	=all;
    (yyval).strs[1]	=storage;
    (yyval).strs[2]	=type;
    (yyval).strs[3]	=id;
	(yyval).token	=(yyvsp[(1) - (3)]).token;
    (yyval).strs[4]	=semantic;
}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 992 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 997 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 1002 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
			}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 1007 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
			}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 1012 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (4)]).strs[0];
		string type		=(yyvsp[(2) - (4)]).strs[0];
		string template_=(yyvsp[(3) - (4)]).strs[0];
		if(template_.length())
			type+=string("<")+template_+string(">");
		string id		=(yyvsp[(4) - (4)]).strs[0];
		string all		=(((yyvsp[(1) - (4)]).strs[0]+" ")+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+" ")+(yyvsp[(4) - (4)]).strs[0];
		(yyval).strs[0]		=all;
		(yyval).strs[1]		=storage;
		(yyval).strs[2]		=type;
		(yyval).strs[3]		=id;
		(yyval).token		=(yyvsp[(2) - (4)]).token;
	}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 1027 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1032 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1037 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1041 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1045 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1050 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1055 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1060 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1065 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1070 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1076 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1081 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1087 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1094 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 99:
/* Line 1792 of yacc.c  */
#line 1106 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 100:
/* Line 1792 of yacc.c  */
#line 1120 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable	= (yyvsp[(1) - (5)]).boolean;
	(yyval).prog					= (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0]				= (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1127 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders),buildPassState,gEffect->textureSamplersByShader);
    delete (yyvsp[(1) - (1)]).shaders;
	buildPassState			=PassState();
}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1134 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 103:
/* Line 1792 of yacc.c  */
#line 1144 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 104:
/* Line 1792 of yacc.c  */
#line 1157 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1165 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1173 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1182 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1186 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1192 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1200 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				errSem("Pass definitions like vs(430)=vs_main are no longer supported. Please use SetVertexShader() etc.");
			}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1205 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 112:
/* Line 1792 of yacc.c  */
#line 1279 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 113:
/* Line 1792 of yacc.c  */
#line 1291 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 114:
/* Line 1792 of yacc.c  */
#line 1311 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 115:
/* Line 1792 of yacc.c  */
#line 1347 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1358 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1364 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1368 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1372 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1377 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1382 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1386 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1395 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1401 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1406 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 126:
/* Line 1792 of yacc.c  */
#line 1419 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			stringReplaceAll(init_declarator_list,type_spec+type_spec,type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1428 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1432 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1436 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1440 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 131:
/* Line 1792 of yacc.c  */
#line 1478 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1482 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1486 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1491 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1495 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1499 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
					(yyval).strs[1]="";
				}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1505 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=";\n";
					(yyval).strs[1]="";
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1510 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1515 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
					(yyval).strs[1]="";
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1521 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1526 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string s1=(yyvsp[(1) - (7)]).strs[0];
					string s2=(yyvsp[(2) - (7)]).strs[0];
					string s3=(yyvsp[(3) - (7)]).strs[0];
					string s4=(yyvsp[(4) - (7)]).strs[0];
					string s5=(yyvsp[(5) - (7)]).strs[0];
					string s6=(yyvsp[(6) - (7)]).strs[0];
					string s7=(yyvsp[(7) - (7)]).strs[0];
					(yyval).strs[0]=(s1+s2+s3+s4+s5+s6+"\n")+s7;
					(yyval).strs[1]="";
				}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1538 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1543 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1548 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
					(yyval).strs[1]="";
				}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1554 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1559 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1564 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1569 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 149:
/* Line 1792 of yacc.c  */
#line 1584 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).strs[1]="";
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1590 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1594 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1598 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1601 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1605 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1610 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1616 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1620 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1624 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1628 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1632 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1645 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1649 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1653 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1658 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1662 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1666 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1670 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1674 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1678 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1682 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1690 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1694 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1699 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1703 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1707 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1711 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1715 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1719 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1723 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1727 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1731 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1735 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1739 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1743 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1747 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1751 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1755 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1759 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1763 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1767 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1771 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1775 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1779 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1783 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1787 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1791 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1795 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texture";
}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1799 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="textureLod";
}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1803 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 215:
/* Line 1792 of yacc.c  */
#line 1813 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 216:
/* Line 1792 of yacc.c  */
#line 1823 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[0];			//Command
					}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1828 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (4)]).strs[2];			//Command
					}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1833 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (6)]).strs[1];
						string x			=(yyvsp[(3) - (6)]).strs[0];
						string y			=(yyvsp[(5) - (6)]).strs[0];

						(yyval).strs[0]=GetSizeFunction( textureName, x, y,"");
					}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1841 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (8)]).strs[1];
						string x			=(yyvsp[(3) - (8)]).strs[0];
						string y			=(yyvsp[(5) - (8)]).strs[0];
						string z			=(yyvsp[(7) - (8)]).strs[0];
						(yyval).strs[0]=GetSizeFunction( textureName, x, y,z);
					}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1849 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName		=(yyvsp[(1) - (6)]).strs[1];
						string command			=(yyvsp[(1) - (6)]).strs[2];
						string samplerStateName	=(yyvsp[(3) - (6)]).strs[0];
						string otherParams		=(yyvsp[(5) - (6)]).strs[0];

						//
						if(!IsDeclared(samplerStateName))
						{
							errSem(string("Undeclared sampler state ")+samplerStateName);
						}
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

  case 221:
/* Line 1792 of yacc.c  */
#line 1892 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 222:
/* Line 1792 of yacc.c  */
#line 1957 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						// ok this could be a function call.
						string command=(yyvsp[(1) - (3)]).strs[2];
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1963 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[2]=expr3;			//Command
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1970 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1974 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 1978 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars=(yyvsp[(1) - (3)]).vars;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 1986 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars = new vector<YYSTYPE::variable>;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 1994 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 1999 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 2006 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 2013 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 2020 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 2027 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 2031 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 2035 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 2039 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 2043 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 2047 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 2055 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 2063 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 2067 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (5)]).strs[0];
						(yyval).num=0;
					}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 2072 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2076 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2080 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2084 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 2087 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 2091 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2096 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 2100 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 250:
/* Line 1792 of yacc.c  */
#line 2209 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 2214 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 2220 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 2225 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 2229 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 2234 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 2239 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 2244 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 5082 "src/glfxLALRParser.cpp"
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
#line 2247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


	GLTextureType ToGLTextureType(int t)
	{
		switch(t)
		{
		case TEXTURE2D:
			return gsampler2D;
		case TEXTURE2DMS:
			return gsampler2DMS;
		case TEXTURE3D:
			return gsampler3D;
		case TEXTURECUBE:
			return gsamplerCube;
		case RW_TEXTURE2D:
			return gimage2D;
		case IMAGE3D:
		case RW_TEXTURE3D:
		case RW_TEXTURE3D_FLOAT4:
			return gimage3D;
		case RW_TEXTURE2DARRAY:
			return gimage2DArray;
		default:
			return unknwownTextureType;
		};
	}
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
    throw std::runtime_error(errMsg.str());
}

void resetGlfxParse()
{
	buildFunction.clear();
	functions.clear();
	buildStruct					=Struct();
	gEffect->declaredTextures.clear();
	read_shader=false;
	read_function=false;
}
