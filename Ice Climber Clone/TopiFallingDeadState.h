#pragma once
#include "State.h"

class Topi;

class TopiFallingDeadState : public State
{
	virtual void Enter() override;
	virtual void Run() override;
	virtual State* GetNextState() override;
	virtual void Exit() override;

private:
	std::shared_ptr<Topi> _topi;

	const float FALL_COOLDOWN = 0.5f;
	const float FALLSPEED = 50;

	float _fallTimer = 0;
};

