#pragma once

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderManager
{
private:

	// Vertex Shader Code
	const char* VertexShader = "											\n\
		#version 330                                                        \n\
																			\n\
		layout (location = 0) in vec3 pos;                                  \n\
																			\n\
		void main()                                                         \n\
		{                                                                   \n\
			gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);                   \n\
		}";

	// Fragment Shader Code
	const char* PixelShader = "												\n\
		#version 330                                                        \n\
																			\n\
		out vec4 color;                                                     \n\
																			\n\
		void main()                                                         \n\
		{                                                                   \n\
			color = vec4(1.0, 0.0, 0.0, 1.0);                               \n\
		}";

public:
	// Each object we draw will need to have it's own VAO, VBO and ShaderProgram
	GLuint VertexArrayObject;
	GLuint VertexBufferObject;
	GLuint ShaderProgram;

	ShaderManager();
	~ShaderManager();

	// Provide basic generic testing for Shaders / Shader Programs
	bool VerifyIsValid(GLuint ShaderProgram, GLenum StatusType);

	// Instantiate a single Shader Pass
	void CreateShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

	// Create a new shader program and compile it's individual components
	void CompileShaders();

	void Render();

	void CreateTriangle();


};

