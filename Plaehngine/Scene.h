#pragma once
#include "GameObject.h"
#include "ComponentEssentials.h"
#include "Input.h"
#include "Camera.h"
#include "Sprite.h"
#include "Audio.h"
#include <memory>

class Scene
{
public:
	virtual void Load() = 0;
	void Unload();
};

