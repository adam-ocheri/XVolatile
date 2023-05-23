#include "ShaderBase.h"
#include <sstream>


ShaderBase::ShaderBase()
{
	Color = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	// Initialize a new Shader Program
	ShaderProgram = glCreateProgram();

	VertexShader = "											\n\
		#version 330                                                        \n\
																			\n\
		layout (location = 0) in vec3 pos;                                  \n\
																			\n\
		void main()                                                         \n\
		{                                                                   \n\
			gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);                   \n\
		}";



	// Fragment Shader Code
	PixelShader = "												\n\
		#version 330                                                        \n\
																			\n\
		out vec4 color;                                                     \n\
																			\n\
		void main()                                                         \n\
		{                                                                   \n\
			color = vec4(1.0, 0.0, 0.0, 1.0);                               \n\
		}";
}

ShaderBase::ShaderBase(Vector4 color)
{
	Color = color;
	// Initialize a new Shader Program
	ShaderProgram = glCreateProgram();


	VertexShader = "											\n\
		#version 330                                                        \n\
																			\n\
		layout (location = 0) in vec3 pos;                                  \n\
																			\n\
		void main()                                                         \n\
		{                                                                   \n\
			gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);                   \n\
		}";

	std::stringstream formattedPS;
	formattedPS << "				\n"
		<< "#version 330																						\n"
		<< "																									\n"
		<< "out vec4 color;																						\n"
		<< "																									\n"
		<< "void main()																							\n"
		<< "{																									\n"
		<< "  color = vec4(" << Color.X << "," << Color.Y << "," << Color.Z << "," << Color.W << ");" << "		\n"
		<< "}";

	PixelShader = formattedPS.str();
	//PixelShader = new char[formattedPS.str().length() + 1];
	//memcpy(const_cast<char*>(PixelShader), formattedPS.str().c_str(), formattedPS.str().length() + 1);

}

ShaderBase::ShaderBase(Vector4 color, Vector4 posOffset)
{
	Color = color;
	PositionOffset = posOffset;

	// Initialize a new Shader Program
	ShaderProgram = glCreateProgram();


	std::stringstream formattedVS;
	formattedVS << "				\n"
		<< "#version 330																						\n"
		<< "																									\n"
		<< "layout (location = " << 0 << ") in vec3 pos;														\n"
		<< "																									\n"
		<< "void main()																							\n"
		<< "{																									\n"
		<< "  gl_Position = vec4(pos.x * " << PositionOffset.X << "," 
							 << "pos.y * " << PositionOffset.Y << "," 
							 << "pos.z * " << PositionOffset.Z << "," 
							 << "1.0 * " << PositionOffset.W	  << ");" << "										\n"
		<< "}";

	VertexShader = formattedVS.str();
	//VertexShader = new char[formattedVS.str().length() + 1];
	//memcpy(const_cast<char*>(VertexShader), formattedVS.str().c_str(), formattedVS.str().length() + 1);

	std::stringstream formattedPS;
	formattedPS << "				\n"
		<< "#version 330																						\n"
		<< "																									\n"
		<< "out vec4 color;																						\n"
		<< "																									\n"
		<< "void main()																							\n"
		<< "{																									\n"
		<< "  color = vec4(" << Color.X << "," << Color.Y << "," << Color.Z << "," << Color.W << ");" << "		\n"
		<< "}";

	PixelShader = formattedPS.str();
	//PixelShader = new char[formattedPS.str().length() + 1];
	//memcpy(const_cast<char*>(PixelShader), formattedPS.str().c_str(), formattedPS.str().length() + 1);
}

ShaderBase::~ShaderBase()
{

}
