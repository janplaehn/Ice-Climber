#pragma once
#include "Component.h"

class IntroCamera : public Component
{
public:

	virtual void Update() override;
private:
	const float SPEED = 95;
	const float MAX_POSITION_Y = 700;
};

