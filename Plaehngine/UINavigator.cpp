#include "UINavigator.h"

void UINavigator::BeginPlay()
{
	if (_buttons.size() > _buttonIndex) {
		_buttons[_buttonIndex]->Select();
	}
}

void UINavigator::Update()
{
	if (_buttons.size() <= 0) {
		return;
	}

	int prevIndex = _buttonIndex;

	if (Input::GetKeyStatus()._left) {
		_buttonIndex--;
	}
	else if (Input::GetKeyStatus()._left) {
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

	if (Input::GetKeyStatus()._jump) {
		_buttons[_buttonIndex]->Press();
	}
}
