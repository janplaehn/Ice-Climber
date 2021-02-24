#include "GameTime.h"
#include "SDL.h"

float GameTime::GetElapsedTime()
{
	return SDL_GetTicks() / 1000.f;
}

float GameTime::_timeScale = 1.0f;