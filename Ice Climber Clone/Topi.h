#pragma once
#include "Enemy.h"

class AudioSource;
class Animation;
class Sprite;

class Topi : public Enemy
{
public:

	Animation* _animation;
	GameObject* _ice;
	Sprite* _deathSprite;

	AudioSource* _deathSource;
	AudioSource* _fallSource;

private:

	virtual void Update() override;

	enum TopiState
	{
		WALKING,
		FETCHICE,
		WALKWITHICE,
		DEADWALKING,
		DEADFALLING
	};

	TopiState _state = WALKING;

	void ChangeDirection();
	void Damage() override;

	float _fallTimer = 0;
	float _rebuildTimer = 0;
	int _tilesRebuilt = 0;

	const float FALL_COOLDOWN = 0.5f;
	const float REBUILD_COOLDOWN = 1.0f;
	const float WALKSPEED = 10;
	const float FALLSPEED = 50;
	const int REBUILDCOUNT = 2;
};