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
		string texture_name	=ts->textureName;
		if(declaredTextures.find(texture_name)!=declaredTextures.end())
		{
			string sampler_type=declaredTextures[texture_name].type;
			//str<<"uniform "<<sampler_type<<" "<<tsname<<";\n";
			additionalTextureDeclarations[tsname].type		=sampler_type;
			additionalTextureDeclarations[tsname].type_enum =declaredTextures[texture_name].type_enum;
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
		auto j=declaredTextures.find(textureName);
		if(j!=declaredTextures.end())
			return j->second.type_enum;
		return 0;
	}
	/// The GLSL texture types. "g" stands for the data type - could be "u" for unsigned int, "i" for int, or nothing - for float.
	enum GLTextureType
	{
		unknwownTextureType
		,gsampler1D					//	GL_TEXTURE_1D						1D texture
		,gsampler2D					//	GL_TEXTURE_2D						2D texture
		,gsampler3D					//	GL_TEXTURE_3D						3D texture
		,gsamplerCube				//	GL_TEXTURE_CUBE_MAP					Cubemap Texture
		,gsampler2DRect				//	GL_TEXTURE_RECTANGLE				Rectangle Texture
		,gsampler1DArray			//	GL_TEXTURE_1D_ARRAY					1D Array Texture
		,gsampler2DArray			//	GL_TEXTURE_2D_ARRAY					2D Array Texture
		,gsamplerCubeArray			//	GL_TEXTURE_CUBE_MAP_ARRAY			Cubemap Array Texture		(requires GL 4.0 or ARB_texture_cube_map_array)
		,gsamplerBuffer				//	GL_TEXTURE_BUFFER					Buffer Texture
		,gsampler2DMS				//	GL_TEXTURE_2D_MULTISAMPLE			Multisample Texture
		,gsampler2DMSArray			//	GL_TEXTURE_2D_MULTISAMPLE_ARRAY		Multisample Array Texture
		,sampler1DShadow			//	GL_TEXTURE_1D
		,sampler2DShadow			//	GL_TEXTURE_2D
		,samplerCubeShadow			//	GL_TEXTURE_CUBE_MAP
		,sampler2DRectShadow		//	GL_TEXTURE_RECTANGLE
		,sampler1DArrayShadow		//	GL_TEXTURE_1D_ARRAY
		,sampler2DArrayShadow		//	GL_TEXTURE_2D_ARRAY
		,samplerCubeArrayShadow		//	GL_TEXTURE_CUBE_MAP_ARRAY
		// Read-write textures - "images" in GLSL parlance:
		,gimage1D					//	GL_TEXTURE_1D or single layer from GL_TEXTURE_1D_ARRAY
		,gimage2D					//	GL_TEXTURE_2D or single layer from:GL_TEXTURE_2D_ARRAY GL_TEXTURE_CUBE_MAP GL_TEXTURE_CUBE_MAP_ARRAY GL_TEXTURE_3D
		,gimage3D					//	GL_TEXTURE_3D
		,gimageCube					//	GL_TEXTURE_CUBE_MAP
		,gimage2DRect				//	GL_TEXTURE_RECTANGLE
		,gimage1DArray				//	GL_TEXTURE_1D_ARRAY
		,gimage2DArray				//	GL_TEXTURE_2D_ARRAY
		,gimageCubeArray			//	GL_TEXTURE_CUBE_MAP_ARRAY (requires GL 4.0 or ARB_texture_cube_map_array)
		,gimageBuffer				//	GL_TEXTURE_BUFFER
		,gimage2DMS					//	GL_TEXTURE_2D_MULTISAMPLE or single layer from: GL_TEXTURE_2D_MULTISAMPLE_ARRAY
		,gimage2DMSArray			//	GL_TEXTURE_2D_MULTISAMPLE_ARRAY
	};
	GLTextureType ToGLTextureType(int t);
	
	string GetSizeFunction(string textureName,string x,string y,string z)
	{
		int glTextureType	=ToGLTextureType(GetTextureType(buildFunction,textureName));
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
     SHADER = 260,
     CONSTANT_BUFFER = 261,
     PROGRAM = 262,
     INTERFACE = 263,
     IDENTIFIER = 264,
     SAMPLE = 265,
     SAMPLE_LOD = 266,
     GET_DIMS = 267,
     STORAGEQ = 268,
     GL_FRAGDEPTH = 269,
     SHADER_COMMAND = 270,
     SET_RASTERIZER_COMMAND = 271,
     SET_DEPTH_COMMAND = 272,
     SET_BLEND_COMMAND = 273,
     SV_DISPATCHTHREADID = 274,
     SV_GROUPTHREADID = 275,
     SV_GROUPID = 276,
     SV_VERTEXID = 277,
     NUM = 278,
     INCLUDE = 279,
     SAMPLER = 280,
     FLOAT = 281,
     LAYOUT = 282,
     LINE = 283,
     TECHNIQUE = 284,
     PASS = 285,
     GROUP = 286,
     RENDER_STATE_DECL = 287,
     QUOTED_STRING = 288,
     SHADER_LINE = 289,
     SHADER_TYPE = 290,
     COMPILE_SHADER = 291,
     CONSTRUCT_GS_WITH_SO = 292,
     STRUCT = 293,
     PRAGMA = 294,
     DEFINE = 295,
     UNDEF = 296,
     MACRO_DEFINITION = 297,
     EOL = 298,
     DECL_SHADER = 299,
     PROFILE = 300,
     WARNING = 301,
     DEF = 302,
     MESSAGE = 303,
     PACK_MATRIX = 304,
     RW_TEXTURE2D = 305,
     RW_TEXTURE3D = 306,
     RW_TEXTURE2DARRAY = 307,
     RW_TEXTURE3D_FLOAT4 = 308,
     TEXTURE2DMS = 309,
     TEXTURE2D = 310,
     TEXTURE3D = 311,
     IMAGE3D = 312,
     KNOWN_TYPE = 313,
     STRUCTUREDBUFFER = 314,
     RW_STRUCTUREDBUFFER = 315,
     RETURN = 316,
     BREAK = 317,
     CONTINUE = 318,
     DO = 319,
     FOR = 320,
     GOTO = 321,
     IF = 322,
     WHILE = 323,
     ELSE = 324,
     TIMES_EQUALS = 325,
     OVER_EQUALS = 326,
     PERCENT_EQUALS = 327,
     PLUS_EQUALS = 328,
     MINUS_EQUALS = 329,
     LEFT_SHIFT_EQUALS = 330,
     RIGHT_SHIFT_EQUALS = 331,
     AND_EQUALS = 332,
     XOR_EQUALS = 333,
     OR_EQUALS = 334,
     AND = 335,
     OR = 336,
     LESS_EQ = 337,
     GRTR_EQ = 338,
     LEFT_SHIFT = 339,
     RIGHT_SHIFT = 340,
     PLUS_PLUS = 341,
     MINUS_MINUS = 342,
     EQ_EQ = 343,
     NOT_EQ = 344,
     SA_MAXVERTEXCOUNT = 345,
     SA_NUMTHREADS = 346,
     SHADER_PROFILE = 347
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
#line 555 "src/glfxLALRParser.cpp"

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
#define YYLAST   642

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  117
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  100
/* YYNRULES -- Number of rules.  */
#define YYNRULES  254
/* YYNRULES -- Number of states.  */
#define YYNSTATES  540

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   347

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   115,     2,     2,     2,   113,   108,     2,
      94,    96,   111,   109,    99,   110,   116,   112,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    95,    93,
     103,   100,   104,   105,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    97,     2,    98,   107,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   101,   106,   102,   114,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92
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
     303,   304,   306,   307,   312,   314,   316,   318,   319,   321,
     323,   325,   327,   330,   333,   336,   337,   339,   342,   344,
     350,   352,   355,   357,   360,   362,   373,   379,   387,   397,
     402,   408,   410,   417,   426,   431,   436,   437,   440,   441,
     445,   447,   450,   452,   453,   457,   460,   462,   466,   468,
     472,   474,   478,   483,   487,   491,   494,   496,   499,   501,
     507,   515,   521,   529,   539,   543,   546,   549,   553,   555,
     557,   559,   560,   562,   563,   567,   569,   573,   575,   579,
     581,   583,   585,   587,   589,   591,   593,   595,   597,   599,
     601,   603,   609,   611,   615,   617,   621,   623,   627,   629,
     633,   635,   639,   641,   645,   649,   651,   655,   659,   663,
     667,   669,   673,   677,   679,   683,   687,   689,   693,   697,
     701,   703,   705,   708,   711,   714,   716,   718,   720,   722,
     724,   726,   728,   730,   734,   738,   740,   745,   752,   761,
     768,   773,   777,   781,   784,   787,   791,   793,   795,   799,
     804,   806,   810,   812,   814,   818,   820,   822,   825,   828,
     829,   832,   833,   837,   838,   841,   843,   848,   850,   853,
     857,   858,   860,   862,   864
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     118,     0,    -1,   118,   119,    -1,    -1,     8,   138,     9,
     143,    93,   141,    -1,    43,    -1,   120,    -1,    39,    46,
      94,   127,    95,    23,    96,    -1,     4,   123,   125,     9,
      93,    -1,     4,   124,   125,     9,    93,    -1,     4,     9,
       9,    93,    -1,    97,    90,    94,    23,    96,    98,    -1,
      97,    91,    94,    23,    99,    23,    99,    23,    96,    98,
      -1,    27,   131,     9,    93,    -1,    27,   132,    -1,    53,
       9,    93,    -1,    53,     9,    99,    -1,    40,    42,    43,
      -1,    41,     9,    43,    -1,    38,     9,   145,    93,    -1,
      32,     9,   210,    93,    -1,    45,    92,    94,    23,    96,
      93,    -1,    44,     9,   100,   166,    93,    -1,    27,   138,
     126,   141,    -1,     6,     9,   139,   145,    93,   141,    -1,
       9,     9,    94,   149,    96,   140,   142,   141,    -1,   122,
       9,     9,    94,   149,    96,   144,   142,   141,    -1,     7,
     138,     9,   101,   161,   102,   141,    -1,   130,    -1,    31,
     138,     9,   101,   128,   102,   141,    -1,    28,   138,    23,
      23,   141,    -1,    28,    23,    23,    -1,     5,   139,    -1,
      55,    -1,    56,    -1,    54,    -1,    57,    -1,    50,    -1,
      51,    -1,    52,    -1,    59,    -1,    60,    -1,   103,     9,
     104,    -1,    -1,    94,    23,    99,    23,    99,    23,    96,
      -1,     9,    -1,    23,    -1,   128,   129,    -1,   129,    -1,
      29,     9,   101,   158,   102,    -1,    29,   138,     9,   101,
     158,   102,   141,    -1,    94,   135,    96,    -1,    94,   133,
      96,    -1,   133,    99,   134,    -1,   134,    -1,   136,    -1,
       9,    -1,   136,    99,   136,    99,   136,    -1,     9,   100,
     137,    -1,     9,    -1,    23,    -1,    -1,    -1,    -1,    -1,
     101,   171,   102,    -1,    -1,    95,     9,    -1,    -1,   101,
     146,   102,    -1,   146,   147,    -1,   147,    -1,   148,     9,
       9,   151,   209,    93,    -1,     4,    -1,    -1,   149,    99,
     150,    -1,   150,    -1,    -1,   153,   151,   157,    -1,    97,
     152,    98,    -1,    -1,    23,    -1,    -1,   155,   154,   125,
       9,    -1,     9,    -1,   123,    -1,    13,    -1,    -1,    19,
      -1,    21,    -1,    20,    -1,    22,    -1,    95,    23,    -1,
      95,   156,    -1,    95,     9,    -1,    -1,   159,    -1,   159,
     160,    -1,   160,    -1,    30,     9,   101,   161,   102,    -1,
     162,    -1,   162,   165,    -1,   165,    -1,   162,   164,    -1,
     164,    -1,     9,    94,    26,    99,    26,    99,    26,    99,
      26,    96,    -1,    16,    94,     9,    96,    93,    -1,    17,
      94,     9,    99,    23,    96,    93,    -1,    18,    94,     9,
      99,   163,    99,    23,    96,    93,    -1,   167,   100,   168,
      93,    -1,    15,    94,   166,    96,    93,    -1,     9,    -1,
      37,    94,     9,    99,    33,    96,    -1,    36,    94,    92,
      99,     9,    94,    96,    96,    -1,    35,    94,    23,    96,
      -1,     9,    94,    96,   169,    -1,    -1,    95,   170,    -1,
      -1,   170,    99,   207,    -1,   207,    -1,   171,   177,    -1,
     177,    -1,    -1,    28,    23,    23,    -1,   216,   174,    -1,
     175,    -1,   174,    99,   175,    -1,   176,    -1,   176,   100,
     203,    -1,     9,    -1,    94,   176,    96,    -1,   176,    97,
      23,    98,    -1,   176,    97,    98,    -1,   176,    94,    96,
      -1,   181,    93,    -1,    93,    -1,   173,    93,    -1,   180,
      -1,    67,    94,   181,    96,   177,    -1,    67,    94,   181,
      96,   177,    69,   177,    -1,    68,    94,   181,    96,   177,
      -1,    64,   177,    68,    94,   181,    96,    93,    -1,    65,
      94,   178,    93,   179,    93,   179,    96,   177,    -1,    66,
       9,    93,    -1,    63,    93,    -1,    62,    93,    -1,    61,
     179,    93,    -1,   172,    -1,   181,    -1,   173,    -1,    -1,
     181,    -1,    -1,   101,   171,   102,    -1,   182,    -1,   181,
      99,   182,    -1,   184,    -1,   196,   183,   182,    -1,   100,
      -1,    70,    -1,    71,    -1,    72,    -1,    73,    -1,    74,
      -1,    75,    -1,    76,    -1,    77,    -1,    78,    -1,    79,
      -1,   185,    -1,   185,   105,   181,    95,   184,    -1,   186,
      -1,   185,    81,   186,    -1,   187,    -1,   186,    80,   187,
      -1,   188,    -1,   187,   106,   188,    -1,   189,    -1,   188,
     107,   189,    -1,   190,    -1,   189,   108,   190,    -1,   191,
      -1,   190,    88,   191,    -1,   190,    89,   191,    -1,   192,
      -1,   191,   103,   192,    -1,   191,   104,   192,    -1,   191,
      82,   192,    -1,   191,    83,   192,    -1,   193,    -1,   192,
      84,   193,    -1,   192,    85,   193,    -1,   194,    -1,   193,
     109,   194,    -1,   193,   110,   194,    -1,   195,    -1,   194,
     111,   195,    -1,   194,   112,   195,    -1,   194,   113,   195,
      -1,   196,    -1,   201,    -1,    86,   196,    -1,    87,   196,
      -1,   197,   195,    -1,   108,    -1,   111,    -1,   109,    -1,
     110,    -1,   114,    -1,   115,    -1,    10,    -1,    11,    -1,
     201,   116,   198,    -1,   201,   116,    12,    -1,   205,    -1,
     201,    97,   181,    98,    -1,   200,    94,   182,    99,   182,
      96,    -1,   200,    94,   182,    99,   182,    99,   182,    96,
      -1,   199,    94,   182,    99,   202,    96,    -1,   201,    94,
     202,    96,    -1,   201,    94,    96,    -1,   201,   116,     9,
      -1,   201,    86,    -1,   201,    87,    -1,   202,    99,   182,
      -1,   182,    -1,   182,    -1,   101,   204,   102,    -1,   101,
     204,    99,   102,    -1,   203,    -1,   204,    99,   203,    -1,
       9,    -1,   206,    -1,    94,   181,    96,    -1,    23,    -1,
      26,    -1,    13,   208,    -1,    14,   208,    -1,    -1,    95,
       9,    -1,    -1,   101,   211,   102,    -1,    -1,   211,   212,
      -1,   212,    -1,   213,   100,   215,    93,    -1,   121,    -1,
       9,   214,    -1,    97,    23,    98,    -1,    -1,     9,    -1,
      23,    -1,    26,    -1,     9,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   341,   341,   342,   346,   350,   353,   356,   359,   392,
     408,   414,   418,   424,   427,   433,   439,   445,   449,   455,
     472,   512,   522,   541,   544,   559,   682,   716,   721,   724,
     732,   739,   745,   750,   750,   750,   750,   750,   750,   750,
     756,   756,   762,   768,   772,   786,   789,   792,   796,   799,
     803,   813,   817,   822,   826,   830,   834,   838,   846,   852,
     856,   861,   868,   875,   882,   886,   893,   898,   903,   906,
     911,   917,   922,   941,   946,   949,   963,   979,   984,  1015,
    1021,  1025,  1031,  1035,  1050,  1055,  1060,  1065,  1068,  1073,
    1078,  1083,  1088,  1093,  1099,  1105,  1110,  1117,  1129,  1143,
    1150,  1157,  1167,  1180,  1188,  1196,  1205,  1209,  1215,  1223,
    1228,  1302,  1314,  1334,  1370,  1381,  1388,  1391,  1396,  1400,
    1405,  1409,  1418,  1425,  1429,  1442,  1451,  1455,  1459,  1463,
    1501,  1505,  1509,  1514,  1518,  1522,  1528,  1533,  1538,  1544,
    1549,  1561,  1566,  1571,  1577,  1582,  1587,  1592,  1607,  1613,
    1617,  1622,  1624,  1629,  1633,  1639,  1643,  1647,  1651,  1655,
    1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,
    1672,  1676,  1681,  1685,  1689,  1693,  1697,  1701,  1705,  1709,
    1713,  1717,  1722,  1726,  1730,  1734,  1738,  1742,  1746,  1750,
    1754,  1758,  1762,  1766,  1770,  1774,  1778,  1782,  1786,  1790,
    1794,  1798,  1802,  1806,  1810,  1814,  1814,  1814,  1814,  1814,
    1814,  1818,  1822,  1826,  1836,  1846,  1851,  1856,  1864,  1872,
    1909,  1974,  1980,  1987,  1991,  1995,  2003,  2011,  2016,  2023,
    2030,  2037,  2044,  2048,  2052,  2056,  2060,  2064,  2072,  2081,
    2084,  2089,  2092,  2096,  2099,  2104,  2108,  2217,  2222,  2228,
    2234,  2237,  2242,  2247,  2252
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHITESPACE", "UNIFORM", "SHADER",
  "CONSTANT_BUFFER", "PROGRAM", "INTERFACE", "IDENTIFIER", "SAMPLE",
  "SAMPLE_LOD", "GET_DIMS", "STORAGEQ", "GL_FRAGDEPTH", "SHADER_COMMAND",
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
  "optional_semantic", "optional_render_state_list", "render_state_list",
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
     345,   346,   347,    59,    40,    58,    41,    91,    93,    44,
      61,   123,   125,    60,    62,    63,   124,    94,    38,    43,
      45,    42,    47,    37,   126,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   117,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     120,   121,   122,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   125,   125,   126,   127,   127,   128,   128,   129,
     130,   131,   132,   133,   133,   134,   134,   135,   136,   137,
     137,   138,   139,   140,   141,   142,   143,   144,   144,   145,
     146,   146,   147,   148,   148,   149,   149,   149,   150,   151,
     151,   152,   152,   153,   154,   154,   155,   155,   156,   156,
     156,   156,   157,   157,   157,   157,   158,   159,   159,   160,
     161,   162,   162,   162,   162,   163,   164,   164,   164,   165,
     165,   166,   166,   166,   167,   168,   168,   169,   169,   170,
     170,   171,   171,   171,   172,   173,   174,   174,   175,   175,
     176,   176,   176,   176,   176,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   178,
     178,   178,   179,   179,   180,   181,   181,   182,   182,   183,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     184,   184,   185,   185,   186,   186,   187,   187,   188,   188,
     189,   189,   190,   190,   190,   191,   191,   191,   191,   191,
     192,   192,   192,   193,   193,   193,   194,   194,   194,   194,
     195,   196,   196,   196,   196,   197,   197,   197,   197,   197,
     197,   198,   198,   199,   200,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   202,   202,   203,   203,   203,
     204,   204,   205,   205,   205,   206,   206,   207,   207,   208,
     209,   209,   210,   210,   211,   211,   212,   212,   213,   214,
     214,   215,   215,   215,   216
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
       0,     1,     0,     4,     1,     1,     1,     0,     1,     1,
       1,     1,     2,     2,     2,     0,     1,     2,     1,     5,
       1,     2,     1,     2,     1,    10,     5,     7,     9,     4,
       5,     1,     6,     8,     4,     4,     0,     2,     0,     3,
       1,     2,     1,     0,     3,     2,     1,     3,     1,     3,
       1,     3,     4,     3,     3,     2,     1,     2,     1,     5,
       7,     5,     7,     9,     3,     2,     2,     3,     1,     1,
       1,     0,     1,     0,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     4,     6,     8,     6,
       4,     3,     3,     2,     2,     3,     1,     1,     3,     4,
       1,     3,     1,     1,     3,     1,     1,     2,     2,     0,
       2,     0,     3,     0,     2,     1,     4,     1,     2,     3,
       0,     1,     1,     1,     1
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
       0,   243,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    66,    87,
      56,     0,    54,     0,    55,     0,     0,    64,     0,     0,
       0,     0,     0,    74,     0,     0,    17,    18,     0,     0,
      15,    16,     0,     0,     0,    10,     0,     0,     0,     0,
       0,     0,    86,     0,    76,    80,     0,     0,    52,     0,
      51,     0,    13,     0,    23,    64,     0,     0,   250,     0,
     247,     0,   245,     0,    20,    73,    74,    71,     0,    19,
      45,    46,     0,   111,     0,     0,     0,     0,     0,     0,
      87,    42,     8,     9,    64,     0,     0,     0,     0,     0,
       0,   100,   104,   102,     0,    64,    63,    87,    82,    95,
      84,    85,    43,    59,    60,    58,    53,    55,     0,     0,
       0,    30,     0,     0,    96,    98,     0,     0,    48,     0,
     248,     0,   242,   244,     0,    69,    70,     0,     0,     0,
       0,    22,     0,     0,     0,     0,    24,     0,     0,     0,
       0,     0,    64,   103,   101,   116,     4,     0,    75,    81,
       0,     0,    78,     0,     0,     0,     0,    64,    97,     0,
      64,    47,     0,    31,   251,   252,   253,     0,    80,     0,
       0,     0,    21,    11,     0,    68,     0,     0,     0,     0,
       0,    27,     0,     0,   123,    64,    79,    94,    88,    90,
      89,    91,    92,    93,    83,    57,     0,     0,    50,     0,
      29,   249,   246,   241,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,     0,   109,   232,   235,   236,
       0,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   136,     0,   123,   205,   207,   208,   206,   209,   210,
       0,   148,     0,   122,   138,     0,   155,   157,   170,   172,
     174,   176,   178,   180,   182,   185,   190,   193,   196,   200,
       0,     0,     0,   201,   215,   233,     0,    25,     0,     0,
       0,     0,     0,     0,     0,     0,    67,    64,   110,   106,
       0,     0,     0,   118,     0,   232,     0,   152,   146,   145,
       0,   151,     0,     0,     0,   202,   203,     0,     0,    65,
     121,   137,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   159,     0,   204,   200,     0,     0,   223,
     224,     0,     0,     0,   130,     0,   125,   126,   128,    44,
      99,    49,   240,    72,     0,   112,     0,    26,     0,     0,
       0,     0,   115,   124,   147,     0,   150,     0,   149,   144,
       0,     0,   234,   154,   156,   173,     0,   175,   177,   179,
     181,   183,   184,   188,   189,   186,   187,   191,   192,   194,
     195,   197,   198,   199,   158,     0,     0,   221,   226,     0,
       0,   222,   211,   212,   214,   213,     0,     0,     0,     0,
       0,     0,    12,   107,     0,     0,   239,   239,   117,   120,
       0,   153,     0,     0,     0,     0,     0,   220,     0,   216,
     131,   127,   134,     0,   133,     0,   227,   129,   113,     0,
       0,   237,   238,     0,     0,     0,   139,   141,   171,     0,
       0,   225,   132,   230,     0,     0,   108,   119,     0,   153,
       0,   219,   217,     0,     0,   228,     0,   142,     0,   140,
       0,   229,   231,     0,     0,   218,     0,   143,     0,   105
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    23,    24,   120,    25,    37,    38,    64,    77,
     132,   177,   178,    26,    45,    46,    71,    72,    73,    74,
     165,    41,    39,   207,   114,   245,   101,   269,    84,   126,
     127,   128,   103,   104,   159,   210,   105,   162,   106,   253,
     212,   173,   174,   175,   150,   151,   342,   152,   153,   136,
     154,   243,   422,   478,   300,   301,   302,   406,   407,   408,
     303,   427,   346,   304,   305,   306,   394,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   465,   321,   322,   323,   459,   497,   514,   324,   325,
     479,   501,   332,    82,   121,   122,   123,   180,   227,   326
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -481
static const yytype_int16 yypact[] =
{
    -481,   391,  -481,   351,  -481,    11,  -481,  -481,    38,   -37,
    -481,  -481,  -481,    69,    82,   108,    85,    96,  -481,   147,
      83,   191,    30,  -481,  -481,   196,  -481,   204,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,    70,    70,  -481,
    -481,   215,   235,   162,   256,   280,  -481,   198,   283,   308,
     309,   218,   221,   229,   281,   290,   236,   240,   -48,   243,
     244,   330,   247,   332,   337,   338,   221,   249,  -481,    29,
     251,    71,  -481,   257,   253,   263,   334,  -481,   335,   258,
     260,    15,   270,   360,   274,    59,  -481,  -481,     3,   345,
    -481,  -481,   346,   347,   277,  -481,   271,   287,   288,   291,
      20,   292,  -481,    81,  -481,   289,   275,    60,  -481,   256,
    -481,   363,  -481,   293,  -481,  -481,   344,   380,   307,   389,
    -481,    -5,  -481,   313,  -481,  -481,     9,  -481,   405,  -481,
    -481,  -481,   320,  -481,   322,   323,   328,   329,   331,   325,
      29,  -481,  -481,  -481,  -481,   339,   343,   348,   349,   361,
     324,    20,  -481,  -481,   340,  -481,  -481,   415,   416,   362,
    -481,  -481,    70,  -481,  -481,  -481,  -481,  -481,   251,   342,
     433,  -481,   429,   356,   344,  -481,   450,   -23,  -481,   437,
    -481,   438,  -481,  -481,   106,  -481,  -481,   453,   440,   372,
     456,  -481,   373,   369,   445,    91,  -481,     3,   460,   461,
     462,   449,  -481,  -481,  -481,   464,  -481,   376,  -481,  -481,
     378,   163,  -481,   465,   363,   379,   381,  -481,  -481,   382,
    -481,  -481,   383,  -481,  -481,  -481,  -481,   386,   289,   384,
     385,   387,  -481,  -481,   388,   390,   393,   394,   392,   395,
     396,  -481,   399,   402,   165,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,   473,    20,  -481,   344,
    -481,  -481,  -481,   403,  -481,   488,   466,   477,   492,   376,
     409,   410,   481,   496,  -481,   411,  -481,   497,  -481,  -481,
     485,   268,   417,   418,   165,   419,   500,   420,   421,   268,
     268,  -481,   268,   165,  -481,  -481,  -481,  -481,  -481,  -481,
      -1,  -481,   423,  -481,  -481,   -43,  -481,  -481,   -53,   432,
     412,   413,   414,    10,   -50,   164,   161,   184,  -481,   375,
     268,   425,   427,   -68,  -481,  -481,    -4,  -481,   428,   424,
     426,   508,   430,   431,   434,   435,  -481,  -481,  -481,  -481,
     436,   439,   441,   442,   504,  -481,   443,   444,  -481,  -481,
     467,   279,   446,   268,   268,  -481,  -481,    93,   153,  -481,
    -481,  -481,  -481,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,   268,   268,   268,   268,   268,   268,   268,
     268,   268,   268,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,   268,  -481,  -481,   268,   268,  -481,
    -481,     8,   268,   185,  -481,    -4,   447,  -481,    58,  -481,
    -481,  -481,  -481,  -481,   448,  -481,   451,  -481,   452,   503,
     511,   269,  -481,  -481,  -481,   454,  -481,   457,   444,  -481,
     105,   138,  -481,  -481,  -481,   432,    35,   412,   413,   414,
      10,   -50,   -50,   164,   164,   164,   164,   161,   161,   184,
     184,  -481,  -481,  -481,  -481,   455,   458,  -481,  -481,   139,
     200,  -481,  -481,  -481,  -481,  -481,    63,    -4,   459,    -2,
     234,   463,  -481,  -481,   468,   469,  -481,  -481,   470,  -481,
     268,   268,   165,   165,   268,   268,   268,  -481,   268,  -481,
    -481,  -481,  -481,   472,  -481,   234,  -481,  -481,  -481,   512,
     471,  -481,  -481,   269,   146,   475,   478,  -481,  -481,   173,
     182,  -481,  -481,  -481,   188,   474,  -481,  -481,   479,   268,
     165,  -481,  -481,   268,   199,  -481,   515,  -481,   480,  -481,
     482,  -481,  -481,   476,   165,  -481,   516,  -481,   483,  -481
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -481,  -481,  -481,  -481,  -481,  -481,   484,  -481,   -36,  -481,
    -481,  -481,   374,  -481,  -481,  -481,  -481,   486,  -481,  -102,
    -481,   154,   513,  -481,  -114,   294,  -481,  -481,   490,  -481,
     487,  -481,   422,   401,   333,  -481,  -481,  -481,  -481,  -481,
    -481,   301,  -481,   397,   295,  -481,  -481,   489,   491,   377,
    -481,  -481,  -481,  -481,   273,  -481,   226,  -481,   113,   176,
    -284,  -481,  -470,  -481,  -278,  -317,  -481,    98,  -481,   219,
     220,   217,   223,   216,   -67,  -163,   -65,   -63,  -310,  -231,
    -481,  -481,  -481,  -481,  -481,   102,  -480,  -481,  -481,  -481,
      86,   111,  -481,  -481,  -481,   493,  -481,  -481,  -481,  -481
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -255
static const yytype_int16 yytable[] =
{
     350,   171,    65,   347,   118,   404,   176,   167,   277,   169,
     395,   505,   133,   125,   357,   513,   360,   345,   399,   400,
      40,   493,   278,   119,   118,   279,   401,   280,   364,   402,
     196,   278,   372,   373,   279,   145,   146,   147,   148,   134,
     135,   206,   102,   119,   532,    90,   434,    43,   403,   528,
     362,    91,   365,   374,   375,   149,   363,    44,   355,   356,
     281,   282,   283,   284,   285,   286,   287,   288,   130,   163,
     451,   452,   453,   428,   360,   430,   431,   454,    51,   220,
     455,   456,   131,   164,   458,   289,   290,   436,   241,   396,
     405,    52,   291,   292,   289,   290,   494,   182,   370,   371,
     293,   359,   292,   258,   457,    55,   260,   294,   295,   296,
     297,   185,   255,   298,   299,   224,   294,   295,   296,   297,
      59,    60,   298,   299,   460,   -77,   213,    54,   -77,   225,
     484,   327,   226,   396,   363,   396,   396,   396,   396,   396,
     396,   396,   396,   396,   396,   396,   396,   396,   396,   396,
     396,   396,   468,   496,    53,   469,    56,   468,   470,   490,
     469,    42,   277,    47,    48,    49,    50,   108,   458,   510,
     109,   511,   247,    63,   277,    57,   278,   156,   496,   279,
     157,   280,   248,   249,   250,   251,   252,   235,   278,   432,
     157,   279,   363,   280,   461,   462,   463,   464,   506,   507,
      58,   482,   504,   347,   363,    61,   530,   496,   345,   443,
     444,   445,   446,    62,   281,   282,   283,   284,   285,   286,
     287,   288,   278,   417,    67,   279,   281,   282,   283,   284,
     285,   286,   287,   288,   483,   487,   529,   363,   488,   289,
     290,   347,   518,   345,    68,   363,   291,   292,   376,   377,
     537,   289,   290,   396,   293,   433,    69,   278,   291,   292,
     279,   294,   295,   296,   297,    70,   293,   298,   299,   521,
     378,   379,   488,   294,   295,   296,   297,   345,   522,   298,
     299,   523,   476,   477,   160,   289,   290,   524,   277,    75,
     525,   278,    76,   292,   279,   380,   381,   382,   489,   363,
     495,   531,   278,   441,   442,   279,    78,   294,   295,   296,
     297,   447,   448,   298,   299,   449,   450,    79,    80,    81,
     289,   290,    83,    85,    86,    28,    29,    30,   292,    31,
      32,    33,    34,    87,    89,   495,    88,    92,    93,    94,
      95,    96,   294,   295,   296,   297,    97,    98,   298,   299,
     100,   107,   111,   110,   289,   290,   112,   113,   115,   116,
      27,   117,   292,   124,   125,   289,   290,   129,   137,   138,
     139,   140,   168,   292,   172,   141,   294,   295,   296,   297,
     142,   143,   298,   299,   144,   155,   158,   294,   295,   296,
     297,     2,   170,   298,   299,     3,     4,     5,     6,     7,
       8,    28,    29,    30,   179,    31,    32,    33,    34,   176,
      35,    36,   181,   184,   187,   188,   189,   190,     9,    10,
      11,   191,    12,    13,   194,   192,   202,   193,   102,    14,
      15,    16,    17,   197,    18,    19,    20,   198,   216,   209,
     205,   214,   199,   200,    21,   383,   384,   385,   386,   387,
     388,   389,   390,   391,   392,   201,   215,   211,   217,   219,
     222,   223,   228,   229,   230,   231,   232,   233,   234,   237,
     238,   239,   240,   242,   254,   393,   246,   244,   256,   262,
     264,   261,   257,   259,   265,   268,   266,   267,    22,   270,
     271,   272,   274,   275,   273,   276,   328,   333,   331,   334,
     335,   336,   338,   339,   340,   341,  -254,   343,   344,   352,
     348,   349,   366,   351,   353,   354,   361,   412,   367,   397,
     368,   398,   369,   413,   409,   414,   410,   423,   411,   474,
     415,   416,   418,   419,   475,   425,   424,   421,   515,   429,
     420,   533,   538,   363,   471,   473,   467,   520,   480,   472,
     481,   221,   329,    66,   485,   492,    99,   486,   208,   498,
     330,   263,   195,   337,   516,   500,   358,   499,   519,   503,
     512,   218,   527,   526,   236,   536,   534,   426,   535,   539,
     491,   466,   508,   435,   438,   440,   437,   509,   502,   517,
     161,   439,     0,     0,     0,   166,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   186,   183,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     203,     0,   204
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-481)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
     284,   115,    38,   281,     9,     9,    29,   109,     9,   111,
     320,   481,     9,     4,   292,   495,   300,     9,    86,    87,
       9,    23,    23,    28,     9,    26,    94,    28,    81,    97,
     144,    23,    82,    83,    26,    15,    16,    17,    18,    36,
      37,   155,    13,    28,   524,    93,   363,     9,   116,   519,
      93,    99,   105,   103,   104,    35,    99,    94,   289,   290,
      61,    62,    63,    64,    65,    66,    67,    68,     9,     9,
     380,   381,   382,   351,   358,   353,   354,   394,     9,   102,
     397,   398,    23,    23,   401,    86,    87,   365,   202,   320,
      94,     9,    93,    94,    86,    87,    98,   102,    88,    89,
     101,   102,    94,   217,    96,     9,   220,   108,   109,   110,
     111,   102,   214,   114,   115,     9,   108,   109,   110,   111,
      90,    91,   114,   115,   402,    96,   162,    42,    99,    23,
      95,   245,    26,   364,    99,   366,   367,   368,   369,   370,
     371,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,    94,   470,    46,    97,     9,    94,   100,    96,
      97,     7,     9,     9,    10,    11,    12,    96,   485,   486,
      99,   488,     9,   103,     9,    92,    23,    96,   495,    26,
      99,    28,    19,    20,    21,    22,    23,    96,    23,    96,
      99,    26,    99,    28,     9,    10,    11,    12,   482,   483,
       9,    96,   480,   481,    99,     9,   523,   524,     9,   372,
     373,   374,   375,     9,    61,    62,    63,    64,    65,    66,
      67,    68,    23,   337,     9,    26,    61,    62,    63,    64,
      65,    66,    67,    68,    96,    96,   520,    99,    99,    86,
      87,   519,    96,     9,     9,    99,    93,    94,    84,    85,
     534,    86,    87,   484,   101,   102,    94,    23,    93,    94,
      26,   108,   109,   110,   111,     9,   101,   114,   115,    96,
     109,   110,    99,   108,   109,   110,   111,     9,    96,   114,
     115,    99,    13,    14,     9,    86,    87,    99,     9,     9,
     102,    23,    94,    94,    26,   111,   112,   113,    98,    99,
     101,   102,    23,   370,   371,    26,    23,   108,   109,   110,
     111,   376,   377,   114,   115,   378,   379,     9,     9,   101,
      86,    87,   101,    94,    43,    50,    51,    52,    94,    54,
      55,    56,    57,    43,    94,   101,   100,    94,    94,     9,
      93,     9,   108,   109,   110,   111,     9,     9,   114,   115,
     101,   100,    99,    96,    86,    87,    93,    23,    23,   101,
       9,   101,    94,    93,     4,    86,    87,    93,    23,    23,
      23,    94,     9,    94,    30,   104,   108,   109,   110,   111,
      93,    93,   114,   115,    93,    93,    97,   108,   109,   110,
     111,     0,    99,   114,   115,     4,     5,     6,     7,     8,
       9,    50,    51,    52,    97,    54,    55,    56,    57,    29,
      59,    60,    23,   100,     9,    95,    94,    94,    27,    28,
      29,    93,    31,    32,    99,    96,   102,    96,    13,    38,
      39,    40,    41,    94,    43,    44,    45,    94,     9,    23,
     100,    99,    94,    94,    53,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    94,    23,    95,   102,     9,
      23,    23,     9,    23,    92,     9,    93,    98,    23,     9,
       9,     9,    23,     9,     9,   100,    98,   101,    99,    93,
      96,    98,   101,   101,    99,    95,    99,    99,    97,    96,
      96,    99,    96,    94,    99,    93,    23,     9,    95,    33,
      23,     9,    93,    93,    23,     9,     9,    96,    23,     9,
      93,    93,    80,    94,    94,    94,    93,     9,   106,    94,
     107,    94,   108,    93,    96,    94,   102,    23,   102,    26,
      96,    96,    96,    94,    23,    68,    93,    95,    26,    93,
      99,    26,    26,    99,    96,    93,    99,    69,    94,    98,
      93,   177,   257,    40,    99,    96,    66,    99,   157,    96,
     259,   228,   140,   269,    93,    96,   293,    99,    93,    99,
      98,   174,    93,    99,   197,    99,    96,   351,    96,    96,
     467,   405,   484,   364,   367,   369,   366,   485,   477,   503,
     106,   368,    -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   126,   121,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     151,    -1,   151
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   118,     0,     4,     5,     6,     7,     8,     9,    27,
      28,    29,    31,    32,    38,    39,    40,    41,    43,    44,
      45,    53,    97,   119,   120,   122,   130,     9,    50,    51,
      52,    54,    55,    56,    57,    59,    60,   123,   124,   139,
       9,   138,   138,     9,    94,   131,   132,   138,   138,   138,
     138,     9,     9,    46,    42,     9,     9,    92,     9,    90,
      91,     9,     9,   103,   125,   125,   139,     9,     9,    94,
       9,   133,   134,   135,   136,     9,    94,   126,    23,     9,
       9,   101,   210,   101,   145,    94,    43,    43,   100,    94,
      93,    99,    94,    94,     9,    93,     9,     9,     9,   145,
     101,   143,    13,   149,   150,   153,   155,   100,    96,    99,
      96,    99,    93,    23,   141,    23,   101,   101,     9,    28,
     121,   211,   212,   213,    93,     4,   146,   147,   148,    93,
       9,    23,   127,     9,    36,    37,   166,    23,    23,    23,
      94,   104,    93,    93,    93,    15,    16,    17,    18,    35,
     161,   162,   164,   165,   167,    93,    96,    99,    97,   151,
       9,   123,   154,     9,    23,   137,   134,   136,     9,   136,
      99,   141,    30,   158,   159,   160,    29,   128,   129,    97,
     214,    23,   102,   212,   100,   102,   147,     9,    95,    94,
      94,    93,    96,    96,    99,   149,   141,    94,    94,    94,
      94,    94,   102,   164,   165,   100,   141,   140,   150,    23,
     152,    95,   157,   125,    99,    23,     9,   102,   160,     9,
     102,   129,    23,    23,     9,    23,    26,   215,     9,    23,
      92,     9,    93,    98,    23,    96,   166,     9,     9,     9,
      23,   141,     9,   168,   101,   142,    98,     9,    19,    20,
      21,    22,    23,   156,     9,   136,    99,   101,   141,   101,
     141,    98,    93,   151,    96,    99,    99,    99,    95,   144,
      96,    96,    99,    99,    96,    94,    93,     9,    23,    26,
      28,    61,    62,    63,    64,    65,    66,    67,    68,    86,
      87,    93,    94,   101,   108,   109,   110,   111,   114,   115,
     171,   172,   173,   177,   180,   181,   182,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   199,   200,   201,   205,   206,   216,   141,    23,   161,
     158,    95,   209,     9,    33,    23,     9,   142,    93,    93,
      23,     9,   163,    96,    23,     9,   179,   181,    93,    93,
     177,    94,     9,    94,    94,   196,   196,   181,   171,   102,
     177,    93,    93,    99,    81,   105,    80,   106,   107,   108,
      88,    89,    82,    83,   103,   104,    84,    85,   109,   110,
     111,   112,   113,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,   100,   183,   195,   196,    94,    94,    86,
      87,    94,    97,   116,     9,    94,   174,   175,   176,    96,
     102,   102,     9,    93,    94,    96,    96,   141,    96,    94,
      99,    95,   169,    23,    93,    68,   173,   178,   181,    93,
     181,   181,    96,   102,   182,   186,   181,   187,   188,   189,
     190,   191,   191,   192,   192,   192,   192,   193,   193,   194,
     194,   195,   195,   195,   182,   182,   182,    96,   182,   202,
     181,     9,    10,    11,    12,   198,   176,    99,    94,    97,
     100,    96,    98,    93,    26,    23,    13,    14,   170,   207,
      94,    93,    96,    96,    95,    99,    99,    96,    99,    98,
      96,   175,    96,    23,    98,   101,   182,   203,    96,    99,
      96,   208,   208,    99,   181,   179,   177,   177,   184,   202,
     182,   182,    98,   203,   204,    26,    93,   207,    96,    93,
      69,    96,    96,    99,    99,   102,    99,    93,   179,   177,
     182,   102,   203,    26,    96,    96,    99,   177,    26,    96
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
	    gLexPassthrough=true;
	}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 347 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		gEffect->m_interfaces[(yyvsp[(3) - (6)]).strs[0]]=Effect::InterfaceDcl((yyvsp[(4) - (6)]).strs[0], (yyvsp[(1) - (6)]).lineno);
	}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 351 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 354 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 357 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 360 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string texture_type=(yyvsp[(2) - (5)]).strs[0];
		int type_enum=(yyvsp[(2) - (5)]).token;
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
		declaredTextures[texture_name].type_enum=type_enum;
		gEffect->m_sharedCode<<decl.str();
		if(compute_only)
			gEffect->m_sharedCode<<"#endif\n";
	}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 393 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 409 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream decl;
		decl<<(yyvsp[(1) - (4)]).strs[0]<<" "<<(yyvsp[(2) - (4)]).strs[0]<<" "<<(yyvsp[(3) - (4)]).strs[0]<<";";
		gEffect->m_sharedCode<<decl.str();
	}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 415 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		maxVertexCount=(yyvsp[(4) - (6)]).num;
	}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 419 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		currentCsLayout.x=(yyvsp[(4) - (10)]).num;
		currentCsLayout.y=(yyvsp[(6) - (10)]).num;
		currentCsLayout.z=(yyvsp[(8) - (10)]).num;
	}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 425 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 428 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str=(yyvsp[(1) - (2)]).strs[0]+" "+(yyvsp[(2) - (2)]).strs[0];
		glfxWrite(str.c_str());
		glfxPopState();
	}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 434 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) uniform image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+";";
		glfxWrite(str.c_str());
	}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 440 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string str="layout(rgba32f) image3D ";
		str+=(yyvsp[(2) - (3)]).strs[0]+",";
		glfxWrite(str.c_str());
	}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 446 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name					=(yyvsp[(2) - (3)]).strs[0];
	}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 450 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		string name		=(yyvsp[(2) - (3)]).strs[0];
		string str		=string("#undef ")+name+"\n";
		glfxWrite(str.c_str()); 
	}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 456 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 473 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 513 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 523 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 542 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 545 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 560 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 683 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 717 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyvsp[(5) - (7)]).prog->m_separable=(yyvsp[(1) - (7)]).boolean;
		gEffect->m_programs[(yyvsp[(3) - (7)]).strs[0]]=(yyvsp[(5) - (7)]).prog;
	}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 722 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 725 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 733 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(3) - (5)]).num;
		current_filenumber	=(yyvsp[(4) - (5)]).num;
		global_linenumber	=(yyvsp[(1) - (5)]).lineno+1;// the line AFTER the #line directve.
		WriteLineNumber(gEffect->m_sharedCode,current_filenumber,last_linenumber);
	}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 740 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		last_linenumber		=(yyvsp[(2) - (3)]).num;
		current_filenumber	=(yyvsp[(3) - (3)]).num;
		global_linenumber	=(yyvsp[(1) - (3)]).lineno;
	}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 746 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
		(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
	}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 751 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 757 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num		=(yyvsp[(1) - (1)]).num;
		(yyval).token	=(yyvsp[(1) - (1)]).token;
	}
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 763 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	=(yyvsp[(2) - (3)]).strs[0];
		(yyval).num		=1;
	}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 768 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).num		=0;
	}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 773 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 787 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 790 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 793 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 797 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			  }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 800 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		buildTechniqueGroup.m_techniques[(yyvsp[(2) - (5)]).strs[0]] = (yyvsp[(4) - (5)]).tech;
	}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 804 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 814 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		  }
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 818 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).layoutType=NORMAL_LAYOUT_TYPE;
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		 }
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 823 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 827 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 831 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 835 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 839 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 847 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				(yyval).num=(yyvsp[(3) - (3)]).num;
		   }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 853 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 857 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		   }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 861 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to fx scanning */
	read_shader=false;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 868 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_shader=true;
	read_function=false;
    gLexPassthrough=false;
}
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 875 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	read_function=true;
	read_shader=false;
    gLexPassthrough=false;
}
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 882 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Switch lex to passthrough mode */
    gLexPassthrough=true;
}
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 886 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]=(yyvsp[(2) - (3)]).strs[0];
	// string 1 is the return value, if present.
	(yyval).strs[1]= (yyvsp[(2) - (3)]).strs[1];
    (yyval).lineno= (yyvsp[(2) - (3)]).lineno;
}
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 893 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* Read next block */
    (yyval).strs[0]= glfxreadblock('{', '}');
    (yyval).lineno= glfxget_lineno();
}
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 899 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
 }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 903 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
 }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 907 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="{\n";
	(yyval).strs[0]+=((yyvsp[(2) - (3)]).strs[0]+"\n}\n");
}
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 912 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string list			=(yyvsp[(1) - (2)]).strs[0];
	string new_member	=(yyvsp[(2) - (2)]).strs[0];
    (yyval).strs[0]=(list+"\n")+new_member;
}
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 918 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	string member	=(yyvsp[(1) - (1)]).strs[0];
    (yyval).strs[0]=member;
}
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 923 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 942 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="uniform";
}
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 946 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).strs[0]="";
}
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 950 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).vars		=(yyvsp[(1) - (3)]).vars;
		(yyval).strs[0]	=((yyvsp[(1) - (3)]).strs[0]+",")+(yyvsp[(3) - (3)]).strs[0];

		YYSTYPE::variable var;
		var.storage		=(yyvsp[(3) - (3)]).strs[1];
		var.type		=(yyvsp[(3) - (3)]).strs[2];
		var.identifier	=(yyvsp[(3) - (3)]).strs[3];
		var.semantic	=(yyvsp[(3) - (3)]).strs[4];
		var.type_enum	=(yyvsp[(3) - (3)]).token;
		(yyval).vars->push_back(var);
		buildFunction.parameters.push_back(var);
	}
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 964 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		YYSTYPE::variable var;
		string s1	=(yyvsp[(1) - (1)]).strs[0];
		(yyval).strs[0]	=s1;
		var.storage		=(yyvsp[(1) - (1)]).strs[1];
		var.type		=(yyvsp[(1) - (1)]).strs[2];
		var.identifier	=(yyvsp[(1) - (1)]).strs[3];
		var.semantic	=(yyvsp[(1) - (1)]).strs[4];
		var.type_enum	=(yyvsp[(1) - (1)]).token;
    
		(yyval).vars = new vector<YYSTYPE::variable>;
		(yyval).vars->push_back(var);
		buildFunction.parameters.push_back(var);
	}
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 979 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]	="";
		(yyval).vars = new vector<YYSTYPE::variable>;
	}
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 985 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 79:
/* Line 1792 of yacc.c  */
#line 1016 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(string("[")+(yyvsp[(2) - (3)]).strs[0])+"]";
					(yyval).num=(yyvsp[(2) - (3)]).num;
				}
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 1021 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
				}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 1026 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
					(yyval).num=(yyvsp[(1) - (1)]).num;
			}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 1031 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
					(yyval).num=0;
			}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 1036 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 84:
/* Line 1792 of yacc.c  */
#line 1051 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 1056 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]		=(yyvsp[(1) - (1)]).strs[0];
				(yyval).token		=(yyvsp[(1) - (1)]).token;
			}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 1061 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 1065 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]="";
	}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 1069 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_DISPATCHTHREADID;
	}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 1074 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPID;
	}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1079 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_GROUPTHREADID;
	}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1084 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		(yyval).num=SV_VERTEXID;
	}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1089 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).num=(yyvsp[(2) - (2)]).num;
		(yyval).rType=REGISTER_INT;
	}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1094 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=SEMANTIC;
		(yyval).num=(yyvsp[(2) - (2)]).num;
	}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1100 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
		(yyval).rType=REGISTER_NAME;
	}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1105 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).rType=REGISTER_NONE;
	}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1111 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	Technique *t = new Technique(*((yyvsp[(1) - (1)]).passes));
	(yyval).tech = t;
	delete (yyvsp[(1) - (1)]).passes;
}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1118 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 98:
/* Line 1792 of yacc.c  */
#line 1130 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 99:
/* Line 1792 of yacc.c  */
#line 1144 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyvsp[(4) - (5)]).prog->m_separable	= (yyvsp[(1) - (5)]).boolean;
	(yyval).prog					= (yyvsp[(4) - (5)]).prog;
	(yyval).strs[0]				= (yyvsp[(2) - (5)]).strs[0];
}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 1151 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
    (yyval).prog = new Program(*((yyvsp[(1) - (1)]).shaders),buildPassState,gEffect->textureSamplersByShader);
    delete (yyvsp[(1) - (1)]).shaders;
	buildPassState			=PassState();
}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1158 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 102:
/* Line 1792 of yacc.c  */
#line 1168 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 103:
/* Line 1792 of yacc.c  */
#line 1181 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=(yyvsp[(1) - (2)]).shaders;
		(yyval).shaders=(yyvsp[(1) - (2)]).shaders;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1189 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		map<ShaderType, Program::Shader>* map1=new map<ShaderType, Program::Shader>();
		(yyval).shaders=map1;
		(yyval).strs[0]	="";
		(yyval).strs[1]	="";
		(yyval).sType	=(ShaderType)((int)NUM_OF_SHADER_TYPES+1);
	}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1197 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		  (yyval).strs[0]=(yyvsp[(1) - (10)]).strs[0]+"(";
		  (yyval).strs[0]+=(yyvsp[(3) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(5) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(7) - (10)]).strs[0]+",";
		  (yyval).strs[0]+=(yyvsp[(9) - (10)]).strs[0]+")";
	  }
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1206 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string rast_name=(yyvsp[(3) - (5)]).strs[0];
			 }
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1210 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string depth_name=(yyvsp[(3) - (7)]).strs[0];
				 int index=(yyvsp[(5) - (7)]).num;
				 buildPassState.depthStencilState=depth_name;
			 }
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1216 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				 string blend_name=(yyvsp[(3) - (9)]).strs[0];
				 string vec4text=(yyvsp[(5) - (9)]).strs[0];
				 buildPassState.blendState=blend_name;
				 unsigned mask=(yyvsp[(7) - (9)]).unum;
			 }
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1224 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				errSem("Pass definitions like vs(430)=vs_main are no longer supported. Please use SetVertexShader() etc.");
			}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1229 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 111:
/* Line 1792 of yacc.c  */
#line 1303 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 112:
/* Line 1792 of yacc.c  */
#line 1315 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 113:
/* Line 1792 of yacc.c  */
#line 1335 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 114:
/* Line 1792 of yacc.c  */
#line 1371 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num	=(yyvsp[(3) - (4)]).num;
					(yyval).sType=(yyvsp[(1) - (4)]).sType;
				}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1382 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).lineno=(yyvsp[(1) - (4)]).lineno;
					(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0];
					(yyval).strs[1]=(yyvsp[(4) - (4)]).strs[0];
				}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1388 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).num=0;
				}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1392 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(2) - (2)]).strs[0];
				}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1396 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]="";
				}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1401 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
					(yyval).strs[0]+=(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1406 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1410 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(1) - (2)]).strs[0];
					string statement=(yyvsp[(2) - (2)]).strs[0];
					(yyval).strs[0]	=statement_list;
					(yyval).strs[0]	+=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (2)]).strs[1]+(yyvsp[(2) - (2)]).strs[1];
				}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1419 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]	=statement;
					(yyval).strs[1]	=(yyvsp[(1) - (1)]).strs[1];
				}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1425 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]	="";
					(yyval).strs[1]	="";
				}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1430 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 125:
/* Line 1792 of yacc.c  */
#line 1443 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			string type_spec=(yyvsp[(1) - (2)]).strs[0];
			(yyval).strs[0]=type_spec+" ";
			string init_declarator_list=(yyvsp[(2) - (2)]).strs[0];
			stringReplaceAll(init_declarator_list,"%type%",type_spec);
			stringReplaceAll(init_declarator_list,type_spec+type_spec,type_spec);
			(yyval).strs[0]+=init_declarator_list;
		}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1452 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1456 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1460 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 1464 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 130:
/* Line 1792 of yacc.c  */
#line 1502 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 1506 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 1510 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).num=(yyvsp[(3) - (4)]).num;
			(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
		}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 1515 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 1519 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 1523 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).lineno=(yyvsp[(1) - (2)]).lineno;
					(yyval).strs[1]="";
				}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 1529 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=";\n";
					(yyval).strs[1]="";
				}
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 1534 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 1539 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string compound_statement=(yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=compound_statement;
					(yyval).strs[1]="";
				}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 1545 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 1550 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 141:
/* Line 1792 of yacc.c  */
#line 1562 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
					(yyval).strs[1]="";
				}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 1567 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (7)]).strs[0]+(yyvsp[(2) - (7)]).strs[0]+(yyvsp[(3) - (7)]).strs[0]+(yyvsp[(4) - (7)]).strs[0]+(yyvsp[(5) - (7)]).strs[0]+(yyvsp[(6) - (7)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 1572 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement=(yyvsp[(9) - (9)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (9)]).strs[0]+(yyvsp[(2) - (9)]).strs[0]+(yyvsp[(3) - (9)]).strs[0]+(yyvsp[(4) - (9)]).strs[0]+(yyvsp[(5) - (9)]).strs[0]+(yyvsp[(6) - (9)]).strs[0]+(yyvsp[(7) - (9)]).strs[0]+(yyvsp[(8) - (9)]).strs[0]+statement;
					(yyval).strs[1]="";
				}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 1578 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 1583 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 1588 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+";\n";
					(yyval).strs[1]="";
				}
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 1593 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 148:
/* Line 1792 of yacc.c  */
#line 1608 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				(yyval).strs[1]="";
				(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
			}
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 1614 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 1618 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 1622 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 1625 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
			}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 1629 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
				(yyval).strs[0]="";
			}
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 1634 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string statement_list=(yyvsp[(2) - (3)]).strs[0];
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+statement_list+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 1640 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 1644 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 1648 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;

  case 158:
/* Line 1792 of yacc.c  */
#line 1652 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
		}
    break;

  case 159:
/* Line 1792 of yacc.c  */
#line 1656 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 169:
/* Line 1792 of yacc.c  */
#line 1669 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 170:
/* Line 1792 of yacc.c  */
#line 1673 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
	}
    break;

  case 171:
/* Line 1792 of yacc.c  */
#line 1677 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (5)]).strs[0]+(yyvsp[(2) - (5)]).strs[0]+(yyvsp[(3) - (5)]).strs[0]+(yyvsp[(4) - (5)]).strs[0]+(yyvsp[(5) - (5)]).strs[0];
		}
    break;

  case 172:
/* Line 1792 of yacc.c  */
#line 1682 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 173:
/* Line 1792 of yacc.c  */
#line 1686 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0];
				}
    break;

  case 174:
/* Line 1792 of yacc.c  */
#line 1690 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 175:
/* Line 1792 of yacc.c  */
#line 1694 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 176:
/* Line 1792 of yacc.c  */
#line 1698 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 177:
/* Line 1792 of yacc.c  */
#line 1702 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 178:
/* Line 1792 of yacc.c  */
#line 1706 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 179:
/* Line 1792 of yacc.c  */
#line 1710 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 180:
/* Line 1792 of yacc.c  */
#line 1714 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 181:
/* Line 1792 of yacc.c  */
#line 1718 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 182:
/* Line 1792 of yacc.c  */
#line 1723 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 183:
/* Line 1792 of yacc.c  */
#line 1727 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 184:
/* Line 1792 of yacc.c  */
#line 1731 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 185:
/* Line 1792 of yacc.c  */
#line 1735 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 186:
/* Line 1792 of yacc.c  */
#line 1739 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 187:
/* Line 1792 of yacc.c  */
#line 1743 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 188:
/* Line 1792 of yacc.c  */
#line 1747 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 189:
/* Line 1792 of yacc.c  */
#line 1751 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 190:
/* Line 1792 of yacc.c  */
#line 1755 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 191:
/* Line 1792 of yacc.c  */
#line 1759 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 192:
/* Line 1792 of yacc.c  */
#line 1763 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 193:
/* Line 1792 of yacc.c  */
#line 1767 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 194:
/* Line 1792 of yacc.c  */
#line 1771 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 195:
/* Line 1792 of yacc.c  */
#line 1775 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 196:
/* Line 1792 of yacc.c  */
#line 1779 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 197:
/* Line 1792 of yacc.c  */
#line 1783 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 198:
/* Line 1792 of yacc.c  */
#line 1787 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 199:
/* Line 1792 of yacc.c  */
#line 1791 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
}
    break;

  case 200:
/* Line 1792 of yacc.c  */
#line 1795 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 201:
/* Line 1792 of yacc.c  */
#line 1799 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 202:
/* Line 1792 of yacc.c  */
#line 1803 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 203:
/* Line 1792 of yacc.c  */
#line 1807 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 204:
/* Line 1792 of yacc.c  */
#line 1811 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
}
    break;

  case 210:
/* Line 1792 of yacc.c  */
#line 1815 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
}
    break;

  case 211:
/* Line 1792 of yacc.c  */
#line 1819 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="texture";
}
    break;

  case 212:
/* Line 1792 of yacc.c  */
#line 1823 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
	(yyval).strs[0]="textureLod";
}
    break;

  case 213:
/* Line 1792 of yacc.c  */
#line 1827 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 214:
/* Line 1792 of yacc.c  */
#line 1837 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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
#line 1847 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (1)]).strs[0];			//Command
					}
    break;

  case 216:
/* Line 1792 of yacc.c  */
#line 1852 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (4)]).strs[0]+(yyvsp[(2) - (4)]).strs[0]+(yyvsp[(3) - (4)]).strs[0]+(yyvsp[(4) - (4)]).strs[0];
						(yyval).strs[2]=(yyvsp[(1) - (4)]).strs[2];			//Command
					}
    break;

  case 217:
/* Line 1792 of yacc.c  */
#line 1857 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (6)]).strs[1];
						string x			=(yyvsp[(3) - (6)]).strs[0];
						string y			=(yyvsp[(5) - (6)]).strs[0];

						(yyval).strs[0]=GetSizeFunction( textureName, x, y,"");
					}
    break;

  case 218:
/* Line 1792 of yacc.c  */
#line 1865 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string textureName	=(yyvsp[(1) - (8)]).strs[1];
						string x			=(yyvsp[(3) - (8)]).strs[0];
						string y			=(yyvsp[(5) - (8)]).strs[0];
						string z			=(yyvsp[(7) - (8)]).strs[0];
						(yyval).strs[0]=GetSizeFunction( textureName, x, y,z);
					}
    break;

  case 219:
/* Line 1792 of yacc.c  */
#line 1873 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 220:
/* Line 1792 of yacc.c  */
#line 1910 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 221:
/* Line 1792 of yacc.c  */
#line 1975 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						// ok this could be a function call.
						string command=(yyvsp[(1) - (3)]).strs[2];
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
					}
    break;

  case 222:
/* Line 1792 of yacc.c  */
#line 1981 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						string expr1=(yyvsp[(1) - (3)]).strs[0];
						string expr3=(yyvsp[(3) - (3)]).strs[0];
						(yyval).strs[2]=expr3;			//Command
						(yyval).strs[0]=expr1+(yyvsp[(2) - (3)]).strs[0]+expr3;
					}
    break;

  case 223:
/* Line 1792 of yacc.c  */
#line 1988 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 224:
/* Line 1792 of yacc.c  */
#line 1992 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (2)]).strs[0]+(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 225:
/* Line 1792 of yacc.c  */
#line 1996 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars=(yyvsp[(1) - (3)]).vars;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(3) - (3)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 226:
/* Line 1792 of yacc.c  */
#line 2004 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars = new vector<YYSTYPE::variable>;
						YYSTYPE::variable var;
						var.identifier	=(yyvsp[(1) - (1)]).strs[0];
						(yyval).vars->push_back(var);
					}
    break;

  case 227:
/* Line 1792 of yacc.c  */
#line 2012 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					string assignment_exp = (yyvsp[(1) - (1)]).strs[0];
					(yyval).strs[0]=assignment_exp;
				}
    break;

  case 228:
/* Line 1792 of yacc.c  */
#line 2017 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (3)]).children;
					string initlist = (yyvsp[(1) - (3)]).strs[0] + (yyvsp[(2) - (3)]).strs[0] + (yyvsp[(3) - (3)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 229:
/* Line 1792 of yacc.c  */
#line 2024 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(2) - (4)]).children;
					string initlist = (yyvsp[(1) - (4)]).strs[0] + (yyvsp[(2) - (4)]).strs[0] + (yyvsp[(3) - (4)]).strs[0] + (yyvsp[(4) - (4)]).strs[0];
					(yyval).strs[0] = initlist;
				}
    break;

  case 230:
/* Line 1792 of yacc.c  */
#line 2031 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children.clear();
					children.push_back((yyvsp[(1) - (1)]));
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 231:
/* Line 1792 of yacc.c  */
#line 2038 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					vector<glfxstype> &children = (yyval).children;
					children = (yyvsp[(1) - (3)]).children;
					children.push_back((yyvsp[(3) - (3)]));
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 232:
/* Line 1792 of yacc.c  */
#line 2045 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 233:
/* Line 1792 of yacc.c  */
#line 2049 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 234:
/* Line 1792 of yacc.c  */
#line 2053 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (3)]).strs[0]+(yyvsp[(2) - (3)]).strs[0]+(yyvsp[(3) - (3)]).strs[0];
				}
    break;

  case 235:
/* Line 1792 of yacc.c  */
#line 2057 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 236:
/* Line 1792 of yacc.c  */
#line 2061 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
				}
    break;

  case 237:
/* Line 1792 of yacc.c  */
#line 2065 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 238:
/* Line 1792 of yacc.c  */
#line 2073 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
		ostringstream layoutDef;
		//layoutDef<<"#line "<<$1.lineno<<endl;
		layoutDef<<"layout"<<(yyvsp[(2) - (2)]).strs[0]<<' '<<"out float "<<(yyvsp[(1) - (2)]).strs[0]<<';'<<endl;
		(yyval).strs[0]=layoutDef.str();
	}
    break;

  case 239:
/* Line 1792 of yacc.c  */
#line 2081 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    { /* read parenthesis */
		(yyval).strs[0]=glfxreadblock('(', ')');
	}
    break;

  case 240:
/* Line 1792 of yacc.c  */
#line 2085 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]		=(yyvsp[(2) - (2)]).strs[0];
					}
    break;

  case 241:
/* Line 1792 of yacc.c  */
#line 2089 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).strs[0]="";
					}
    break;

  case 242:
/* Line 1792 of yacc.c  */
#line 2093 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (3)]).lineno;
					}
    break;

  case 243:
/* Line 1792 of yacc.c  */
#line 2096 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
					}
    break;

  case 244:
/* Line 1792 of yacc.c  */
#line 2100 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(2) - (2)]).lineno;
					}
    break;

  case 245:
/* Line 1792 of yacc.c  */
#line 2105 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
						(yyval).lineno		=(yyvsp[(1) - (1)]).lineno;
					}
    break;

  case 246:
/* Line 1792 of yacc.c  */
#line 2109 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
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

  case 247:
/* Line 1792 of yacc.c  */
#line 2218 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (1)]).lineno;
							(yyval).num		=-1;
						}
    break;

  case 248:
/* Line 1792 of yacc.c  */
#line 2223 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno	=(yyvsp[(1) - (2)]).lineno;
							(yyval).strs[0]	=(yyvsp[(1) - (2)]).strs[0];
							(yyval).num		=(yyvsp[(2) - (2)]).num;
						}
    break;

  case 249:
/* Line 1792 of yacc.c  */
#line 2229 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=(yyvsp[(2) - (3)]).num;
							 (yyval).fnum=(yyvsp[(2) - (3)]).fnum;
						}
    break;

  case 250:
/* Line 1792 of yacc.c  */
#line 2234 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							 (yyval).num=0;
						}
    break;

  case 251:
/* Line 1792 of yacc.c  */
#line 2238 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
						}
    break;

  case 252:
/* Line 1792 of yacc.c  */
#line 2243 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).num=(yyvsp[(1) - (1)]).num;
						}
    break;

  case 253:
/* Line 1792 of yacc.c  */
#line 2248 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
							(yyval).lineno=(yyvsp[(1) - (1)]).lineno;
							(yyval).fnum=(yyvsp[(1) - (1)]).fnum;
						}
    break;

  case 254:
/* Line 1792 of yacc.c  */
#line 2253 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"
    {
			(yyval).strs[0]=(yyvsp[(1) - (1)]).strs[0];
		}
    break;


/* Line 1792 of yacc.c  */
#line 5068 "src/glfxLALRParser.cpp"
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
#line 2256 "C:\\Simul\\master\\Simul\\External\\glfx\\src\\glfx.ypp"


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
	declaredTextures.clear();
	read_shader=false;
	read_function=false;
}
