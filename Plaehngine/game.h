#pragma once
#include "GameObject.h"

class Game : public GameObject
{
public:

	virtual void Create(class Plaehngine* engine) = 0;

	virtual void Init() = 0;

	virtual void Update(float dt) = 0;

	virtual void Receive(Message m) = 0;

	virtual void Destroy() = 0;

protected:
	bool bIsRunning = true;
};

