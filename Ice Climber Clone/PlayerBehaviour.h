#pragma once
#include "Component.h"

class AABBCollider;
class AudioSource;
class GameObject;
class LifeUI;
class Rigidbody;
class Animation;
class AABBCollider;
class BonusTimer;

class PlayerBehaviour : public Component
{

	float time_fire_pressed;	// time from the last time the fire button was pressed

public:

	virtual void BeginPlay();
	virtual void Update();

	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(float move);

	void OnCollision(std::shared_ptr<AABBCollider> other, Vector2D normal) override;

	class Sprite* _walkSprite;
	class Sprite* _jumpSprite;
	class Sprite* _attackSprite;

	std::shared_ptr<AudioSource> _jumpSource;
	std::shared_ptr<AudioSource> _deathSource;
	std::shared_ptr<AudioSource> _gameOverSource;
	std::shared_ptr<AudioSource> _goalSource;

	std::shared_ptr<GameObject> _gameOverUI;
	std::shared_ptr<GameObject> _hammer;
	std::shared_ptr<LifeUI> _lifeUI;

	std::shared_ptr<Rigidbody> _rigidbody;
	std::shared_ptr<Animation> _animation;
	std::shared_ptr<AABBCollider> _collider;
	std::vector< std::shared_ptr<BonusTimer>> _timers;

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
	std::shared_ptr<Transform> condor = nullptr;
	float _attackDuration = 2.0f / 8.0f;
	float _attackTimer = 0;
	float _winTimer = 0;
	float _timeSinceLastGroundHit = 0.05f;
};
