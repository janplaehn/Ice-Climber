#pragma once
#include "Enemy.h"

class Nitpicker : public Enemy
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

	class Sprite* _deathSprite;
	class AudioSource* _deathSource;

	// Inherited via Enemy
	virtual void Damage() override;
};

