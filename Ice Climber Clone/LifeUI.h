#pragma once
#include "Component.h"

class Renderer;

class LifeUI : public Component
{
public:

	void UpdateLifeCounter(int amount);
	void AddRenderer(Renderer* renderer);

private:

	std::vector<Renderer*> _lifeRenderers;
};

