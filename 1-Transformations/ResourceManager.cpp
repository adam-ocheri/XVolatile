#include "ResourceManager.h"
#include <stdio.h>

ResourceManager::ResourceManager()
{
	ShaderPrograms = {};
	TopologyGroups = {};
	BuildRenderData();
}

void ResourceManager::BuildRenderData()
{
	//setup shaders
	ShaderBase* Shader = new ShaderBase(Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector4(0.8f, 0.8f, 0.0f, 0.0f));
	ShaderManager* Manager = new ShaderManager(Shader);
	ShaderPrograms.push_back(Manager);

	//setup topology
	vector<Vector3> Verts;
	Verts.push_back(Vector3(-0.5f, -0.5f, 0.0f));
	Verts.push_back(Vector3(0.5f, -0.5f, 0.0f));
	Verts.push_back(Vector3(0.0f, 0.5f, 0.0f));

	TopologyBase* Topo = new TopologyBase(Verts);
	TopologyGroups.push_back(Topo);

	//setup shaders --------------------------------------------------------------------------------------------
	ShaderBase* Shader2 = new ShaderBase(Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector4(0.25f, 0.25f, 0.0f, 0.0f));
	ShaderManager* Manager2 = new ShaderManager(Shader2);
	ShaderPrograms.push_back(Manager2);

	//setup topology
	vector<Vector3> Verts2;
	Verts2.push_back(Vector3(0.5f, 0.5f, 0.0f));
	Verts2.push_back(Vector3(-0.5f, 0.5f, 0.0f));
	Verts2.push_back(Vector3(0.0f, -0.5f, 0.0f));

	TopologyBase* Topo2 = new TopologyBase(Verts2);
	TopologyGroups.push_back(Topo2);

	//Compile and Build --------------------------------------------------------------------------------------------
	for (size_t i = 0; i < ShaderPrograms.size(); ++i)
	{
		//ShaderPrograms.at(i)->Shader->AttributePointer_LayoutLocation = i;
		ShaderPrograms.at(i)->CompileShaders();

		//TopologyGroups.at(i)->AttributePointer_LayoutLocation = i;
		TopologyGroups.at(i)->CreateTopology();
	}
}

void ResourceManager::Render()
{
	for (ShaderManager* ShaderProgram : ShaderPrograms)
	{
		ShaderProgram->Render(TopologyGroups.at(ShaderProgram->Shader->AttributePointer_LayoutLocation)->VertexArrayObject);

		size_t z = 0;
		z = z - 1;
		printf("looping renderer..., I: %d", z);
	}
}
