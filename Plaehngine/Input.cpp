#include "Input.h"
#include "SDL.h"

void Input::Init()
{
	_key._fire = _key._left = _key._right = _key._escape = false;
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
				_key._fire = true;
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
				_key._fire = false;
				break;
			case SDLK_LEFT:
				_key._left = false;
				break;
			case SDLK_RIGHT:
				_key._right = false;
				break;
			}
		}

	}
}

Input::KeyStatus Input::GetKeyStatus()
{
	return _key;
}

Input::KeyStatus Input::_key;
