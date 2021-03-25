#include "Nitpicker.h"
#include "ComponentEssentials.h"
#include "Scores.h"

void Nitpicker::Update()
{

	_transform->_position = _transform->_position + _velocity * GameTime::_delta;

	if (_isDead) return;

	MoveHorizontally();
	MoveVertically();
	ComputeSpriteFlip();
}

void Nitpicker::SetDeathSprite(Sprite* sprite)
{
	_deathSprite = sprite;
}

void Nitpicker::SetDeathAudioSource(std::shared_ptr<AudioSource> source)
{
	_deathAudioSource = source;
}

void Nitpicker::Damage()
{
	if (_isDead) return;
	_deathAudioSource->Play();
	_isDead = true;
	GetComponent<AABBCollider>()->_enabled = false;
	GetComponent<Animation>()->_spriteSheet = _deathSprite;
	_velocity = FALL_VELOCITY;
	Scores::_nitpickers++;
}

void Nitpicker::MoveHorizontally()
{
	if (_accelerateHorizontally) {
		_velocity.x += ACCELERATION.x * GameTime::_delta;
		if (_velocity.x > MAX_VELOCITY.x) {
			_accelerateHorizontally = false;
		}
	}
	else {
		_velocity.x -= ACCELERATION.x * GameTime::_delta;
		if (_velocity.x < -MAX_VELOCITY.x) {
			_accelerateHorizontally = true;
		}
	}
}

void Nitpicker::MoveVertically()
{
	if (_accelerateVertically) {
		_velocity.y += ACCELERATION.y * GameTime::_delta;
		if (_velocity.y > MAX_VELOCITY.y) {
			_accelerateVertically = false;
		}
	}
	else {
		_velocity.y -= ACCELERATION.y * GameTime::_delta;
		if (_velocity.y < -MAX_VELOCITY.y) {
			_accelerateVertically = true;
		}
	}
}

void Nitpicker::ComputeSpriteFlip()
{
	_transform->_flipType = (_velocity.x > 0) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}
