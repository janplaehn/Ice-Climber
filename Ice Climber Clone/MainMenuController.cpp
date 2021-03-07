#include "MainMenuController.h"
#include "Scenes.h"
#include "PlayScene.h"

void MainMenuController::Update()
{
}

void MainMenuController::LoadSinglePlayer()
{
	Scenes::LoadScene<PlayScene>();
}
