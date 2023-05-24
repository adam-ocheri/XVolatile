#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;

	Vector4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w)
	{}
};

class ShaderBase
{
public:
	ShaderBase();
	ShaderBase(Vector4 color);
	ShaderBase(Vector4 color, Vector4 posOffset);
	~ShaderBase();

	size_t AttributePointer_LayoutLocation = 0;

	Vector4 Color;
	Vector4 PositionOffset;

	// Shader Program ID
	GLuint ShaderProgram;

	// Vertex Shader Code
	std::string VertexShader;

	// Fragment Shader Code
	std::string PixelShader;
};

