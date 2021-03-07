#include "Input.h"
#include "SDL.h"
#include "Plaehngine.h"

void Input::Init(Plaehngine* engine)
{
	_engine = engine;

	AddKey(SDL_SCANCODE_ESCAPE);
}

void Input::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			_engine->Quit();
		}

	}

	SDL_PumpEvents();
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < _keys.size(); i++)
	{
		Key k = _keys[i];
		switch (k._status)
		{
		case IDLE:
			if (currentKeyStates[k._scanCode]) k._status = PRESSED;
			else k._status = IDLE;
			break;
		case PRESSED:
			if (currentKeyStates[k._scanCode]) k._status = HELD;
			else k._status = RELEASED;
			break;
		case HELD:
			if (currentKeyStates[k._scanCode]) k._status = HELD;
			else k._status = RELEASED;
			break;
		case RELEASED:
			if (currentKeyStates[k._scanCode]) k._status = PRESSED;
			else k._status = IDLE;
			break;
		default:
			break;
		}
		_keys[i] = k;
	}

	if (GetKeyStatus(SDL_SCANCODE_ESCAPE) == PRESSED) {
		_engine->Quit();
	}
}

Input::KeyStatus Input::GetKeyStatus(int scanCode)
{
	for (Key k : _keys)
	{
		if (k._scanCode == scanCode) return k._status;
	}
	return UNDEFINED;
}

void Input::AddKey(int scanCode)
{
	for (Key k : _keys)
	{
		if (k._scanCode == scanCode) return;
	}

	Key key;
	key._scanCode = scanCode;
	_keys.push_back(key);
}

void Input::Quit()
{
	_keys.clear();
}

std::vector<Input::Key> Input::_keys;
Plaehngine* Input::_engine;
