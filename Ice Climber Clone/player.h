#pragma once

#include "gameObject.h"

// the main player
class Player : public GameObject
{
public:

	int lives;	// it's game over when goes below zero 

	virtual ~Player();

	virtual void Init();

	virtual void Receive(Message m);

	void RemoveLife();
};
