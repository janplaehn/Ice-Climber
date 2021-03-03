#include "Transform.h"

Transform::Transform()
{
	_position = Vector2D::Zero();
	_rotation = 0;
	_scale = Vector2D::One();
	_pivot = Vector2D::One() / 2;
	_flipType = SDL_FLIP_NONE;
}

Transform::Transform(const Transform* transform)
{
	_position = transform->_position;
	_rotation = transform->_rotation;
	_scale = transform->_scale;
	_pivot = transform->_pivot;
	_flipType = transform->_flipType;
}
