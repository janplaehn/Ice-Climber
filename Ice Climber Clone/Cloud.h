#pragma once
#include "Component.h"

class Cloud : public Component
{
public:

	void SetMoveRight(bool moveRight);
	void SetSpeed(float speed);

	virtual void Update() override;

private:

	bool _moveRight = true;
	float _speed = 20;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _moveRight, _speed);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Cloud, "Cloud")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Cloud, Component)