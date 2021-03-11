#include "Cloud.h"
#include "Transform.h"

void Cloud::SetMoveRight(bool moveRight)
{
	_moveRight = moveRight;
}

void Cloud::SetSpeed(float speed)
{
	_speed = speed;
}

void Cloud::Update()
{
	Vector2D direction = _moveRight ? Vector2D::Right() : Vector2D::Left();

	_transform->_position = _transform->_position + direction * _speed * GameTime::_delta;

	if (_transform->_position.x > Screen::_width) _transform->_position.x = 0;
	if (_transform->_position.x < 0) _transform->_position.x = Screen::_width;
}
