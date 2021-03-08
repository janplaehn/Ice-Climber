#pragma once
#include "Component.h"

class PlayerBehaviour : public Component
{

	float time_fire_pressed;	// time from the last time the fire button was pressed

public:

	virtual void BeginPlay();
	virtual void Update();

	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(float move);

	void OnCollision(class AABBCollider* other, Vector2D normal);

	class Sprite* _walkSprite;
	class Sprite* _jumpSprite;
	class Sprite* _attackSprite;

	class AudioSource* _jumpSource;
	class AudioSource* _deathSource;
	class AudioSource* _gameOverSource;

	class GameObject* _gameOverUI;
	class GameObject* _hammer;
	class LifeUI* _lifeUI;

	class Rigidbody* _rigidbody;
	class Animation* _animation;
	class AABBCollider* _collider;
	std::vector<class BonusTimer*> _timers;

	int _lives = 3;

private:
	const float WALKSPEED = 400;
	const float JUMPFORCE = 450;

	bool _isOnGround = false;
	bool _isInvincible = false;
	float _invincibilityTime = 0;
	float _invincibilityDuration = 2.0f;

	Vector2D _lastGroundedPosition = Vector2D::Zero();

	void LoseLife();

	bool _isAttacking = false;
	bool _hasWon = false;
	bool _isInBonus = false;
	Transform* condor = nullptr;
	float _attackDuration = 2.0f / 8.0f;
	float _attackTimer = 0;
	float _timeSinceLastGroundHit = 0.05f;
};
