#pragma once
#include "component.h"

class RenderComponent : public Component
{

public:
	RenderComponent(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Update(float dt);
	virtual void Destroy();

	class Sprite* _sprite;
};
