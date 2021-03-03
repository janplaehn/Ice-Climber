#pragma once
#include "Game.h"

class IceClimberGame : public Game
{

public:

	virtual void Create(class Plaehngine* engine);

	virtual void Init();

	virtual void Update(float dt);

	virtual void Destroy();
};