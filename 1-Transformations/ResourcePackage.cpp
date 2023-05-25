#include "ResourcePackage.h"

int ResourcePackage::LayoutLocation_Counter = -1;

ResourcePackage::ResourcePackage() : ResourcePackage(Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector4())
{}

ResourcePackage::ResourcePackage(Vector4 color) : ResourcePackage(color, Vector4())
{}

ResourcePackage::ResourcePackage(std::vector<Vector3> vertexData) : ResourcePackage(Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector4(), vertexData)
{}

ResourcePackage::ResourcePackage(Vector4 color, Vector4 posOffset) : AttributePointer_LayoutLocation(++LayoutLocation_Counter)
{
	Shader = new ShaderBase(color, posOffset);
	ShaderProgram = new ShaderManager(Shader);
	TopologyGroup = new TopologyBase();

	ShaderProgram->CompileShaders();
	TopologyGroup->CreateTopology();
}

ResourcePackage::ResourcePackage(Vector4 color, Vector4 posOffset, std::vector<Vector3> vertexData) : AttributePointer_LayoutLocation(++LayoutLocation_Counter)
{
	Shader = new ShaderBase(color, posOffset);
	ShaderProgram = new ShaderManager(Shader);
	TopologyGroup = new TopologyBase(vertexData);

	ShaderProgram->CompileShaders();
	TopologyGroup->CreateTopology();
}

void ResourcePackage::Render()
{
	ShaderProgram->Render(TopologyGroup->VertexArrayObject);
}
