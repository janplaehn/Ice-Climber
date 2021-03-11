#pragma once
#include "Component.h"

class Cloud : public Component
{
public:

	void SetMoveRight(bool moveRight);
	void SetSpeed(float speed);

private:

	virtual void Update() override;

	bool _moveRight = true;
	float _speed = 20;
};

