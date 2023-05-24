#pragma once

#include "ShaderManager.h"
#include <vector>

class ShaderProgramManager
{
	ShaderProgramManager();

	void SetupRenderQueue();

	vector<ShaderManager*> ShaderPrograms;

	void Render();
};

