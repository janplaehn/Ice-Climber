#include "Button.h"
#include "ComponentEssentials.h"

Button::Button()
{
}

void Button::Awake()
{
	_text = _gameObject->AddComponent<Text>();
}

void Button::Press()
{
	if (_onPressedFunction != nullptr) {
		_onPressedFunction();
	}
	OnPressed();
}

void Button::Select()
{
	OnSelected();
}

void Button::Deselect()
{
	OnDeselected();
}

void Button::Deactivate()
{
	_isActive = true;
	OnDeactivate();
}

void Button::Activate()
{
	_isActive = false;
	OnActivate();
}
