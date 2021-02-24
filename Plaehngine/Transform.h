#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform(Plaehngine* engine, GameObject* go);

	virtual void Update(float dt) {};

	Vector2D _position = Vector2D::Zero();
	float _rotation;
	Vector2D _scale;
	Vector2D _pivot;
	SDL_RendererFlip _flipType;
};