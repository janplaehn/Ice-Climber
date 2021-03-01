#include "GameOverUIBehaviour.h"
#include "ComponentEssentials.h"

void GameOverUIBehaviour::Update(float dt)
{
	_transform->_position.y += dt * _moveSpeed;
	if (_transform->_position.y > _maxY) {
		_transform->_position.y = _maxY;
	}
}
