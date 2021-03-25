#pragma once
#include "Component.h"

class IntroCamera : public Component
{
public:

	virtual void Update() override;
private:
	const float SPEED = 95;
	const float MAX_POSITION_Y = 700;


public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(IntroCamera, "IntroCamera")
CEREAL_REGISTER_POLYMORPHIC_RELATION(IntroCamera, Component)