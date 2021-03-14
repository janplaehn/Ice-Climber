#include "TopiFetchIceState.h"
#include "ComponentEssentials.h"
#include "Topi.h"
#include <Physics.h>
#include "TopiWalkWithIceState.h"

void TopiFetchIceState::Enter()
{
    _topi = GetComponent<Topi>();
    _topi->ChangeDirection();

    _topi->_ice->_enabled = false;
	_topi->_animation->_frameRate = 24;
}

void TopiFetchIceState::Run()
{
	Vector2D moveAmount = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? Vector2D::Right() * WALKSPEED * GameTime::_delta : Vector2D::Left() * WALKSPEED * GameTime::_delta;
    _transform->_position = _transform->_position + moveAmount;

	if ((_transform->_position.y - Camera::_position.y) < -16) {
		_gameObject->_enabled = false;
	}
}

State* TopiFetchIceState::GetNextState()
{
	if (_transform->_position.x > Screen::_width) {
		return new TopiWalkWithIceState();
	}
	if (_transform->_position.x < 0) {
		return new TopiWalkWithIceState();
	}

	Vector2D pointCastPosition = _transform->_flipType == SDL_FLIP_HORIZONTAL ? Vector2D(6, -4) : Vector2D(-6, -4);
	pointCastPosition = pointCastPosition + _transform->_position;
	AABBCollider* result = nullptr;

	if (Physics::PointCast(pointCastPosition, &result, true)) {
		if (!result->_gameObject->_enabled) {
			_topi->Damage();
		}
	}

    return this;
}

void TopiFetchIceState::Exit()
{
}
