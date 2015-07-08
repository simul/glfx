#include "glfxParser.h"
#include "glfxEffect.h"

using namespace std;
using namespace glfxParser;

bool IsIntegerType(const string &type)
{
	if(type.substr(0,3)=="int"||type.substr(0,4)=="ivec"||type.substr(0,4)=="uvec"||type.substr(0,4)=="uint")
	{
		return true;
	}
	return false;
}

void Compile(glfxParser::ShaderType shaderType,const CompilableShader &sh,CompiledShader *compiledShader)
{
	compiledShader->transformFeedbackTopology = UNDEFINED_TOPOLOGY;
	std::ostringstream shaderCode;
	std::ostringstream extraDeclarations;
	std::ostringstream finalCode;
	string shaderContent=sh.function.content;
	// Add shader parameters
	for(vector<glfxstype::variable>::const_iterator it=sh.function.parameters.begin();it!=sh.function.parameters.end();++it)
	{
		bool as_interface=(shaderType!=VERTEX_SHADER);
		string outBlockNamespace=it->identifier;
		string type(it->type);
		string storage(it->storage);
		if(storage.length()==0)
			storage="in";
		if(storage==string("inout"))
		{
			size_t brack_pos=type.find("<");
			if(it->template_.size())
			{
				string output_type=type;
				type=it->template_;
				stringReplaceAll(output_type,"PointStream","points");
				stringReplaceAll(output_type,"LineStream","line_strip");
				stringReplaceAll(output_type,"TriangleStream","triangle_strip");
				//shaderCode<<"layout("<<output_type<<") out;\n";
			}
		}
		map<string,Struct*>::const_iterator u=gEffect->m_structs.find(type);
		map<string, Effect::InterfaceDcl>::const_iterator varType=gEffect->m_interfaces.find(type);
	
		if(u!=gEffect->m_structs.end())
		{
			const Struct *s=u->second;
		// Geometry shader outputs have the "inout" storage specifier, and a template-looking type.
		// We must convert them to something like:
		// layout(output_primitive,maxverts=vert_count) out;
		// and an untemplated output type.
		//	points
		//	line_strip
		//	triangle_strip
			if(storage==string("inout"))
			{
				compiledShader->outputStruct=type;
				string output_type=it->type;
				{
					if (output_type.find("PointStream")<output_type.length())
					{
						compiledShader->transformFeedbackTopology = POINTS;
					}
					if (output_type.find("LineStream")<output_type.length())
					{
						compiledShader->transformFeedbackTopology = LINES;
					}
					if (output_type.find("TriangleStream")<output_type.length())
					{
						compiledShader->transformFeedbackTopology = TRIANGLES;
					}
					stringReplaceAll(output_type,"PointStream","points");
					stringReplaceAll(output_type,"LineStream","line_strip");
					stringReplaceAll(output_type,"TriangleStream","triangle_strip");
					shaderCode<<"layout("<<output_type<<",max_vertices="<<sh.maxGSVertexCount<<") out;\n";
	//if(shaderType==GEOMETRY_SHADER)
	
		//shaderCode<<"layout(max_vertices="<<sh.maxGSVertexCount<<")\n";
	
				}
				// In the actual shader code, convert HLSL-style member function calls to GLSL type
				// stream commands:
				string appendcall=outBlockNamespace+".Append";
				size_t pos=shaderContent.find(appendcall);
				while(pos<shaderContent.size())
				{
					// We must replace something of the form vSream.Append(OUT)
					// with something like:
					// vStream.pos	=OUT.pos;
					// vStream.txc	=OUT.txc;
					// EmitVertex();

					// First extract the name of the appended struct:
					size_t startpos=shaderContent.find("(",pos);
					size_t endpos=shaderContent.find(")",startpos);
					if(startpos>=shaderContent.length()||endpos>=shaderContent.length())
						break;
			
					string localStructName=shaderContent.substr(startpos+1,endpos-startpos-1);
					ostringstream vertexEmitCode;
					for(int i=0;i<(int)s->m_structMembers.size();i++)
					{
						const StructMember &m=s->m_structMembers[i];
						vertexEmitCode<<outBlockNamespace<<"."<<m.name<<"="<<localStructName<<"."<<m.name<<"; ";
					}
					vertexEmitCode<<"EmitVertex()";
					shaderContent.replace(shaderContent.begin()+pos,shaderContent.begin()+endpos+1,vertexEmitCode.str());
					pos=shaderContent.find(appendcall,endpos);
			
				}
				stringReplaceAll(shaderContent,outBlockNamespace+".RestartStrip()","EndPrimitive();");
				as_interface=true;
				storage="out";
			}
			// Geometry shader storage (line,lineadj,point) needs special consideration.
			// it gets moved to this kind of declaration:
			// layout(triangles) in;
			// layout (triangle_strip, max_vertices=6) out;
			if(storage==string("line")||storage==string("point")||storage==string("triangle")||storage==string("lineadj")||storage==string("triangleadj"))
			{
				// primitive type			vertices per primitive
				//	points					1
				//	lines					2
				//	lines_adjacency			4
				//	triangles				3
				//	triangles_adjacency		6
				storage+="s";
				stringReplaceAll(storage,"adjs","s_adjacency");
				shaderCode<<"layout("<<storage<<") in;\n";
				storage="in";
				as_interface=true;
			}
			if(as_interface)
			{
				string interfaceName	=outBlockNamespace;
				if(shaderType!=GEOMETRY_SHADER)
				{
					interfaceName+="IO";
					extraDeclarations<<type<<" "<<outBlockNamespace<<";\n";
				}
				shaderCode<<storage<<" "<<type<<"IO\n";
				shaderCode<<"{\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					shaderCode<<'\t';
					if(IsIntegerType(m.type))
						shaderCode<<"flat ";
					shaderCode<<m.type<<' '<<m.name<<";"<<endl;
				}
				shaderCode<<"} "<<interfaceName<<";\n";
				// Now we have to copy... EVERY MEMBER from the "interface" to the struct instance. Thanks, OpenGL!
				if(shaderType!=GEOMETRY_SHADER)
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					extraDeclarations<<outBlockNamespace<<"."<<m.name<<"="<<interfaceName<<"."<<m.name<<";\n";
				}
				if(shaderType==GEOMETRY_SHADER)
					compiledShader->outputStructName=type+"IO";
			}
			else
			{
				extraDeclarations<<type<<" "<<outBlockNamespace<<";\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					string sem=(type+"_")+m.name;
					if(m.semantic.length())
						sem=(sem+"_")+m.semantic;
					// If built-in, it's implicit: don't add it as a declaration.
					if(m.semantic==string("gl_VertexID"))
					{
						sem=m.semantic;
					}
					else
					{
						//shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
						shaderCode<<storage<<' '<<m.type<<' '<<sem<<";"<<endl;
					}
					extraDeclarations<<outBlockNamespace<<"."<<m.name<<"="<<sem<<";\n";
				}
			}
			continue;
		}
		else if(varType!=gEffect->m_interfaces.end())
		{
			type+=varType->second.id;
		}
		if(it->template_.length()>0)
		{
			extraDeclarations<<it->type<<" "<<outBlockNamespace<<"="<<it->template_<<";\n"<<endl;
		}
		else
		{
		// First put #line in to make sure that all our definitions produce correct-looking warnings/errors.
			shaderCode<<"#line "<<sh.main_linenumber<<" "<<sh.current_filenumber<<endl;
			shaderCode<<it->storage<<' '<<type<<' '<<it->identifier<<';\n'<<endl;
		}
	}
	// Add the return variable.
	if(sh.function.returnType!=string("void"))
	{
		map<string,Struct*>::const_iterator u=gEffect->m_structs.find(sh.function.returnType);
		if(u==gEffect->m_structs.end())
		{
			string returnVariable="returnVariable";
			// if we're returning a simple type, we declare it as an output.
			shaderCode<<"out "<<sh.function.returnType<<" "<<returnVariable<<";\n";
			finalCode<<returnVariable<<"="<<sh.returnable<<";"<<endl;
		}
		else
		{
			bool as_interface=(shaderType!=FRAGMENT_SHADER);
			const Struct *s=u->second;
			string outBlockNamespace="outBlockNamespace";
			if(as_interface)
			{
				string output_name=sh.function.returnType+"IO";
				shaderCode<<"out "<<output_name<<"\n{\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					shaderCode<<"\t";
					if(IsIntegerType(m.type))
						shaderCode<<"flat ";
					shaderCode<<m.type<<" "<<m.name<<";\n";
					string output_member_name=(output_name+".")+m.name;
					compiledShader->feedbackOutput.push_back(output_member_name);
				}
				shaderCode<<"} "<<outBlockNamespace<<";"<<endl;
				if(shaderType==VERTEX_SHADER)
				{
					compiledShader->outputStruct=sh.function.returnType;
					compiledShader->outputStructName=sh.function.returnType+"IO";
				}
			}
			string returnVariable=sh.returnable;
			if(returnVariable.find("(")<returnVariable.length())
			{
				returnVariable="returnVariable";
				finalCode<<sh.function.returnType<<" "<<returnVariable<<"="<<sh.returnable<<";"<<endl;
			}
			for(int i=0;i<(int)s->m_structMembers.size();i++)
			{
				const StructMember &m=s->m_structMembers[i];
				string sem=(sh.function.returnType+"_")+m.name;
				if(m.semantic.length())
					sem=(sem+"_")+m.semantic;
				// Special outputs:
				if(m.semantic==string("gl_Position")||m.semantic==string("SV_POSITION"))
				{
					string builtin_name="gl_Position";
					// It's implicit, don't declare:
					//shaderCode<<"out "<<m.type<<' '<<builtin_name<<";"<<endl;
					// Flip y of output because we consider GL textures to be "upside-down".
					finalCode<<returnVariable<<"."<<m.name<<".y*=rescaleVertexShaderY;"<<endl;
					finalCode<<builtin_name<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
				else if(m.semantic.substr(0,9)==string("SV_TARGET"))
				{
					string numstr=m.semantic.substr(9,m.semantic.length()-9);
					int num=0;
					 char * pEnd;
					num=strtol(numstr.c_str(),&pEnd,10);
					if(num>=0)
						shaderCode<<"layout(location = "<<num<<") ";
				}
				else if(m.semantic.substr(0,9)==string("SV_DEPTH"))
				{
					sem="gl_FragDepth";
				}
				else
				{
					if(shaderType==FRAGMENT_SHADER)
						continue;
				}
				if(as_interface)
				{
					if(outBlockNamespace.length())
						finalCode<<outBlockNamespace<<".";
					finalCode<<m.name<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
				else
				{
					shaderCode<<"out "<<m.type<<' '<<sem<<";"<<endl;
					finalCode<<sem<<"="<<returnVariable<<"."<<m.name<<";"<<endl;
				}
			}
		}
	}
	// Add definition and code
	shaderCode<<"#line "<<sh.main_linenumber<<" "<<sh.current_filenumber<<endl;
	shaderCode<<"void main()\n{\n";
	if(extraDeclarations.str().length())
		shaderCode<<extraDeclarations.str()<<"\n";
	shaderCode<<"#line "<<sh.content_linenumber<<" "<<sh.current_filenumber<<endl;
	shaderCode<<shaderContent<<"\n"<<finalCode.str()<<"\n}\n";

	compiledShader->source=shaderCode.str();

	// now we must put a #line directive in the shared code, because we've just snipped out a bunch of what was there:
}