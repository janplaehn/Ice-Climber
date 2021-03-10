#pragma once
#include "Scene.h"
class MainMenu : public Scene
{
	virtual void Load() override;

	static std::string ToString(int number, int digitCount);
};

