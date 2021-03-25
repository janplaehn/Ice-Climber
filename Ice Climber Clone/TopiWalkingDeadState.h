#pragma once
#include "State.h"

class Topi;

class TopiWalkingDeadState : public State
{
	virtual void Enter() override;
	virtual void Run() override;
	virtual State* GetNextState() override;
	virtual void Exit() override;

private:
	std::shared_ptr<Topi> _topi;

	const float WALKSPEED = 20;
};

