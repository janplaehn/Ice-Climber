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
};

