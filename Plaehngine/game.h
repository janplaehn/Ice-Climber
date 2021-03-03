#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class Game
{
public:

	virtual void Init() = 0;

	virtual void Update() = 0;

	virtual void Destroy() = 0;

	virtual std::string GetName() = 0;
	virtual std::string GetIconPath() = 0;
	virtual Vector2D GetWindowSize() = 0;
	virtual Vector2D GetResolution() = 0;
};

