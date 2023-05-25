#pragma once

#include "ShaderManager.h"
#include "TopologyBase.h"
#include "ResourcePackage.h"
#include <vector>

class ResourceManager
{
private:
	vector<ShaderManager*> ShaderPrograms;
	vector<TopologyBase*> TopologyGroups;
	vector<ResourcePackage*> ResourcePackages;
	
public:
	//static int BufferLocation;

	ResourceManager();

	void BuildRenderData();
	void Render();
};

