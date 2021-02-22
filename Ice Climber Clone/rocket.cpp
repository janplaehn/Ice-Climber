#include "rocket.h"
#include "SDL.h"
#include "Vector2D.h"
#include "Transform.h"

void Rocket::Init(Vector2D position)
{
	GameObject::Init();

	_transform->_position.x =  position.x;
	_transform->_position.y = position.y;
}

void Rocket::Receive(Message m)
{
	if (!_enabled)
		return;

	if (m == HIT)
	{
		_enabled = false;
	}
}