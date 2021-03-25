#include "TopiWalkWithIceState.h"
#include "Topi.h"
#include "ComponentEssentials.h"
#include <Physics.h>
#include "TopiWalkingState.h"

void TopiWalkWithIceState::Enter()
{
    _topi = GetComponent<Topi>();
    _topi->ChangeDirection();
    _topi->_ice->_enabled = true;
	_tilesRebuilt = 0;
	_topi->_animation->_frameRate = 12;
	_rebuildTimer = 0;
	_tilesRebuilt = 0;
}

void TopiWalkWithIceState::Run()
{
    _topi->_ice->_transform->_position = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? _transform->_position + Vector2D::Right() * 10 : _transform->_position + Vector2D::Left() * 10;
	
	if (_tilesRebuilt > 0) {
		_rebuildTimer += GameTime::_delta;
	}

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

	Vector2D pointCastPosition = _transform->_flipType == SDL_FLIP_HORIZONTAL ? Vector2D(6, -4) : Vector2D(-6, -4);
	pointCastPosition = pointCastPosition + _transform->_position;
	std::shared_ptr<AABBCollider> result = Physics::PointCast(pointCastPosition, true);
	if (result != nullptr) {
		if (!result->_gameObject->_enabled) {
			result->_gameObject->_enabled = true;
			_rebuildTimer = 0;
			_tilesRebuilt++;
		}
	}
}

State* TopiWalkWithIceState::GetNextState()
{
	if (_tilesRebuilt > 0 &&  _rebuildTimer > REBUILD_COOLDOWN) {
		return new TopiWalkingState();
		_rebuildTimer = 0;
	}
	if (_tilesRebuilt >= REBUILDCOUNT) {
		return new TopiWalkingState();
	}

    return this;
}

void TopiWalkWithIceState::Exit()
{
	_topi->_ice->_enabled = false;
}
