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
	
	//setup topology
	vector<Vector3> Verts;
	Verts.push_back(Vector3(-0.5f, -0.5f, 0.0f));
	Verts.push_back(Vector3(0.5f, -0.5f, 0.0f));
	Verts.push_back(Vector3(0.0f, 0.5f, 0.0f));

	vector<Vector3> Verts2;
	Verts2.push_back(Vector3(0.5f, 0.5f, 0.0f));
	Verts2.push_back(Vector3(-0.5f, 0.5f, 0.0f));
	Verts2.push_back(Vector3(0.0f, -0.5f, 0.0f));

	ResourcePackage* Package1 = new ResourcePackage(Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector4(), Verts);
	ResourcePackage* Package2 = new ResourcePackage(Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector4(), Verts2);

	ResourcePackages.push_back(Package1);
	ResourcePackages.push_back(Package2);
}

void ResourceManager::Render()
{
	for (ResourcePackage* Package : ResourcePackages)
	{
		Package->Render();
	}
}
