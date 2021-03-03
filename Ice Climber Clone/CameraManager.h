#pragma once
#include "Component.h"
class CameraManager :	public Component
{
public:
	CameraManager(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Update(float dt) override;

	class Transform* _player;

private:
	const float MAX_CAMERA_DISTANCE = 100;
};

