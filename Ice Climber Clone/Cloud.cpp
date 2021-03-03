#include "Cloud.h"
#include "Transform.h"

void Cloud::Update()
{
	Vector2D direction = _moveRight ? Vector2D::Right() : Vector2D::Left();

	_transform->_position = _transform->_position + direction * SPEED * GameTime::_delta;

	if (_transform->_position.x > (Screen::_width))
		_transform->_position.x = 0;

	if (_transform->_position.x < 0)
		_transform->_position.x = (Screen::_width);
}
