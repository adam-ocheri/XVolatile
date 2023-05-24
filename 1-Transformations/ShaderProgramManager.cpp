#include "ShaderProgramManager.h"

ShaderProgramManager::ShaderProgramManager()
{
	ShaderPrograms = {};
}

void ShaderProgramManager::SetupRenderQueue()
{
	//ShaderBase* Shader = new ShaderBase();
	//ShaderManager* Manager = new ShaderManager();

	//Manager->GatherResources(Shader);

	//ShaderPrograms.push_back(Manager);

	

	for (int i = 0; i < 1; ++i)
	{
		//ShaderPrograms.at(i);
		const int a = 1;
	}
}

void ShaderProgramManager::Render()
{
	for (ShaderManager* ShaderProgram : ShaderPrograms)
	{
		ShaderProgram->Render();
	}
}
