#include "UINavigator.h"

void UINavigator::BeginPlay()
{
	if (_buttons.size() > _buttonIndex) {
		_buttons[_buttonIndex]->Select();
	}

	Input::AddKey(SDL_SCANCODE_LEFT);
	Input::AddKey(SDL_SCANCODE_RIGHT);
	Input::AddKey(SDL_SCANCODE_UP);
	Input::AddKey(SDL_SCANCODE_DOWN);
	Input::AddKey(SDL_SCANCODE_SPACE);
	Input::AddKey(SDL_SCANCODE_ESCAPE);
}

void UINavigator::Update()
{
	if (_buttons.size() <= 0) {
		return;
	}

	int prevIndex = _buttonIndex;

	if (Input::GetKeyStatus(SDL_SCANCODE_LEFT) == Input::PRESSED || Input::GetKeyStatus(SDL_SCANCODE_UP) == Input::PRESSED) {
		_buttonIndex--;
	}
	else if (Input::GetKeyStatus(SDL_SCANCODE_RIGHT) == Input::PRESSED || Input::GetKeyStatus(SDL_SCANCODE_DOWN) == Input::PRESSED) {
		_buttonIndex++;
	}

	if (_buttonIndex < 0) {
		_buttonIndex = _buttons.size() - 1;
	}
	if (_buttonIndex >= _buttons.size()) {
		_buttonIndex = 0;
	}

	if (prevIndex != _buttonIndex) {
		_buttons[prevIndex]->Deselect();
		_buttons[_buttonIndex]->Select();
	}

	if (Input::GetKeyStatus(SDL_SCANCODE_SPACE) == Input::PRESSED) {
		_buttons[_buttonIndex]->Press();
	}
}
