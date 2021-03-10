#pragma once
#include "Button.h"

class IceClimberButton : public Button
{
protected:

	virtual void Awake() override;
	virtual void Update() override;
	virtual void OnPressed() override;
	virtual void OnSelected() override;
	virtual void OnDeselected() override;
	virtual void OnDeactivate() override;
	virtual void OnActivate() override;

	const Color COLOR_SELECTED = Color::White();
	const Color COLOR_DEFAULT = Color(128, 128, 128);
};

