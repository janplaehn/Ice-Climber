#pragma once
#include "Component.h"
#include "Physics.h"

class AABBCollider : public Component
{

public:
	float _width = 10;
	float _height = 10;
	Vector2D _offset;
	bool _isTrigger = false;

	AABBCollider();

	void ApplySpriteSize(class Sprite* sprite);

	virtual void BeginPlay();

	virtual void Update();

	virtual void Render();

	virtual void Destroy();

	virtual SDL_Rect GetRect();
};
