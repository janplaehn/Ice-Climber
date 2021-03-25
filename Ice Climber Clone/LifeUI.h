#pragma once
#include "Component.h"

class Renderer;

class LifeUI : public Component
{
public:

	void UpdateLifeCounter(int amount);
	void AddRenderer(std::shared_ptr<Renderer> renderer);

private:

	std::vector<std::shared_ptr<Renderer>> _lifeRenderers;
};

