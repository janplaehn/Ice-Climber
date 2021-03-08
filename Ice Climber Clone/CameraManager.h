#pragma once
#include "Component.h"
class CameraManager :	public Component
{
public:

	virtual void Update() override;

	class Transform* _player;

private:
	const float MAX_CAMERA_DISTANCE = 100;
	float _highestPlayerPos = 0;
};

