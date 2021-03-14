#pragma once
#include "Component.h"

class IntroCamera : public Component
{
private:
	const float SPEED = 95;
	const float MAX_POSITION_Y = 700;

	virtual void Update() override;
};

