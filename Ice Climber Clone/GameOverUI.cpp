#include "GameOverUI.h"
#include "ComponentEssentials.h"
#include "Scenes.h"
#include "MainMenu.h"

void GameOverUI::Update()
{
	_transform->_position.y += GameTime::_delta * SPEED;
	if (_transform->_position.y > MAX_POSITION_Y) {
		_transform->_position.y = MAX_POSITION_Y;
		Scenes::LoadScene<MainMenu>();
	}
}
