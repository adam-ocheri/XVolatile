#pragma once

#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
using namespace std;
#include "ShaderBase.h"


class ShaderManager
{
private:

	

public:
	// Vertex Shader Code
	static const char* VertexShader;

	// Fragment Shader Code
	static const char* PixelShader;

	// Each object we draw will need to have it's own VAO, VBO and ShaderProgram
	GLuint VertexArrayObject;
	GLuint VertexBufferObject;
	GLuint ShaderProgram;

	vector<GLuint> VBOA;
	vector<map<int, std::tuple<GLuint, const char*, GLenum>>> ShaderMaps;

	ShaderManager();
	~ShaderManager();

	// Provide basic generic testing for Shaders / Shader Programs
	bool VerifyIsValid(GLuint ShaderProgram, GLenum StatusType);

	// Provide basic generic testing for Shaders / Shader Programs
	void RegisterShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

	// Instantiate a single Shader Pass
	void CreateShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

	// Compile All Shaders
	void CompileShaders();

	// Create a new shader program and compile it's individual components
	void CompileShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

	void GatherResources(GLuint ShaderProgram, const char* VertexShader, const char* PixelShader);
	void GatherResources(ShaderBase* ShaderData);

	void Render();

	void CreateTriangle();

	//char* VertexShader;
	//char* PixelShader;
};

