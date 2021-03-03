#include "GameOverUIBehaviour.h"
#include "ComponentEssentials.h"
#include "Scenes.h"
#include "MainMenu.h"

void GameOverUIBehaviour::Update()
{
	_transform->_position.y += GameTime::_delta * _moveSpeed;
	if (_transform->_position.y > _maxY) {
		_transform->_position.y = _maxY;
		Scenes::LoadScene<MainMenu>();
	}
}
