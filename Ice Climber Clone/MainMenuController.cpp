#include "MainMenuController.h"
#include "Scenes.h"
#include "PlayScene.h"
#include "IntroScene.h"

void MainMenuController::Update()
{
}

void MainMenuController::LoadSinglePlayer()
{
	Scenes::LoadScene<IntroScene>();
}
