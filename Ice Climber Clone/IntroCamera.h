#pragma once
#include "Component.h"

class IntroCamera : public Component
{
private:
	const float SPEED = 80;
	const float MAX_POSITION_Y = 700;

	virtual void Update() override;
};

