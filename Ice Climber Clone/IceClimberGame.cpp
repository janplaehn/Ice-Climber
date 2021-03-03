#include "IceClimbergame.h"
#include "Scenes.h"
#include "PlayScene.h"

void IceClimberGame::Create(class Plaehngine* engine)
{
	Scenes::LoadScene<PlayScene>();
}

void IceClimberGame::Init()
{
	
}

void IceClimberGame::Update(float dt)
{
}

void IceClimberGame::Destroy()
{
}
