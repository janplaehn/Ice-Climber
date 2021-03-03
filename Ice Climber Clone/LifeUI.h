#pragma once
#include "Component.h"

class LifeUI : public Component
{

public:
	LifeUI(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	std::vector<class Renderer*> _lifeRenderers;

	void UpdateLifeCounter(int amount);

	virtual void Update() override;
};

