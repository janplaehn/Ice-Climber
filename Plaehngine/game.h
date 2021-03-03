#pragma once
#include "GameObject.h"

class Game
{
public:

	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Destroy() = 0;
};

