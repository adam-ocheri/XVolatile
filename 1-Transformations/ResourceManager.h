#pragma once

#include "ShaderManager.h"
#include "TopologyBase.h"
#include <vector>

class ResourceManager
{
private:
	vector<ShaderManager*> ShaderPrograms;
	vector<TopologyBase*> TopologyGroups;

	
public:
	//static int BufferLocation;

	ResourceManager();

	void BuildRenderData();
	void Render();
};

