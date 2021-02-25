#include "PlayerBehaviour.h"
#include "Screen.h"
#include "Transform.h"
#include "AudioSource.h"
#include "Rigidbody.h"
#include "AABBCollider.h"
#include "SpriteRenderer.h"
#include "AABBCollider.h"

void PlayerBehaviour::Init()
{

	time_fire_pressed = -10000.f;

	_rigidbody = GetComponent<Rigidbody>();
	_spriteRenderer = GetComponent<SpriteRenderer>();
	_collider = GetComponent<AABBCollider>();
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
		_jumpSource->Play();
		_spriteRenderer->_sprite = _jumpSprite;
	}

	if (_transform->_position.x > (Screen::WIDTH))
		_transform->_position.x = 0;

	if (_transform->_position.x < 0)
		_transform->_position.x = (Screen::WIDTH);

	_isOnGround = false;

	_transform->_flipType = (_rigidbody->_velocity.x > 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void PlayerBehaviour::Move(float move)
{
	_rigidbody->_velocity.x += move;
}

void PlayerBehaviour::OnCollision(AABBCollider* other)
{
	if (other->_transform->_position.y < _transform->_position.y) { //Todo: Fix this madness! Check for Top and bottom instead or return a hit point from the collision!
		_isOnGround = true;
		_spriteRenderer->_sprite = _walkSprite;
	}

	if ((other->_gameObject->_tag == "Tile") && (other->_transform->_position.y > _transform->_position.y + _collider->_height)) {
		other->_gameObject->Destroy();
		_tileBreakSource->Play();
	}
}
