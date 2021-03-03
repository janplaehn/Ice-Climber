#include "IceClimbergame.h"
#include "Scenes.h"
#include "PlayScene.h"
#include "MainMenu.h"
#include "TtfFont.h"

void IceClimberGame::Init()
{
	TtfFont::Create("Assets/Fonts/retro.ttf", "Retro", 16);
	Scenes::LoadScene<MainMenu>();
}

void IceClimberGame::Update()
{
}

void IceClimberGame::Destroy()
{
}

std::string IceClimberGame::GetName()
{
	return "Ice Climber";
}

std::string IceClimberGame::GetIconPath()
{
	return "Assets/Player/icon.png";
}

Vector2D IceClimberGame::GetWindowSize()
{
	return Vector2D(1024,960);
}

Vector2D IceClimberGame::GetResolution()
{
	return Vector2D(256,240);
}
