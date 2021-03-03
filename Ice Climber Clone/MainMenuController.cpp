#include "MainMenuController.h"
#include "Scenes.h"
#include "PlayScene.h"

void MainMenuController::Update()
{
	if (Input::GetKeyStatus()._jump) {
		Scenes::LoadScene<PlayScene>();
	}
}
