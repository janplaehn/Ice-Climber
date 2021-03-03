#pragma once
#include "Component.h"

class Cloud : public Component
{
public:

	bool _moveRight = true;


	virtual void Update() override;


private:
	const float SPEED = 20;
};

