#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TopologyBase
{
public:

	TopologyBase();
	TopologyBase(size_t Location);;

	void CreateTriangle();

	size_t AttributePointer_LayoutLocation = 0;

	GLuint VertexArrayObject;
	GLuint VertexBufferObject;
};

