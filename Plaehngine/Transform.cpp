#include "Transform.h"

Transform::Transform()
{
	_position = Vector2D::Zero();
	_rotation = 0;
	_scale = Vector2D::One();
	_pivot = Vector2D::One() / 2;
	_flipType = SDL_FLIP_NONE;
}
