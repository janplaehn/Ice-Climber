#pragma once
#include "Component.h"

class TopiBehaviour : public Component
{
public:
	TopiBehaviour(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Update(float dt);

protected:
	const float WALKSPEED = 10;
};

