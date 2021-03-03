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

	AABBCollider(Plaehngine* engine, GameObject* go);
	void InitializeWithSprite(class Sprite* sprite);

	ObjectPool<GameObject>* _collisionObjects = new ObjectPool<GameObject>(); // collision will be tested with these objects
	virtual void Update();

	virtual void Render();

	virtual void Destroy();

	virtual SDL_Rect GetRect();
};
