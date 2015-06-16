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
	
	void DeclareTextureSampler(const TextureSampler *ts)
	{
		auto i=gEffect->additionalTextureDeclarations.find(ts->textureSamplerName());
		if(i!=gEffect->additionalTextureDeclarations.end())
			return;

		string tsname		=ts->textureSamplerName();
		string texture_name	=ts->textureName;
		if (gEffect->declaredTextures.find(texture_name) != gEffect->declaredTextures.end())
		{
			string sampler_type = gEffect->declaredTextures[texture_name].type;
			//str<<"uniform "<<sampler_type<<" "<<tsname<<";\n";
			gEffect->additionalTextureDeclarations[tsname].type		=sampler_type;
			gEffect->additionalTextureDeclarations[tsname].type_enum = gEffect->declaredTextures[texture_name].type_enum;
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
	GLTextureType GetTextureType(const Function &function,const string &textureName)
	{
		for(vector<glfxstype::variable>::const_iterator i=function.parameters.begin();i!=function.parameters.end();i++)
		{
			if(textureName==i->identifier)
				return (GLTextureType)i->type_enum;
		}
		auto j = gEffect->declaredTextures.find(textureName);
		if (j != gEffect->declaredTextures.end())
			return (GLTextureType)j->second.type_enum;
		return unknwownTextureType;
	}
	GLTextureType ToGLTextureType(int t);
	bool IsRWTexture(GLTextureType glTextureType)
	{
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
				return true;
				break;
			default:
				return false;
		break;
		}
	}
	string GetSizeFunction(string textureName,string x,string y,string z)
	{
		GLTextureType glTextureType	=GetTextureType(buildFunction,textureName);
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
		int return_size=GetTextureDimension(glTextureType);
		ostringstream full_expr;
		// NOTE the spaces around the textureName. We might need to replace it with a sampler name, so we make sure we can find it
		// as a whole word easily.
		full_expr<<"{ivec"<<return_size<<" iv=";
		if(IsRWTexture(glTextureType))
		{
			full_expr<<"imageSize";
		}
		else
			full_expr<<"textureSize";
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
#line 381 "src/glfxLALRParser.cpp"

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
     LOAD = 268,
     GET_DIMS = 269,
     STORAGEQ = 270,
     GL_FRAGDEPTH = 271,
     SHADER_COMMAND = 272,
     SET_RASTERIZER_COMMAND = 273,
     SET_DEPTH_COMMAND = 274,
     SET_BLEND_COMMAND = 275,
     SV_DISPATCHTHREADID = 276,
     SV_GROUPTHREADID = 277,
     SV_GROUPID = 278,
     SV_VERTEXID = 279,
     NUM = 280,
     INCLUDE = 281,
     SAMPLER = 282,
     FLOAT = 283,
     LAYOUT = 284,
     LINE = 285,
     TECHNIQUE = 286,
     PASS = 287,
     GROUP = 288,
     RENDER_STATE_DECL = 289,
     QUOTED_STRING = 290,
     SHADER_LINE = 291,
     SHADER_TYPE = 292,
     COMPILE_SHADER = 293,
     CONSTRUCT_GS_WITH_SO = 294,
     STRUCT = 295,
     PRAGMA = 296,
     DEFINE = 297,
     UNDEF = 298,
     MACRO_DEFINITION = 299,
     EOL = 300,
     DECL_SHADER = 301,
     PROFILE = 302,
     WARNING = 303,
     DEF = 304,
     MESSAGE = 305,
     PACK_MATRIX = 306,
     RW_TEXTURE2D = 307,
     RW_TEXTURE3D = 308,
     RW_TEXTURE2DARRAY = 309,
     RW_TEXTURE3D_FLOAT4 = 310,
     TEXTURE2DMS = 311,
     TEXTURE2D = 312,
     TEXTURE3D = 313,
     TEXTURECUBE = 314,
     IMAGE3D = 315,
     KNOWN_TYPE = 316,
     STRUCTUREDBUFFER = 317,
     RW_STRUCTUREDBUFFER = 318,
     RETURN = 319,
     BREAK = 320,
     CONTINUE = 321,
     DO = 322,
     FOR = 323,
     GOTO = 324,
     IF = 325,
     WHILE = 326,
     ELSE = 327,
     TIMES_EQUALS = 328,
     OVER_EQUALS = 329,
     PERCENT_EQUALS = 330,
     PLUS_EQUALS = 331,
     MINUS_EQUALS = 332,
     LEFT_SHIFT_EQUALS = 333,
     RIGHT_SHIFT_EQUALS = 334,
     AND_EQUALS = 335,
     XOR_EQUALS = 336,
     OR_EQUALS = 337,
     AND = 338,
     OR = 339,
     LESS_EQ = 340,
     GRTR_EQ = 341,
     LEFT_SHIFT = 342,
     RIGHT_SHIFT = 343,
     PLUS_PLUS = 344,
     MINUS_MINUS = 345,
     EQ_EQ = 346,
     NOT_EQ = 347,
     SA_MAXVERTEXCOUNT = 348,
     SA_NUMTHREADS = 349,
     SATURATE = 350,
     SHADER_PROFILE = 351
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
#line 543 "src/glfxLALRParser.cpp"

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
#define YYLAST   697

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  121
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  262
/* YYNRULES -- Number of states.  */
#define YYNSTATES  557

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   351

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   119,     2,     2,     2,   117,   112,     2,
      98,   100,   115,   113,   103,   114,   120,   116,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    99,    97,
     107,   104,   108,   109,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   101,     2,   102,   111,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   105,   110,   106,   118,     2,     2,     2,
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
      95,    96
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
     727,   729,   731,   733,   735,   737,   741,   745,   749,   751,
     756,   763,   772,   777,   784,   789,   793,   797,   800,   803,
     807,   809,   811,   815,   820,   822,   826,   828,   830,   832,
     836,   838,   840,   843,   846,   847,   853,   854,   857,   860,
     861,   865,   866,   869,   871,   876,   878,   881,   885,   886,
     888,   890,   892
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     122,     0,    -1,   122,   123,    -1,    -1,     9,   142,    10,
     147,    97,   145,    -1,    45,    -1,   124,    -1,    41,    48,
      98,   131,    99,    25,   100,    -1,     4,   127,   129,    10,
     215,    97,    -1,     4,   128,   129,    10,    97,    -1,     4,
      10,    10,    97,    -1,   101,    93,    98,    25,   100,   102,
      -1,   101,    94,    98,    25,   103,    25,   103,    25,   100,
     102,    -1,    29,   135,    10,    97,    -1,    29,   136,    -1,
      55,    10,    97,    -1,    55,    10,   103,    -1,    42,    44,
      45,    -1,    43,    10,    45,    -1,    40,    10,   149,    97,
      -1,    34,    10,   215,   217,    97,    -1,    47,    96,    98,
      25,   100,    97,    -1,    46,    10,   104,   170,    97,    -1,
      29,   142,   130,   145,    -1,     7,    10,   215,   143,   149,
      97,   145,    -1,    10,    10,    98,   153,   100,   144,   146,
     145,    -1,   126,    10,    10,    98,   153,   100,   148,   146,
     145,    -1,     8,   142,    10,   105,   165,   106,   145,    -1,
     134,    -1,    33,   142,    10,   105,   132,   106,   145,    -1,
      30,   142,    25,    25,   145,    -1,    30,    25,    25,    -1,
       6,   143,    -1,    57,    -1,    58,    -1,    56,    -1,    60,
      -1,    52,    -1,    53,    -1,    54,    -1,    59,    -1,    62,
      -1,    63,    -1,   107,    10,   108,    -1,    -1,    98,    25,
     103,    25,   103,    25,   100,    -1,    10,    -1,    25,    -1,
     132,   133,    -1,   133,    -1,    31,    10,   105,   162,   106,
      -1,    31,   142,    10,   105,   162,   106,   145,    -1,    98,
     139,   100,    -1,    98,   137,   100,    -1,   137,   103,   138,
      -1,   138,    -1,   140,    -1,    10,    -1,   140,   103,   140,
     103,   140,    -1,    10,   104,   141,    -1,    10,    -1,    25,
      -1,    -1,    -1,    -1,    -1,   105,   175,   106,    -1,    -1,
      99,    10,    -1,    -1,   105,   150,   106,    -1,   150,   151,
      -1,   151,    -1,   152,    10,    10,   155,   216,    97,    -1,
       4,    -1,    -1,   153,   103,   154,    -1,   154,    -1,    -1,
     157,   155,   161,    -1,   101,   156,   102,    -1,    -1,    25,
      -1,    -1,   159,   158,   129,    10,    -1,    10,    -1,   127,
      -1,    15,    -1,    -1,    21,    -1,    23,    -1,    22,    -1,
      24,    -1,    99,    25,    -1,    99,   160,    -1,    99,    10,
      -1,    -1,   163,    -1,   163,   164,    -1,   164,    -1,    32,
      10,   105,   165,   106,    -1,   166,    -1,   166,   169,    -1,
     169,    -1,   166,   168,    -1,   168,    -1,    10,    98,    28,
     103,    28,   103,    28,   103,    28,   100,    -1,    18,    98,
      10,   100,    97,    -1,    19,    98,    10,   103,    25,   100,
      97,    -1,    20,    98,    10,   103,   167,   103,    25,   100,
      97,    -1,   171,   104,   172,    97,    -1,    17,    98,   170,
     100,    97,    -1,    10,    -1,    39,    98,    10,   103,    35,
     100,    -1,    38,    98,    96,   103,    10,    98,   100,   100,
      -1,    37,    98,    25,   100,    -1,    10,    98,   100,   173,
      -1,    -1,    99,   174,    -1,    -1,   174,   103,   213,    -1,
     213,    -1,   175,   181,    -1,   181,    -1,    -1,    30,    25,
      25,    -1,   223,   178,    -1,   179,    -1,   178,   103,   179,
      -1,   180,    -1,   180,   104,   209,    -1,    10,    -1,    98,
     180,   100,    -1,   180,   101,    25,   102,    -1,   180,   101,
     102,    -1,   180,    98,   100,    -1,   185,    97,    -1,    97,
      -1,   177,    97,    -1,   184,    -1,    70,    98,   185,   100,
     181,    -1,    70,    98,   185,   100,   181,    72,   181,    -1,
      71,    98,   185,   100,   181,    -1,    67,   181,    71,    98,
     185,   100,    97,    -1,    68,    98,   182,    97,   183,    97,
     183,   100,   181,    -1,    69,    10,    97,    -1,    66,    97,
      -1,    65,    97,    -1,    64,   183,    97,    -1,   176,    -1,
     185,    -1,   177,    -1,    -1,   185,    -1,    -1,   105,   175,
     106,    -1,   186,    -1,   185,   103,   186,    -1,   188,    -1,
     200,   187,   186,    -1,   104,    -1,    73,    -1,    74,    -1,
      75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,    -1,
      80,    -1,    81,    -1,    82,    -1,   189,    -1,   189,   109,
     185,    99,   188,    -1,   190,    -1,   189,    84,   190,    -1,
     191,    -1,   190,    83,   191,    -1,   192,    -1,   191,   110,
     192,    -1,   193,    -1,   192,   111,   193,    -1,   194,    -1,
     193,   112,   194,    -1,   195,    -1,   194,    91,   195,    -1,
     194,    92,   195,    -1,   196,    -1,   195,   107,   196,    -1,
     195,   108,   196,    -1,   195,    85,   196,    -1,   195,    86,
     196,    -1,   197,    -1,   196,    87,   197,    -1,   196,    88,
     197,    -1,   198,    -1,   197,   113,   198,    -1,   197,   114,
     198,    -1,   199,    -1,   198,   115,   199,    -1,   198,   116,
     199,    -1,   198,   117,   199,    -1,   200,    -1,   207,    -1,
      89,   200,    -1,    90,   200,    -1,   201,   199,    -1,   112,
      -1,   115,    -1,   113,    -1,   114,    -1,   118,    -1,   119,
      -1,    11,    -1,    12,    -1,    13,    -1,   207,   120,   203,
      -1,   207,   120,   202,    -1,   207,   120,    14,    -1,   211,
      -1,   207,   101,   185,   102,    -1,   206,    98,   186,   103,
     186,   100,    -1,   206,    98,   186,   103,   186,   103,   186,
     100,    -1,   204,    98,   208,   100,    -1,   205,    98,   186,
     103,   208,   100,    -1,   207,    98,   208,   100,    -1,   207,
      98,   100,    -1,   207,   120,    10,    -1,   207,    89,    -1,
     207,    90,    -1,   208,   103,   186,    -1,   186,    -1,   186,
      -1,   105,   210,   106,    -1,   105,   210,   103,   106,    -1,
     209,    -1,   210,   103,   209,    -1,    10,    -1,    95,    -1,
     212,    -1,    98,   185,   100,    -1,    25,    -1,    28,    -1,
      15,   214,    -1,    16,   214,    -1,    -1,    99,     5,    98,
      10,   100,    -1,    -1,    99,    10,    -1,    99,   160,    -1,
      -1,   105,   218,   106,    -1,    -1,   218,   219,    -1,   219,
      -1,   220,   104,   222,    97,    -1,   125,    -1,    10,   221,
      -1,   101,    25,   102,    -1,    -1,    10,    -1,    25,    -1,
      28,    -1,    10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   325,   325,   326,   368,   372,   375,   378,   381,   414,
     430,   436,   440,   446,   449,   455,   461,   467,   471,   477,
     494,   534,   544,   563,   566,   583,   707,   741,   745,   748,
     756,   763,   769,   774,   774,   774,   774,   774,   774,   774,
     774,   780,   780,   786,   792,   796,   810,   813,   816,   820,
     823,   827,   837,   841,   846,   850,   854,   858,   862,   870,
     876,   880,   885,   892,   899,   906,   910,   917,   922,   927,
     930,   935,   941,   946,   965,   970,   973,   987,  1003,  1008,
    1039,  1045,  1049,  1055,  1059,  1081,  1086,  1091,  1096,  1099,
    1104,  1109,  1114,  1119,  1124,  1130,  1136,  1141,  1148,  1160,
    1174,  1181,  1188,  1206,  1228,  1237,  1246,  1255,  1259,  1265,
    1273,  1281,  1347,  1359,  1379,  1416,  1427,  1434,  1437,  1442,
    1446,  1451,  1455,  1464,  1471,  1475,  1488,  1497,  1501,  1505,
    1509,  1547,  1551,  1555,  1560,  1564,  1568,  1574,  1579,  1584,
    1590,  1595,  1607,  1612,  1617,  1623,  1628,  1633,  1638,  1653,
    1659,  1663,  1668,  1670,  1675,  1679,  1685,  1689,  1693,  1697,
    1720,  1725,  1726,  1727,  1728,  1729,  1730,  1731,  1732,  1733,
    1734,  1739,  1743,  1748,  1752,  1756,  1760,  1764,  1768,  1772,
    1776,  1780,  1784,  1789,  1793,  1797,  1801,  1805,  1809,  1813,
    1817,  1821,  1825,  1829,  1833,  1837,  1841,  1845,  1849,  1853,
    1857,  1861,  1865,  1872,  1876,  1880,  1884,  1884,  1884,  1884,
    1884,  1884,  1888,  1892,  1896,  1900,  1910,  1920,  1930,  1936,
    1965,  1973,  1981,  2029,  2072,  2137,  2143,  2150,  2154,  2158,
    2166,  2174,  2179,  2186,  2193,  2200,  2207,  2211,  2216,  2220,
    2224,  2228,  2232,  2240,  2249,  2252,  2265,  2269,  2273,  2278,
    2281,  2285,  2288,  2293,  2297,  2406,  2411,  2417,  2423,  2426,
    2431,  2436,  2441
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHITESPACE", "UNIFORM", "REGISTER",
  "SHADER", "CONSTANT_BUFFER", "PROGRAM", "INTERFACE", "IDENTIFIER",
  "SAMPLE", "SAMPLE_LOD", "LOAD", "GET_DIMS", "STORAGEQ", "GL_FRAGDEPTH",
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
  "unary_operator", "sampling_command", "tex_load_command", "tex_load_exp",
  "sampling_exp", "get_dims_exp", "postfix_exp", "argument_exp_list",
  "initializer", "initializer_list", "primary_exp", "const", "layout",
  "read_parenthesis", "optional_register_semantic", "optional_semantic",
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
     345,   346,   347,   348,   349,   350,   351,    59,    40,    58,
      41,    91,    93,    44,    61,   123,   125,    60,    62,    63,
     124,    94,    38,    43,    45,    42,    47,    37,   126,    33,
      46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   121,   122,   122,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     124,   125,   126,   127,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   129,   129,   130,   131,   131,   132,   132,
     133,   134,   135,   136,   137,   137,   138,   138,   139,   140,
     141,   141,   142,   143,   144,   145,   146,   147,   148,   148,
     149,   150,   150,   151,   152,   152,   153,   153,   153,   154,
     155,   155,   156,   156,   157,   158,   158,   159,   159,   160,
     160,   160,   160,   161,   161,   161,   161,   162,   163,   163,
     164,   165,   166,   166,   166,   166,   167,   168,   168,   168,
     169,   169,   170,   170,   170,   171,   172,   172,   173,   173,
     174,   174,   175,   175,   175,   176,   177,   178,   178,   179,
     179,   180,   180,   180,   180,   180,   181,   181,   181,   181,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     182,   182,   182,   183,   183,   184,   185,   185,   186,   186,
     187,   187,   187,   187,   187,   187,   187,   187,   187,   187,
     187,   188,   188,   189,   189,   190,   190,   191,   191,   192,
     192,   193,   193,   194,   194,   194,   195,   195,   195,   195,
     195,   196,   196,   196,   197,   197,   197,   198,   198,   198,
     198,   199,   200,   200,   200,   200,   201,   201,   201,   201,
     201,   201,   202,   202,   203,   204,   205,   206,   207,   207,
     207,   207,   207,   207,   207,   207,   207,   207,   207,   208,
     208,   209,   209,   209,   210,   210,   211,   211,   211,   211,
     212,   212,   213,   213,   214,   215,   215,   216,   216,   216,
     217,   217,   218,   218,   219,   219,   220,   221,   221,   222,
     222,   222,   223
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
       1,     1,     1,     1,     1,     3,     3,     3,     1,     4,
       6,     8,     4,     6,     4,     3,     3,     2,     2,     3,
       1,     1,     3,     4,     1,     3,     1,     1,     1,     3,
       1,     1,     2,     2,     0,     5,     0,     2,     2,     0,
       3,     0,     2,     1,     4,     1,     2,     3,     0,     1,
       1,     1,     1
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
      32,   246,     0,     0,     0,     0,     0,    14,     0,     0,
       0,     0,   246,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,     0,
      67,    88,    57,     0,    55,     0,    56,     0,     0,    65,
       0,     0,     0,   251,    75,     0,     0,    17,    18,     0,
       0,    15,    16,     0,     0,     0,    10,     0,   246,     0,
       0,     0,     0,     0,    87,     0,    77,    81,     0,     0,
      53,     0,    52,     0,    13,     0,    23,    65,     0,     0,
       0,     0,    74,    75,    72,     0,    19,    46,    47,     0,
     112,     0,     0,     0,     0,     0,     0,    88,    43,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     105,   103,     0,    65,    64,    88,    83,    96,    85,    86,
      44,    60,    61,    59,    54,    56,     0,     0,     0,    30,
       0,     0,    97,    99,     0,     0,    49,   258,     0,   255,
       0,   253,     0,    20,    70,    71,     0,     0,     0,     0,
      22,     0,     0,     0,     0,     8,     0,    65,     0,     0,
       0,     0,     0,    65,   104,   102,   117,     4,     0,    76,
      82,     0,     0,    79,     0,     0,     0,     0,    65,    98,
       0,    65,    48,     0,   256,     0,   250,   252,     0,    81,
       0,     0,     0,    21,    11,     0,    69,   245,    24,     0,
       0,     0,     0,     0,    27,     0,     0,   124,    65,    80,
      95,    89,    91,    90,    92,    93,    94,    84,    58,     0,
       0,    51,     0,    29,     0,    31,   259,   260,   261,     0,
     249,     7,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,     0,   110,   236,   240,   241,     0,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   237,   137,
       0,   124,   206,   208,   209,   207,   210,   211,     0,   149,
       0,   123,   139,     0,   156,   158,   171,   173,   175,   177,
     179,   181,   183,   186,   191,   194,   197,   201,     0,     0,
       0,     0,   202,   218,   238,     0,    25,     0,     0,     0,
     257,   254,     0,     0,     0,     0,     0,    68,    65,   111,
     107,     0,     0,     0,   119,     0,   236,     0,   153,   147,
     146,     0,   152,     0,     0,     0,   203,   204,     0,     0,
      66,   122,   138,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   160,     0,   205,   201,     0,     0,
       0,   227,   228,     0,     0,     0,   131,     0,   126,   127,
     129,    45,   100,    50,   247,   248,    73,     0,   113,     0,
      26,     0,     0,     0,     0,   116,   125,   148,     0,   151,
       0,   150,   145,     0,     0,   239,   155,   157,   174,     0,
     176,   178,   180,   182,   184,   185,   189,   190,   187,   188,
     192,   193,   195,   196,   198,   199,   200,   159,   230,     0,
       0,     0,   225,     0,     0,   226,   212,   213,   214,   217,
     216,   215,     0,     0,     0,     0,     0,     0,    12,   108,
       0,     0,   244,   244,   118,   121,     0,   154,     0,     0,
       0,   222,     0,     0,     0,   224,   219,   132,   128,   135,
       0,   134,     0,   231,   130,   114,     0,     0,   242,   243,
       0,     0,     0,   140,   142,   172,   229,     0,     0,   133,
     234,     0,     0,   109,   120,     0,   154,     0,   223,   220,
       0,     0,   232,     0,   143,     0,   141,     0,   233,   235,
       0,     0,   221,     0,   144,     0,   106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   179,    25,    38,    39,    65,    79,
     129,   175,   176,    26,    46,    47,    73,    74,    75,    76,
     163,    42,    40,   208,   116,   248,   103,   276,    85,   123,
     124,   125,   105,   106,   157,   211,   107,   160,   108,   256,
     213,   171,   172,   173,   148,   149,   353,   150,   151,   133,
     152,   246,   435,   494,   308,   309,   310,   418,   419,   420,
     311,   440,   357,   312,   313,   314,   405,   315,   316,   317,
     318,   319,   320,   321,   322,   323,   324,   325,   326,   327,
     328,   480,   481,   329,   330,   331,   332,   469,   514,   531,
     333,   334,   495,   518,    68,   343,   121,   180,   181,   182,
     224,   269,   335
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -494
static const yytype_int16 yypact[] =
{
    -494,   444,  -494,     8,  -494,    13,  -494,  -494,    18,   -68,
    -494,  -494,  -494,    39,   121,    85,   110,   148,  -494,   199,
     123,   207,   -54,  -494,  -494,   211,  -494,   231,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,   143,   143,
    -494,   183,   270,   278,   201,   299,   301,  -494,   216,   287,
     314,   315,   183,   222,   232,   286,   288,   228,   237,    31,
     238,   240,   329,   245,   333,   337,   340,   350,  -494,   254,
    -494,   -10,   256,    -2,  -494,   262,   264,   271,   346,  -494,
     347,   268,   273,   276,   378,   289,     4,  -494,  -494,    44,
     359,  -494,  -494,   360,   364,   293,  -494,   284,   183,   304,
     297,   222,    16,   305,  -494,    56,  -494,   308,   367,     6,
    -494,   299,  -494,   404,  -494,   312,  -494,  -494,   386,   391,
      11,   331,  -494,    20,  -494,   419,  -494,  -494,  -494,   332,
    -494,   334,   335,   338,   330,   336,   339,   -10,  -494,   341,
    -494,   424,   342,   345,   349,   357,   358,   361,   352,    16,
    -494,  -494,   353,  -494,  -494,   422,   420,   362,  -494,  -494,
     143,  -494,  -494,  -494,  -494,  -494,   256,   365,   435,  -494,
     452,   366,   386,  -494,   457,   -22,  -494,   370,   451,  -494,
      -3,  -494,   375,  -494,  -494,  -494,   470,   456,   387,   472,
    -494,   395,   392,   463,   133,  -494,   393,  -494,    44,   485,
     486,   487,   473,  -494,  -494,  -494,   490,  -494,   396,  -494,
    -494,   400,   147,  -494,   493,   404,   401,   402,  -494,  -494,
     403,  -494,  -494,   480,  -494,   481,  -494,  -494,   117,   308,
     409,   407,   408,  -494,  -494,   410,   413,  -494,  -494,   414,
     415,   416,   417,   418,  -494,   423,   425,   251,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,  -494,   491,
      16,  -494,   386,  -494,   421,  -494,  -494,  -494,  -494,   427,
     426,  -494,   507,   492,   501,   518,   396,   432,   433,   506,
     522,  -494,   434,  -494,   523,  -494,  -494,   510,   298,   439,
     440,   251,   441,   528,   442,   443,   298,   298,  -494,  -494,
     298,   251,  -494,  -494,  -494,  -494,  -494,  -494,   125,  -494,
     445,  -494,  -494,    33,  -494,  -494,   -71,   460,   436,   437,
     438,    73,    66,    12,    62,   181,  -494,   106,   298,   446,
     449,   453,   -46,  -494,  -494,    -4,  -494,   454,   447,   450,
    -494,  -494,   384,   455,   459,   458,   461,  -494,  -494,  -494,
    -494,   462,   465,   464,   466,   524,  -494,   467,   468,  -494,
    -494,   484,   351,   469,   298,   298,  -494,  -494,   142,   188,
    -494,  -494,  -494,  -494,   298,   298,   298,   298,   298,   298,
     298,   298,   298,   298,   298,   298,   298,   298,   298,   298,
     298,   298,   298,   298,  -494,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,  -494,  -494,  -494,   298,  -494,  -494,   298,   298,
     298,  -494,  -494,    48,   298,   214,  -494,    -4,   471,  -494,
     -29,  -494,  -494,  -494,  -494,  -494,  -494,   475,  -494,   474,
    -494,   476,   531,   535,   219,  -494,  -494,  -494,   479,  -494,
     482,   468,  -494,   162,   163,  -494,  -494,  -494,   460,   -40,
     436,   437,   438,    73,    66,    66,    12,    12,    12,    12,
      62,    62,   181,   181,  -494,  -494,  -494,  -494,  -494,   168,
     477,   478,  -494,   169,   145,  -494,  -494,  -494,  -494,  -494,
    -494,  -494,   -12,    -4,   483,   -17,   285,   488,  -494,  -494,
     489,   494,  -494,  -494,   495,  -494,   298,   298,   251,   251,
     298,  -494,   298,   298,   298,  -494,  -494,  -494,  -494,  -494,
     497,  -494,   285,  -494,  -494,  -494,   540,   496,  -494,  -494,
     219,   170,   498,   500,  -494,  -494,  -494,   184,   189,  -494,
    -494,    41,   499,  -494,  -494,   503,   298,   251,  -494,  -494,
     298,   239,  -494,   541,  -494,   504,  -494,   505,  -494,  -494,
     508,   251,  -494,   542,  -494,   509,  -494
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -494,  -494,  -494,  -494,  -494,  -494,   502,  -494,   -35,  -494,
    -494,  -494,   411,  -494,  -494,  -494,  -494,   511,  -494,   -91,
    -494,   190,   514,  -494,  -116,   302,  -494,  -494,   512,  -494,
     513,  -494,   448,   429,   368,  -494,  -494,  -494,  -494,   247,
    -494,   325,  -494,   431,   348,  -494,  -494,   515,   516,   398,
    -494,  -494,  -494,  -494,   290,  -494,   244,  -494,   107,   195,
    -291,  -494,  -485,  -494,  -285,  -363,  -494,   101,  -494,   241,
     230,   236,   242,   235,  -107,  -180,   -97,   -85,  -296,  -271,
    -494,  -494,  -494,  -494,  -494,  -494,  -494,  -411,  -493,  -494,
    -494,  -494,    97,   126,   -42,  -494,  -494,  -494,   517,  -494,
    -494,  -494,  -494
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -263
static const yytype_int16 yytable[] =
{
     361,   169,   473,   358,    66,   104,   416,   177,   510,   174,
      83,   447,   522,   375,   127,   368,   161,   371,    27,   530,
     165,   177,   167,    41,   122,   366,   367,   178,    44,   128,
      45,   162,   406,   143,   144,   145,   146,   207,   376,    60,
      61,   178,   467,   411,   412,   468,   470,   471,   549,    52,
     468,   545,   413,   147,   130,   414,   139,   407,   356,   500,
      28,    29,    30,   374,    31,    32,    33,    34,    35,   484,
      36,    37,   485,   285,   415,   486,   286,   441,   371,   443,
     444,   238,   131,   132,   221,   511,   484,   244,   507,   485,
     -78,   449,   527,   -78,   417,   464,   465,   466,   110,   387,
     388,   111,   261,   226,   407,   263,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   513,   258,   214,   184,   266,    91,   474,
     373,    53,   336,    54,    92,   284,   374,   296,   297,   526,
     468,   528,   267,   298,   541,   268,   300,   542,   472,   513,
     285,   383,   384,   286,    55,   287,   154,   250,    56,   155,
     302,   303,   304,   305,   381,   382,   306,   307,   251,   252,
     253,   254,   255,   385,   386,   389,   390,   547,   513,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   288,
     289,   290,   291,   292,   293,   294,   295,    43,   284,    48,
      49,    50,    51,   456,   457,   458,   459,   523,   524,    57,
     404,   521,   358,   285,   296,   297,   286,    59,   287,    58,
     298,    62,   299,   300,   475,   476,   477,   478,   479,   407,
     301,   370,   430,   236,   492,   493,   155,   302,   303,   304,
     305,    63,   445,   306,   307,   374,   546,   506,   374,   356,
      64,   358,   288,   289,   290,   291,   292,   293,   294,   295,
     554,   284,   498,   499,   285,   374,   374,   286,   501,   505,
     535,   502,   502,   374,   454,   455,   285,   296,   297,   286,
      69,   287,    67,   298,   538,   299,   300,   502,    70,   539,
     460,   461,   540,   301,   446,   356,   391,   392,   393,    71,
     302,   303,   304,   305,   462,   463,   306,   307,   356,    72,
     285,    77,    80,   286,    78,   288,   289,   290,   291,   292,
     293,   294,   295,   285,    81,    82,   286,    84,   296,   297,
      86,    87,    89,    88,   298,    90,    93,   300,    94,    95,
     296,   297,    96,    97,   512,   548,   298,    98,   299,   300,
      99,   302,   303,   304,   305,   100,   301,   306,   307,   102,
     109,   284,   112,   302,   303,   304,   305,   113,   114,   306,
     307,   115,   117,   118,   296,   297,   285,   158,   119,   286,
     298,   120,   122,   300,   134,   135,   126,   296,   297,   136,
     512,   137,   138,   298,   424,   141,   300,   302,   303,   304,
     305,   140,   153,   306,   307,   251,   252,   253,   254,   156,
     302,   303,   304,   305,   166,   168,   306,   307,   170,    28,
      29,    30,   174,    31,    32,    33,    34,    35,   183,   186,
     191,   187,   188,   189,   196,   190,   192,   104,   195,   197,
     296,   297,   193,   198,     2,   210,   298,   199,     3,   300,
       4,     5,     6,     7,     8,   200,   201,   206,   203,   202,
     216,   212,   217,   302,   303,   304,   305,   220,   215,   306,
     307,   223,   218,     9,    10,    11,   225,    12,    13,   228,
     229,   230,   232,   231,    14,    15,    16,    17,   235,    18,
      19,    20,   233,   237,   234,   240,   241,   242,   243,    21,
     245,   247,   249,   257,   259,   264,   265,   260,   262,   271,
     272,   273,   275,   274,   277,   278,   337,   344,   281,   279,
     280,   282,   283,   340,   341,   342,   346,   345,   347,   349,
     350,   351,   352,  -262,   354,   355,   359,   360,   363,   362,
     364,   365,   372,   377,   408,    22,   378,   409,   379,   436,
     380,   410,   426,   422,   421,   438,   423,   427,   428,   490,
     491,   429,   431,   432,   437,   434,   442,   433,   532,   550,
     555,   374,   537,   489,   483,   487,   488,   496,   348,   497,
     503,   504,   101,   509,   209,   194,   222,   339,   515,   425,
     508,   369,   516,   533,   517,   536,   239,   270,   520,   529,
     544,   525,   543,   219,   551,   552,   439,   450,   338,   556,
     159,   553,   482,   142,   451,   453,   448,   534,     0,   519,
       0,   452,   164,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   185,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   204,   205,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   227
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-494)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     291,   117,   413,   288,    39,    15,    10,    10,    25,    31,
      52,   374,   497,    84,    10,   300,    10,   308,    10,   512,
     111,    10,   113,    10,     4,   296,   297,    30,    10,    25,
      98,    25,   328,    17,    18,    19,    20,   153,   109,    93,
      94,    30,   405,    89,    90,   408,   409,   410,   541,    10,
     413,   536,    98,    37,    10,   101,    98,   328,    10,    99,
      52,    53,    54,   103,    56,    57,    58,    59,    60,    98,
      62,    63,   101,    25,   120,   104,    28,   362,   369,   364,
     365,   197,    38,    39,   106,   102,    98,   203,   100,   101,
     100,   376,   503,   103,    98,   391,   392,   393,   100,    87,
      88,   103,   218,   106,   375,   221,   377,   378,   379,   380,
     381,   382,   383,   384,   385,   386,   387,   388,   389,   390,
     391,   392,   393,   486,   215,   160,   106,    10,    97,   414,
      97,    10,   248,    48,   103,    10,   103,    89,    90,   502,
     503,   504,    25,    95,   103,    28,    98,   106,   100,   512,
      25,    85,    86,    28,    44,    30,   100,    10,    10,   103,
     112,   113,   114,   115,    91,    92,   118,   119,    21,    22,
      23,    24,    25,   107,   108,   113,   114,   540,   541,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    64,
      65,    66,    67,    68,    69,    70,    71,     7,    10,     9,
      10,    11,    12,   383,   384,   385,   386,   498,   499,    10,
     104,   496,   497,    25,    89,    90,    28,    10,    30,    96,
      95,    10,    97,    98,    10,    11,    12,    13,    14,   500,
     105,   106,   348,   100,    15,    16,   103,   112,   113,   114,
     115,    10,   100,   118,   119,   103,   537,   102,   103,    10,
     107,   536,    64,    65,    66,    67,    68,    69,    70,    71,
     551,    10,   100,   100,    25,   103,   103,    28,   100,   100,
     100,   103,   103,   103,   381,   382,    25,    89,    90,    28,
      10,    30,    99,    95,   100,    97,    98,   103,    10,   100,
     387,   388,   103,   105,   106,    10,   115,   116,   117,    98,
     112,   113,   114,   115,   389,   390,   118,   119,    10,    10,
      25,    10,    25,    28,    98,    64,    65,    66,    67,    68,
      69,    70,    71,    25,    10,    10,    28,   105,    89,    90,
      98,    45,   104,    45,    95,    98,    98,    98,    98,    10,
      89,    90,    97,    10,   105,   106,    95,    10,    97,    98,
      10,   112,   113,   114,   115,     5,   105,   118,   119,   105,
     104,    10,   100,   112,   113,   114,   115,   103,    97,   118,
     119,    25,    25,   105,    89,    90,    25,    10,   105,    28,
      95,   105,     4,    98,    25,    25,    97,    89,    90,    25,
     105,    98,   108,    95,    10,    98,    98,   112,   113,   114,
     115,    97,    97,   118,   119,    21,    22,    23,    24,   101,
     112,   113,   114,   115,    10,   103,   118,   119,    32,    52,
      53,    54,    31,    56,    57,    58,    59,    60,    97,    10,
     100,    99,    98,    98,    10,    97,   100,    15,    97,    97,
      89,    90,   103,    98,     0,    25,    95,    98,     4,    98,
       6,     7,     8,     9,    10,    98,    98,   104,   106,    98,
      25,    99,    10,   112,   113,   114,   115,    10,   103,   118,
     119,   101,   106,    29,    30,    31,    25,    33,    34,   104,
      10,    25,    10,    96,    40,    41,    42,    43,    25,    45,
      46,    47,    97,   100,   102,    10,    10,    10,    25,    55,
      10,   105,   102,    10,   103,    25,    25,   105,   105,   100,
     103,   103,    99,   103,   100,   100,    25,    10,   100,   103,
     103,    98,    97,   102,    97,    99,    25,    35,    10,    97,
      97,    25,    10,    10,   100,    25,    97,    97,    10,    98,
      98,    98,    97,    83,    98,   101,   110,    98,   111,    25,
     112,    98,    97,   106,   100,    71,   106,    98,   100,    28,
      25,   100,   100,    98,    97,    99,    97,   103,    28,    28,
      28,   103,    72,    97,   103,   100,   102,    98,   276,    97,
     103,   103,    68,   100,   155,   137,   175,   262,   100,   342,
     483,   301,   103,    97,   100,    97,   198,   229,   103,   102,
      97,   500,   103,   172,   100,   100,   362,   377,   260,   100,
     108,   103,   417,   101,   378,   380,   375,   520,    -1,   493,
      -1,   379,   111,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   149,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   180
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   122,     0,     4,     6,     7,     8,     9,    10,    29,
      30,    31,    33,    34,    40,    41,    42,    43,    45,    46,
      47,    55,   101,   123,   124,   126,   134,    10,    52,    53,
      54,    56,    57,    58,    59,    60,    62,    63,   127,   128,
     143,    10,   142,   142,    10,    98,   135,   136,   142,   142,
     142,   142,    10,    10,    48,    44,    10,    10,    96,    10,
      93,    94,    10,    10,   107,   129,   129,    99,   215,    10,
      10,    98,    10,   137,   138,   139,   140,    10,    98,   130,
      25,    10,    10,   215,   105,   149,    98,    45,    45,   104,
      98,    97,   103,    98,    98,    10,    97,    10,    10,    10,
       5,   143,   105,   147,    15,   153,   154,   157,   159,   104,
     100,   103,   100,   103,    97,    25,   145,    25,   105,   105,
     105,   217,     4,   150,   151,   152,    97,    10,    25,   131,
      10,    38,    39,   170,    25,    25,    25,    98,   108,   215,
      97,    98,   149,    17,    18,    19,    20,    37,   165,   166,
     168,   169,   171,    97,   100,   103,   101,   155,    10,   127,
     158,    10,    25,   141,   138,   140,    10,   140,   103,   145,
      32,   162,   163,   164,    31,   132,   133,    10,    30,   125,
     218,   219,   220,    97,   106,   151,    10,    99,    98,    98,
      97,   100,   100,   103,   153,    97,    10,    97,    98,    98,
      98,    98,    98,   106,   168,   169,   104,   145,   144,   154,
      25,   156,    99,   161,   129,   103,    25,    10,   106,   164,
      10,   106,   133,   101,   221,    25,   106,   219,   104,    10,
      25,    96,    10,    97,   102,    25,   100,   100,   145,   170,
      10,    10,    10,    25,   145,    10,   172,   105,   146,   102,
      10,    21,    22,    23,    24,    25,   160,    10,   140,   103,
     105,   145,   105,   145,    25,    25,    10,    25,    28,   222,
     155,   100,   103,   103,   103,    99,   148,   100,   100,   103,
     103,   100,    98,    97,    10,    25,    28,    30,    64,    65,
      66,    67,    68,    69,    70,    71,    89,    90,    95,    97,
      98,   105,   112,   113,   114,   115,   118,   119,   175,   176,
     177,   181,   184,   185,   186,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   204,
     205,   206,   207,   211,   212,   223,   145,    25,   165,   162,
     102,    97,    99,   216,    10,    35,    25,    10,   146,    97,
      97,    25,    10,   167,   100,    25,    10,   183,   185,    97,
      97,   181,    98,    10,    98,    98,   200,   200,   185,   175,
     106,   181,    97,    97,   103,    84,   109,    83,   110,   111,
     112,    91,    92,    85,    86,   107,   108,    87,    88,   113,
     114,   115,   116,   117,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,   104,   187,   199,   200,    98,    98,
      98,    89,    90,    98,   101,   120,    10,    98,   178,   179,
     180,   100,   106,   106,    10,   160,    97,    98,   100,   100,
     145,   100,    98,   103,    99,   173,    25,    97,    71,   177,
     182,   185,    97,   185,   185,   100,   106,   186,   190,   185,
     191,   192,   193,   194,   195,   195,   196,   196,   196,   196,
     197,   197,   198,   198,   199,   199,   199,   186,   186,   208,
     186,   186,   100,   208,   185,    10,    11,    12,    13,    14,
     202,   203,   180,   103,    98,   101,   104,   100,   102,    97,
      28,    25,    15,    16,   174,   213,    98,    97,   100,   100,
      99,   100,   103,   103,   103,   100,   102,   100,   179,   100,
      25,   102,   105,   186,   209,   100,   103,   100,   214,   214,
     103,   185,   183,   181,   181,   188,   186,   208,   186,   102,
     209,   210,    28,    97,   213,   100,    97,    72,   100,   100,
     103,   103,   106,   103,    97,   183,   181,   186,   106,   209,
      28,   100,   100,   103,   181,    28,   100
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
#line 326 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { // Initialization code
	    gEffect->m_sharedCode.str("");    // clear the stream
		gEffect->m_sharedCode<<"#define GLSL\n";
// Some GLSL compilers can't abide seeing a "discard" in the source of a shader that isn't a fragment shader, even if it's in unused, shared code.
	gEffect->m_sharedCode<<"#if !defined(GL_FRAGMENT_SHADER)\n"
							"#define discard\n"
						"#endif\n";
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
#line 369 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 373 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 376 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 379 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 382 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 415 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 431 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 437 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 441 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout.x=(yyvsp[(4) - (10)]).num;
		currentCsLayout.y=(yyvsp[(6) - (10)]).num;
		currentCsLayout.z=(yyvsp[(8) - (10)]).num;
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 447 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 450 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 456 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 462 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 468 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name					=(yyvsp[(2) - (3)]).strs[0];
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 472 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name		=(yyvsp[(2) - (3)]).strs[0];
		string str		=string("#undef ")+name+"\n";
		glfxWrite(str.c_str()); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 478 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 495 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 535 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 545 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 564 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 567 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 584 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 708 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 742 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 746 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 749 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 757 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 764 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 770 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 775 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 781 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 787 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 792 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 797 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 811 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 814 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 817 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 821 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 824 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 828 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 838 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 842 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 847 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 851 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 855 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 859 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 863 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 871 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				(yyval).num=(yyvsp[(3) - (3)]).num;
		   }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 877 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 881 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 885 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 892 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 899 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_function=true;
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 906 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 910 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 917 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 923 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
 }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 927 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
 }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 931 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="{\n";
	(yyval).strs[0]+=((yyvsp[(2) - (3)]).strs[0]+"\n}\n");
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 936 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string list			=(yyvsp[(1) - (2)]).strs[0];
	string new_member	=(yyvsp[(2) - (2)]).strs[0];
    (yyval).strs[0]=(list+"\n")+new_member;
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 942 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string member	=(yyvsp[(1) - (1)]).strs[0];
    (yyval).strs[0]=member;
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 947 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 966 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="uniform";
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 970 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 974 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 988 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1003 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 1009 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1040 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 1045 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 1050 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
			}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 1055 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
			}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 1060 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1082 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1087 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1092 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1096 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1100 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1105 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1110 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1115 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1120 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1125 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1131 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1136 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1142 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1149 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1161 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1175 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable	= (yyvsp[(1) - (5)]).boolean;
	(yyval).prog					= (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0]				= (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1182 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders), buildPassState, gEffect->textureSamplersByShader, (yyvsp[(1) - (1)]).strs[2]);
    delete (yyvsp[(1) - (1)]).shaders;
	buildPassState			=PassState();
}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1189 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		ShaderType sType				=(yyvsp[(2) - (2)]).sType;
		string preamble					=(yyvsp[(2) - (2)]).strs[0];
		string name						=(yyvsp[(2) - (2)]).strs[1];
		string compiledShaderName		=(yyvsp[(2) - (2)]).strs[3];
		(yyval).strs[2]						=(yyvsp[(1) - (2)]).strs[2]+(yyvsp[(2) - (2)]).strs[2];// compute layout
		CompiledShaderMap::iterator i	=gEffect->m_compiledShaders.find(compiledShaderName);
		if(i!=gEffect->m_compiledShaders.end())
			(*map1)[sType].src					=&i->second->source;
		else if(compiledShaderName.length())
			errSem(string("Compiled shader not found: ")+compiledShaderName);
		(*map1)[sType].preamble				=preamble;
		(*map1)[sType].name					=name;
		(*map1)[sType].compiledShaderName	=compiledShaderName;
		(yyval).shaders							=map1;
	}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1207 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		string preamble				=(yyvsp[(1) - (1)]).strs[0];
		string name					=(yyvsp[(1) - (1)]).strs[1];
		string compiledShaderName	=(yyvsp[(1) - (1)]).strs[3];
		ShaderType sType			=(yyvsp[(1) - (1)]).sType;
		(yyval).strs[0]					=(yyvsp[(1) - (1)]).strs[0];
		(yyval).strs[1]					=(yyvsp[(1) - (1)]).strs[1];
		(yyval).strs[2]					=(yyvsp[(1) - (1)]).strs[2];
		(yyval).strs[3]					=compiledShaderName;
		CompiledShaderMap::iterator i=gEffect->m_compiledShaders.find(compiledShaderName);
		(yyval).sType							=sType;
		if(i!=gEffect->m_compiledShaders.end())
			(*map1)[sType].src					=&i->second->source;
		else if(compiledShaderName.length())
			errSem(string("Compiled shader not found: ")+compiledShaderName);
		(*map1)[sType].name					=name;
		(*map1)[sType].compiledShaderName	=compiledShaderName;
		(*map1)[sType].preamble				=preamble;
		(yyval).shaders=map1;
	}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1229 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		//.map<ShaderType, Program::Shader>* map1=$1.shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).strs[2]	=(yyvsp[(1) - (2)]).strs[2];
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1238 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders	=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).strs[2]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1247 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1256 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1260 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1266 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1274 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0] = "";
				(yyval).strs[1] = "";
				(yyval).strs[2] = "";
				errSem("Pass definitions like vs(430)=vs_main are no longer supported. Please use SetVertexShader() etc.");
			}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1282 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]	="";
				(yyval).strs[1]	="";
				(yyval).strs[2]	="";
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
					if(shaderCommand<NumShaderCommands)
					{
						string shaderName=compiledShader->m_functionName;
						if(_stricmp(shaderName.c_str(),"NULL")!=0)
						{
							//theShader<<gEffect->m_sharedCode.str();
							//map<string, string>::const_iterator it=gEffect->m_shaders.find(shaderName);
							/*if(it==gEffect->m_shaders.end())
							{
								ostringstream errMsg;
								errMsg<<"Unable to find referenced shader \""<<shaderName<<'\"';
								errSem(errMsg.str(), $3.lineno);
							}
							else*/
							{
								if (shaderCommand == COMPUTE_SHADER)
									theShader << gEffect->m_shaderLayouts[shaderName].text() << "\n";
								// Currently in case of error it never returns (throw)
								// TODO: Handle continuation in case of error
								//theShader<<compiledShader->source;
							}
						}
						(yyval).strs[0]	=theShader.str();
						(yyval).strs[1]	=shaderName;
						(yyval).strs[3]	=compiledShaderName;
						//if (shaderCommand == COMPUTE_SHADER)
						//	$$.strs[2] = gEffect->m_shaderLayouts[shaderName].text();
					}
				}
			}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1348 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1360 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1380 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

			gEffect->MergeTextureSamplers(sh.function.textureSamplers,shaderName);

			stringstream ss;
			ss << (yyvsp[(5) - (8)]).strs[0]<<"Compiled"<<version_num;
			string compiledShaderName						=ss.str();
			(yyval).strs[0]										=compiledShaderName;

			CompiledShader *compiledShader					=gEffect->m_compiledShaders[compiledShaderName];

			gEffect->m_compiledShaders[compiledShaderName]	=compiledShader=new CompiledShader;
			compiledShader->m_functionName					=(yyvsp[(5) - (8)]).strs[0];
			compiledShader->shaderType						=(yyvsp[(1) - (8)]).sType;
			compiledShader->version							= (yyval).num = version_num;
			// "Compile" the shader - in the sense of "concatenate the strings and prepare it as GLSL source":
			Compile((yyvsp[(1) - (8)]).sType, sh, compiledShader);
			//gEffect->m_shaders[shaderName] = compiledShader->source; 
		}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1417 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1428 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1434 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1438 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1442 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1447 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1452 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1456 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1465 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1471 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1476 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1489 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1498 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1502 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1506 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1510 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1548 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1552 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1556 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1561 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1565 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1569 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
					(yyval).strs[1]="";
				}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1575 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=";\n";
					(yyval).strs[1]="";
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1580 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1585 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
					(yyval).strs[1]="";
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1591 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1596 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1608 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1613 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1618 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
					(yyval).strs[1]="";
				}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1624 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1629 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1634 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1639 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1654 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).strs[1]="";
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1660 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1664 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1668 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1671 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1675 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1680 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1690 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1694 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1698 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string unary_exp			=(yyvsp[(1) - (3)]).strs[0];
			string assignment_operator	=(yyvsp[(2) - (3)]).strs[0];
			string assignment_exp		=(yyvsp[(3) - (3)]).strs[0];
			string varName				=(yyvsp[(1) - (3)]).strs[1];
			string index				=(yyvsp[(1) - (3)]).strs[3];
			// Is it actually a texture we're indexing?
			GLTextureType glTextureType			=GetTextureType(buildFunction,varName);
			if(glTextureType==0||!IsRWTexture(glTextureType))
			{
				(yyval).strs[0]=unary_exp+assignment_operator+assignment_exp;
			}
			else
			{
				ostringstream str;
				if((yyvsp[(2) - (3)]).token=='=')
					str<<"imageStore("<<varName<<",ivec"<<GetTextureDimension(glTextureType)<<"("<<index<<"),"<<assignment_exp<<")";
				else
					errSem(string("Unsupported operator for image store: ")+assignment_operator);
				(yyval).strs[0]=str.str();
			}
		}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1721 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).token=(yyvsp[(1) - (1)]).token;
				}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1735 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).token=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1740 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1744 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1749 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1753 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1757 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1761 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1765 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1769 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1773 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1777 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1781 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1785 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1790 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1794 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1798 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1802 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1806 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1810 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1814 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1818 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1822 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1826 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1830 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1834 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1838 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1842 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1846 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1850 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1854 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1858 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1862 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1866 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	(yyval).strs[1]=(yyvsp[(1) - (1)]).strs[1];
	(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[2];
	(yyval).strs[3]=(yyvsp[(1) - (1)]).strs[3];
}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1873 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1877 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1881 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1885 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1889 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texture";
}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1893 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="textureLod";
}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1897 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texelFetch";
}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 1901 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1911 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 217:
/* Line 1792 of yacc.c  */
#line 1921 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 218:
/* Line 1792 of yacc.c  */
#line 1931 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).token=(yyvsp[(1) - (1)]).token;
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[0];			//Command
					}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1937 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string varName=(yyvsp[(1) - (4)]).strs[0];
						string index=(yyvsp[(3) - (4)]).strs[0];
						(yyval).strs[1]=varName;
						(yyval).strs[3]=index;
						(yyval).strs[2]=(yyvsp[(1) - (4)]).strs[2];			//Command

						
						// Is it actually a texture we're indexing?
						GLTextureType glTextureType			=GetTextureType(buildFunction,varName);
						if(glTextureType==0)
						{
							(yyval).strs[0]=varName+(yyvsp[(2) - (4)]).strs[0]+index+(yyvsp[(4) - (4)]).strs[0];
						}
						else
						{
							ostringstream str;
							if(IsRWTexture(glTextureType))
							{
								str<<"imageLoad("<<varName<<",ivec"<<GetTextureDimension(glTextureType)<<"("<<index<<"))";
							}
							else
							{
								str<<"texelFetch("<<varName<<",ivec"<<GetTextureDimension(glTextureType)<<"("<<index<<"),0)";
							}
							(yyval).strs[0]=str.str();
						}
					}
    break;

  case 220:
/* Line 1792 of yacc.c  */
#line 1966 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (6)]).strs[1];
						string x			=(yyvsp[(3) - (6)]).strs[0];
						string y			=(yyvsp[(5) - (6)]).strs[0];

						(yyval).strs[0]=GetSizeFunction( textureName, x, y,"");
					}
    break;

  case 221:
/* Line 1792 of yacc.c  */
#line 1974 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (8)]).strs[1];
						string x			=(yyvsp[(3) - (8)]).strs[0];
						string y			=(yyvsp[(5) - (8)]).strs[0];
						string z			=(yyvsp[(7) - (8)]).strs[0];
						(yyval).strs[0]=GetSizeFunction( textureName, x, y,z);
					}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1982 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName		=(yyvsp[(1) - (4)]).strs[1];
						string command			=(yyvsp[(1) - (4)]).strs[2];
						string pos,msaa_index;
						if((yyvsp[(3) - (4)]).vars)
						{
							auto vars=*((yyvsp[(3) - (4)]).vars);
							delete (yyvsp[(3) - (4)]).vars;
							pos				=vars[0].identifier;
							
							if(vars.size()>1)
								msaa_index=vars[1].identifier;
						}
						int glTextureType	=(GetTextureType(buildFunction,textureName));
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
						full_expr<<command<<"("<<textureName<<","<<pos<<".xy";
						if(return_size==3)
							full_expr<<"z,"<<pos<<".w";
						else if(!msaa_index.length())
							full_expr<<","<<pos<<".z";
						else
							full_expr<<",int("<<msaa_index<<")";
						full_expr<<")";
						(yyval).strs[0]				=full_expr.str();
					}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 2030 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 224:
/* Line 1792 of yacc.c  */
#line 2073 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 225:
/* Line 1792 of yacc.c  */
#line 2138 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						// ok this could be a function call.
						string command=(yyvsp[(1) - (3)]).strs[2];
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 2144 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[2]=expr3;			//Command
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 2151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 2155 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 2159 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars=(yyvsp[(1) - (3)]).vars;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 2167 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars = new vector<YYSTYPE::variable>;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 2175 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 2180 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 2187 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 2194 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 2201 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 2208 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 2212 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).token=(yyvsp[(1) - (1)]).token;
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 2217 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 2221 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 2225 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 2229 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 2233 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2241 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2249 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2253 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 246:
/* Line 1792 of yacc.c  */
#line 2265 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]	="";
						(yyval).num		=-1;
					}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 2270 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2274 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 2278 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 2282 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 2285 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 2289 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 2294 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 2298 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 255:
/* Line 1792 of yacc.c  */
#line 2407 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 2412 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 2418 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 258:
/* Line 1792 of yacc.c  */
#line 2423 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 2427 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 2432 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 2437 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 2442 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 5318 "src/glfxLALRParser.cpp"
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
#line 2445 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
