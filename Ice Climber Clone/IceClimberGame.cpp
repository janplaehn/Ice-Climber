#include "IceClimbergame.h"
#include "Scenes.h"
#include "PlayScene.h"
#include "MainMenu.h"
#include "TtfFont.h"
#include "ImageFont.h"

void IceClimberGame::Init()
{
	TtfFont::Create("Assets/Fonts/retro.ttf", "Retro", 16);
	ImageFont::Create("Assets/Fonts/iceClimber.png", "Ice Climber", "0123456789ABDGLNOPRSUWY!x.TIME", 8, 8);

	Input::WatchKey(SDL_SCANCODE_RIGHT);
	Input::WatchKey(SDL_SCANCODE_LEFT);
	Input::WatchKey(SDL_SCANCODE_SPACE);
	Input::WatchKey(SDL_SCANCODE_A);
	Input::WatchKey(SDL_SCANCODE_LEFT);
	Input::WatchKey(SDL_SCANCODE_RIGHT);
	Input::WatchKey(SDL_SCANCODE_UP);
	Input::WatchKey(SDL_SCANCODE_DOWN);
	Input::WatchKey(SDL_SCANCODE_SPACE);
	Input::WatchKey(SDL_SCANCODE_ESCAPE);

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
