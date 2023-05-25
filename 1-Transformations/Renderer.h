#pragma once

#include "ResourceManager.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	ResourceManager* ResourceGroup;

	void Render();
};

