#pragma once
#include "Component.h"

class LifeUI : public Component
{

public:

	std::vector<class Renderer*> _lifeRenderers;

	void UpdateLifeCounter(int amount);

	virtual void Update() override;
};

