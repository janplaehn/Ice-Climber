#pragma once
#include "LevelScene.h"

class IntroScene : public LevelScene
{
	virtual void Load() override;
	virtual void LoadIntroCondor();
	virtual void LoadStaticTimer(Vector2D position);
};

