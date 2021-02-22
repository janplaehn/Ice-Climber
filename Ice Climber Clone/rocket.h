#pragma once

#include "gameObject.h"

// rockets are shot by the player towards the aliens
class Rocket : public GameObject
{

public:

	virtual void Init(struct Vector2D position);

	virtual void Receive(Message m);
	
};