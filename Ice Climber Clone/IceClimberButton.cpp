#include "IceClimberButton.h"
#include "ComponentEssentials.h"

void IceClimberButton::Awake()
{
	Button::Awake();
}

void IceClimberButton::BeginPlay()
{
	_source = GetComponent<AudioSource>();
}

void IceClimberButton::Update()
{
}

void IceClimberButton::OnPressed()
{
	if (_source != nullptr) {
		_source->Play();
	}
}

void IceClimberButton::OnSelected()
{
	_text->_tint = COLOR_SELECTED;
	if (_source != nullptr) {
		_source->Play();
	}
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
