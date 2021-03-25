#pragma once
#include "LevelScene.h"

class IntroScene : public LevelScene
{
public:
	virtual void Load() override;
protected:
	virtual void LoadIntroCondor();
	virtual void LoadStaticTimer(Vector2D position);
};

