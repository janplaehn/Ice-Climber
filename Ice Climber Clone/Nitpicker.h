#pragma once
#include "Enemy.h"

class Sprite;
class AudioSource;

class Nitpicker : public Enemy
{
public:

	virtual void SetDeathSprite(Sprite* sprite);
	virtual void SetDeathAudioSource(AudioSource* deathSource);

private:

	virtual void Update() override;

	virtual void Damage() override;
	virtual void MoveHorizontally();
	virtual void MoveVertically();
	virtual void ComputeSpriteFlip();

	bool _accelerateVertically = false;
	bool _accelerateHorizontally = true;
	Vector2D _velocity = Vector2D::Zero();

	Sprite* _deathSprite;
	AudioSource* _deathAudioSource;

	const Vector2D ACCELERATION = Vector2D(5, 3);
	const Vector2D MAX_VELOCITY = Vector2D(35, 10);
	const Vector2D FALL_VELOCITY = Vector2D(0, -60);
};