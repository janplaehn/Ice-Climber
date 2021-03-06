#pragma once
#include "Component.h"
#include "Button.h"

class UINavigator : public Component
{
public:
	virtual void BeginPlay() override;
	virtual void Update() override;

	std::vector<Button*> _buttons;
	int _buttonIndex = 0;
};

