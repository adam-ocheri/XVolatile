#include "Renderer.h"

Renderer::Renderer()
{
	ResourceGroup = new ResourceManager();
}

Renderer::~Renderer()
{
	delete ResourceGroup;
}

void Renderer::Render()
{
	ResourceGroup->Render();
}
