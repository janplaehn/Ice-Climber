#include "TopiWalkingState.h"
#include "ComponentEssentials.h"
#include "Topi.h"
#include "Physics.h"
#include "TopiFetchIceState.h"

void TopiWalkingState::Enter()
{
	_topi = GetComponent<Topi>();
    _topi->_animation->_frameRate = 12;
	_topi->_ice->_enabled = false;
}

void TopiWalkingState::Run()
{

   Vector2D moveAmount = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? Vector2D::Right() * WALKSPEED * GameTime::_delta : Vector2D::Left() * WALKSPEED * GameTime::_delta;
    _transform->_position = _transform->_position + moveAmount;

	if (_transform->_position.x > Screen::_width) {
		_transform->_position.x = 0;
	}
	if (_transform->_position.x < 0) {
		_transform->_position.x = Screen::_width;
	}

	if ((_transform->_position.y - Camera::_position.y) < -16) {
		_gameObject->_enabled = false;
	}
}

State* TopiWalkingState::GetNextState()
{
	Vector2D pointCastPosition = _transform->_flipType == SDL_FLIP_HORIZONTAL ? Vector2D(6, -4) : Vector2D(-6, -4);
	pointCastPosition = pointCastPosition + _transform->_position;
	AABBCollider* result = nullptr;
	if (Physics::PointCast(pointCastPosition, &result, true)) {
		if (!result->_gameObject->_enabled) {
			return new TopiFetchIceState();
		}
	}
    return this;
}

void TopiWalkingState::Exit()
{
}
