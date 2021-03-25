#include "TopiWalkingDeadState.h"
#include "ComponentEssentials.h"
#include "Topi.h"
#include <Physics.h>
#include "TopiFallingDeadState.h"

void TopiWalkingDeadState::Enter()
{
    _topi = GetComponent<Topi>();
    _topi->_animation->_frameRate = 4;
	_topi->_animation->_spriteSheet = _topi->_deathSprite;

	GetComponent<AABBCollider>()->_enabled = false;
	_topi->_animation->_frame = 0;
	_topi->ChangeDirection();
}

void TopiWalkingDeadState::Run()
{
    Vector2D moveAmount = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? Vector2D::Right() * WALKSPEED * GameTime::_delta : Vector2D::Left() * WALKSPEED * GameTime::_delta;
    _transform->_position = _transform->_position + moveAmount;

	if (_transform->_position.x > Screen::_width) {
		_gameObject->_enabled = false;
	}
	if (_transform->_position.x < 0) {
		_gameObject->_enabled = false;
	}

	if ((_transform->_position.y - Camera::_position.y) < -16) {
		_gameObject->_enabled = false;
	}
}

State* TopiWalkingDeadState::GetNextState()
{

	Vector2D pointCastPosition = _transform->_flipType == SDL_FLIP_HORIZONTAL ? Vector2D(6, -4) : Vector2D(-6, -4);
	pointCastPosition = pointCastPosition + _transform->_position;
	std::shared_ptr<AABBCollider> result = Physics::PointCast(pointCastPosition, true);
	if (result != nullptr) {
		if (!result->_gameObject->_enabled) {
			return new TopiFallingDeadState();
		}
	}
    return this;
}

void TopiWalkingDeadState::Exit()
{
}
