#include "PlayerBehaviour.h"
#include "Screen.h"
#include "Transform.h"
#include "AudioSource.h"
#include "Rigidbody.h"
#include "AABBCollider.h"
#include "Animation.h"
#include "AABBCollider.h"

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
			_animation->_frameStart = 0;
		}
	}
	else {
		_animation->_frameRate = 0;
		if (_rigidbody->_velocity.y > 200.0f) {
			_animation->_frameStart = 0;
		}
		else {
			_animation->_frameStart = 32;
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
}

void PlayerBehaviour::Move(float move)
{
	_rigidbody->_velocity.x += move;
}

void PlayerBehaviour::OnCollision(AABBCollider* other)
{
	if (other->_transform->_position.y < _transform->_position.y && !other->_isTrigger) { //Todo: Fix this madness! Check for Top and bottom instead or return a hit point from the collision!
		_isOnGround = true;
		_animation->_spriteSheet = _walkSprite;
	}

	if ((other->_gameObject->_tag == "Tile") && (other->_transform->_position.y > _transform->_position.y + _collider->_height/2)) {
		other->_gameObject->Destroy();
		_tileBreakSource->Play();
	}
	else if ((other->_gameObject->_tag == "Topi") && !_isInvincible) {
		_isInvincible = true;
		_invincibilityTime = _invincibilityDuration;
		_lives--;
	}
}
