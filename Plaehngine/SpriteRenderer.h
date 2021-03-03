#pragma once
#include "Renderer.h"

class SpriteRenderer : public Renderer
{

public:
	SpriteRenderer();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	class Sprite* _sprite;
};
