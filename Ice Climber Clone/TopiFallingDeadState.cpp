#include "TopiFallingDeadState.h"
#include "Topi.h"
#include "ComponentEssentials.h"
#include <Physics.h>
#include "TopiWalkingDeadState.h"

void TopiFallingDeadState::Enter()
{
    _topi = GetComponent<Topi>();
    _topi->_fallSource->Play();
    _fallTimer = FALL_COOLDOWN;
    _topi->_animation->_frameRate = 4;
    _topi->_animation->_spriteSheet = _topi->_deathSprite;
}

void TopiFallingDeadState::Run()
{
    Vector2D moveAmount = Vector2D::Down() * FALLSPEED * GameTime::_delta;
    _fallTimer -= GameTime::_delta;
    _transform->_position = _transform->_position + moveAmount;
}

State* TopiFallingDeadState::GetNextState()
{
	Vector2D pointCastPosition = _transform->_flipType == SDL_FLIP_HORIZONTAL ? Vector2D(6, -4) : Vector2D(-6, -4);
	pointCastPosition = pointCastPosition + _transform->_position;
	
	std::shared_ptr<AABBCollider> result = Physics::PointCast(pointCastPosition, true);
	if (result != nullptr) {
		if (result->_gameObject->_enabled) {
			if (_fallTimer < 0 && result->_gameObject->_tag == "Tile") {
				_transform->_position.y = result->_transform->_position.y + result->GetScale().y;
				return new TopiWalkingDeadState();
			}
		}
	}
    return this;
}

void TopiFallingDeadState::Exit()
{
}
