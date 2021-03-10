#pragma once
#include "Component.h"

class GameOverUIBehaviour : public Component
{
private:

	virtual void Update() override;

	const float SPEED = 75;
	const int MAX_POSITION_Y = Screen::_height - 56;
};