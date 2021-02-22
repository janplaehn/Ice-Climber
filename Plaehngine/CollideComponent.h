#pragma once

#include "component.h"

class CollideComponent : public Component
{

public:
	CollideComponent(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	ObjectPool<GameObject>* _collisionObjects; // collision will be tested with these objects
	virtual void Update(float dt);
};
