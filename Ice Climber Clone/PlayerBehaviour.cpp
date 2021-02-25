#include "PlayerBehaviour.h"
#include "Screen.h"
#include "Transform.h"
#include "AudioSource.h"
#include "Rigidbody.h"
#include "AABBCollider.h"
#include "SpriteRenderer.h"

void PlayerBehaviour::Init()
{

	time_fire_pressed = -10000.f;

	_rigidbody = _gameObject->GetComponent<Rigidbody>();
	_spriteRenderer = _gameObject->GetComponent<SpriteRenderer>();
}

void PlayerBehaviour::Update(float dt)
{
	Input::KeyStatus keys =	Input::GetKeyStatus();
	if (keys._right)
		Move(dt * WALKSPEED);
	if (keys._left)
		Move(-dt * WALKSPEED);
	if (keys._fire && _isOnGround)
	{
		_rigidbody->_velocity.y = JUMPFORCE;
		_gameObject->GetComponent<AudioSource>()->Play();
		_spriteRenderer->_sprite = _jumpSprite;
	}

	if (_gameObject->_transform->_position.x > (Screen::WIDTH))
		_gameObject->_transform->_position.x = 0;

	if (_gameObject->_transform->_position.x < 0)
		_gameObject->_transform->_position.x = (Screen::WIDTH);

	_isOnGround = false;
}

void PlayerBehaviour::Move(float move)
{
	_rigidbody->_velocity.x += move;
}

void PlayerBehaviour::OnCollision(AABBCollider* other)
{
	if (other->_gameObject->_transform->_position.y < _gameObject->_transform->_position.y) { //Todo: Fix this madness! Check for Top and bottom instead or return a hit point from the collision!
		_isOnGround = true;
		_spriteRenderer->_sprite = _walkSprite;
	}
}
