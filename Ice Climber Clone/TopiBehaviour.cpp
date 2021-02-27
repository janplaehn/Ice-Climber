#include "TopiBehaviour.h"
#include "Transform.h"
#include <Camera.h>

void TopiBehaviour::Update(float dt)
{
	_transform->_position = _transform->_position + Vector2D::Left() * WALKSPEED * dt;

	if (_transform->_position.x > (Screen::WIDTH))
		_transform->_position.x = 0;

	if (_transform->_position.x < 0)
		_transform->_position.x = (Screen::WIDTH);

	if ((_transform->_position.y - Camera::_position.y) < -16) {
		_gameObject->_enabled = false;
	}
}
