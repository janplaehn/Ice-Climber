#pragma once
#include "Button.h"

class IceClimberButton : public Button
{
	virtual void Awake();
	virtual void Update() override;
	virtual void OnPressed() override;
	virtual void OnSelected() override;
	virtual void OnDeselected() override;
	virtual void OnDeactivate() override;
	virtual void OnActivate() override;

	Color _selectedColor = Color(128,128,128);
	Color _defaultColor = Color::White();

	class AudioSource* _buttonSound;
};

