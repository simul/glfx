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
		case gimage3D:
		case gimage2DArray:
		case gimage2DMSArray:
			return_size=3;
			break;
		default:
			break;
		}
		ostringstream full_expr;
		// NOTE the spaces around the textureName. We might need to replace it with a sampler name, so we make sure we can find it
		// as a whole word easily.
		full_expr<<"{ivec"<<return_size<<" iv=";
		
		switch(glTextureType)
		{
			case gimage1D:
			case gimage2D:
			case gimage3D:
			case gimageCube:
			case gimage2DRect:
			case gimage1DArray:
			case gimage2DArray:
			case gimageCubeArray:
			case gimageBuffer:
			case gimage2DMS:
			case gimage2DMSArray:
				full_expr<<"imageSize";
				break;
			default:
				full_expr<<"textureSize";
		break;
		}
		full_expr<<"( "<<textureName<<" ";
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
#line 396 "src/glfxLALRParser.cpp"

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
     SATURATE = 349,
     SHADER_PROFILE = 350
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
#line 557 "src/glfxLALRParser.cpp"

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
#define YYLAST   664

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  120
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  101
/* YYNRULES -- Number of rules.  */
#define YYNRULES  259
/* YYNRULES -- Number of states.  */
#define YYNSTATES  551

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   350

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   118,     2,     2,     2,   116,   111,     2,
      97,    99,   114,   112,   102,   113,   119,   115,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    98,    96,
     106,   103,   107,   108,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   100,     2,   101,   110,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   104,   109,   105,   117,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    16,    18,    26,    33,
      39,    44,    51,    62,    67,    70,    74,    78,    82,    86,
      91,    97,   104,   110,   115,   123,   132,   142,   150,   152,
     160,   166,   170,   173,   175,   177,   179,   181,   183,   185,
     187,   189,   191,   193,   197,   198,   206,   208,   210,   213,
     215,   221,   229,   233,   237,   241,   243,   245,   247,   253,
     257,   259,   261,   262,   263,   264,   265,   269,   270,   273,
     274,   278,   281,   283,   290,   292,   293,   297,   299,   300,
     304,   308,   309,   311,   312,   317,   319,   321,   323,   324,
     326,   328,   330,   332,   335,   338,   341,   342,   344,   347,
     349,   355,   357,   360,   362,   365,   367,   378,   384,   392,
     402,   407,   413,   415,   422,   431,   436,   441,   442,   445,
     446,   450,   452,   455,   457,   458,   462,   465,   467,   471,
     473,   477,   479,   483,   488,   492,   496,   499,   501,   504,
     506,   512,   520,   526,   534,   544,   548,   551,   554,   558,
     560,   562,   564,   565,   567,   568,   572,   574,   578,   580,
     584,   586,   588,   590,   592,   594,   596,   598,   600,   602,
     604,   606,   608,   614,   616,   620,   622,   626,   628,   632,
     634,   638,   640,   644,   646,   650,   654,   656,   660,   664,
     668,   672,   674,   678,   682,   684,   688,   692,   694,   698,
     702,   706,   708,   710,   713,   716,   719,   721,   723,   725,
     727,   729,   731,   733,   735,   739,   743,   745,   750,   757,
     766,   773,   778,   782,   786,   789,   792,   796,   798,   800,
     804,   809,   811,   815,   817,   819,   821,   825,   827,   829,
     832,   835,   836,   842,   843,   846,   849,   850,   854,   855,
     858,   860,   865,   867,   870,   874,   875,   877,   879,   881
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     121,     0,    -1,   121,   122,    -1,    -1,     9,   141,    10,
     146,    96,   144,    -1,    44,    -1,   123,    -1,    40,    47,
      97,   130,    98,    24,    99,    -1,     4,   126,   128,    10,
     212,    96,    -1,     4,   127,   128,    10,    96,    -1,     4,
      10,    10,    96,    -1,   100,    92,    97,    24,    99,   101,
      -1,   100,    93,    97,    24,   102,    24,   102,    24,    99,
     101,    -1,    28,   134,    10,    96,    -1,    28,   135,    -1,
      54,    10,    96,    -1,    54,    10,   102,    -1,    41,    43,
      44,    -1,    42,    10,    44,    -1,    39,    10,   148,    96,
      -1,    33,    10,   212,   214,    96,    -1,    46,    95,    97,
      24,    99,    96,    -1,    45,    10,   103,   169,    96,    -1,
      28,   141,   129,   144,    -1,     7,    10,   212,   142,   148,
      96,   144,    -1,    10,    10,    97,   152,    99,   143,   145,
     144,    -1,   125,    10,    10,    97,   152,    99,   147,   145,
     144,    -1,     8,   141,    10,   104,   164,   105,   144,    -1,
     133,    -1,    32,   141,    10,   104,   131,   105,   144,    -1,
      29,   141,    24,    24,   144,    -1,    29,    24,    24,    -1,
       6,   142,    -1,    56,    -1,    57,    -1,    55,    -1,    59,
      -1,    51,    -1,    52,    -1,    53,    -1,    58,    -1,    61,
      -1,    62,    -1,   106,    10,   107,    -1,    -1,    97,    24,
     102,    24,   102,    24,    99,    -1,    10,    -1,    24,    -1,
     131,   132,    -1,   132,    -1,    30,    10,   104,   161,   105,
      -1,    30,   141,    10,   104,   161,   105,   144,    -1,    97,
     138,    99,    -1,    97,   136,    99,    -1,   136,   102,   137,
      -1,   137,    -1,   139,    -1,    10,    -1,   139,   102,   139,
     102,   139,    -1,    10,   103,   140,    -1,    10,    -1,    24,
      -1,    -1,    -1,    -1,    -1,   104,   174,   105,    -1,    -1,
      98,    10,    -1,    -1,   104,   149,   105,    -1,   149,   150,
      -1,   150,    -1,   151,    10,    10,   154,   213,    96,    -1,
       4,    -1,    -1,   152,   102,   153,    -1,   153,    -1,    -1,
     156,   154,   160,    -1,   100,   155,   101,    -1,    -1,    24,
      -1,    -1,   158,   157,   128,    10,    -1,    10,    -1,   126,
      -1,    14,    -1,    -1,    20,    -1,    22,    -1,    21,    -1,
      23,    -1,    98,    24,    -1,    98,   159,    -1,    98,    10,
      -1,    -1,   162,    -1,   162,   163,    -1,   163,    -1,    31,
      10,   104,   164,   105,    -1,   165,    -1,   165,   168,    -1,
     168,    -1,   165,   167,    -1,   167,    -1,    10,    97,    27,
     102,    27,   102,    27,   102,    27,    99,    -1,    17,    97,
      10,    99,    96,    -1,    18,    97,    10,   102,    24,    99,
      96,    -1,    19,    97,    10,   102,   166,   102,    24,    99,
      96,    -1,   170,   103,   171,    96,    -1,    16,    97,   169,
      99,    96,    -1,    10,    -1,    38,    97,    10,   102,    34,
      99,    -1,    37,    97,    95,   102,    10,    97,    99,    99,
      -1,    36,    97,    24,    99,    -1,    10,    97,    99,   172,
      -1,    -1,    98,   173,    -1,    -1,   173,   102,   210,    -1,
     210,    -1,   174,   180,    -1,   180,    -1,    -1,    29,    24,
      24,    -1,   220,   177,    -1,   178,    -1,   177,   102,   178,
      -1,   179,    -1,   179,   103,   206,    -1,    10,    -1,    97,
     179,    99,    -1,   179,   100,    24,   101,    -1,   179,   100,
     101,    -1,   179,    97,    99,    -1,   184,    96,    -1,    96,
      -1,   176,    96,    -1,   183,    -1,    69,    97,   184,    99,
     180,    -1,    69,    97,   184,    99,   180,    71,   180,    -1,
      70,    97,   184,    99,   180,    -1,    66,   180,    70,    97,
     184,    99,    96,    -1,    67,    97,   181,    96,   182,    96,
     182,    99,   180,    -1,    68,    10,    96,    -1,    65,    96,
      -1,    64,    96,    -1,    63,   182,    96,    -1,   175,    -1,
     184,    -1,   176,    -1,    -1,   184,    -1,    -1,   104,   174,
     105,    -1,   185,    -1,   184,   102,   185,    -1,   187,    -1,
     199,   186,   185,    -1,   103,    -1,    72,    -1,    73,    -1,
      74,    -1,    75,    -1,    76,    -1,    77,    -1,    78,    -1,
      79,    -1,    80,    -1,    81,    -1,   188,    -1,   188,   108,
     184,    98,   187,    -1,   189,    -1,   188,    83,   189,    -1,
     190,    -1,   189,    82,   190,    -1,   191,    -1,   190,   109,
     191,    -1,   192,    -1,   191,   110,   192,    -1,   193,    -1,
     192,   111,   193,    -1,   194,    -1,   193,    90,   194,    -1,
     193,    91,   194,    -1,   195,    -1,   194,   106,   195,    -1,
     194,   107,   195,    -1,   194,    84,   195,    -1,   194,    85,
     195,    -1,   196,    -1,   195,    86,   196,    -1,   195,    87,
     196,    -1,   197,    -1,   196,   112,   197,    -1,   196,   113,
     197,    -1,   198,    -1,   197,   114,   198,    -1,   197,   115,
     198,    -1,   197,   116,   198,    -1,   199,    -1,   204,    -1,
      88,   199,    -1,    89,   199,    -1,   200,   198,    -1,   111,
      -1,   114,    -1,   112,    -1,   113,    -1,   117,    -1,   118,
      -1,    11,    -1,    12,    -1,   204,   119,   201,    -1,   204,
     119,    13,    -1,   208,    -1,   204,   100,   184,   101,    -1,
     203,    97,   185,   102,   185,    99,    -1,   203,    97,   185,
     102,   185,   102,   185,    99,    -1,   202,    97,   185,   102,
     205,    99,    -1,   204,    97,   205,    99,    -1,   204,    97,
      99,    -1,   204,   119,    10,    -1,   204,    88,    -1,   204,
      89,    -1,   205,   102,   185,    -1,   185,    -1,   185,    -1,
     104,   207,   105,    -1,   104,   207,   102,   105,    -1,   206,
      -1,   207,   102,   206,    -1,    10,    -1,    94,    -1,   209,
      -1,    97,   184,    99,    -1,    24,    -1,    27,    -1,    14,
     211,    -1,    15,   211,    -1,    -1,    98,     5,    97,    10,
      99,    -1,    -1,    98,    10,    -1,    98,   159,    -1,    -1,
     104,   215,   105,    -1,    -1,   215,   216,    -1,   216,    -1,
     217,   103,   219,    96,    -1,   124,    -1,    10,   218,    -1,
     100,    24,   101,    -1,    -1,    10,    -1,    24,    -1,    27,
      -1,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   340,   340,   341,   378,   382,   385,   388,   391,   424,
     440,   446,   450,   456,   459,   465,   471,   477,   481,   487,
     504,   544,   554,   573,   576,   593,   717,   751,   756,   759,
     767,   774,   780,   785,   785,   785,   785,   785,   785,   785,
     785,   791,   791,   797,   803,   807,   821,   824,   827,   831,
     834,   838,   848,   852,   857,   861,   865,   869,   873,   881,
     887,   891,   896,   903,   910,   917,   921,   928,   933,   938,
     941,   946,   952,   957,   976,   981,   984,   998,  1014,  1019,
    1050,  1056,  1060,  1066,  1070,  1092,  1097,  1102,  1107,  1110,
    1115,  1120,  1125,  1130,  1135,  1141,  1147,  1152,  1159,  1171,
    1185,  1192,  1199,  1209,  1222,  1230,  1238,  1247,  1251,  1257,
    1265,  1270,  1344,  1356,  1376,  1412,  1423,  1430,  1433,  1438,
    1442,  1447,  1451,  1460,  1467,  1471,  1484,  1493,  1497,  1501,
    1505,  1543,  1547,  1551,  1556,  1560,  1564,  1570,  1575,  1580,
    1586,  1591,  1603,  1608,  1613,  1619,  1624,  1629,  1634,  1649,
    1655,  1659,  1664,  1666,  1671,  1675,  1681,  1685,  1689,  1693,
    1697,  1701,  1702,  1703,  1704,  1705,  1706,  1707,  1708,  1709,
    1710,  1714,  1718,  1723,  1727,  1731,  1735,  1739,  1743,  1747,
    1751,  1755,  1759,  1764,  1768,  1772,  1776,  1780,  1784,  1788,
    1792,  1796,  1800,  1804,  1808,  1812,  1816,  1820,  1824,  1828,
    1832,  1836,  1840,  1844,  1848,  1852,  1856,  1856,  1856,  1856,
    1856,  1856,  1860,  1864,  1868,  1878,  1888,  1894,  1899,  1907,
    1915,  1958,  2023,  2029,  2036,  2040,  2044,  2052,  2060,  2065,
    2072,  2079,  2086,  2093,  2097,  2102,  2106,  2110,  2114,  2118,
    2126,  2135,  2138,  2151,  2155,  2159,  2164,  2167,  2171,  2174,
    2179,  2183,  2292,  2297,  2303,  2309,  2312,  2317,  2322,  2327
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
  "SATURATE", "SHADER_PROFILE", "';'", "'('", "':'", "')'", "'['", "']'",
  "','", "'='", "'{'", "'}'", "'<'", "'>'", "'?'", "'|'", "'^'", "'&'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'~'", "'!'", "'.'", "$accept",
  "prog", "tok", "line_statement", "ignore_line_statement",
  "shader_and_layout", "texture_type", "buffer_type",
  "optional_templateval", "layout_params", "warning-specifier",
  "technique_decls", "group_technique_decl", "technique_decl",
  "cs_layout_spec", "normal_layout_spec", "tx_layout", "layout_s",
  "cs_layout", "layout_el", "layout_def", "lex_fx", "shader_fx",
  "function_fx", "lex_passthrough", "function_content", "read_block",
  "optional_return_semantic", "struct_definition", "struct_member_list",
  "struct_memb", "optional_uniform", "param_declaration_list",
  "param_declaration", "opt_sq", "opt_num", "param", "type_name",
  "opt_storage", "input_semantic", "location", "tech_def", "pass_list",
  "pass_def", "prog_def", "shaders_list", "vec4", "shader_fn",
  "shader_def", "shader_compile", "shader_lvalue", "shader_rvalue",
  "shader_layout", "shader_layout_list", "statement_list",
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
  "optional_register_semantic", "optional_semantic",
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
     345,   346,   347,   348,   349,   350,    59,    40,    58,    41,
      91,    93,    44,    61,   123,   125,    60,    62,    63,   124,
      94,    38,    43,    45,    42,    47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     123,   124,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   127,   128,   128,   129,   130,   130,   131,   131,
     132,   133,   134,   135,   136,   136,   137,   137,   138,   139,
     140,   140,   141,   142,   143,   144,   145,   146,   147,   147,
     148,   149,   149,   150,   151,   151,   152,   152,   152,   153,
     154,   154,   155,   155,   156,   157,   157,   158,   158,   159,
     159,   159,   159,   160,   160,   160,   160,   161,   162,   162,
     163,   164,   165,   165,   165,   165,   166,   167,   167,   167,
     168,   168,   169,   169,   169,   170,   171,   171,   172,   172,
     173,   173,   174,   174,   174,   175,   176,   177,   177,   178,
     178,   179,   179,   179,   179,   179,   180,   180,   180,   180,
     180,   180,   180,   180,   180,   180,   180,   180,   180,   180,
     181,   181,   181,   182,   182,   183,   184,   184,   185,   185,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   187,   187,   188,   188,   189,   189,   190,   190,   191,
     191,   192,   192,   193,   193,   193,   194,   194,   194,   194,
     194,   195,   195,   195,   196,   196,   196,   197,   197,   197,
     197,   198,   199,   199,   199,   199,   200,   200,   200,   200,
     200,   200,   201,   201,   202,   203,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   205,   205,   206,   206,
     206,   207,   207,   208,   208,   208,   208,   209,   209,   210,
     210,   211,   212,   212,   213,   213,   213,   214,   214,   215,
     215,   216,   216,   217,   218,   218,   219,   219,   219,   220
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     7,     6,     5,
       4,     6,    10,     4,     2,     3,     3,     3,     3,     4,
       5,     6,     5,     4,     7,     8,     9,     7,     1,     7,
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
       4,     1,     3,     1,     1,     1,     3,     1,     1,     2,
       2,     0,     5,     0,     2,     2,     0,     3,     0,     2,
       1,     4,     1,     2,     3,     0,     1,     1,     1,     1
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
      32,   243,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,   243,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,     0,
      67,    88,    57,     0,    55,     0,    56,     0,     0,    65,
       0,     0,     0,   248,    75,     0,     0,    17,    18,     0,
       0,    15,    16,     0,     0,     0,    10,     0,   243,     0,
       0,     0,     0,     0,    87,     0,    77,    81,     0,     0,
      53,     0,    52,     0,    13,     0,    23,    65,     0,     0,
       0,     0,    74,    75,    72,     0,    19,    46,    47,     0,
     112,     0,     0,     0,     0,     0,     0,    88,    43,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     105,   103,     0,    65,    64,    88,    83,    96,    85,    86,
      44,    60,    61,    59,    54,    56,     0,     0,     0,    30,
       0,     0,    97,    99,     0,     0,    49,   255,     0,   252,
       0,   250,     0,    20,    70,    71,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     8,     0,    65,     0,     0,
       0,     0,     0,    65,   104,   102,   117,     4,     0,    76,
      82,     0,     0,    79,     0,     0,     0,     0,    65,    98,
       0,    65,    48,     0,   253,     0,   247,   249,     0,    81,
       0,     0,     0,    21,    11,     0,    69,   242,    24,     0,
       0,     0,     0,     0,    27,     0,     0,   124,    65,    80,
      95,    89,    91,    90,    92,    93,    94,    84,    58,     0,
       0,    51,     0,    29,     0,    31,   256,   257,   258,     0,
     246,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,     0,   110,   233,   237,   238,     0,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   234,   137,
       0,   124,   206,   208,   209,   207,   210,   211,     0,   149,
       0,   123,   139,     0,   156,   158,   171,   173,   175,   177,
     179,   181,   183,   186,   191,   194,   197,   201,     0,     0,
       0,   202,   216,   235,     0,    25,     0,     0,     0,   254,
     251,     0,     0,     0,     0,     0,    68,    65,   111,   107,
       0,     0,     0,   119,     0,   233,     0,   153,   147,   146,
       0,   152,     0,     0,     0,   203,   204,     0,     0,    66,
     122,   138,   136,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   160,     0,   205,   201,     0,     0,   224,
     225,     0,     0,     0,   131,     0,   126,   127,   129,    45,
     100,    50,   244,   245,    73,     0,   113,     0,    26,     0,
       0,     0,     0,   116,   125,   148,     0,   151,     0,   150,
     145,     0,     0,   236,   155,   157,   174,     0,   176,   178,
     180,   182,   184,   185,   189,   190,   187,   188,   192,   193,
     195,   196,   198,   199,   200,   159,     0,     0,   222,   227,
       0,     0,   223,   212,   213,   215,   214,     0,     0,     0,
       0,     0,     0,    12,   108,     0,     0,   241,   241,   118,
     121,     0,   154,     0,     0,     0,     0,     0,   221,     0,
     217,   132,   128,   135,     0,   134,     0,   228,   130,   114,
       0,     0,   239,   240,     0,     0,     0,   140,   142,   172,
       0,     0,   226,   133,   231,     0,     0,   109,   120,     0,
     154,     0,   220,   218,     0,     0,   229,     0,   143,     0,
     141,     0,   230,   232,     0,     0,   219,     0,   144,     0,
     106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   179,    25,    38,    39,    65,    79,
     129,   175,   176,    26,    46,    47,    73,    74,    75,    76,
     163,    42,    40,   208,   116,   248,   103,   276,    85,   123,
     124,   125,   105,   106,   157,   211,   107,   160,   108,   256,
     213,   171,   172,   173,   148,   149,   352,   150,   151,   133,
     152,   246,   433,   489,   308,   309,   310,   416,   417,   418,
     311,   438,   356,   312,   313,   314,   404,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   476,   329,   330,   331,   470,   508,   525,   332,   333,
     490,   512,    68,   342,   121,   180,   181,   182,   224,   269,
     334
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -496
static const yytype_int16 yypact[] =
{
    -496,   397,  -496,     8,  -496,    20,  -496,  -496,    52,     0,
    -496,  -496,  -496,    93,   123,    96,    56,   135,  -496,   140,
      84,   176,   -20,  -496,  -496,   224,  -496,   239,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   133,   133,
    -496,   182,   246,   263,   189,   278,   280,  -496,   198,   279,
     300,   301,   182,   216,   233,   287,   289,   231,   247,   -74,
     248,   256,   346,   264,   349,   351,   354,   360,  -496,   270,
    -496,   -10,   265,   -11,  -496,   268,   275,   283,   361,  -496,
     371,   292,   294,   296,   404,   288,    10,  -496,  -496,     4,
     385,  -496,  -496,   386,   387,   315,  -496,   306,   182,   318,
     323,   216,   181,   319,  -496,    -1,  -496,   321,   284,    19,
    -496,   278,  -496,   414,  -496,   326,  -496,  -496,   400,   402,
       2,   337,  -496,    21,  -496,   424,  -496,  -496,  -496,   342,
    -496,   338,   347,   350,   348,   363,   343,   -10,  -496,   352,
    -496,   439,   367,   353,   369,   370,   372,   373,   359,   181,
    -496,  -496,   362,  -496,  -496,   454,   447,   374,  -496,  -496,
     133,  -496,  -496,  -496,  -496,  -496,   265,   375,   449,  -496,
     464,   376,   400,  -496,   465,   -22,  -496,   378,   452,  -496,
      -5,  -496,   377,  -496,  -496,  -496,   469,   458,   389,   475,
    -496,   390,   388,   463,    81,  -496,   391,  -496,     4,   478,
     481,   482,   470,  -496,  -496,  -496,   483,  -496,   392,  -496,
    -496,   394,   368,  -496,   488,   414,   398,   395,  -496,  -496,
     399,  -496,  -496,   477,  -496,   480,  -496,  -496,     9,   321,
     403,   405,   406,  -496,  -496,   407,   408,  -496,  -496,   411,
     412,   410,   413,   415,  -496,   416,   409,   258,  -496,  -496,
    -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,  -496,   492,
     181,  -496,   400,  -496,   417,  -496,  -496,  -496,  -496,   421,
     422,  -496,   509,   487,   498,   513,   392,   428,   429,   502,
     517,  -496,   430,  -496,   518,  -496,  -496,   506,    47,   435,
     436,   258,   437,   523,   438,   440,    47,    47,  -496,  -496,
      47,   258,  -496,  -496,  -496,  -496,  -496,  -496,   124,  -496,
     442,  -496,  -496,   -16,  -496,  -496,   -70,   457,   427,   431,
     432,    76,    89,    51,   120,   100,  -496,   380,    47,   443,
     445,   -44,  -496,  -496,    -4,  -496,   446,   441,   444,  -496,
    -496,   328,   448,   450,   451,   453,  -496,  -496,  -496,  -496,
     455,   456,   459,   460,   524,  -496,   461,   462,  -496,  -496,
     485,   305,   466,    47,    47,  -496,  -496,    82,   195,  -496,
    -496,  -496,  -496,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,    47,  -496,  -496,  -496,  -496,  -496,  -496,  -496,
    -496,  -496,  -496,  -496,    47,  -496,  -496,    47,    47,  -496,
    -496,   158,    47,   118,  -496,    -4,   467,  -496,   -51,  -496,
    -496,  -496,  -496,  -496,  -496,   468,  -496,   471,  -496,   472,
     529,   527,   229,  -496,  -496,  -496,   473,  -496,   479,   462,
    -496,   102,   128,  -496,  -496,  -496,   457,   -63,   427,   431,
     432,    76,    89,    89,    51,    51,    51,    51,   120,   120,
     100,   100,  -496,  -496,  -496,  -496,   474,   476,  -496,  -496,
     149,   165,  -496,  -496,  -496,  -496,  -496,    57,    -4,   484,
     -17,   269,   486,  -496,  -496,   489,   490,  -496,  -496,   491,
    -496,    47,    47,   258,   258,    47,    47,    47,  -496,    47,
    -496,  -496,  -496,  -496,   493,  -496,   269,  -496,  -496,  -496,
     532,   494,  -496,  -496,   229,   151,   496,   495,  -496,  -496,
     175,   179,  -496,  -496,  -496,   121,   497,  -496,  -496,   499,
      47,   258,  -496,  -496,    47,    58,  -496,   533,  -496,   501,
    -496,   503,  -496,  -496,   504,   258,  -496,   536,  -496,   505,
    -496
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -496,  -496,  -496,  -496,  -496,  -496,   500,  -496,   -37,  -496,
    -496,  -496,   396,  -496,  -496,  -496,  -496,   507,  -496,   -90,
    -496,   307,   511,  -496,  -116,   297,  -496,  -496,   508,  -496,
     510,  -496,   512,   419,   336,  -496,  -496,  -496,  -496,   236,
    -496,   320,  -496,   425,   324,  -496,  -496,   514,   515,   382,
    -496,  -496,  -496,  -496,   285,  -496,   220,  -496,   109,   173,
    -291,  -496,  -482,  -496,  -285,  -357,  -496,   101,  -496,   227,
     222,   226,   232,   228,   -83,  -174,   -85,   -84,  -296,  -270,
    -496,  -496,  -496,  -496,  -496,   115,  -495,  -496,  -496,  -496,
      91,   125,   -43,  -496,  -496,  -496,   434,  -496,  -496,  -496,
    -496
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -260
static const yytype_int16 yytable[] =
{
     360,   169,    66,   357,   104,   177,   414,   504,   174,    83,
     516,   524,   177,   374,   130,   367,   445,   370,    27,   266,
     127,   165,    91,   167,   178,   122,   365,   366,    92,   161,
      41,   178,   405,   267,   128,   495,   268,   207,   375,   373,
     543,   131,   132,   162,   409,   410,   479,   465,   539,   480,
     466,   467,   481,   411,   469,   139,   412,   355,   406,    28,
      29,    30,    44,    31,    32,    33,    34,    35,   355,    36,
      37,   285,    60,    61,   286,   413,   439,   370,   441,   442,
     372,   238,   285,   221,   505,   286,   373,   244,   110,   -78,
     447,   111,   -78,   415,   462,   463,   464,    45,   154,    55,
     226,   155,   261,    52,   406,   263,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   214,   507,   258,   184,   471,   472,   473,
     474,   475,   335,    53,   284,   296,   297,   386,   387,   469,
     521,   298,   522,    54,   300,    56,   296,   297,   285,   507,
      57,   286,   298,   287,   479,   300,   501,   480,   302,   303,
     304,   305,   506,   542,   306,   307,   380,   381,   355,   302,
     303,   304,   305,   382,   383,   306,   307,   541,   507,    58,
     236,   443,   285,   155,   373,   286,    59,   288,   289,   290,
     291,   292,   293,   294,   295,   384,   385,   143,   144,   145,
     146,   493,   517,   518,   373,   284,   515,   357,   454,   455,
     456,   457,   296,   297,   390,   391,   392,   147,   298,   285,
     299,   300,   286,   535,   287,   406,   536,   494,   301,   369,
     373,   428,   388,   389,    62,   302,   303,   304,   305,    64,
     540,   306,   307,   487,   488,   357,   296,   297,   498,    63,
     529,   499,   298,   373,   548,   300,    69,   468,   288,   289,
     290,   291,   292,   293,   294,   295,   500,   373,   284,   302,
     303,   304,   305,    70,   532,   306,   307,   499,   533,   355,
      67,   534,   285,   296,   297,   286,    71,   287,    72,   298,
      77,   299,   300,   285,   158,    78,   286,   452,   453,   301,
     444,   458,   459,    80,   460,   461,   302,   303,   304,   305,
      81,    82,   306,   307,    43,   284,    48,    49,    50,    51,
      84,   288,   289,   290,   291,   292,   293,   294,   295,   285,
      86,    87,   286,    88,    89,    28,    29,    30,   422,    31,
      32,    33,    34,    35,    90,    93,   296,   297,   251,   252,
     253,   254,   298,    94,   299,   300,    95,   296,   297,    97,
      96,    98,   301,   298,    99,   100,   300,   112,   109,   302,
     303,   304,   305,   506,   102,   306,   307,   113,   250,   114,
     302,   303,   304,   305,   126,   115,   306,   307,   251,   252,
     253,   254,   255,   296,   297,   117,   118,     2,   119,   298,
     120,     3,   300,     4,     5,     6,     7,     8,   122,   134,
     135,   136,   137,   138,   140,   153,   302,   303,   304,   305,
     141,   156,   306,   307,   166,     9,    10,    11,   168,    12,
      13,   170,   174,   183,   186,   188,    14,    15,    16,    17,
     187,    18,    19,    20,   189,   193,   190,   191,   195,   196,
     198,    21,   393,   394,   395,   396,   397,   398,   399,   400,
     401,   402,   192,   197,   203,   206,   199,   200,   104,   201,
     202,   210,   212,   216,   217,   220,   225,   215,   223,   229,
     228,   218,   230,   403,   231,   232,   233,   235,   240,   234,
     237,   241,   242,   245,   243,   249,   247,    22,   257,   260,
     259,   264,   271,   262,   265,   283,   275,   272,   273,   274,
     277,   278,   279,   282,   281,   280,   336,   340,   339,   343,
     341,   344,   345,   346,   348,   349,   350,   351,  -259,   353,
     354,   358,   359,   362,   361,   363,   377,   364,   371,   376,
     407,   378,   408,   379,   424,   419,   420,   425,   434,   421,
     426,   486,   427,   430,   429,   436,   485,   435,   432,   526,
     544,   431,   440,   549,   373,   270,   531,   482,   484,   478,
     491,   222,   483,   347,   209,   492,   496,   423,   497,   101,
     239,   437,   338,   503,   337,   509,   368,   502,   477,   511,
     527,   510,   530,   514,   523,   538,   519,   219,   448,   537,
     545,   446,   546,   449,   550,   528,   547,   451,   159,   142,
     450,   520,     0,   513,   227,     0,     0,     0,   164,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   204,   205
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-496)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     291,   117,    39,   288,    14,    10,    10,    24,    30,    52,
     492,   506,    10,    83,    10,   300,   373,   308,    10,    10,
      10,   111,    96,   113,    29,     4,   296,   297,   102,    10,
      10,    29,   328,    24,    24,    98,    27,   153,   108,   102,
     535,    37,    38,    24,    88,    89,    97,   404,   530,   100,
     407,   408,   103,    97,   411,    98,   100,    10,   328,    51,
      52,    53,    10,    55,    56,    57,    58,    59,    10,    61,
      62,    24,    92,    93,    27,   119,   361,   368,   363,   364,
      96,   197,    24,   105,   101,    27,   102,   203,    99,    99,
     375,   102,   102,    97,   390,   391,   392,    97,    99,    43,
     105,   102,   218,    10,   374,   221,   376,   377,   378,   379,
     380,   381,   382,   383,   384,   385,   386,   387,   388,   389,
     390,   391,   392,   160,   481,   215,   105,   412,    10,    11,
      12,    13,   248,    10,    10,    88,    89,    86,    87,   496,
     497,    94,   499,    47,    97,    10,    88,    89,    24,   506,
      10,    27,    94,    29,    97,    97,    99,   100,   111,   112,
     113,   114,   104,   105,   117,   118,    90,    91,    10,   111,
     112,   113,   114,    84,    85,   117,   118,   534,   535,    95,
      99,    99,    24,   102,   102,    27,    10,    63,    64,    65,
      66,    67,    68,    69,    70,   106,   107,    16,    17,    18,
      19,    99,   493,   494,   102,    10,   491,   492,   382,   383,
     384,   385,    88,    89,   114,   115,   116,    36,    94,    24,
      96,    97,    27,   102,    29,   495,   105,    99,   104,   105,
     102,   347,   112,   113,    10,   111,   112,   113,   114,   106,
     531,   117,   118,    14,    15,   530,    88,    89,    99,    10,
      99,   102,    94,   102,   545,    97,    10,    99,    63,    64,
      65,    66,    67,    68,    69,    70,   101,   102,    10,   111,
     112,   113,   114,    10,    99,   117,   118,   102,    99,    10,
      98,   102,    24,    88,    89,    27,    97,    29,    10,    94,
      10,    96,    97,    24,    10,    97,    27,   380,   381,   104,
     105,   386,   387,    24,   388,   389,   111,   112,   113,   114,
      10,    10,   117,   118,     7,    10,     9,    10,    11,    12,
     104,    63,    64,    65,    66,    67,    68,    69,    70,    24,
      97,    44,    27,    44,   103,    51,    52,    53,    10,    55,
      56,    57,    58,    59,    97,    97,    88,    89,    20,    21,
      22,    23,    94,    97,    96,    97,    10,    88,    89,    10,
      96,    10,   104,    94,    10,     5,    97,    99,   103,   111,
     112,   113,   114,   104,   104,   117,   118,   102,    10,    96,
     111,   112,   113,   114,    96,    24,   117,   118,    20,    21,
      22,    23,    24,    88,    89,    24,   104,     0,   104,    94,
     104,     4,    97,     6,     7,     8,     9,    10,     4,    24,
      24,    24,    97,   107,    96,    96,   111,   112,   113,   114,
      97,   100,   117,   118,    10,    28,    29,    30,   102,    32,
      33,    31,    30,    96,    10,    97,    39,    40,    41,    42,
      98,    44,    45,    46,    97,   102,    96,    99,    96,    10,
      97,    54,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    99,    96,   105,   103,    97,    97,    14,    97,
      97,    24,    98,    24,    10,    10,    24,   102,   100,    10,
     103,   105,    24,   103,    95,    10,    96,    24,    10,   101,
      99,    10,    10,    10,    24,   101,   104,   100,    10,   104,
     102,    24,    99,   104,    24,    96,    98,   102,   102,   102,
      99,    99,   102,    97,    99,   102,    24,    96,   101,    10,
      98,    34,    24,    10,    96,    96,    24,    10,    10,    99,
      24,    96,    96,    10,    97,    97,   109,    97,    96,    82,
      97,   110,    97,   111,    96,    99,   105,    97,    24,   105,
      99,    24,    99,    97,    99,    70,    27,    96,    98,    27,
      27,   102,    96,    27,   102,   229,    71,    99,    96,   102,
      97,   175,   101,   276,   155,    96,   102,   341,   102,    68,
     198,   361,   262,    99,   260,    99,   301,   478,   415,    99,
      96,   102,    96,   102,   101,    96,   495,   172,   376,   102,
      99,   374,    99,   377,    99,   514,   102,   379,   108,   101,
     378,   496,    -1,   488,   180,    -1,    -1,    -1,   111,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   149
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   121,     0,     4,     6,     7,     8,     9,    10,    28,
      29,    30,    32,    33,    39,    40,    41,    42,    44,    45,
      46,    54,   100,   122,   123,   125,   133,    10,    51,    52,
      53,    55,    56,    57,    58,    59,    61,    62,   126,   127,
     142,    10,   141,   141,    10,    97,   134,   135,   141,   141,
     141,   141,    10,    10,    47,    43,    10,    10,    95,    10,
      92,    93,    10,    10,   106,   128,   128,    98,   212,    10,
      10,    97,    10,   136,   137,   138,   139,    10,    97,   129,
      24,    10,    10,   212,   104,   148,    97,    44,    44,   103,
      97,    96,   102,    97,    97,    10,    96,    10,    10,    10,
       5,   142,   104,   146,    14,   152,   153,   156,   158,   103,
      99,   102,    99,   102,    96,    24,   144,    24,   104,   104,
     104,   214,     4,   149,   150,   151,    96,    10,    24,   130,
      10,    37,    38,   169,    24,    24,    24,    97,   107,   212,
      96,    97,   148,    16,    17,    18,    19,    36,   164,   165,
     167,   168,   170,    96,    99,   102,   100,   154,    10,   126,
     157,    10,    24,   140,   137,   139,    10,   139,   102,   144,
      31,   161,   162,   163,    30,   131,   132,    10,    29,   124,
     215,   216,   217,    96,   105,   150,    10,    98,    97,    97,
      96,    99,    99,   102,   152,    96,    10,    96,    97,    97,
      97,    97,    97,   105,   167,   168,   103,   144,   143,   153,
      24,   155,    98,   160,   128,   102,    24,    10,   105,   163,
      10,   105,   132,   100,   218,    24,   105,   216,   103,    10,
      24,    95,    10,    96,   101,    24,    99,    99,   144,   169,
      10,    10,    10,    24,   144,    10,   171,   104,   145,   101,
      10,    20,    21,    22,    23,    24,   159,    10,   139,   102,
     104,   144,   104,   144,    24,    24,    10,    24,    27,   219,
     154,    99,   102,   102,   102,    98,   147,    99,    99,   102,
     102,    99,    97,    96,    10,    24,    27,    29,    63,    64,
      65,    66,    67,    68,    69,    70,    88,    89,    94,    96,
      97,   104,   111,   112,   113,   114,   117,   118,   174,   175,
     176,   180,   183,   184,   185,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   202,
     203,   204,   208,   209,   220,   144,    24,   164,   161,   101,
      96,    98,   213,    10,    34,    24,    10,   145,    96,    96,
      24,    10,   166,    99,    24,    10,   182,   184,    96,    96,
     180,    97,    10,    97,    97,   199,   199,   184,   174,   105,
     180,    96,    96,   102,    83,   108,    82,   109,   110,   111,
      90,    91,    84,    85,   106,   107,    86,    87,   112,   113,
     114,   115,   116,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,   103,   186,   198,   199,    97,    97,    88,
      89,    97,   100,   119,    10,    97,   177,   178,   179,    99,
     105,   105,    10,   159,    96,    97,    99,    99,   144,    99,
      97,   102,    98,   172,    24,    96,    70,   176,   181,   184,
      96,   184,   184,    99,   105,   185,   189,   184,   190,   191,
     192,   193,   194,   194,   195,   195,   195,   195,   196,   196,
     197,   197,   198,   198,   198,   185,   185,   185,    99,   185,
     205,   184,    10,    11,    12,    13,   201,   179,   102,    97,
     100,   103,    99,   101,    96,    27,    24,    14,    15,   173,
     210,    97,    96,    99,    99,    98,   102,   102,    99,   102,
     101,    99,   178,    99,    24,   101,   104,   185,   206,    99,
     102,    99,   211,   211,   102,   184,   182,   180,   180,   187,
     205,   185,   185,   101,   206,   207,    27,    96,   210,    99,
      96,    71,    99,    99,   102,   102,   105,   102,    96,   182,
     180,   185,   105,   206,    27,    99,    99,   102,   180,    27,
      99
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
#line 341 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream

		gEffect->m_sharedCode<<"#define GLSL\n";
		gEffect->m_sharedCode<<"float saturate(float x)"
						"{"
						"	return clamp(x,0.0,1.0);"
						"}"
						""
						"vec2 saturate(vec2 x)"
						"{"
						"	return clamp(x,vec2(0.0,0.0),vec2(1.0,1.0));"
						"}"
						""
						"vec3 saturate(vec3 x)"
						"{"
						"	return clamp(x,vec3(0.0,0.0,0.0),vec3(1.0,1.0,1.0));"
						"}"
						""
						"vec4 saturate(vec4 x)"
						"{"
						"	return clamp(x,vec4(0.0,0.0,0.0,0.0),vec4(1.0,1.0,1.0,1.0));"
						"}\n";
		

	gEffect->m_sharedCode<<"vec4 mul(mat4 m,vec4 v)"
							"{"
							"	return m*v;"
							"}"
							"vec3 mul(mat3 m,vec3 v)"
							"{"
							"	return m*v;"
							"}"
							"vec2 mul(mat2 m,vec2 v)"
							"{"
							"	return m*v;"
							"}\n";
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 379 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 383 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 386 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 389 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 392 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string texture_type=(yyvsp[(2) - (6)]).strs[0];
		GLTextureType type_enum = ToGLTextureType((yyvsp[(2) - (6)]).token);
		bool compute_only=(texture_type==string("image3D"))||(texture_type.substr(0,2)==string("RW"));
		
		stringReplaceAll(texture_type,"RWTexture","image");
		ostringstream decl;
		if(compute_only)
			gEffect->m_sharedCode<<"#ifdef IN_COMPUTE_SHADER\n";
		string template_type=(yyvsp[(3) - (6)]).strs[0];
		string texture_name=(yyvsp[(4) - (6)]).strs[0];
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
#line 425 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 441 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 447 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 451 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout.x=(yyvsp[(4) - (10)]).num;
		currentCsLayout.y=(yyvsp[(6) - (10)]).num;
		currentCsLayout.z=(yyvsp[(8) - (10)]).num;
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 457 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 460 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 466 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 472 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 478 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name					=(yyvsp[(2) - (3)]).strs[0];
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 482 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name		=(yyvsp[(2) - (3)]).strs[0];
		string str		=string("#undef ")+name+"\n";
		glfxWrite(str.c_str()); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 488 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 505 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 545 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 555 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 574 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 577 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string bufferName	=(yyvsp[(2) - (7)]).strs[0];
		string def			=(yyvsp[(5) - (7)]).strs[0];
		string semantic		=(yyvsp[(3) - (7)]).strs[0];
		int buffer_number	=(yyvsp[(3) - (7)]).num;

		ostringstream str;
		WriteLineNumber(str,current_filenumber,(yyvsp[(1) - (7)]).lineno+(last_linenumber-global_linenumber));
		str<< "layout(std140) uniform "<<(yyvsp[(2) - (7)]).strs[0]<<(yyvsp[(5) - (7)]).strs[0]<<";\n";
		WriteLineNumber(str,current_filenumber,glfxget_lineno()+(last_linenumber-global_linenumber));

		glfxWrite(str.str().c_str());
		// Set to default:
		buildStruct					=Struct();
	}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 594 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
					//if(j->semantic.size())
					//	params<<": "<<j->semantic;
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
						//if(j->semantic.size())
						//	params<<": "<<j->semantic;
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
					//if(j->semantic.size())
					//	params<<": "<<j->semantic;
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
#line 718 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 752 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 757 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 760 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 768 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 775 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 781 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 786 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 792 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 798 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 803 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 808 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 822 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 825 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 828 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 832 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 835 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 839 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 849 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 853 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 858 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 862 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 866 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 870 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 874 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 882 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				(yyval).num=(yyvsp[(3) - (3)]).num;
		   }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 888 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 892 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 896 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 903 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 910 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_function=true;
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 917 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 921 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 928 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 934 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
 }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 938 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
 }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 942 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="{\n";
	(yyval).strs[0]+=((yyvsp[(2) - (3)]).strs[0]+"\n}\n");
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 947 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string list			=(yyvsp[(1) - (2)]).strs[0];
	string new_member	=(yyvsp[(2) - (2)]).strs[0];
    (yyval).strs[0]=(list+"\n")+new_member;
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 953 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string member	=(yyvsp[(1) - (1)]).strs[0];
    (yyval).strs[0]=member;
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 958 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 977 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="uniform";
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 981 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 985 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 999 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1014 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 1020 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    ostringstream prepend;
	string semantic		=(yyvsp[(1) - (3)]).strs[0];
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
	string all		=(((yyvsp[(1) - (3)]).strs[1]+" ")+(yyvsp[(1) - (3)]).strs[2]+" ")+id+(yyvsp[(3) - (3)]).strs[0];
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
#line 1051 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 1056 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 1061 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
			}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 1066 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
			}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 1071 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (4)]).strs[0];
		string type		=(yyvsp[(2) - (4)]).strs[0];
		string template_=(yyvsp[(3) - (4)]).strs[0];
		// TODO: We discard template information in parameters. Should we insert a layout spec?
		//if(template_.length())
			//type+=string("<")+template_+string(">");
		string id		=(yyvsp[(4) - (4)]).strs[0];
		if(template_.length()>=4&&(template_.substr(0,4)==string("uint")||template_.substr(0,4)==string("uvec")))
			type=string("u")+type;
		else if(template_.length()>=4&&template_.substr(0,4)==string("ivec"))
			type=string("i")+type;
		else if(template_.length()>=3&&template_.substr(0,3)==string("int"))
			type=string("i")+type;
	//	string all		=((storage+" ")+type+" ")+id;
		(yyval).strs[0]		=template_;
		(yyval).strs[1]		=storage;
		(yyval).strs[2]		=type;
		(yyval).strs[3]		=id;
		(yyval).token		=(yyvsp[(2) - (4)]).token;
	}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 1093 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1098 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1103 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1107 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1111 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1116 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1121 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1126 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1131 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1136 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1142 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1147 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1153 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1172 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1186 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable	= (yyvsp[(1) - (5)]).boolean;
	(yyval).prog					= (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0]				= (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1193 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders),buildPassState,gEffect->textureSamplersByShader);
    delete (yyvsp[(1) - (1)]).shaders;
	buildPassState			=PassState();
}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1200 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1210 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1223 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1231 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1239 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1248 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1252 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1258 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1266 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				errSem("Pass definitions like vs(430)=vs_main are no longer supported. Please use SetVertexShader() etc.");
			}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1271 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1345 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1357 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1377 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1413 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1424 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1430 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1434 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1438 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1443 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1448 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1452 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1461 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1467 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1472 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1485 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1494 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1498 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1502 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1506 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1544 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1548 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1552 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1557 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1561 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1565 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
					(yyval).strs[1]="";
				}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1571 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=";\n";
					(yyval).strs[1]="";
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1576 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1581 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
					(yyval).strs[1]="";
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1587 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1592 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1604 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1609 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1614 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
					(yyval).strs[1]="";
				}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1620 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1625 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1630 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1635 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1650 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).strs[1]="";
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1656 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1660 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1664 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1667 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1671 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1676 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1682 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1690 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1694 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1698 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1711 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1715 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1719 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1724 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1728 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1732 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1736 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1740 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1744 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1748 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1752 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1756 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1760 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1765 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1769 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1773 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1777 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1781 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1785 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1789 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1793 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1797 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1801 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1805 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1809 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1813 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1817 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1821 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1825 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1829 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1833 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1837 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1841 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1845 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1849 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1853 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1857 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1861 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texture";
}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1865 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="textureLod";
}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1869 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1879 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1889 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).token=(yyvsp[(1) - (1)]).token;
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[0];			//Command
					}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1895 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (4)]).strs[2];			//Command
					}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1900 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (6)]).strs[1];
						string x			=(yyvsp[(3) - (6)]).strs[0];
						string y			=(yyvsp[(5) - (6)]).strs[0];

						(yyval).strs[0]=GetSizeFunction( textureName, x, y,"");
					}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1908 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1916 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1959 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 2024 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						// ok this could be a function call.
						string command=(yyvsp[(1) - (3)]).strs[2];
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 2030 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[2]=expr3;			//Command
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 2037 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 2041 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 2045 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 2053 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 2061 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 2066 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 2073 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 2080 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 2087 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 2094 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 2098 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).token=(yyvsp[(1) - (1)]).token;
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 2103 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 2107 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 2111 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 2115 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 2119 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 2127 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 2135 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 2139 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string id	=(yyvsp[(4) - (5)]).strs[0];
						(yyval).strs[0]	=id;
						(yyval).num		=-1;
						if(id.length()>1)
						{
							string nstr	=id.substr(1,id.length()-1);
							int num		=atoi(nstr.c_str());
							(yyval).num		=num;
						}
					}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]	="";
						(yyval).num		=-1;
					}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2156 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 2164 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 2168 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2171 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 2175 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 2180 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 2184 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 252:
/* Line 1792 of yacc.c  */
#line 2293 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 2298 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 2304 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 2309 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 2313 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 2318 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 2323 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 2328 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 5179 "src/glfxLALRParser.cpp"
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
#line 2331 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
	buildStruct		=Struct();
	gEffect->declaredTextures.clear();
	read_shader		=false;
	read_function	=false;
}
