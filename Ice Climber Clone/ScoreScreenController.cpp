#include "ScoreScreenController.h"
#include "Scenes.h"
#include "PlayScene.h"

void ScoreScreenController::Update()
{
	_timer += GameTime::_delta;
	if (_timer < 3) return;

	if (Input::GetKeyStatus(SDL_SCANCODE_SPACE) == Input::PRESSED) {
		Scenes::LoadScene<PlayScene>();
	}
}
