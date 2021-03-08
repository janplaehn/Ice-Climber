#pragma once
#include "Component.h"

class ScoreScreenController : public Component
{
	// Inherited via Component
	virtual void Update() override;

private:
	float _timer = 0;
};