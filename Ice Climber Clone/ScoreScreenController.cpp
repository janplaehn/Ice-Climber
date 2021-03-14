#include "ScoreScreenController.h"
#include "Scenes.h"
#include "LevelScene.h"

void ScoreScreenController::Update()
{
	_timer += GameTime::_delta;
	if (_timer < INPUT_DELAY) return;

	if (Input::GetKeyStatus(SDL_SCANCODE_SPACE) == Input::PRESSED) {
		Scenes::LoadScene<LevelScene>();
	}
}
