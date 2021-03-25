#pragma once
#include "Component.h"

class Transform;

class LevelCamera :	public Component
{
public:

	void SetPlayerTransform(std::shared_ptr<Transform> player);

	virtual void Update() override;

private:

	const float MAX_CAMERA_DISTANCE = 100;

	std::shared_ptr<Transform> _player = nullptr;

	float _highestPlayerPosition = 0;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _player);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(LevelCamera, "LevelCamera")
CEREAL_REGISTER_POLYMORPHIC_RELATION(LevelCamera, Component)