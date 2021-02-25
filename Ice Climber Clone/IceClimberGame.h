#pragma once
#include "Game.h"

class IceClimberGame : public Game
{

	GameObject* player;
	GameObject* _background;

	bool game_over = false;

	unsigned int score = 0;

public:

	virtual void Create(class Plaehngine* engine);

	virtual void Init();

	virtual void Update(float dt);

	virtual void Receive(Message m);

	virtual void Destroy();
};