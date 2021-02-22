#include "playerBehaviourComponent.h"
#include "gameObject.h"
#include "Plaehngine.h"
#include "rocket.h"
#include "gameSettings.h"
#include "Screen.h"
#include "Vector2D.h"
#include "Transform.h"
#include <AudioSource.h>


void PlayerBehaviourComponent::Init()
{
	_gameObject->_transform->_position.x = 320;
	_gameObject->_transform->_position.y = Screen::HEIGHT - 32;

	time_fire_pressed = -10000.f;
}

void PlayerBehaviourComponent::Update(float dt)
{
	Plaehngine::KeyStatus keys;
	_engine->GetKeyStatus(keys);
	if (keys._right)
		Move(dt * GameSettings::PLAYER_SPEED);
	if (keys._left)
		Move(-dt * GameSettings::PLAYER_SPEED);
	if (keys._fire)
	{
		if (CanFire())
		{
			// fetches a rocket from the pool and use it in game_objects
			Rocket* rocket = rockets_pool->FirstAvailable();
			if (rocket != NULL)	// rocket is NULL is the object pool can not provide an object
			{
				rocket->Init(Vector2D(_gameObject->_transform->_position.x, Screen::HEIGHT - 52));
				GameObject::_gameObjects.insert(rocket);
				_gameObject->GetComponent<AudioSource>()->Play();
			}
		}
	}
}

void PlayerBehaviourComponent::Move(float move)
{
	_gameObject->_transform->_position.x += move;

	if (_gameObject->_transform->_position.x > (Screen::WIDTH - 32))
		_gameObject->_transform->_position.x = Screen::WIDTH - 32;

	if (_gameObject->_transform->_position.x < 0)
		_gameObject->_transform->_position.x = 0;
}

bool PlayerBehaviourComponent::CanFire()
{
	// shoot just if enough time passed by
	if ((_engine->GetElapsedTime() - time_fire_pressed) < (GameSettings::FIRE_TIME_INTERVAL / GameSettings::time_multiplier))
		return false;

	time_fire_pressed = _engine->GetElapsedTime();
	return true;
}
