#pragma once
#include "component.h"

class AlienBehaviourComponent : public Component
{
	friend class Alien;

public:

	AlienBehaviourComponent(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Init();
	virtual void Create(ObjectPool<class Rocket>* bulletsPool);
	// Inherited via Component
	virtual void Update(float dt) override;

protected:
	ObjectPool<class Rocket>* bullets_pool;

	virtual void Move(float dt);
	virtual void Move(float moveX, float moveY);
	virtual bool ShouldChangeDirection();
	virtual void ChangeDirection();
	virtual int Direction();
	virtual void ShootIfTimeToShoot(float dt);
	virtual void Shoot();
	virtual void ComputeNewShootInterval();
	virtual void CheckGameOver();

	const float MOVESPEED = 60;
	bool bMoveRight = true;

	const float _minShootInterval = 0;
	const float _maxShootInterval = 120;
	float _currentShootInterval;
	float _timeSinceLastShot;
};

