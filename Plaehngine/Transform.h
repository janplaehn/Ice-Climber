#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();

	virtual void Update() {};

	Vector2D _position = Vector2D::Zero();
	float _rotation;
	Vector2D _scale;
	Vector2D _pivot;
	SDL_RendererFlip _flipType;
	bool _isInScreenSpace = false;
};