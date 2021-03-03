#include "GameOverUIBehaviour.h"
#include "ComponentEssentials.h"
#include "Scenes.h"
#include "PlayScene.h"

void GameOverUIBehaviour::Update(float dt)
{
	_transform->_position.y += dt * _moveSpeed;
	if (_transform->_position.y > _maxY) {
		_transform->_position.y = _maxY;
		Scenes::LoadScene<PlayScene>();
	}
}
