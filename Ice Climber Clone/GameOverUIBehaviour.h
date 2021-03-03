#pragma once
#include "Component.h"
class GameOverUIBehaviour : public Component
{
public:
	GameOverUIBehaviour(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

protected:
	const float _moveSpeed = 75;
	const int _maxY = Screen::HEIGHT - 56;

	virtual void Update() override;
};