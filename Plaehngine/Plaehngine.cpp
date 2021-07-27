#include "ApplicationState.h"
#include "Plaehngine.h"
#include "Random.h"
#include "Audio.h"
#include "Input.h"
#include "GameTime.h"
#include "Game.h"
#include "Scenes.h"
#include "Graphics.h"
#include "Physics.h"

#ifdef PLAEHNGINE_EDITOR
#include "PlaehngineEditor.h"
#endif

Plaehngine::Plaehngine(Game* game) {
	Init(game);
	Run();
	Quit();
}

void Plaehngine::Init(Game* game)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Graphics::Init(game);
	Input::Init();
	Audio::Init(game);
	Random::Init();
	game->Init();

#ifdef PLAEHNGINE_EDITOR
	PlaehngineEditor::Init();
#else 
	ApplicationState::Start();
#endif
}

void Plaehngine::Destroy()
{
	Scenes::Quit();
	Graphics::Quit();
	Audio::Quit();
	Input::Quit();
	SDL_Quit();
}

void Plaehngine::Quit() {
	Destroy();
	exit(0);
}

void Plaehngine::Run()
{
	while (true)
	{
		Physics::Run();
		Input::ProcessInput();
		GameTime::Run();
		Scenes::Run();
		Graphics::Run();

#ifdef PLAEHNGINE_EDITOR
		PlaehngineEditor::Run();
#endif

		if (Input::_isQueueingQuit) {
			break;
		}
	}
}