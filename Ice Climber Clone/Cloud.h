#pragma once
#include "Component.h"

class Cloud : public Component
{
public:

	bool _moveRight = true;


	virtual void Update() override;

	float _speed = 20;
};

