#pragma once
#include "Enemy.h"

class Topi : public Enemy
{
public:
	Topi(Plaehngine* engine, GameObject* go);

	virtual void Update(float dt);

	class Animation* _animation;
	GameObject* _ice;
	class Sprite* _deathSprite;

	class AudioSource* _deathSource;
	class AudioSource* _fallSource;

protected:
	const float WALKSPEED = 10;
	const float FALLSPEED = 50;

	enum TopiState
	{
		WALKING,
		FETCHICE,
		WALKWITHICE,
		DEADWALKING,
		DEADFALLING
	};

	TopiState _state = WALKING;

	virtual void ChangeDirection();

private:

	virtual void Damage() override;

	float _fallCooldown = 0.5f;
	float _fallTimer = 0;
	float _rebuildCooldown = 1.0f;
	float _rebuildTimer = 0;
	int _tilesRebuilt = 0;
	const int REBUILDCOUNT = 2;
};

