#include "TopiBehaviour.h"
#include "Transform.h"
#include <Camera.h>
#include <Physics.h>
#include "AABBCollider.h"
#include "Animation.h"

TopiBehaviour::TopiBehaviour(Plaehngine* engine, GameObject* go)
	: Component(engine, go)
{
}

void TopiBehaviour::Update(float dt)
{
	_ice->_enabled = (_state == WALKWITHICE);
	_ice->_transform->_position	= (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? _transform->_position + Vector2D::Right() * 10 : _transform->_position + Vector2D::Left() * 10;

	Vector2D moveAmount = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? Vector2D::Right() * WALKSPEED * dt : Vector2D::Left() * WALKSPEED * dt;

	if (_state == FETCHICE) {
		moveAmount = moveAmount * 3;
		_animation->_frameRate = 12 * 3;
	}
	else {
		_animation->_frameRate = 12;
	}

	_transform->_position = _transform->_position + moveAmount;

	if (_transform->_position.x > Screen::WIDTH) {
		if (_state == FETCHICE) {
			ChangeDirection();
			_state = WALKWITHICE;
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
		else {
			_transform->_position.x = Screen::WIDTH;
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
				_state = WALKING;
			}
			else {
				_state = FETCHICE;
				ChangeDirection();
			}
		}
	}
}

void TopiBehaviour::ChangeDirection()
{
	_transform->_flipType = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}
