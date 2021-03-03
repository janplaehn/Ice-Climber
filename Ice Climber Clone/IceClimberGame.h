#pragma once
#include "Game.h"

class IceClimberGame : public Game
{

public:

	virtual void Init();

	virtual void Update();

	virtual void Destroy();
};