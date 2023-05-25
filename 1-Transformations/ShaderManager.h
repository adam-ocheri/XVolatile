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

	// Provide basic generic testing for Shaders / Shader Programs
	bool VerifyIsValid(GLuint ShaderProgram, GLenum StatusType);

	// Pass Shader Data to the manager
	void RegisterShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

	// Instantiate a single Shader Pass
	void CreateShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

	// Create a new shader program and compile it's individual components
	void CompileShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

public:

	ShaderBase* Shader;

	vector<map<int, std::tuple<GLuint, const char*, GLenum>>> ShaderMaps;

	ShaderManager();
	ShaderManager(ShaderBase* shader);
	~ShaderManager();

	// Compile All Shaders
	void CompileShaders();

	void GatherResources();
	void GatherResources(ShaderBase* ShaderData);
	void GatherResources(GLuint ShaderProgram, const char* VertexShader, const char* PixelShader);

	void Render(GLuint VAO);
};

