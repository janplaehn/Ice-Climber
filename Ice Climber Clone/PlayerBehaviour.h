#pragma once

#include "component.h";

class PlayerBehaviour : public Component
{

	float time_fire_pressed;	// time from the last time the fire button was pressed

public:
	PlayerBehaviour(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual ~PlayerBehaviour() {}

	virtual void Init();

	virtual void Update(float dt);

	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(float move);

	void OnCollision(class AABBCollider* other);

	class Sprite* _walkSprite;
	class Sprite* _jumpSprite;

	class AudioSource* _jumpSource;
	class AudioSource* _tileBreakSource;

private:
	const float WALKSPEED = 400;
	const float JUMPFORCE = 450;

	class Rigidbody* _rigidbody;
	class Animation* _animation;
	class AABBCollider* _collider;

	bool _isOnGround = false;
	bool _isInvincible = false;
	float _invincibilityTime = 0;
	float _invincibilityDuration = 2.0f;

	int _lives = 3;
};
