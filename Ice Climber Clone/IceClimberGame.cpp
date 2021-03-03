#include "IceClimbergame.h"
#include "Scenes.h"
#include "PlayScene.h"

void IceClimberGame::Init()
{
	Scenes::LoadScene<PlayScene>();
}

void IceClimberGame::Update()
{
}

void IceClimberGame::Destroy()
{
}
