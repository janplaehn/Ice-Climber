#pragma once

#include "renderComponent.h"
#include "playerBehaviourComponent.h"
#include "Game.h"

class IceClimberGame : public Game
{

	class Player* player;

	class Sprite * life_sprite;
	bool game_over = false;

	unsigned int score = 0;

public:

	virtual void Create(class Plaehngine* engine);

	virtual void Init();

	virtual void Update(float dt);


	//Todo: Move to Renderer Class
	virtual void Draw();

	virtual void Receive(Message m);

	virtual void Destroy();
};