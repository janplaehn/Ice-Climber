#include "LifeUI.h"
#include "ComponentEssentials.h"

void LifeUI::UpdateLifeCounter(int amount)
{
	for (int i = 0; i < _lifeRenderers.size(); i++)
	{
		_lifeRenderers[i]->_enabled = (i < amount);
	}
}

void LifeUI::AddRenderer(Renderer* renderer)
{
	_lifeRenderers.push_back(renderer);
}
