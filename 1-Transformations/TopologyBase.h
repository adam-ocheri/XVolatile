#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>


struct Vector3
{
	GLfloat X;
	GLfloat Y;
	GLfloat Z;

	Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z)
	{}
};

class TopologyBase
{
private:
	static size_t LayoutLocation;
public:

	TopologyBase();
	TopologyBase(size_t Location);
	TopologyBase(std::vector<Vector3> VertexData);
	TopologyBase(size_t Location, std::vector<Vector3> VertexData);

	void CreateTopology();

	std::vector<Vector3> Vertices;

	size_t AttributePointer_LayoutLocation = 0;

	GLuint VertexArrayObject;
	GLuint VertexBufferObject;
};

