#pragma once

#include "gameObject.h"

class Alien : public GameObject {

public:

	virtual ~Alien();

	virtual void Init();

	virtual void Receive(Message m);

	static const int WIDTH = 32;


protected:
	class AlienBehaviourComponent* alienBehaviourComponent;
};