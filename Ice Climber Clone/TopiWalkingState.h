#pragma once
#include "State.h"

class Topi;

class TopiWalkingState : public State
{
	virtual void Enter() override;
	virtual void Run() override;
	virtual State* GetNextState() override;
	virtual void Exit() override;

private:
	const float WALKSPEED = 10;
	Topi* _topi = nullptr;
};

