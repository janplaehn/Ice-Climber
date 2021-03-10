#pragma once
#include "Component.h"

class Transform;

class CameraManager :	public Component
{
public:
	void SetPlayerTransform(Transform* player);

private:
	virtual void Update() override;
	Transform* _player = nullptr;

	const float MAX_CAMERA_DISTANCE = 100;
	float _highestPlayerPosition = 0;
};

