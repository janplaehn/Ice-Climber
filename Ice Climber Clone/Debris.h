#pragma once
#include "Component.h"
class Debris : public Component
{
public:
	virtual void Update() override;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Debris, "Debris")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Debris, Component)