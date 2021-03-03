#include "GameTime.h"
#include "SDL.h"

void GameTime::Init()
{
	_lastTime = GetElapsedTime();
}

float GameTime::GetElapsedTime()
{
	return SDL_GetTicks() / 1000.f;
}

void GameTime::Run()
{
	float newTime = GameTime::GetElapsedTime();
	_delta = newTime - _lastTime;
	_delta = _delta * _scale;
	_lastTime = newTime;
	

	if (_delta < (1.0f / 60.0f)) {
		int delay = (int)((1.0f / 60.0f - _delta) * 1000.0f);
		SDL_Delay(delay);
	}
}

float GameTime::_scale = 1.0f;
float GameTime::_lastTime = 0;
float GameTime::_delta = 0;