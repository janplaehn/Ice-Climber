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

public:
	friend class cereal::access;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _text, _isActive);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Button, "Button")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Button, Component)