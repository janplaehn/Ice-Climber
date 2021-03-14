#pragma once
#include "State.h"

class Topi;

class TopiWalkWithIceState : public State
{
	virtual void Enter() override;
	virtual void Run() override;
	virtual State* GetNextState() override;
	virtual void Exit() override;

private:
	const float REBUILD_COOLDOWN = 1.0f;
	const int REBUILDCOUNT = 2;
	const float WALKSPEED = 10;

	Topi* _topi = nullptr;
	float _rebuildTimer = 0;
	int _tilesRebuilt = 0;
};

