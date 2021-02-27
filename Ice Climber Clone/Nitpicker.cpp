#include "Nitpicker.h"
#include "Transform.h"

Nitpicker::Nitpicker(Plaehngine* engine, GameObject* go)
	: Component(engine, go)
{
}

void Nitpicker::Update(float dt)
{

	_transform->_position = _transform->_position + _speed * dt;

	//Horizontal movement
	if (_accelerateHorizontally) {
		_speed.x += _horizontalAcceleration * dt;
		if (_speed.x > _maxSpeed.x) {
			_accelerateHorizontally = false;
		}
	}
	else {
		_speed.x -= _horizontalAcceleration * dt;
		if (_speed.x < -_maxSpeed.x) {
			_accelerateHorizontally = true;
		}
	}

	//VErtical movement
	if (_accelerateVertically) {
		_speed.y += _verticalAcceleration * dt;
		if (_speed.y > _maxSpeed.y) {
			_accelerateVertically = false;
		}
	}
	else {
		_speed.y -= _verticalAcceleration * dt;
		if (_speed.y < -_maxSpeed.y) {
			_accelerateVertically = true;
		}
	}

	_transform->_flipType = _speed.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}
