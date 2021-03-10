#include "IceClimberButton.h"
#include "ComponentEssentials.h"

void IceClimberButton::Awake()
{
	Button::Awake();
}

void IceClimberButton::Update()
{
}

void IceClimberButton::OnPressed()
{
}

void IceClimberButton::OnSelected()
{
	_text->_tint = COLOR_SELECTED;
}

void IceClimberButton::OnDeselected()
{
	_text->_tint = COLOR_DEFAULT;
}

void IceClimberButton::OnDeactivate()
{
}

void IceClimberButton::OnActivate()
{
}
