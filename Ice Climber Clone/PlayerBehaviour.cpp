#include "PlayerBehaviour.h"
#include "Screen.h"
#include "Transform.h"
#include "AudioSource.h"
#include "Rigidbody.h"
#include "AABBCollider.h"
#include "Animation.h"
#include "AABBCollider.h"
#include "LifeUI.h"
#include <Camera.h>

void PlayerBehaviour::Init()
{

	time_fire_pressed = -10000.f;

	_rigidbody = GetComponent<Rigidbody>();
	_animation = GetComponent<Animation>();
	_collider = GetComponent<AABBCollider>();
}

void PlayerBehaviour::Update(float dt)
{
	Input::KeyStatus keys =	Input::GetKeyStatus();
	if (keys._right)
		Move(dt * WALKSPEED);
	if (keys._left)
		Move(-dt * WALKSPEED);
	if (keys._fire && _isOnGround)
	{
		_rigidbody->_velocity.y = JUMPFORCE;
		_jumpSource->Play();
		_animation->_spriteSheet = _jumpSprite;
	}

	if (_transform->_position.x > (Screen::WIDTH))
		_transform->_position.x = 0;

	if (_transform->_position.x < 0)
		_transform->_position.x = (Screen::WIDTH);

	_transform->_flipType = (_rigidbody->_velocity.x > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

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
		_invincibilityTime -= dt;

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


	_isOnGround = false;

	if ((_transform->_position.y - Camera::_position.y) < 0) {
		LoseLife();
	}
}

void PlayerBehaviour::Move(float move)
{
	_rigidbody->_velocity.x += move;
}

void PlayerBehaviour::OnCollision(AABBCollider* other)
{
	if (other->_transform->_position.y < _transform->_position.y && !other->_isTrigger) { //Todo: Fix this madness! Check for Top and bottom instead or return a hit point from the collision!
		_isOnGround = true;
		_lastGroundedPosition = _transform->_position;
		_animation->_spriteSheet = _walkSprite;
	}

	if ((other->_gameObject->_tag == "Tile") && (other->_transform->_position.y > _transform->_position.y + _collider->_height/2)) {
		other->_gameObject->_enabled = false;
		_tileBreakSource->Play();
	}
	else if ((other->_gameObject->_tag == "Topi") && !_isInvincible) {
		LoseLife();
	}
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
