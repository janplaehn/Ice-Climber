#pragma once
#include "Component.h"

class GameOverUI : public Component
{
public:
	virtual void Update() override;
private:

	const float SPEED = 75;
	const int MAX_POSITION_Y = Screen::_height - 56;

public:
	friend class cereal::access;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(GameOverUI, "GameOverUI")
CEREAL_REGISTER_POLYMORPHIC_RELATION(GameOverUI, Component)