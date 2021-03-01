#include "Nitpicker.h"
#include "Transform.h"
#include "AABBCollider.h"
#include "Animation.h"
#include "AudioSource.h"

Nitpicker::Nitpicker(Plaehngine* engine, GameObject* go)
	: Enemy(engine, go)
{
}

void Nitpicker::Update(float dt)
{

	_transform->_position = _transform->_position + _speed * dt;

	if (_isDead) return;

	//Horizontal movement
	if (_accelerateHorizontally) {
		_speed.x += _horizontalAcceleration * dt;
		if (_speed.x > _maxSpeed.x) {
			_accelerateHorizontally = false;
		}
	}
	else {
		_speed.x -= _horizontalAcceleration * dt;
		if (_speed.x < -_maxSpeed.x) {
			_accelerateHorizontally = true;
		}
	}

	//VErtical movement
	if (_accelerateVertically) {
		_speed.y += _verticalAcceleration * dt;
		if (_speed.y > _maxSpeed.y) {
			_accelerateVertically = false;
		}
	}
	else {
		_speed.y -= _verticalAcceleration * dt;
		if (_speed.y < -_maxSpeed.y) {
			_accelerateVertically = true;
		}
	}

	_transform->_flipType = _speed.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

void Nitpicker::Damage()
{
	if (_isDead) return;
	_deathSource->Play();
	_isDead = true;
	_gameObject->GetComponent<AABBCollider>()->_enabled = false;
	_gameObject->GetComponent<Animation>()->_spriteSheet = _deathSprite;
	_speed = Vector2D(0, -60);
}
