#pragma once
#include "Game.h"

class IceClimberGame : public Game
{

public:

	virtual void Init();

	virtual void Update();

	virtual void Destroy();

	virtual std::string GetName() override;
	virtual std::string GetIconPath() override;
	virtual Vector2D GetWindowSize() override;
	virtual Vector2D GetResolution() override;
};