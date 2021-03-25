#pragma once
#include "Component.h"

class GameOverUI : public Component
{
public:
	virtual void Update() override;
private:

	const float SPEED = 75;
	const int MAX_POSITION_Y = Screen::_height - 56;
};