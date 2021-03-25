#pragma once
#include "Component.h"

class Enemy : public Component
{
public:

    virtual void Damage() = 0;

protected:

    bool _isDead = false;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _isDead);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Enemy, "Enemy")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Enemy, Component)