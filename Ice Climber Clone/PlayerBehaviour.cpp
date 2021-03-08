#include "PlayerBehaviour.h"
#include "Screen.h"
#include "ComponentEssentials.h"
#include "LifeUI.h"
#include "Camera.h"

void PlayerBehaviour::BeginPlay()
{

	time_fire_pressed = -10000.f;

	_rigidbody = GetComponent<Rigidbody>();
	_animation = GetComponent<Animation>();
	_collider = GetComponent<AABBCollider>();
}

void PlayerBehaviour::Update()
{
	if (_isAttacking) {
		_animation->_spriteSheet = _attackSprite;
		_animation->_frameRate = 8;
		_attackTimer += GameTime::_delta;
		_hammer->_enabled = true;
		_hammer->GetComponent<AABBCollider>()->_offset = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? Vector2D(12, 4) :  Vector2D(-12, 4);
		if (_attackTimer > _attackDuration) {
			_attackTimer = 0;
			_isAttacking = false;
			_hammer->GetComponent<AABBCollider>()->_offset = Vector2D(0, 24);
			_hammer->_enabled = false;
		}
		return;
	}

	if (Input::GetKeyStatus(SDL_SCANCODE_RIGHT) == Input::HELD || Input::GetKeyStatus(SDL_SCANCODE_RIGHT) == Input::PRESSED)
		Move(GameTime::_delta * WALKSPEED);
	if (Input::GetKeyStatus(SDL_SCANCODE_LEFT) == Input::HELD || Input::GetKeyStatus(SDL_SCANCODE_LEFT) == Input::PRESSED)
		Move(-GameTime::_delta * WALKSPEED);
	if (Input::GetKeyStatus(SDL_SCANCODE_SPACE) == Input::PRESSED && _isOnGround && !_isAttacking)
	{
		_rigidbody->_velocity.y = JUMPFORCE;
		_jumpSource->Play();
		_animation->_spriteSheet = _jumpSprite;

	}
	else if (Input::GetKeyStatus(SDL_SCANCODE_A) == Input::PRESSED && _isOnGround && !_isAttacking)
	{
		_rigidbody->_velocity = Vector2D::Zero();
		_animation->_spriteSheet = _attackSprite;
		_animation->_frameRate = 8;
		_animation->_frame = 0;
		_isAttacking = true;
		_attackTimer = 0;
		return;
	}

	if (_transform->_position.x > (Screen::_width))
		_transform->_position.x = 0;

	if (_transform->_position.x < 0)
		_transform->_position.x = (Screen::_width);

	if (abs(_rigidbody->_velocity.x) > 0.1f) {
		_transform->_flipType = (_rigidbody->_velocity.x > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	}

	if (_isOnGround) {
		_animation->_frameRate = abs(_rigidbody->_velocity.x) * 0.3f;

		if (abs(_rigidbody->_velocity.x) < 10.0f) {
			_animation->_frameRate = 0;
			_animation->_frame = 0;
		}
	}
	else {
		_animation->_frameRate = 0;
		if (_rigidbody->_velocity.y > 200.0f) {
			_animation->_frame = 0;
		}
		else {
			_animation->_frame = 1;
		}
	}

	if (_isInvincible) {
		_invincibilityTime -= GameTime::_delta;

		float param, fractpart;
		double intpart;
		param = _invincibilityTime * 10.0f;
		fractpart = modf(param, &intpart);

		_animation->_enabled = (fractpart > 0.5f);
		if (_invincibilityTime < 0) {
			_isInvincible = false;
			_animation->_enabled = true;
		}
	}

	_hammer->_enabled = !_isOnGround;
	if (!_isOnGround) {
		_hammer->GetComponent<AABBCollider>()->_offset = Vector2D(0, 24);
	}
	_hammer->_transform->_position = _transform->_position;

	_isOnGround = false;

	if ((_transform->_position.y - Camera::_position.y) < 0) {
		LoseLife();
	}
}

void PlayerBehaviour::Move(float move)
{
	_rigidbody->_velocity.x += move;
}

void PlayerBehaviour::OnCollision(AABBCollider* other, Vector2D normal)
{
	if (normal.y == -1 && !other->_isTrigger) { //Todo: Fix this madness! Check for Top and bottom instead or return a hit point from the collision!
		_isOnGround = true;
		_lastGroundedPosition = _transform->_position;
		if (!_isAttacking) _animation->_spriteSheet = _walkSprite;
	}

	//if ((other->_gameObject->_tag == "Topi") && !_isInvincible) {
	//	LoseLife();
	//}
}

void PlayerBehaviour::LoseLife()
{
	_isInvincible = true;
	_invincibilityTime = _invincibilityDuration;
	_transform->_position = _lastGroundedPosition;
	_lives--;
	_deathSource->Play();
	_lifeUI->UpdateLifeCounter(_lives);
	_rigidbody->_velocity = Vector2D::Zero();

	if (_lives < 0) {
		_gameObject->_enabled = false;
		_gameOverUI->_enabled = true;
		_gameOverSource->Play();
	}
}
