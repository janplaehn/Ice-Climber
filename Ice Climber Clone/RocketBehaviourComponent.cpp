#include "RocketBehaviourComponent.h"
#include "gameSettings.h"
#include "gameObject.h"
#include "Screen.h"
#include "Transform.h"

void RocketBehaviourComponent::Init()
{
}

void RocketBehaviourComponent::Update(float dt)

{
	float dir = Direction();
	float speed = GameSettings::ROCKET_SPEED * dt * dir;
	_gameObject->_transform->_position.y -= speed; // rocket_speed * time

	if (_gameObject->_transform->_position.y < 0 || _gameObject->_transform->_position.y > Screen::HEIGHT) // When the rocket reaches the edge of the screen, it disappears.
		_gameObject->_enabled = false;
}

float RocketBehaviourComponent::Direction()
{
	return bMoveUp ? 1.0f : -1.0f;
}
