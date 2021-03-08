#include "ScoreScreenController.h"
#include "Scenes.h"
#include "PlayScene.h"

void ScoreScreenController::Update()
{
	if (Input::GetKeyStatus(SDL_SCANCODE_SPACE) == Input::PRESSED) {
		Scenes::LoadScene<PlayScene>();
	}
}
