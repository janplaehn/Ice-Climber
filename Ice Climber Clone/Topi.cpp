#include "Topi.h"
#include "Transform.h"
#include <Camera.h>
#include <Physics.h>
#include "AABBCollider.h"
#include "Animation.h"
#include "AudioSource.h"

void Topi::Update()
{
	_ice->_enabled = (_state == WALKWITHICE);
	_ice->_transform->_position	= (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? _transform->_position + Vector2D::Right() * 10 : _transform->_position + Vector2D::Left() * 10;

	if (_state == WALKWITHICE && _tilesRebuilt > 0) {
		_rebuildTimer += GameTime::_delta;
		if (_rebuildTimer > _rebuildCooldown) {
			_state = WALKING;
			_rebuildTimer = 0;
		}
	}

	Vector2D moveAmount;
	if (_state == DEADFALLING) {
		moveAmount = Vector2D::Down() * FALLSPEED * GameTime::_delta;
		_fallTimer -= GameTime::_delta;
	}
	else if (_state == DEADWALKING) {
		moveAmount = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? Vector2D::Right() * WALKSPEED * 2 * GameTime::_delta : Vector2D::Left() * WALKSPEED * 2 * GameTime::_delta;
	}
	else {
		moveAmount = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? Vector2D::Right() * WALKSPEED * GameTime::_delta : Vector2D::Left() * WALKSPEED * GameTime::_delta;
	}

	if (_state == FETCHICE) {
		moveAmount = moveAmount * 3;
		_animation->_frameRate = 12 * 2;
	}
	else if ((_state == DEADWALKING) || (_state == DEADFALLING)) {
		_animation->_frameRate = 4;
	}
	else {
		_animation->_frameRate = 12;
	}

	_transform->_position = _transform->_position + moveAmount;

	if (_transform->_position.x > Screen::_width) {
		if (_state == FETCHICE) {
			ChangeDirection();
			_state = WALKWITHICE;
		}
		else if (_state == DEADWALKING) {
			_gameObject->_enabled = false;
		}
		else {
			_transform->_position.x = 0;
		}
	}
	if (_transform->_position.x < 0) {
		if (_state == FETCHICE) {
			ChangeDirection();
			_state = WALKWITHICE;
		}
		else if (_state == DEADWALKING) {
			_gameObject->_enabled = false;
		}
		else {
			_transform->_position.x = Screen::_width;
		}
	}

	if ((_transform->_position.y - Camera::_position.y) < -16) {
		_gameObject->_enabled = false; 
	}

	Vector2D pointCastPosition = _transform->_flipType == SDL_FLIP_HORIZONTAL ? Vector2D(6, -4) : Vector2D(-6, -4);
	pointCastPosition = pointCastPosition + _transform->_position;
	AABBCollider* result = nullptr;

	if (Physics::PointCast(pointCastPosition, &result, true)) {
		if (!result->_gameObject->_enabled) {
			if (_state == WALKWITHICE) {
				result->_gameObject->_enabled = true;
				_rebuildTimer = 0;
				_tilesRebuilt++;
				if (_tilesRebuilt >= REBUILDCOUNT) {
					_state = WALKING;
				}
			}
			else if (_state == DEADWALKING) {
				_state = DEADFALLING;
				_fallSource->Play();
				_fallTimer = _fallCooldown;
			}
			else if (_state == FETCHICE) {
				Damage();
				ChangeDirection();
			}
			else if (!(_state == DEADFALLING)) {
				_state = FETCHICE;
				_tilesRebuilt = 0;
				ChangeDirection();
			}
		}
		else {
			if (_state == DEADFALLING && _fallTimer < 0) {
				_transform->_position.y = result->_transform->_position.y + result->_height;
				_state = DEADWALKING;
				ChangeDirection();
			}
		}
	}

	if ((_state == DEADWALKING) || (_state == DEADFALLING)) {
		_animation->_spriteSheet = _deathSprite;
		_animation->_frameRate = 4;
	}
}

void Topi::ChangeDirection()
{
	_transform->_flipType = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

void Topi::Damage()
{
	GetComponent<AABBCollider>()->_enabled = false;
	_state = DEADWALKING;
	_animation->_frame = 0;
	ChangeDirection();
	_deathSource->Play();
}
