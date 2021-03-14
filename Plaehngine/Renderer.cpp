#include "Renderer.h"
#include <algorithm>

void Renderer::SortRenderers()
{
	std::sort(_renderers.begin(), _renderers.end(), FurtherBack());
}

std::vector<Renderer*> Renderer::_renderers;