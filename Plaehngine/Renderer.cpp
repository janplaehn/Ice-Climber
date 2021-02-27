#include "Renderer.h"
#include <algorithm>

void Renderer::Update(float dt)
{
}


void Renderer::SortRenderers()
{
	std::sort(_renderers.begin(), _renderers.end(), furtherBack());
}

std::vector<Renderer*> Renderer::_renderers;