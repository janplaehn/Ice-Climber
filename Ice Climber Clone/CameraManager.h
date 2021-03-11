#pragma once
#include "Component.h"

class Transform;

class CameraManager :	public Component
{
public:

	void SetPlayerTransform(Transform* player);

private:

	const float MAX_CAMERA_DISTANCE = 100;

	virtual void Update() override;

	Transform* _player = nullptr;

	float _highestPlayerPosition = 0;
};

