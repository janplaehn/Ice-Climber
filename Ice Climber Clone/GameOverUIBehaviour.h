#pragma once
#include "Component.h"

class GameOverUIBehaviour : public Component
{
private:

	const float SPEED = 75;
	const int MAX_POSITION_Y = Screen::_height - 56;

	virtual void Update() override;
};