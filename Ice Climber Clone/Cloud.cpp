#include "Cloud.h"
#include "Transform.h"

void Cloud::Update(float dt)
{
	Vector2D direction = _moveRight ? Vector2D::Right() : Vector2D::Left();

	_transform->_position = _transform->_position + direction * SPEED * dt;

	if (_transform->_position.x > (Screen::WIDTH))
		_transform->_position.x = 0;

	if (_transform->_position.x < 0)
		_transform->_position.x = (Screen::WIDTH);
}
