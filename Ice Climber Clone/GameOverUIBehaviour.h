#pragma once
#include "Component.h"
class GameOverUIBehaviour : public Component
{
protected:
	const float _moveSpeed = 75;
	const int _maxY = Screen::_height - 56;

	virtual void Update() override;
};