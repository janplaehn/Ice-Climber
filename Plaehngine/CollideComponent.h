#pragma once
#include "Component.h"

class CollideComponent : public Component
{

public:
	CollideComponent(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	ObjectPool<GameObject>* _collisionObjects = new ObjectPool<GameObject>(); // collision will be tested with these objects
	virtual void Update(float dt);
};
