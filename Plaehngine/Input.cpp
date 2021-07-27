#include "Input.h"
#include "SDL.h"
#include "Plaehngine.h"
#include "Vector2D.h"
#include <string>

void Input::Init()
{
	WatchKey(SDL_SCANCODE_ESCAPE);
}

void Input::ProcessInput()
{
	_mouseWheelDelta = Vector2D::Zero();

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			_isQueueingQuit = true;
		}

		if (event.type == SDL_MOUSEWHEEL)
		{
			_mouseWheelDelta.x = event.wheel.x;
			_mouseWheelDelta.y = event.wheel.y;
		}
	}

	SDL_PumpEvents();
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < _keys.size(); i++)
	{
		Key& k = _keys[i];
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
	}

	int x, y;
	const Uint32 buttonStates = SDL_GetMouseState(&x, &y);

	_mouseDelta = Vector2D(x, y) - _mousePosition;
	_mousePosition.x = x;
	_mousePosition.y = y;

	for (int i = 0; i < _buttons.size(); i++)
	{
		Key& b = _buttons[i];
		switch (b._status)
		{
		case IDLE:
			if (buttonStates & SDL_BUTTON(b._scanCode)) b._status = PRESSED;
			else b._status = IDLE;
			break;
		case PRESSED:
			if (buttonStates & SDL_BUTTON(b._scanCode)) b._status = HELD;
			else b._status = RELEASED;
			break;
		case HELD:
			if (buttonStates & SDL_BUTTON(b._scanCode)) b._status = HELD;
			else b._status = RELEASED;
			break;
		case RELEASED:
			if (buttonStates & SDL_BUTTON(b._scanCode)) b._status = PRESSED;
			else b._status = IDLE;
			break;
		default:
			break;
		}
	}

	if (GetKeyStatus(SDL_SCANCODE_ESCAPE) == PRESSED) {
		_isQueueingQuit = true;
	}
}

Input::KeyStatus Input::GetKeyStatus(int scanCode)
{
	for (Key k : _keys)
	{
		if (k._scanCode == scanCode) return k._status;
	}
	SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Tried to read input %s, but Scancode has not been specified before!", std::to_string(scanCode).c_str());
	return UNDEFINED;
}

Input::KeyStatus Input::GetButtonStatus(int button)
{

	for (Key k : _buttons)
	{
		if (k._scanCode == button) return k._status;
	}
	SDL_LogError(SDL_LOG_CATEGORY_INPUT, "Tried to read input %s, but Button has not been specified before!", std::to_string(button).c_str());
	return UNDEFINED;
}

void Input::WatchButton(int button)
{
	for (Key k : _buttons)
	{
		if (k._scanCode == button) return;
	}

	Key key;
	key._scanCode = button;
	_buttons.push_back(key);
}

void Input::WatchKey(int scanCode)
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
std::vector<Input::Key> Input::_buttons;
Vector2D Input::_mousePosition;
Vector2D Input::_mouseDelta;
Vector2D Input::_mouseWheelDelta;
bool Input::_isQueueingQuit;
