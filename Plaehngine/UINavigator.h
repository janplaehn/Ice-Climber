#pragma once
#include "Component.h"
#include "Button.h"

class UINavigator : public Component
{
public:
	virtual void BeginPlay() override;
	virtual void Update() override;

	std::vector<std::shared_ptr<Button>> _buttons;
	int _buttonIndex = 0;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _buttons, _buttonIndex);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(UINavigator, "UINavigator")
CEREAL_REGISTER_POLYMORPHIC_RELATION(UINavigator, Component)