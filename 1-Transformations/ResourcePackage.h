#pragma once

#include "ShaderManager.h"
#include "TopologyBase.h"
#include <vector>

class ResourcePackage
{
private:
	static int LayoutLocation_Counter;
public:
	
	ResourcePackage();
	ResourcePackage(Vector4 color);
	ResourcePackage(std::vector<Vector3> vertexData);
	ResourcePackage(Vector4 color, Vector4 posOffset);
	ResourcePackage(Vector4 color, Vector4 posOffset, std::vector<Vector3> vertexData);

	size_t AttributePointer_LayoutLocation;

	ShaderBase* Shader;
	ShaderManager* ShaderProgram;
	TopologyBase* TopologyGroup;

	void Render();
};

