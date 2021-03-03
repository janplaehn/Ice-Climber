#pragma once
#include "Component.h"

class Cloud : public Component
{
public:
	Cloud(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	bool _moveRight = true;


	virtual void Update() override;


private:
	const float SPEED = 20;
};

