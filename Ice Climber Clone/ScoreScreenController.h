#pragma once
#include "Component.h"

class ScoreScreenController : public Component
{
private:

	const float INPUT_DELAY = 3;

	virtual void Update() override;

	float _timer = 0;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(ScoreScreenController, "ScoreScreenController")
CEREAL_REGISTER_POLYMORPHIC_RELATION(ScoreScreenController, Component)