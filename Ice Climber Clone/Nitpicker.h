#pragma once
#include "Component.h"
class Nitpicker : public Component
{
public:
	Nitpicker(Plaehngine* engine, GameObject* go);

	virtual void Update(float dt) override;

	Vector2D _speed = Vector2D::Zero();

	bool _accelerateVertically = false;
	bool _accelerateHorizontally = true;

	float _horizontalAcceleration = 5;
	float _verticalAcceleration = 3;

	Vector2D _maxSpeed = Vector2D(35, 10);
};

