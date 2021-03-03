#pragma once
#include "Renderer.h"
class Animation : public Renderer
{

public:
	Animation();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	class Sprite* _spriteSheet;
	int _spriteWidth;
	float _frameRate = 12;

	float _timer = 0;
	int _frame = 0;
};

