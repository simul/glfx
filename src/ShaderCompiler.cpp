#include "glfxParser.h"
#include "glfxEffect.h"

using namespace std;
using namespace glfxParser;

string Compile(glfxParser::ShaderType shaderType,const CompilableShader &sh)
{
	std::ostringstream shaderCode;
	std::ostringstream extraDeclarations;
	std::ostringstream finalCode;
	string shaderContent=sh.shaderContent;
	// Add shader parameters
	for(vector<glfxstype::variable>::const_iterator it=sh.vars.begin();it!=sh.vars.end();++it)
	{
		bool as_interface=(shaderType!=VERTEX_SHADER);
		string structInstanceName=it->identifier;
		string type(it->type);
		string storage(it->storage);
		if(storage.length()==0)
			storage="in";
		if(storage==string("inout"))
		{
			size_t brack_pos=type.find("<");
			if(brack_pos<type.length())
			{
				string output_type=type.substr(0,brack_pos);
				type=type.substr(brack_pos+1,type.length()-brack_pos-2);
				stringReplaceAll(output_type,"PointStream","points");
				stringReplaceAll(output_type,"LineStream","line_strip");
				stringReplaceAll(output_type,"TriangleStream","triangle_strip");
				shaderCode<<"layout("<<output_type<<") out;\n";
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
				size_t brack_pos=type.find("<");
				if(brack_pos<type.length())
				{
					string output_type=type.substr(0,brack_pos);
					type=type.substr(brack_pos+1,type.length()-brack_pos-2);
					stringReplaceAll(output_type,"PointStream","points");
					stringReplaceAll(output_type,"LineStream","line_strip");
					stringReplaceAll(output_type,"TriangleStream","triangle_strip");
					shaderCode<<"layout("<<output_type<<") out;\n";
				}
				// In the actual shader code, convert HLSL-style member function calls to GLSL type
				// stream commands:
				string appendcall=structInstanceName+".Append";
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
						vertexEmitCode<<structInstanceName<<"."<<m.name<<"="<<localStructName<<"."<<m.name<<"; ";
					}
					vertexEmitCode<<"EmitVertex()";
					shaderContent.replace(shaderContent.begin()+pos,shaderContent.begin()+endpos+1,vertexEmitCode.str());
					pos=shaderContent.find(appendcall,endpos);
			
				}
				stringReplaceAll(shaderContent,structInstanceName+".RestartStrip()","EndPrimitive();");
				as_interface=true;
				storage="out";
			}
			// Geometry shader storage (line,lineadj,point) needs special consideration.
			// it gets moved to this kind of declaration:
			// layout(triangles) in;
			// layout (triangle_strip, max_vertices=6) out;
			if(storage==string("line")||storage==string("point")||storage==string("triangle")||storage==string("lineadj")||storage==string("triangleadj"))
			{
				storage+="s";
				stringReplaceAll(storage,"adjs","s_adjacency");
				shaderCode<<"layout("<<storage<<") in;\n";
				storage="in";
				as_interface=true;
			}
			if(as_interface)
			{
				string interfaceName	=structInstanceName;
				if(shaderType!=GEOMETRY_SHADER)
				{
					interfaceName+="IO";
					extraDeclarations<<type<<" "<<structInstanceName<<";\n";
				}
				shaderCode<<storage<<" "<<type<<"IO\n";
				shaderCode<<"{\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					shaderCode<<'\t'<<m.type<<' '<<m.name<<";"<<endl;
				}
				shaderCode<<"} "<<interfaceName<<";\n";
				// Now we have to copy... EVERY MEMBER from the "interface" to the struct instance. Thanks, OpenGL!
				if(shaderType!=GEOMETRY_SHADER)
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					extraDeclarations<<structInstanceName<<"."<<m.name<<"="<<interfaceName<<"."<<m.name<<";\n";
				}
			}
			else
			{
				extraDeclarations<<type<<" "<<structInstanceName<<";\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					string sem=(type+"_")+m.name;
					if(m.semantic.length())
						sem=(sem+"_")+m.semantic;
					if(m.semantic==string("gl_VertexID"))
						sem=m.semantic;
					//shaderCode<<"#line "<<main_linenumber<<" "<<current_filenumber<<endl;
					shaderCode<<storage<<' '<<m.type<<' '<<sem<<";"<<endl;
					extraDeclarations<<structInstanceName<<"."<<m.name<<"="<<sem<<";\n";
				}
			}
			continue;
		}
		else if(varType!=gEffect->m_interfaces.end())
		{
			type+=varType->second.id;
		//	lineno=varType->second.atLine;
		}
		////else
		//	lineno=$1.lineno;
		if(it->semantic.length()>0)
		{
			extraDeclarations<<it->type<<" "<<structInstanceName<<"="<<it->semantic<<";\n"<<endl;
//			shaderCode<<"#define "<<it->identifier<<" "<<it->semantic<<endl;
		}
		else
		{
		// First put #line in to make sure that all our definitions produce correct-looking warnings/errors.
			shaderCode<<"#line "<<sh.main_linenumber<<" "<<sh.current_filenumber<<endl;
			shaderCode<<it->storage<<' '<<type<<' '<<it->identifier<<';\n'<<endl;
		}
	}
	// Add the return variable.
	if(sh.returnType!=string("void"))
	{
		map<string,Struct*>::const_iterator u=gEffect->m_structs.find(sh.returnType);
		if(u==gEffect->m_structs.end())
		{
			string returnVariable="returnVariable";
			// if we're returning a simple type, we declare it as an output.
			shaderCode<<"out "<<sh.returnType<<" "<<returnVariable<<";\n";
			finalCode<<returnVariable<<"="<<sh.returnable<<";"<<endl;
		}
		else
		{
			const Struct *s=u->second;
			string structInstanceName="structInstanceName";
			if(shaderType!=FRAGMENT_SHADER)
			{
				shaderCode<<"out "<<sh.returnType<<"IO\n{\n";
				for(int i=0;i<(int)s->m_structMembers.size();i++)
				{
					const StructMember &m=s->m_structMembers[i];
					shaderCode<<"\t"<<m.type<<" "<<m.name<<";\n";
				}
				shaderCode<<"} "<<structInstanceName<<";"<<endl;
			}
			for(int i=0;i<(int)s->m_structMembers.size();i++)
			{
				const StructMember &m=s->m_structMembers[i];
				string sem=(sh.returnType+"_")+m.name;
				if(m.semantic.length())
					sem=(sem+"_")+m.semantic;
				// Special outputs:
				if(m.semantic==string("gl_VertexID")||m.semantic==string("SV_POSITION"))
				{
					string builtin_name="gl_Position";
					shaderCode<<"out "<<m.type<<' '<<builtin_name<<";"<<endl;
					finalCode<<builtin_name<<"="<<sh.returnable<<"."<<m.name<<";"<<endl;
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
				//out float gl_FragDepth;
				shaderCode<<"out "<<m.type<<' '<<sem<<";"<<endl;
				finalCode<<sem<<"="<<sh.returnable<<"."<<m.name<<";"<<endl;
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

	return shaderCode.str();
	// now we must put a #line directive in the shared code, because we've just snipped out a bunch of what was there:
}