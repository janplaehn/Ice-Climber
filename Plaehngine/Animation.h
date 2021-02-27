#pragma once
#include "Renderer.h"
class Animation : public Renderer
{

public:
	Animation(Plaehngine* engine, GameObject* go);

	virtual void Update(float dt);
	virtual void Draw();
	virtual void Destroy();

	class Sprite* _spriteSheet;
	int _spriteWidth;
	float _frameRate = 12;

	float _timer = 0;
	float _frameStart = 0;
};

