#pragma once
#include "Game.h"

class PlaehngineEditor : public Game
{
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Destroy() override;

	virtual std::string GetName() override;
	virtual std::string GetIconPath() override;
	virtual Vector2D GetWindowSize() override;
	virtual Vector2D GetResolution() override;
};