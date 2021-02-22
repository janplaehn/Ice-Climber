#pragma once

#include "component.h"

class RocketBehaviourComponent : public Component
{

public:
	RocketBehaviourComponent(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Init();

	void Update(float dt);

	virtual float Direction();

	bool bMoveUp;

};