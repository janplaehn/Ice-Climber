#pragma once
#include "State.h"

class Topi;

class TopiFetchIceState : public State
{
public:
	virtual void Enter() override;
	virtual void Run() override;
	virtual State* GetNextState() override;
	virtual void Exit() override;

private:
	const float WALKSPEED = 30;
	Topi* _topi = nullptr;
};

