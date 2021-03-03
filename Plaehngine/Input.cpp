#include "Input.h"
#include "SDL.h"
#include "Plaehngine.h"

void Input::Init(Plaehngine* engine)
{
	_key._jump = _key._left = _key._right = _key._escape = false;
	_engine = engine;
}

void Input::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			case SDLK_q:
				_key._escape = true;
				break;
			case SDLK_SPACE:
				_key._jump = true;
				break;
			case SDLK_a:
				_key._attack = true;
				break;
			case SDLK_LEFT:
				_key._left = true;
				break;
			case SDLK_RIGHT:
				_key._right = true;
				break;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				_key._jump = false;
				break;
			case SDLK_a:
				_key._attack = false;
				_key._attack = false;
				break;
			case SDLK_LEFT:
				_key._left = false;
				break;
			case SDLK_RIGHT:
				_key._right = false;
				break;
			}
		}
		if (event.type == SDL_QUIT)
		{
			_engine->Quit();
		}

	}

	KeyStatus keys = GetKeyStatus();
	if (keys._escape) {
		_engine->Quit();
	}
}

Input::KeyStatus Input::GetKeyStatus()
{
	return _key;
}

Input::KeyStatus Input::_key;
Plaehngine* Input::_engine;
