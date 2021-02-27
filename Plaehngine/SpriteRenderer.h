#pragma once
#include "Renderer.h"

class SpriteRenderer : public Renderer
{

public:
	SpriteRenderer(Plaehngine* engine, GameObject* go);

	virtual void Update(float dt);
	virtual void Draw();
	virtual void Destroy();

	class Sprite* _sprite;
};
