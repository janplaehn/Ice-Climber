#pragma once
#include "Component.h"

class ScoreScreenController : public Component
{
private:

	const float INPUT_DELAY = 3;

	virtual void Update() override;

	float _timer = 0;
};