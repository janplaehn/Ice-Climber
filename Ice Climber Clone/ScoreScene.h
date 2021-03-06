#pragma once
#include "Scene.h"

class ScoreScene : public Scene
{
public:
	virtual void Load() override;

	static int _mountainIndex;

	std::string ToString(int number, int digitCount);
};