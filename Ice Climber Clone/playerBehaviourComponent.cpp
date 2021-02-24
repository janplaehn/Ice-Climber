#include "PlayerBehaviourComponent.h"
#include "Screen.h"
#include "Transform.h"
#include "AudioSource.h"


void PlayerBehaviourComponent::Init()
{
	_gameObject->_transform->_position.x = Screen::WIDTH/2;
	_gameObject->_transform->_position.y = 20;

	time_fire_pressed = -10000.f;
}

void PlayerBehaviourComponent::Update(float dt)
{
	Input::KeyStatus keys =	Input::GetKeyStatus();
	if (keys._right)
		Move(dt * _playerSpeed);
	if (keys._left)
		Move(-dt * _playerSpeed);
	if (keys._fire)
	{
		_gameObject->GetComponent<AudioSource>()->Play();
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
