#pragma once
#include "Component.h"
class IntroCamera : public Component
{
public:

	virtual void Update() override;

	float _speed = 80;
};

