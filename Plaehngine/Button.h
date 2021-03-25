#pragma once
#include "Component.h"

class Text;

using ButtonFunction = void(*)();

class Button : public Component
{
public:
	virtual void OnPressed() = 0;
	virtual void OnSelected() = 0;
	virtual void OnDeselected() = 0;
	virtual void OnDeactivate() = 0;
	virtual void OnActivate() = 0;

	virtual void Awake();

	void Press();
	void Select();
	void Deselect();
	void Deactivate();
	void Activate();

	ButtonFunction _onPressedFunction;
	class std::shared_ptr<Text> _text;

private:
	bool _isActive = true;
};

