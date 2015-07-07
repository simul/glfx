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
		if(s==string("char4"))
		{
			return "layout(rgba8)";
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
	
	void DeclareTextureSampler(const TextureSampler *ts)
	{
		auto i=gEffect->additionalTextureDeclarations.find(ts->textureSamplerName());
		if(i!=gEffect->additionalTextureDeclarations.end())
			return;

		string tsname		=ts->textureSamplerName();
		string texture_name	=ts->textureName;
		if (gEffect->IsDeclared(texture_name))
		{
			string sampler_type =(gEffect->GetDeclaredTextures()).find(texture_name)->second.type;
			//str<<"uniform "<<sampler_type<<" "<<tsname<<";\n";
			gEffect->additionalTextureDeclarations[tsname].type		=sampler_type;
			auto d=gEffect->GetDeclaredTextures();
			gEffect->additionalTextureDeclarations[tsname].type_enum = (d.find(texture_name))->second.type_enum;
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
		auto j = gEffect->GetDeclaredTextures().find(textureName);
		if (j != gEffect->GetDeclaredTextures().end())
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
	string GetDeclaredType(string name)
	{
		if(gEffect->IsDeclared(name))
			return gEffect->GetDeclaredType(name);
		for(auto i=buildFunction.parameters.begin();i!=buildFunction.parameters.end();i++)
		{
			if(i->identifier==name)
				return i->type;
		}
		return "unknown";
	}
	bool IsBufferType(int t);

/* Line 371 of yacc.c  */
#line 397 "src/glfxLALRParser.cpp"

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
     TEXTURE2DARRAY = 313,
     TEXTURE3D = 314,
     TEXTURECUBE = 315,
     IMAGE3D = 316,
     KNOWN_TYPE = 317,
     STRUCTUREDBUFFER = 318,
     RW_STRUCTUREDBUFFER = 319,
     RETURN = 320,
     BREAK = 321,
     CONTINUE = 322,
     DO = 323,
     FOR = 324,
     GOTO = 325,
     IF = 326,
     WHILE = 327,
     ELSE = 328,
     TIMES_EQUALS = 329,
     OVER_EQUALS = 330,
     PERCENT_EQUALS = 331,
     PLUS_EQUALS = 332,
     MINUS_EQUALS = 333,
     LEFT_SHIFT_EQUALS = 334,
     RIGHT_SHIFT_EQUALS = 335,
     AND_EQUALS = 336,
     XOR_EQUALS = 337,
     OR_EQUALS = 338,
     AND = 339,
     OR = 340,
     LESS_EQ = 341,
     GRTR_EQ = 342,
     LEFT_SHIFT = 343,
     RIGHT_SHIFT = 344,
     PLUS_PLUS = 345,
     MINUS_MINUS = 346,
     EQ_EQ = 347,
     NOT_EQ = 348,
     SA_MAXVERTEXCOUNT = 349,
     SA_NUMTHREADS = 350,
     SATURATE = 351,
     SHADER_PROFILE = 352
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
#line 560 "src/glfxLALRParser.cpp"

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
#define YYLAST   672

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  122
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  103
/* YYNRULES -- Number of rules.  */
#define YYNRULES  265
/* YYNRULES -- Number of states.  */
#define YYNSTATES  561

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   352

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   120,     2,     2,     2,   118,   114,     2,
      99,   101,   110,   115,   104,   116,   121,   117,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   100,    98,
     108,   105,   109,   111,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   102,     2,   103,   113,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   106,   112,   107,   119,     2,     2,     2,
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
      95,    96,    97
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
     187,   189,   191,   193,   195,   199,   200,   208,   210,   212,
     215,   217,   223,   231,   235,   239,   243,   245,   247,   249,
     255,   259,   261,   263,   264,   265,   266,   267,   271,   272,
     275,   276,   280,   283,   285,   292,   294,   295,   299,   301,
     302,   306,   310,   311,   313,   314,   318,   323,   325,   327,
     329,   331,   332,   334,   336,   338,   340,   343,   346,   349,
     350,   352,   355,   357,   363,   365,   368,   370,   373,   375,
     386,   392,   400,   410,   415,   421,   423,   430,   439,   444,
     449,   450,   453,   454,   458,   460,   463,   465,   466,   470,
     473,   475,   479,   481,   485,   487,   491,   496,   500,   504,
     507,   509,   512,   514,   520,   528,   534,   542,   552,   556,
     559,   562,   566,   568,   570,   572,   573,   575,   576,   580,
     582,   586,   588,   592,   594,   596,   598,   600,   602,   604,
     606,   608,   610,   612,   614,   616,   622,   624,   628,   630,
     634,   636,   640,   642,   646,   648,   652,   654,   658,   662,
     664,   668,   672,   676,   680,   682,   686,   690,   692,   696,
     700,   702,   706,   710,   714,   716,   718,   721,   724,   727,
     729,   731,   733,   735,   737,   739,   741,   743,   745,   749,
     753,   757,   759,   764,   771,   780,   785,   792,   797,   801,
     805,   808,   811,   815,   817,   819,   823,   828,   830,   834,
     836,   838,   840,   844,   846,   848,   851,   854,   855,   861,
     862,   865,   868,   869,   873,   874,   877,   879,   884,   886,
     889,   893,   894,   896,   898,   900
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     123,     0,    -1,   123,   124,    -1,    -1,     9,   143,    10,
     148,    98,   146,    -1,    45,    -1,   125,    -1,    41,    48,
      99,   132,   100,    25,   101,    -1,     4,   128,   130,    10,
     216,    98,    -1,     4,   129,   130,    10,    98,    -1,     4,
      10,    10,    98,    -1,   102,    94,    99,    25,   101,   103,
      -1,   102,    95,    99,    25,   104,    25,   104,    25,   101,
     103,    -1,    29,   136,    10,    98,    -1,    29,   137,    -1,
      55,    10,    98,    -1,    55,    10,   104,    -1,    42,    44,
      45,    -1,    43,    10,    45,    -1,    40,    10,   150,    98,
      -1,    34,    10,   216,   218,    98,    -1,    47,    97,    99,
      25,   101,    98,    -1,    46,    10,   105,   171,    98,    -1,
      29,   143,   131,   146,    -1,     7,    10,   216,   144,   150,
      98,   146,    -1,    10,    10,    99,   154,   101,   145,   147,
     146,    -1,   127,    10,    10,    99,   154,   101,   149,   147,
     146,    -1,     8,   143,    10,   106,   166,   107,   146,    -1,
     135,    -1,    33,   143,    10,   106,   133,   107,   146,    -1,
      30,   143,    25,    25,   146,    -1,    30,    25,    25,    -1,
       6,   144,    -1,    57,    -1,    59,    -1,    56,    -1,    58,
      -1,    61,    -1,    52,    -1,    53,    -1,    54,    -1,    60,
      -1,    63,    -1,    64,    -1,   108,    10,   109,    -1,    -1,
      99,    25,   104,    25,   104,    25,   101,    -1,    10,    -1,
      25,    -1,   133,   134,    -1,   134,    -1,    31,    10,   106,
     163,   107,    -1,    31,   143,    10,   106,   163,   107,   146,
      -1,    99,   140,   101,    -1,    99,   138,   101,    -1,   138,
     104,   139,    -1,   139,    -1,   141,    -1,    10,    -1,   141,
     104,   141,   104,   141,    -1,    10,   105,   142,    -1,    10,
      -1,    25,    -1,    -1,    -1,    -1,    -1,   106,   176,   107,
      -1,    -1,   100,    10,    -1,    -1,   106,   151,   107,    -1,
     151,   152,    -1,   152,    -1,   153,    10,    10,   156,   217,
      98,    -1,     4,    -1,    -1,   154,   104,   155,    -1,   155,
      -1,    -1,   158,   156,   162,    -1,   102,   157,   103,    -1,
      -1,    25,    -1,    -1,    25,   110,    25,    -1,   160,   159,
     130,    10,    -1,    10,    -1,   128,    -1,   129,    -1,    15,
      -1,    -1,    21,    -1,    23,    -1,    22,    -1,    24,    -1,
     100,    25,    -1,   100,   161,    -1,   100,    10,    -1,    -1,
     164,    -1,   164,   165,    -1,   165,    -1,    32,    10,   106,
     166,   107,    -1,   167,    -1,   167,   170,    -1,   170,    -1,
     167,   169,    -1,   169,    -1,    10,    99,    28,   104,    28,
     104,    28,   104,    28,   101,    -1,    18,    99,    10,   101,
      98,    -1,    19,    99,    10,   104,    25,   101,    98,    -1,
      20,    99,    10,   104,   168,   104,    25,   101,    98,    -1,
     172,   105,   173,    98,    -1,    17,    99,   171,   101,    98,
      -1,    10,    -1,    39,    99,    10,   104,    35,   101,    -1,
      38,    99,    97,   104,    10,    99,   101,   101,    -1,    37,
      99,    25,   101,    -1,    10,    99,   101,   174,    -1,    -1,
     100,   175,    -1,    -1,   175,   104,   214,    -1,   214,    -1,
     176,   182,    -1,   182,    -1,    -1,    30,    25,    25,    -1,
     224,   179,    -1,   180,    -1,   179,   104,   180,    -1,   181,
      -1,   181,   105,   210,    -1,    10,    -1,    99,   181,   101,
      -1,   181,   102,    25,   103,    -1,   181,   102,   103,    -1,
     181,    99,   101,    -1,   186,    98,    -1,    98,    -1,   178,
      98,    -1,   185,    -1,    71,    99,   186,   101,   182,    -1,
      71,    99,   186,   101,   182,    73,   182,    -1,    72,    99,
     186,   101,   182,    -1,    68,   182,    72,    99,   186,   101,
      98,    -1,    69,    99,   183,    98,   184,    98,   184,   101,
     182,    -1,    70,    10,    98,    -1,    67,    98,    -1,    66,
      98,    -1,    65,   184,    98,    -1,   177,    -1,   186,    -1,
     178,    -1,    -1,   186,    -1,    -1,   106,   176,   107,    -1,
     187,    -1,   186,   104,   187,    -1,   189,    -1,   201,   188,
     187,    -1,   105,    -1,    74,    -1,    75,    -1,    76,    -1,
      77,    -1,    78,    -1,    79,    -1,    80,    -1,    81,    -1,
      82,    -1,    83,    -1,   190,    -1,   190,   111,   186,   100,
     189,    -1,   191,    -1,   190,    85,   191,    -1,   192,    -1,
     191,    84,   192,    -1,   193,    -1,   192,   112,   193,    -1,
     194,    -1,   193,   113,   194,    -1,   195,    -1,   194,   114,
     195,    -1,   196,    -1,   195,    92,   196,    -1,   195,    93,
     196,    -1,   197,    -1,   196,   108,   197,    -1,   196,   109,
     197,    -1,   196,    86,   197,    -1,   196,    87,   197,    -1,
     198,    -1,   197,    88,   198,    -1,   197,    89,   198,    -1,
     199,    -1,   198,   115,   199,    -1,   198,   116,   199,    -1,
     200,    -1,   199,   110,   200,    -1,   199,   117,   200,    -1,
     199,   118,   200,    -1,   201,    -1,   208,    -1,    90,   201,
      -1,    91,   201,    -1,   202,   200,    -1,   114,    -1,   110,
      -1,   115,    -1,   116,    -1,   119,    -1,   120,    -1,    11,
      -1,    12,    -1,    13,    -1,   208,   121,   204,    -1,   208,
     121,   203,    -1,   208,   121,    14,    -1,   212,    -1,   208,
     102,   186,   103,    -1,   207,    99,   187,   104,   187,   101,
      -1,   207,    99,   187,   104,   187,   104,   187,   101,    -1,
     205,    99,   209,   101,    -1,   206,    99,   187,   104,   209,
     101,    -1,   208,    99,   209,   101,    -1,   208,    99,   101,
      -1,   208,   121,    10,    -1,   208,    90,    -1,   208,    91,
      -1,   209,   104,   187,    -1,   187,    -1,   187,    -1,   106,
     211,   107,    -1,   106,   211,   104,   107,    -1,   210,    -1,
     211,   104,   210,    -1,    10,    -1,    96,    -1,   213,    -1,
      99,   186,   101,    -1,    25,    -1,    28,    -1,    15,   215,
      -1,    16,   215,    -1,    -1,   100,     5,    99,    10,   101,
      -1,    -1,   100,    10,    -1,   100,   161,    -1,    -1,   106,
     219,   107,    -1,    -1,   219,   220,    -1,   220,    -1,   221,
     105,   223,    98,    -1,   126,    -1,    10,   222,    -1,   102,
      25,   103,    -1,    -1,    10,    -1,    25,    -1,    28,    -1,
      10,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   341,   341,   342,   396,   400,   403,   406,   409,   444,
     460,   466,   470,   476,   479,   485,   491,   497,   501,   507,
     524,   564,   574,   592,   595,   612,   736,   771,   775,   778,
     786,   793,   799,   804,   804,   804,   804,   804,   804,   804,
     804,   804,   810,   810,   816,   822,   826,   840,   843,   846,
     850,   853,   857,   867,   871,   876,   880,   884,   888,   892,
     900,   906,   910,   915,   922,   929,   936,   940,   947,   952,
     957,   960,   965,   971,   976,   995,  1000,  1003,  1017,  1033,
    1038,  1069,  1075,  1079,  1085,  1090,  1095,  1121,  1126,  1131,
    1136,  1141,  1144,  1149,  1154,  1159,  1164,  1169,  1175,  1181,
    1186,  1193,  1205,  1219,  1226,  1233,  1250,  1271,  1280,  1289,
    1298,  1302,  1308,  1316,  1324,  1390,  1402,  1467,  1510,  1521,
    1528,  1531,  1536,  1540,  1545,  1549,  1558,  1565,  1569,  1582,
    1593,  1597,  1601,  1605,  1655,  1659,  1663,  1670,  1675,  1679,
    1685,  1690,  1695,  1701,  1706,  1718,  1723,  1728,  1734,  1739,
    1744,  1749,  1764,  1770,  1774,  1779,  1781,  1786,  1790,  1796,
    1800,  1804,  1808,  1831,  1836,  1837,  1838,  1839,  1840,  1841,
    1842,  1843,  1844,  1845,  1850,  1854,  1859,  1863,  1867,  1871,
    1875,  1879,  1883,  1887,  1891,  1895,  1900,  1904,  1908,  1912,
    1916,  1920,  1924,  1928,  1932,  1936,  1940,  1944,  1948,  1952,
    1956,  1960,  1964,  1968,  1972,  1976,  1983,  1987,  1991,  1995,
    1995,  1995,  1995,  1995,  1995,  1999,  2003,  2007,  2011,  2021,
    2031,  2041,  2047,  2076,  2084,  2092,  2140,  2191,  2268,  2274,
    2281,  2285,  2289,  2297,  2305,  2310,  2317,  2324,  2331,  2338,
    2342,  2347,  2351,  2355,  2359,  2363,  2371,  2380,  2383,  2396,
    2400,  2404,  2409,  2412,  2416,  2419,  2424,  2428,  2537,  2542,
    2548,  2554,  2557,  2562,  2567,  2572
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
  "TEXTURE2DARRAY", "TEXTURE3D", "TEXTURECUBE", "IMAGE3D", "KNOWN_TYPE",
  "STRUCTUREDBUFFER", "RW_STRUCTUREDBUFFER", "RETURN", "BREAK", "CONTINUE",
  "DO", "FOR", "GOTO", "IF", "WHILE", "ELSE", "TIMES_EQUALS",
  "OVER_EQUALS", "PERCENT_EQUALS", "PLUS_EQUALS", "MINUS_EQUALS",
  "LEFT_SHIFT_EQUALS", "RIGHT_SHIFT_EQUALS", "AND_EQUALS", "XOR_EQUALS",
  "OR_EQUALS", "AND", "OR", "LESS_EQ", "GRTR_EQ", "LEFT_SHIFT",
  "RIGHT_SHIFT", "PLUS_PLUS", "MINUS_MINUS", "EQ_EQ", "NOT_EQ",
  "SA_MAXVERTEXCOUNT", "SA_NUMTHREADS", "SATURATE", "SHADER_PROFILE",
  "';'", "'('", "':'", "')'", "'['", "']'", "','", "'='", "'{'", "'}'",
  "'<'", "'>'", "'*'", "'?'", "'|'", "'^'", "'&'", "'+'", "'-'", "'/'",
  "'%'", "'~'", "'!'", "'.'", "$accept", "prog", "tok", "line_statement",
  "ignore_line_statement", "shader_and_layout", "texture_type",
  "buffer_type", "optional_templateval", "layout_params",
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
     345,   346,   347,   348,   349,   350,   351,   352,    59,    40,
      58,    41,    91,    93,    44,    61,   123,   125,    60,    62,
      42,    63,   124,    94,    38,    43,    45,    47,    37,   126,
      33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   122,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   126,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   129,   129,   130,   130,   131,   132,   132,   133,
     133,   134,   135,   136,   137,   138,   138,   139,   139,   140,
     141,   142,   142,   143,   144,   145,   146,   147,   148,   149,
     149,   150,   151,   151,   152,   153,   153,   154,   154,   154,
     155,   156,   156,   157,   157,   157,   158,   159,   159,   159,
     160,   160,   161,   161,   161,   161,   162,   162,   162,   162,
     163,   164,   164,   165,   166,   167,   167,   167,   167,   168,
     169,   169,   169,   170,   170,   171,   171,   171,   172,   173,
     173,   174,   174,   175,   175,   176,   176,   176,   177,   178,
     179,   179,   180,   180,   181,   181,   181,   181,   181,   182,
     182,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     182,   182,   182,   183,   183,   183,   184,   184,   185,   186,
     186,   187,   187,   188,   188,   188,   188,   188,   188,   188,
     188,   188,   188,   188,   189,   189,   190,   190,   191,   191,
     192,   192,   193,   193,   194,   194,   195,   195,   195,   196,
     196,   196,   196,   196,   197,   197,   197,   198,   198,   198,
     199,   199,   199,   199,   200,   201,   201,   201,   201,   202,
     202,   202,   202,   202,   202,   203,   203,   204,   205,   206,
     207,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   209,   209,   210,   210,   210,   211,   211,   212,
     212,   212,   212,   213,   213,   214,   214,   215,   216,   216,
     217,   217,   217,   218,   218,   219,   219,   220,   220,   221,
     222,   222,   223,   223,   223,   224
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     1,     1,     7,     6,     5,
       4,     6,    10,     4,     2,     3,     3,     3,     3,     4,
       5,     6,     5,     4,     7,     8,     9,     7,     1,     7,
       5,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     7,     1,     1,     2,
       1,     5,     7,     3,     3,     3,     1,     1,     1,     5,
       3,     1,     1,     0,     0,     0,     0,     3,     0,     2,
       0,     3,     2,     1,     6,     1,     0,     3,     1,     0,
       3,     3,     0,     1,     0,     3,     4,     1,     1,     1,
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     1,     4,     6,     8,     4,     6,     4,     3,     3,
       2,     2,     3,     1,     1,     3,     4,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     0,     5,     0,
       2,     2,     0,     3,     0,     2,     1,     4,     1,     2,
       3,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       3,     0,     1,     0,    64,     0,    63,    63,     0,     0,
      63,    63,    63,     0,     0,     0,     0,     0,     5,     0,
       0,     0,     0,     2,     6,     0,    28,     0,    38,    39,
      40,    35,    33,    36,    34,    41,    37,    42,    43,    45,
      45,    32,   249,     0,     0,     0,     0,     0,    14,     0,
       0,     0,     0,   249,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    68,    91,    58,     0,    56,     0,    57,     0,     0,
      66,     0,     0,     0,   254,    76,     0,     0,    17,    18,
       0,     0,    15,    16,     0,     0,     0,    10,     0,   249,
       0,     0,     0,     0,     0,    90,     0,    78,    82,     0,
       0,    54,     0,    53,     0,    13,     0,    23,    66,     0,
       0,     0,     0,    75,    76,    73,     0,    19,    47,    48,
       0,   115,     0,     0,     0,     0,     0,     0,    91,    44,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
     104,   108,   106,     0,    66,    65,    91,    84,    99,    87,
      88,    89,    45,    61,    62,    60,    55,    57,     0,     0,
       0,    30,     0,     0,   100,   102,     0,     0,    50,   261,
       0,   258,     0,   256,     0,    20,    71,    72,     0,     0,
       0,     0,    22,     0,     0,     0,     0,     8,     0,    66,
       0,     0,     0,     0,     0,    66,   107,   105,   120,     4,
       0,    77,    83,     0,     0,    80,     0,     0,     0,     0,
      66,   101,     0,    66,    49,     0,   259,     0,   253,   255,
       0,    82,     0,     0,     0,    21,    11,     0,    70,   248,
      24,     0,     0,     0,     0,     0,    27,     0,     0,   127,
      66,     0,    81,    98,    92,    94,    93,    95,    96,    97,
      86,    59,     0,     0,    52,     0,    29,     0,    31,   262,
     263,   264,     0,   252,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,     0,   113,   239,   243,   244,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   240,   140,     0,   127,   210,   209,   211,   212,   213,
     214,     0,   152,     0,   126,   142,     0,   159,   161,   174,
     176,   178,   180,   182,   184,   186,   189,   194,   197,   200,
     204,     0,     0,     0,     0,   205,   221,   241,     0,    25,
      85,     0,     0,     0,   260,   257,     0,     0,     0,     0,
       0,    69,    66,   114,   110,     0,     0,     0,   122,     0,
     239,     0,   156,   150,   149,     0,   155,     0,     0,     0,
     206,   207,     0,     0,    67,   125,   141,   139,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   163,     0,
     208,   204,     0,     0,     0,   230,   231,     0,     0,     0,
     134,     0,   129,   130,   132,    46,   103,    51,   250,   251,
      74,     0,   116,     0,    26,     0,     0,     0,     0,   119,
     128,   151,     0,   154,     0,   153,   148,     0,     0,   242,
     158,   160,   177,     0,   179,   181,   183,   185,   187,   188,
     192,   193,   190,   191,   195,   196,   198,   199,   201,   202,
     203,   162,   233,     0,     0,     0,   228,     0,     0,   229,
     215,   216,   217,   220,   219,   218,     0,     0,     0,     0,
       0,     0,    12,   111,     0,     0,   247,   247,   121,   124,
       0,   157,     0,     0,     0,   225,     0,     0,     0,   227,
     222,   135,   131,   138,     0,   137,     0,   234,   133,   117,
       0,     0,   245,   246,     0,     0,     0,   143,   145,   175,
     232,     0,     0,   136,   237,     0,     0,   112,   123,     0,
     157,     0,   226,   223,     0,     0,   235,     0,   146,     0,
     144,     0,   236,   238,     0,     0,   224,     0,   147,     0,
     109
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   181,    25,    39,    40,    66,    80,
     130,   177,   178,    26,    47,    48,    74,    75,    76,    77,
     165,    43,    41,   210,   117,   250,   104,   279,    86,   124,
     125,   126,   106,   107,   158,   213,   108,   162,   109,   259,
     215,   173,   174,   175,   149,   150,   357,   151,   152,   134,
     153,   248,   439,   498,   311,   312,   313,   422,   423,   424,
     314,   444,   361,   315,   316,   317,   409,   318,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   484,   485,   332,   333,   334,   335,   473,   518,   535,
     336,   337,   499,   522,    69,   347,   122,   182,   183,   184,
     226,   272,   338
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -504
static const yytype_int16 yypact[] =
{
    -504,   461,  -504,     8,  -504,     9,  -504,  -504,    25,   -54,
    -504,  -504,  -504,    60,    65,    42,    52,   125,  -504,   138,
      32,   143,     7,  -504,  -504,   147,  -504,   151,  -504,  -504,
    -504,  -504,  -504,  -504,  -504,  -504,  -504,  -504,  -504,   111,
     111,  -504,   150,   204,   211,   159,   253,   254,  -504,   166,
     249,   278,   279,   150,   188,   197,   256,   258,   193,   205,
     -49,   207,   213,   300,   215,   304,   308,   309,   317,  -504,
     217,  -504,    -7,   220,    33,  -504,   225,   224,   231,   313,
    -504,   314,   234,   235,   247,   354,   261,    13,  -504,  -504,
     121,   337,  -504,  -504,   340,   341,   271,  -504,   268,   150,
     280,   283,   188,   152,   288,  -504,    51,  -504,   286,   420,
      29,  -504,   253,  -504,   384,  -504,   295,  -504,  -504,   368,
     370,     6,   305,  -504,    20,  -504,   392,  -504,  -504,  -504,
     307,  -504,   311,   312,   306,   315,   316,   320,    -7,  -504,
     310,  -504,   402,   322,   326,   327,   328,   330,   333,   329,
     152,  -504,  -504,   334,  -504,  -504,   406,   408,   338,  -504,
    -504,  -504,   111,  -504,  -504,  -504,  -504,  -504,   220,   345,
     412,  -504,   431,   343,   368,  -504,   434,   -22,  -504,   351,
     430,  -504,    -3,  -504,   352,  -504,  -504,  -504,   435,   437,
     359,   456,  -504,   377,   379,   460,    79,  -504,   385,  -504,
     121,   477,   478,   479,   468,  -504,  -504,  -504,   486,  -504,
     391,  -504,   388,   396,   163,  -504,   490,   384,   401,   403,
    -504,  -504,   404,  -504,  -504,   487,  -504,   488,  -504,  -504,
      49,   286,   410,   411,   413,  -504,  -504,   414,   419,  -504,
    -504,   421,   422,   416,   417,   423,  -504,   415,   427,   265,
    -504,   501,  -504,  -504,  -504,  -504,  -504,  -504,  -504,  -504,
    -504,  -504,   502,   152,  -504,   368,  -504,   425,  -504,  -504,
    -504,  -504,   432,   429,  -504,   521,   497,   508,   524,   391,
     438,   439,   510,   528,  -504,   440,  -504,   529,  -504,  -504,
     515,   332,   444,   445,   265,   446,   534,   447,   448,   332,
     332,  -504,  -504,   332,   265,  -504,  -504,  -504,  -504,  -504,
    -504,   126,  -504,   450,  -504,  -504,   -11,  -504,  -504,   -71,
     465,   441,   442,   436,    73,   -56,    93,    84,   -89,  -504,
     269,   332,   452,   453,   455,   -58,  -504,  -504,    -8,  -504,
    -504,   457,   449,   454,  -504,  -504,   180,   459,   463,   458,
     464,  -504,  -504,  -504,  -504,   466,   467,   469,   470,   535,
    -504,   471,   472,  -504,  -504,   492,   344,   473,   332,   332,
    -504,  -504,   106,   201,  -504,  -504,  -504,  -504,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,  -504,  -504,
    -504,  -504,  -504,  -504,  -504,  -504,  -504,  -504,  -504,   332,
    -504,  -504,   332,   332,   332,  -504,  -504,    48,   332,   266,
    -504,    -8,   474,  -504,   -16,  -504,  -504,  -504,  -504,  -504,
    -504,   476,  -504,   480,  -504,   481,   540,   547,   190,  -504,
    -504,  -504,   475,  -504,   482,   472,  -504,   114,   119,  -504,
    -504,  -504,   465,    28,   441,   442,   436,    73,   -56,   -56,
      93,    93,    93,    93,    84,    84,   -89,   -89,  -504,  -504,
    -504,  -504,  -504,   133,   483,   484,  -504,   156,   124,  -504,
    -504,  -504,  -504,  -504,  -504,  -504,    44,    -8,   485,   -19,
     277,   489,  -504,  -504,   491,   493,  -504,  -504,   494,  -504,
     332,   332,   265,   265,   332,  -504,   332,   332,   332,  -504,
    -504,  -504,  -504,  -504,   496,  -504,   277,  -504,  -504,  -504,
     553,   495,  -504,  -504,   190,   158,   498,   509,  -504,  -504,
    -504,   181,   182,  -504,  -504,   177,   499,  -504,  -504,   503,
     332,   265,  -504,  -504,   332,   299,  -504,   556,  -504,   504,
    -504,   505,  -504,  -504,   500,   265,  -504,   557,  -504,   506,
    -504
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -504,  -504,  -504,  -504,  -504,  -504,   507,   511,   -36,  -504,
    -504,  -504,   398,  -504,  -504,  -504,  -504,   512,  -504,   -92,
    -504,   244,   520,  -504,  -117,   318,  -504,  -504,   513,  -504,
     514,  -504,   462,   516,   360,  -504,  -504,  -504,  -504,   246,
    -504,   346,  -504,   428,   347,  -504,  -504,   517,   518,   409,
    -504,  -504,  -504,  -504,   319,  -504,   242,  -504,   127,   191,
    -294,  -504,  -490,  -504,  -288,  -366,  -504,   109,  -504,   238,
     237,   239,   236,   241,  -147,  -213,  -148,  -145,  -297,  -274,
    -504,  -504,  -504,  -504,  -504,  -504,  -504,  -412,  -503,  -504,
    -504,  -504,    98,   129,   -43,  -504,  -504,  -504,   451,  -504,
    -504,  -504,  -504
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -266
static const yytype_int16 yytable[] =
{
     365,   171,   420,   362,    67,   477,   514,   179,   105,   176,
      84,   526,   451,   534,   379,   372,   179,   375,    27,    42,
     167,   395,   169,   128,   123,   370,   371,   180,   396,   397,
     387,   388,   415,   416,   410,    45,   180,   209,   129,   163,
     380,   417,   553,   471,   418,    46,   472,   474,   475,    92,
     549,   472,   389,   390,   164,    93,   140,   411,   360,   269,
      28,    29,    30,   419,    31,    32,    33,    34,    35,    36,
      53,    37,    38,   288,   270,    54,   289,   271,   445,   375,
     447,   448,   240,   488,   515,   223,   489,   377,   246,   490,
      55,   421,   453,   378,   -79,   531,    56,   -79,   468,   469,
     470,    61,    62,   264,   228,   411,   266,   411,   411,   411,
     411,   411,   411,   411,   411,   411,   411,   411,   411,   411,
     411,   411,   411,   411,   517,   261,   216,   186,   504,    59,
     478,   131,   378,   339,   111,    57,   287,   112,   299,   300,
     530,   472,   532,   488,   301,   511,   489,   303,    58,   476,
     517,   288,   155,    60,   289,   156,   290,    63,   305,   132,
     133,    64,   306,   307,   308,   385,   386,   309,   310,   144,
     145,   146,   147,   253,   460,   461,   462,   463,   551,   517,
     238,   391,   392,   156,   254,   255,   256,   257,   258,   148,
     428,   291,   292,   293,   294,   295,   296,   297,   298,   393,
     394,   254,   255,   256,   257,   496,   497,   449,   527,   528,
     378,   287,   525,   362,    70,   502,   299,   300,   378,    65,
     503,    71,   301,   378,   302,   303,   288,   510,   378,   289,
     411,   290,   304,   374,   505,   434,   305,   506,   458,   459,
     306,   307,   308,   464,   465,   309,   310,   550,   466,   467,
      68,    44,   362,    49,    50,    51,    52,   509,    72,   539,
     506,   558,   378,    73,    78,    79,   291,   292,   293,   294,
     295,   296,   297,   298,    81,   287,   479,   480,   481,   482,
     483,   545,   542,   543,   546,   506,   544,   360,    82,    83,
     288,   299,   300,   289,    85,   290,    87,   301,    90,   302,
     303,    88,   288,    89,    91,   289,    94,   304,   450,   360,
      96,   305,    95,    97,    98,   306,   307,   308,    99,   100,
     309,   310,   101,   103,   288,   110,   113,   289,   114,   115,
     291,   292,   293,   294,   295,   296,   297,   298,   116,   118,
     119,   120,   360,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   121,   287,   299,   300,   288,   123,   127,
     289,   301,   135,   302,   303,   136,   137,   299,   300,   288,
     138,   304,   289,   301,   408,   305,   303,   139,   141,   306,
     307,   308,   142,   516,   309,   310,   154,   305,   157,   299,
     300,   306,   307,   308,   168,   301,   309,   310,   303,   170,
     172,   176,   188,   185,   192,   516,   552,   189,   197,   305,
     190,   191,   198,   306,   307,   308,   193,   194,   309,   310,
     199,   105,   299,   300,   195,   200,   201,   202,   301,   203,
     159,   303,   204,   212,   299,   300,   205,   218,   214,   208,
     301,   219,   305,   303,   222,   231,   306,   307,   308,   217,
     220,   309,   310,   225,   305,   227,   233,   230,   306,   307,
     308,     2,   232,   309,   310,     3,   234,     4,     5,     6,
       7,     8,    28,    29,    30,   235,    31,    32,    33,    34,
      35,    36,   236,    37,    38,   237,   239,   242,   243,   244,
       9,    10,    11,   245,    12,    13,   247,   249,   251,   252,
     260,    14,    15,    16,    17,   262,    18,    19,    20,   263,
     265,   274,   267,   268,   285,   275,    21,   276,   277,   278,
     282,   283,   280,   281,   284,   286,   340,   341,   344,   346,
     345,   348,   349,   350,   351,   355,   353,   354,   356,  -265,
     359,   358,   363,   364,   367,   366,   368,   369,   376,   381,
     384,   412,   413,   382,   414,   383,   426,   430,   425,   432,
     440,   427,   431,    22,   442,   433,   436,   435,   494,   441,
     438,   446,   495,   437,   500,   224,   378,   491,   487,   493,
     501,   536,   541,   492,   554,   559,   513,   507,   508,   102,
     519,   273,   429,   537,   521,   520,   540,   352,   524,   533,
     196,   548,   221,   547,   557,   555,   556,   560,   443,   241,
     342,   343,   486,   529,   512,   143,   160,   452,   454,   456,
     161,   455,   538,   373,   166,   457,   523,     0,     0,     0,
       0,     0,     0,   229,     0,     0,     0,     0,   187,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   206,   207,     0,
       0,     0,   211
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-504)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     294,   118,    10,   291,    40,   417,    25,    10,    15,    31,
      53,   501,   378,   516,    85,   303,    10,   311,    10,    10,
     112,   110,   114,    10,     4,   299,   300,    30,   117,   118,
      86,    87,    90,    91,   331,    10,    30,   154,    25,    10,
     111,    99,   545,   409,   102,    99,   412,   413,   414,    98,
     540,   417,   108,   109,    25,   104,    99,   331,    10,    10,
      52,    53,    54,   121,    56,    57,    58,    59,    60,    61,
      10,    63,    64,    25,    25,    10,    28,    28,   366,   373,
     368,   369,   199,    99,   103,   107,   102,    98,   205,   105,
      48,    99,   380,   104,   101,   507,    44,   104,   395,   396,
     397,    94,    95,   220,   107,   379,   223,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,   397,   490,   217,   162,   107,   100,    97,
     418,    10,   104,   250,   101,    10,    10,   104,    90,    91,
     506,   507,   508,    99,    96,   101,   102,    99,    10,   101,
     516,    25,   101,    10,    28,   104,    30,    10,   110,    38,
      39,    10,   114,   115,   116,    92,    93,   119,   120,    17,
      18,    19,    20,    10,   387,   388,   389,   390,   544,   545,
     101,    88,    89,   104,    21,    22,    23,    24,    25,    37,
      10,    65,    66,    67,    68,    69,    70,    71,    72,   115,
     116,    21,    22,    23,    24,    15,    16,   101,   502,   503,
     104,    10,   500,   501,    10,   101,    90,    91,   104,   108,
     101,    10,    96,   104,    98,    99,    25,   103,   104,    28,
     504,    30,   106,   107,   101,   352,   110,   104,   385,   386,
     114,   115,   116,   391,   392,   119,   120,   541,   393,   394,
     100,     7,   540,     9,    10,    11,    12,   101,    99,   101,
     104,   555,   104,    10,    10,    99,    65,    66,    67,    68,
      69,    70,    71,    72,    25,    10,    10,    11,    12,    13,
      14,   104,   101,   101,   107,   104,   104,    10,    10,    10,
      25,    90,    91,    28,   106,    30,    99,    96,   105,    98,
      99,    45,    25,    45,    99,    28,    99,   106,   107,    10,
      10,   110,    99,    98,    10,   114,   115,   116,    10,    10,
     119,   120,     5,   106,    25,   105,   101,    28,   104,    98,
      65,    66,    67,    68,    69,    70,    71,    72,    25,    25,
     106,   106,    10,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,   106,    10,    90,    91,    25,     4,    98,
      28,    96,    25,    98,    99,    25,    25,    90,    91,    25,
      99,   106,    28,    96,   105,   110,    99,   109,    98,   114,
     115,   116,    99,   106,   119,   120,    98,   110,   102,    90,
      91,   114,   115,   116,    10,    96,   119,   120,    99,   104,
      32,    31,    10,    98,    98,   106,   107,   100,    98,   110,
      99,    99,    10,   114,   115,   116,   101,   101,   119,   120,
      98,    15,    90,    91,   104,    99,    99,    99,    96,    99,
      10,    99,    99,    25,    90,    91,   107,    25,   100,   105,
      96,    10,   110,    99,    10,    10,   114,   115,   116,   104,
     107,   119,   120,   102,   110,    25,    97,   105,   114,   115,
     116,     0,    25,   119,   120,     4,    10,     6,     7,     8,
       9,    10,    52,    53,    54,    98,    56,    57,    58,    59,
      60,    61,   103,    63,    64,    25,   101,    10,    10,    10,
      29,    30,    31,    25,    33,    34,    10,   106,   110,   103,
      10,    40,    41,    42,    43,   104,    45,    46,    47,   106,
     106,   101,    25,    25,    99,   104,    55,   104,   104,   100,
     104,   104,   101,   101,   101,    98,    25,    25,   103,   100,
      98,    10,    35,    25,    10,    25,    98,    98,    10,    10,
      25,   101,    98,    98,    10,    99,    99,    99,    98,    84,
     114,    99,    99,   112,    99,   113,   107,    98,   101,   101,
      25,   107,    99,   102,    72,   101,    99,   101,    28,    98,
     100,    98,    25,   104,    99,   177,   104,   101,   104,    98,
      98,    28,    73,   103,    28,    28,   101,   104,   104,    69,
     101,   231,   346,    98,   101,   104,    98,   279,   104,   103,
     138,    98,   174,   104,   104,   101,   101,   101,   366,   200,
     263,   265,   421,   504,   487,   102,   109,   379,   381,   383,
     109,   382,   524,   304,   112,   384,   497,    -1,    -1,    -1,
      -1,    -1,    -1,   182,    -1,    -1,    -1,    -1,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   150,    -1,
      -1,    -1,   156
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   123,     0,     4,     6,     7,     8,     9,    10,    29,
      30,    31,    33,    34,    40,    41,    42,    43,    45,    46,
      47,    55,   102,   124,   125,   127,   135,    10,    52,    53,
      54,    56,    57,    58,    59,    60,    61,    63,    64,   128,
     129,   144,    10,   143,   143,    10,    99,   136,   137,   143,
     143,   143,   143,    10,    10,    48,    44,    10,    10,    97,
      10,    94,    95,    10,    10,   108,   130,   130,   100,   216,
      10,    10,    99,    10,   138,   139,   140,   141,    10,    99,
     131,    25,    10,    10,   216,   106,   150,    99,    45,    45,
     105,    99,    98,   104,    99,    99,    10,    98,    10,    10,
      10,     5,   144,   106,   148,    15,   154,   155,   158,   160,
     105,   101,   104,   101,   104,    98,    25,   146,    25,   106,
     106,   106,   218,     4,   151,   152,   153,    98,    10,    25,
     132,    10,    38,    39,   171,    25,    25,    25,    99,   109,
     216,    98,    99,   150,    17,    18,    19,    20,    37,   166,
     167,   169,   170,   172,    98,   101,   104,   102,   156,    10,
     128,   129,   159,    10,    25,   142,   139,   141,    10,   141,
     104,   146,    32,   163,   164,   165,    31,   133,   134,    10,
      30,   126,   219,   220,   221,    98,   107,   152,    10,   100,
      99,    99,    98,   101,   101,   104,   154,    98,    10,    98,
      99,    99,    99,    99,    99,   107,   169,   170,   105,   146,
     145,   155,    25,   157,   100,   162,   130,   104,    25,    10,
     107,   165,    10,   107,   134,   102,   222,    25,   107,   220,
     105,    10,    25,    97,    10,    98,   103,    25,   101,   101,
     146,   171,    10,    10,    10,    25,   146,    10,   173,   106,
     147,   110,   103,    10,    21,    22,    23,    24,    25,   161,
      10,   141,   104,   106,   146,   106,   146,    25,    25,    10,
      25,    28,   223,   156,   101,   104,   104,   104,   100,   149,
     101,   101,   104,   104,   101,    99,    98,    10,    25,    28,
      30,    65,    66,    67,    68,    69,    70,    71,    72,    90,
      91,    96,    98,    99,   106,   110,   114,   115,   116,   119,
     120,   176,   177,   178,   182,   185,   186,   187,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     201,   202,   205,   206,   207,   208,   212,   213,   224,   146,
      25,    25,   166,   163,   103,    98,   100,   217,    10,    35,
      25,    10,   147,    98,    98,    25,    10,   168,   101,    25,
      10,   184,   186,    98,    98,   182,    99,    10,    99,    99,
     201,   201,   186,   176,   107,   182,    98,    98,   104,    85,
     111,    84,   112,   113,   114,    92,    93,    86,    87,   108,
     109,    88,    89,   115,   116,   110,   117,   118,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,   105,   188,
     200,   201,    99,    99,    99,    90,    91,    99,   102,   121,
      10,    99,   179,   180,   181,   101,   107,   107,    10,   161,
      98,    99,   101,   101,   146,   101,    99,   104,   100,   174,
      25,    98,    72,   178,   183,   186,    98,   186,   186,   101,
     107,   187,   191,   186,   192,   193,   194,   195,   196,   196,
     197,   197,   197,   197,   198,   198,   199,   199,   200,   200,
     200,   187,   187,   209,   187,   187,   101,   209,   186,    10,
      11,    12,    13,    14,   203,   204,   181,   104,    99,   102,
     105,   101,   103,    98,    28,    25,    15,    16,   175,   214,
      99,    98,   101,   101,   100,   101,   104,   104,   104,   101,
     103,   101,   180,   101,    25,   103,   106,   187,   210,   101,
     104,   101,   215,   215,   104,   186,   184,   182,   182,   189,
     187,   209,   187,   103,   210,   211,    28,    98,   214,   101,
      98,    73,   101,   101,   104,   104,   107,   104,    98,   184,
     182,   187,   107,   210,    28,   101,   101,   104,   182,    28,
     101
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
#line 342 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
							"}\n"
							"vec3 mul(mat3 m,vec3 v)"
							"{"
							"	return m*v;"
							"}\n"
							"vec2 mul(mat2 m,vec2 v)"
							"{"
							"	return m*v;"
							"}\n"
							"vec4 mul(vec4 v,mat4 m)"
							"{"
							"	return v*m;"
							"}\n"
							"vec3 mul(vec3 v,mat3 m)"
							"{"
							"	return v*m;"
							"}\n"
							"vec2 mul(vec2 v,mat2 m)"
							"{"
							"	return v*m;"
							"}\n";
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 397 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 401 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 404 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 407 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 410 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
		WriteLineNumber(decl,current_filenumber,(yyvsp[(1) - (6)]).lineno+last_linenumber-global_linenumber);

		decl<<layout<<"uniform "<<type<<" "<<texture_name<<";\n";
		gEffect->m_declaredTextures[texture_name].type = type;
		gEffect->m_declaredTextures[texture_name].type_enum = type_enum;
		gEffect->m_sharedCode << decl.str(); 
		if(compute_only)
			gEffect->m_sharedCode<<"#endif\n";
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 445 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 461 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 467 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 471 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout.x=(yyvsp[(4) - (10)]).num;
		currentCsLayout.y=(yyvsp[(6) - (10)]).num;
		currentCsLayout.z=(yyvsp[(8) - (10)]).num;
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 477 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 480 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 486 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 492 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 498 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name					=(yyvsp[(2) - (3)]).strs[0];
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 502 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name		=(yyvsp[(2) - (3)]).strs[0];
		string str		=string("#undef ")+name+"\n";
		glfxWrite(str.c_str()); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 508 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 525 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 565 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 575 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		// We here declare that a named shader should be compiled with the specified profile (e.g. GLSL 4.30)
		// and assign a variable name to the shader/profile combination. Later on, in pass definitions,
		// we can assign the shader to one or more passes.
		string compiledShaderName		=(yyvsp[(2) - (5)]).strs[0];
		CompiledShader *compiledShader	=gEffect->m_compiledShaders[(yyvsp[(4) - (5)]).strs[0]];
		CompiledShaderMap::iterator i	=gEffect->m_compiledShaders.find(compiledShaderName);
		if(i!=gEffect->m_compiledShaders.end())
		{
			delete i->second;
			// TODO: Warn here about double-compiling a shader.
			glfxWarning("double-compiling shader ");
		}
		if((yyvsp[(1) - (5)]).sType!=(yyvsp[(4) - (5)]).sType)
			errSem((((string("Shader type mismatch for ")+compiledShaderName+" - can't assign ")+ShaderTypeToString((yyvsp[(4) - (5)]).sType)+" shader to ")+ShaderTypeToString((yyvsp[(1) - (5)]).sType)+" shader").c_str());
		gEffect->m_compiledShaders[compiledShaderName]=compiledShader;
	}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 593 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 596 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 613 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string functionName		=(yyvsp[(2) - (8)]).strs[0];
		Function *f				=new Function;
		*f						=buildFunction;
		if(buildFunction.textureSamplers.size())
		{
	//		std::cout<<"ts: "<<functionName.c_str()<<std::endl;
		}
		gEffect->functions[functionName].push_back(f);
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
				
					
					glfxstype::variable p;
					p.storage		=j->storage;
					p.type			=j->type;
					p.identifier	=(ts->textureName+"_")+ts->samplerStateName;
					p.template_		=j->template_;
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
					// in m_declaredTextures.
					for(auto v=u->second.begin();v!=u->second.end();v++)
					{
						if(start)
							start=false;
						else
							params<<", ";
						TextureSampler *ts=*v;
						string type=GetTypeOfParameter(f->parameters,ts->textureName);
						if(type.length()==0)
							type = gEffect->m_declaredTextures[ts->textureName].type;
						params<<j->storage<<" "<<type<<" "<<ts->textureName<<"_"<<ts->samplerStateName;
						//if(j->semantic.size())
						//	params<<": "<<j->semantic;
						glfxstype::variable p;
						p.storage			=j->storage;
						p.type				=type;
						p.identifier		=ts->textureSamplerName();
						p.template_			=j->template_;
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
#line 737 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		CompilableShader &sh=*(compilableShaders[(yyvsp[(3) - (9)]).strs[0]]=new CompilableShader);
		sh.shaderName			=(yyvsp[(3) - (9)]).strs[0];
		sh.maxGSVertexCount		=maxVertexCount;
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
#line 772 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 776 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 779 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 787 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 794 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 800 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 805 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 811 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 817 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 822 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 827 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 47:
/* Line 1792 of yacc.c  */
#line 841 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 844 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 847 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 851 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 854 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 858 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 53:
/* Line 1792 of yacc.c  */
#line 868 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 872 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 877 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 881 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 885 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 889 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 893 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				currentCsLayout.x=(yyvsp[(1) - (5)]).num;
				currentCsLayout.y=(yyvsp[(3) - (5)]).num;
				currentCsLayout.z=(yyvsp[(5) - (5)]).num;
				(yyval).layoutType=CS_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		  }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 901 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				(yyval).num=(yyvsp[(3) - (3)]).num;
		   }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 907 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 911 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 915 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 922 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 929 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_function=true;
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 936 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 940 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 947 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 953 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
 }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 957 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
 }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 961 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="{\n";
	(yyval).strs[0]+=((yyvsp[(2) - (3)]).strs[0]+"\n}\n");
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 966 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string list			=(yyvsp[(1) - (2)]).strs[0];
	string new_member	=(yyvsp[(2) - (2)]).strs[0];
    (yyval).strs[0]=(list+"\n")+new_member;
}
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 972 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string member	=(yyvsp[(1) - (1)]).strs[0];
    (yyval).strs[0]=member;
}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 977 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
	s.name		=name+sq;
	buildStruct.m_structMembers.push_back(s);
	(yyval).strs[0]=(unif.length()?(unif+" "):"");
    (yyval).strs[0]+=(type+" ")+name;
	(yyval).strs[0]+=sq;
	(yyval).strs[0]+=sem.length()?(string(": ")+sem):"";
	(yyval).strs[0]+=";";
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 996 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="uniform";
}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 1000 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 1004 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars		=(yyvsp[(1) - (3)]).vars;
		(yyval).strs[0]	=((yyvsp[(1) - (3)]).strs[0]+",")+(yyvsp[(3) - (3)]).strs[0];

		YYSTYPE::variable var;
		var.storage		=(yyvsp[(3) - (3)]).strs[1];
		var.type		=(yyvsp[(3) - (3)]).strs[2];
		var.identifier	=(yyvsp[(3) - (3)]).strs[3];
		var.template_	=(yyvsp[(3) - (3)]).strs[4];
		var.type_enum = ToGLTextureType((yyvsp[(3) - (3)]).token);
		(yyval).vars->push_back(var);
		buildFunction.parameters.push_back(var);
	}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 1018 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		YYSTYPE::variable var;
		string s1	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).strs[0]	=s1;
		var.storage		=(yyvsp[(1) - (1)]).strs[1];
		var.type		=(yyvsp[(1) - (1)]).strs[2];
		var.identifier	=(yyvsp[(1) - (1)]).strs[3];
		var.template_	=(yyvsp[(1) - (1)]).strs[4];
		var.type_enum = ToGLTextureType((yyvsp[(1) - (1)]).token);
    
		(yyval).vars = new vector<YYSTYPE::variable>;
		(yyval).vars->push_back(var);
		buildFunction.parameters.push_back(var);
	}
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 1033 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 1039 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    ostringstream prepend;
	string template_		=(yyvsp[(1) - (3)]).strs[0];
	string location			=(yyvsp[(3) - (3)]).strs[1];
    switch((yyvsp[(3) - (3)]).rType)
	{
    case REGISTER_INT:
        prepend<<"layout(location="<<(yyvsp[(3) - (3)]).num<<") ";
        break;
    case REGISTER_NAME:
        prepend<<"layout(location="<<(yyvsp[(3) - (3)]).strs[0]<<") ";
        break;
    case SEMANTIC:
		template_=getGLInputSemantic((yyvsp[(3) - (3)]).num);
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
    (yyval).strs[4]	=template_;
}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 1070 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 1075 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 1080 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
				}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 1085 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 1091 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=(yyvsp[(1) - (3)]).num*(yyvsp[(3) - (3)]).num;
					(yyval).strs[0]=stringFormat("%d",(yyval).num);
				}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1096 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string storage	=(yyvsp[(1) - (4)]).strs[0];
		string type		=(yyvsp[(2) - (4)]).strs[0];
		string template_=(yyvsp[(3) - (4)]).strs[0];
		// TODO: We discard template information in parameters. Should we insert a layout spec?
	
		
		string id		=(yyvsp[(4) - (4)]).strs[0];
		if(template_.length()>=4&&(template_.substr(0,4)==string("uint")||template_.substr(0,4)==string("uvec")))
			type=string("u")+type;
		else if(template_.length()>=4&&template_.substr(0,4)==string("ivec"))
			type=string("i")+type;
		else if(template_.length()>=3&&template_.substr(0,3)==string("int"))
			type=string("i")+type;
		else if(IsBufferType((yyvsp[(2) - (4)]).token))
		{
			if(template_.length()>0)
				type=template_+"[]";
		}
		(yyval).strs[0]		=template_;
		(yyval).strs[1]		=storage;
		(yyval).strs[2]		=type;
		(yyval).strs[3]		=id;
		(yyval).token		=(yyvsp[(2) - (4)]).token;
	}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1122 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1127 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1132 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1137 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1141 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1145 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1150 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1155 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1160 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1165 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1170 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1176 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 1181 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 1187 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1194 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 102:
/* Line 1792 of yacc.c  */
#line 1206 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 103:
/* Line 1792 of yacc.c  */
#line 1220 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable	= (yyvsp[(1) - (5)]).boolean;
	(yyval).prog					= (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0]				= (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1227 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders), buildPassState, gEffect->textureSamplersByShader, (yyvsp[(1) - (1)]).strs[2]);
    delete (yyvsp[(1) - (1)]).shaders;
	buildPassState			=PassState();
}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1234 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		ShaderType sType				=(yyvsp[(2) - (2)]).sType;
		string preamble					=(yyvsp[(2) - (2)]).strs[0];
		string name						=(yyvsp[(2) - (2)]).strs[1];
		string compiledShaderName		=(yyvsp[(2) - (2)]).strs[3];
		(yyval).strs[2]						=(yyvsp[(1) - (2)]).strs[2]+(yyvsp[(2) - (2)]).strs[2];// compute layout
		CompiledShaderMap::iterator i	=gEffect->m_compiledShaders.find(compiledShaderName);
		if(i==gEffect->m_compiledShaders.end())
			(*map1)[sType].compiledShader	=NULL;
		else
			(*map1)[sType].compiledShader	=i->second;
		(*map1)[sType].preamble			=preamble;
		(*map1)[sType].name				=name;
		(yyval).shaders						=map1;
	}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1251 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
		if(i==gEffect->m_compiledShaders.end())
			(*map1)[sType].compiledShader	=NULL;
		else
			(*map1)[sType].compiledShader	=i->second;
		(yyval).sType							=sType;
		(*map1)[sType].name					=name;
		(*map1)[sType].preamble				=preamble;
		(yyval).shaders=map1;
	}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1272 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		//.map<ShaderType, Program::Shader>* map1=$1.shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).strs[2]	=(yyvsp[(1) - (2)]).strs[2];
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1281 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders	=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).strs[2]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1290 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1299 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1303 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1309 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1317 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0] = "";
				(yyval).strs[1] = "";
				(yyval).strs[2] = "";
				errSem("Pass definitions like vs(430)=vs_main are no longer supported. Please use SetVertexShader() etc.");
			}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1325 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
					{
						if((yyval).sType==GEOMETRY_SHADER&&(yyvsp[(3) - (5)]).sType==VERTEX_SHADER)
						{
							(yyval).strs[0]	="";
							(yyval).strs[1]	="";
							(yyval).strs[3]	="NULL";
						}
						else
						{
							errSem((((string("Shader type mismatch for ")+compiledShaderName+" - can't call ")+(yyvsp[(1) - (5)]).strs[0]+" with ")+ShaderTypeToString((yyvsp[(3) - (5)]).sType)+" shader as input.").c_str());
						}
					}
					else
					{
						ostringstream preamble;
						preamble << "#version " << compiledShader->version << endl;
						glfxParser::ShaderCommand shaderCommand=(yyvsp[(1) - (5)]).sCommand;
						if(shaderCommand<NumShaderCommands)
						{
							string shaderName=compiledShader->m_functionName;
							if(_stricmp(shaderName.c_str(),"NULL")!=0)
							{
								
								if (shaderCommand == COMPUTE_SHADER)
									preamble << gEffect->m_shaderLayouts[shaderName].text() << "\n";
							}
							(yyval).strs[0]	=preamble.str();
							(yyval).strs[1]	=shaderName;
							(yyval).strs[3]	=compiledShaderName;
							//if (shaderCommand == COMPUTE_SHADER)
							//	$$.strs[2] = gEffect->m_shaderLayouts[shaderName].text();
						}
					}
				}
			}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1391 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 116:
/* Line 1792 of yacc.c  */
#line 1403 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).lineno						=(yyvsp[(5) - (6)]).lineno;
			(yyval).sType						=GEOMETRY_SHADER;
			string gsName					=(yyvsp[(3) - (6)]).strs[0];
			string definition				=(yyvsp[(5) - (6)]).strs[0];
			CompiledShaderMap::iterator i	=gEffect->m_compiledShaders.find(gsName);
			string tempName					=gsName+"_GS_with_SO";
			(yyval).strs[0]						=tempName;
			CompiledShader *new_cs			=NULL;
			gEffect->m_compiledShaders[tempName]=new_cs=new CompiledShader;
			if(i==gEffect->m_compiledShaders.end())
			{
				ostringstream msg;
				msg<<"Compiled shader "<<gsName<<" not found for streamout"<<endl;
				errSem(msg.str().c_str());
			}
			else
			{
				CompiledShader *compiledShader	=i->second;
				*new_cs=*compiledShader;
				if(definition.size())
				{
					find_and_replace(definition,"\"","");
					std::vector<std::string> elements=split(definition,';');
					new_cs->feedbackOutput.clear();
					auto u=gEffect->m_structs.find(new_cs->outputStruct);
					if(u==gEffect->m_structs.end())
					{
						errSem(string("can't find output struct ")+new_cs->outputStruct);
					}
					else
					for(int i=0;i<elements.size();i++)
					{
						const Struct *struc=(u->second);
						string decl=elements[i];
						vector<string> parts=split(decl,'.');
						if(parts.size()!=1&&parts.size()!=2)
						{
							errSem("Invalid Streamout definition");
							continue;
						}
						string semantic=parts[0];
						string swizzle;
						if(parts.size()==2)
							swizzle=parts[1];
						for(int i=0;i<(int)struc->m_structMembers.size();i++)
						{
							const StructMember &m=struc->m_structMembers[i];
							if(m.semantic==semantic)
							{
								string modified=(new_cs->outputStructName+".")+m.name;
								if(swizzle.size())
								{
								//	modified+=".";
								//	modified+=swizzle;
								}
								new_cs->feedbackOutput.push_back(modified);
								break;
							}
						}
					}
				}
			}
		}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1468 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
			stringstream ss;
			ss << (yyvsp[(5) - (8)]).strs[0]<<"Compiled"<<version_num;
			string compiledShaderName						=ss.str();
			(yyval).strs[0]										=compiledShaderName;
			auto u=compilableShaders.find(shaderName);
			if(u==compilableShaders.end())
			{
				errSem(string("Can't find shader ")+shaderName);
			}
			else
			{
				CompilableShader &sh=*(u->second);
				gEffect->m_shaderLayouts[shaderName]	=sh.csLayout;

				gEffect->MergeTextureSamplers(sh.function.textureSamplers,shaderName);

				CompiledShader *compiledShader					=gEffect->m_compiledShaders[compiledShaderName];

				gEffect->m_compiledShaders[compiledShaderName]	=compiledShader=new CompiledShader;
				compiledShader->m_functionName					=(yyvsp[(5) - (8)]).strs[0];
				compiledShader->shaderType						=(yyvsp[(1) - (8)]).sType;
				compiledShader->version							= (yyval).num = version_num;
				// "Compile" the shader - in the sense of "concatenate the strings and prepare it as GLSL source":
				Compile((yyvsp[(1) - (8)]).sType, sh, compiledShader);
			}
		}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1511 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1522 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1528 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1532 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1536 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1541 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1546 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1550 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1559 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1565 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1570 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 129:
/* Line 1792 of yacc.c  */
#line 1583 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			if(type_spec=="float")
				type_spec="";
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			stringReplaceAll(init_declarator_list,type_spec+type_spec,type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 1594 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1598 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1602 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1606 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			// An expression of the form vec2 c=....;
			// Pass-through normally, but most GLSL compilers cannot handle array initializers.
			string declarator	=(yyvsp[(1) - (3)]).strs[0];
			string initializer	=(yyvsp[(3) - (3)]).strs[0];
			if((yyvsp[(3) - (3)]).children.size()<=1)
			{
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+initializer;
			}
			else
			{
				ostringstream declare_lines;
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
				size_t sq_pos=(int)name.find("[");
				// Ugly test to see if we're initializing a list here:
				if(sq_pos<name.length())
				{
					name=name.substr(0,sq_pos);
					declare_lines<<(yyvsp[(1) - (3)]).strs[1]<<"["<<(yyvsp[(3) - (3)]).children.size()<<"];\n";
					for(int i=0;i<(yyvsp[(3) - (3)]).children.size();i++)
					{
						string c=(yyvsp[(3) - (3)]).children[i].strs[0];
						std::replace( c.begin(), c.end(), '{', '('); 
						std::replace( c.begin(), c.end(), '}', ')'); 
						declare_lines<<"\t"<<name<<"["<<i<<"]=%type%"<<c<<";\n";
					}
				}
				else
				{
					declare_lines<<(yyvsp[(1) - (3)]).strs[0]<<";\n";
					// So we're probably initializing a struct instead.
					errSem("Don't yet know how to handle initialization lists for non-arrays!");
				}
				(yyval).strs[0]=declare_lines.str();
			}
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1656 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1660 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1664 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
			(yyval).strs[1]=(yyvsp[(1) - (4)]).strs[0];
			(yyval).strs[2]=(yyvsp[(3) - (4)]).strs[0];
		}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1671 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
			(yyval).strs[1]=(yyvsp[(1) - (3)]).strs[0];
		}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1676 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1680 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
					(yyval).strs[1]="";
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=";\n";
					(yyval).strs[1]="";
				}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 1691 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1696 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
					(yyval).strs[1]="";
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1702 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1707 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 145:
/* Line 1792 of yacc.c  */
#line 1719 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1724 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1729 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
					(yyval).strs[1]="";
				}
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 1735 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1740 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1745 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1750 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 152:
/* Line 1792 of yacc.c  */
#line 1765 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).strs[1]="";
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1771 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1775 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1779 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1782 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1786 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1791 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1797 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 160:
/* Line 1792 of yacc.c  */
#line 1801 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 161:
/* Line 1792 of yacc.c  */
#line 1805 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 162:
/* Line 1792 of yacc.c  */
#line 1809 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 163:
/* Line 1792 of yacc.c  */
#line 1832 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).token=(yyvsp[(1) - (1)]).token;
				}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1846 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).token=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1851 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1855 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1860 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1864 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1868 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1872 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1876 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1880 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1884 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1888 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1892 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1896 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1901 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1905 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1909 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1913 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1917 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1921 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1925 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1929 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1933 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1937 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1941 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1945 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1949 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1953 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1957 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1961 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1965 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1969 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1973 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 205:
/* Line 1792 of yacc.c  */
#line 1977 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	(yyval).strs[1]=(yyvsp[(1) - (1)]).strs[1];
	(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[2];
	(yyval).strs[3]=(yyvsp[(1) - (1)]).strs[3];
}
    break;

  case 206:
/* Line 1792 of yacc.c  */
#line 1984 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 207:
/* Line 1792 of yacc.c  */
#line 1988 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 208:
/* Line 1792 of yacc.c  */
#line 1992 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 214:
/* Line 1792 of yacc.c  */
#line 1996 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 215:
/* Line 1792 of yacc.c  */
#line 2000 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texture";
}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 2004 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="textureLod";
}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 2008 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texelFetch";
}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 2012 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 219:
/* Line 1792 of yacc.c  */
#line 2022 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 220:
/* Line 1792 of yacc.c  */
#line 2032 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 221:
/* Line 1792 of yacc.c  */
#line 2042 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).token=(yyvsp[(1) - (1)]).token;
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[0];			//Command
					}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 2048 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 223:
/* Line 1792 of yacc.c  */
#line 2077 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (6)]).strs[1];
						string x			=(yyvsp[(3) - (6)]).strs[0];
						string y			=(yyvsp[(5) - (6)]).strs[0];

						(yyval).strs[0]=GetSizeFunction( textureName, x, y,"");
					}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 2085 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (8)]).strs[1];
						string x			=(yyvsp[(3) - (8)]).strs[0];
						string y			=(yyvsp[(5) - (8)]).strs[0];
						string z			=(yyvsp[(7) - (8)]).strs[0];
						(yyval).strs[0]=GetSizeFunction( textureName, x, y,z);
					}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 2093 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 226:
/* Line 1792 of yacc.c  */
#line 2141 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName		=(yyvsp[(1) - (6)]).strs[1];
						string command			=(yyvsp[(1) - (6)]).strs[2];
						string samplerStateName	=(yyvsp[(3) - (6)]).strs[0];
						string otherParams		=(yyvsp[(5) - (6)]).strs[0];

						// The actual texturing command depends on the type of the texture.
						if(IsDeclared(textureName))
						{
							string type=GetDeclaredType(textureName);
							if(type==string("samplerCube"))
							{
							//.	command="texture";
							}
						}
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

  case 227:
/* Line 1792 of yacc.c  */
#line 2192 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (4)]).strs[0];
						string expr2=(yyvsp[(2) - (4)]).strs[0];
						string params;
						auto vars=*((yyvsp[(3) - (4)]).vars);
						delete (yyvsp[(3) - (4)]).vars;
						string expr4=(yyvsp[(4) - (4)]).strs[0];
						// ok this could be a function call.
						string command=(yyvsp[(1) - (4)]).strs[2];
						auto j=gEffect->functions.find(command);
						if(j==gEffect->functions.end())
						{
							params=(yyvsp[(3) - (4)]).strs[0];
						}
						else
						{
							auto u=j->second.begin();
							for(;u!=j->second.end();u++)
							{
								if((*u)->parameters.size()==vars.size())
									break;
							}
							if(u==j->second.end())
							{
								errSem("No matching function definition found.");
								break;
							}
							const Function &f=**u;
							buildFunction.functionsCalled.insert(*u);
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

  case 228:
/* Line 1792 of yacc.c  */
#line 2269 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						// ok this could be a function call.
						string command=(yyvsp[(1) - (3)]).strs[2];
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 2275 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[2]=expr3;			//Command
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 2282 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 2286 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 2290 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars=(yyvsp[(1) - (3)]).vars;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 2298 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars = new vector<YYSTYPE::variable>;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 2306 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 2311 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 2318 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 2325 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 2332 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 2339 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 2343 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).token=(yyvsp[(1) - (1)]).token;
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 2348 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 2352 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2356 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2360 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2364 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 2372 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 247:
/* Line 1792 of yacc.c  */
#line 2380 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2384 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 249:
/* Line 1792 of yacc.c  */
#line 2396 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]	="";
						(yyval).num		=-1;
					}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 2401 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 2405 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 2409 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 2413 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 2416 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 255:
/* Line 1792 of yacc.c  */
#line 2420 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 256:
/* Line 1792 of yacc.c  */
#line 2425 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 257:
/* Line 1792 of yacc.c  */
#line 2429 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 258:
/* Line 1792 of yacc.c  */
#line 2538 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 259:
/* Line 1792 of yacc.c  */
#line 2543 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 260:
/* Line 1792 of yacc.c  */
#line 2549 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 261:
/* Line 1792 of yacc.c  */
#line 2554 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 262:
/* Line 1792 of yacc.c  */
#line 2558 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 263:
/* Line 1792 of yacc.c  */
#line 2563 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 264:
/* Line 1792 of yacc.c  */
#line 2568 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 265:
/* Line 1792 of yacc.c  */
#line 2573 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 5457 "src/glfxLALRParser.cpp"
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
#line 2576 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
		case TEXTURE2DARRAY:
			return gsampler2DArray;
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
	
	bool IsBufferType(int t)
	{
		switch(t)
		{
		case STRUCTUREDBUFFER:
		case RW_STRUCTUREDBUFFER:
			return true;
		default:
			return false;
		};
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
	buildStruct		=Struct();
	gEffect->Clear();
	read_shader		=false;
	read_function	=false;
}
