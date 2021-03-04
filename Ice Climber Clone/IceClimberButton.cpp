#include "IceClimberButton.h"
#include "ComponentEssentials.h"

void IceClimberButton::Awake()
{
	Button::Awake();
	_buttonSound = _gameObject->AddComponent<AudioSource>();
	//_buttonSound->_clip = Audio::LoadSound("blablaSoundbla.bla");
}

void IceClimberButton::Update()
{
}

void IceClimberButton::OnPressed()
{
}

void IceClimberButton::OnSelected()
{
	_buttonSound->Play();
	_text->_tint = _selectedColor;
}

void IceClimberButton::OnDeselected()
{
	_text->_tint = _defaultColor;
}

void IceClimberButton::OnDeactivate()
{
}

void IceClimberButton::OnActivate()
{
}
