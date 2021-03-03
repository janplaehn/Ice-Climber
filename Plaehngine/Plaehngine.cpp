#include "Plaehngine.h"
#include "Random.h"
#include "Audio.h"
#include "Input.h"
#include "GameTime.h"
#include "Game.h"
#include "Scenes.h"
#include "Graphics.h"

//Todo: Add A Config to initialize this
//Todo: Add More Window Options stuffs
//Todo: Add Player Settings (Name, etc.)

bool Plaehngine::Init(Game* game)
{
	SDL_Log("Initializing the engine...\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL failed the initialization: %s\n", SDL_GetError());
		return false;
	}

	Graphics::Init();
	Input::Init(this);
	Audio::Init();
	Random::Init();
	GameTime::Init();
	GameObject::_engine = this;

	_game = game;
	_game->Init();

	SDL_Log("Engine up and running...\n");

	return true;
}

void Plaehngine::Destroy()
{
	Scenes::Quit();
	Graphics::Quit();
	Audio::Quit();
	SDL_Quit();
	delete _game;
}

void Plaehngine::Quit() {
	Destroy();
	exit(0);
}

void Plaehngine::Run()
{
	while (true)
	{
		GameTime::Run();
		Scenes::Run();
		Physics::Run();
		Graphics::Run();
		Input::ProcessInput();
	}
}