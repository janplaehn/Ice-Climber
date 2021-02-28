#pragma once
#include "Component.h"

class Cloud : public Component
{
public:
	Cloud(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	bool _moveRight = true;


	virtual void Update(float dt) override;


private:
	const float SPEED = 20;
};

