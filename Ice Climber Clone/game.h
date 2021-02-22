#pragma once

#include "renderComponent.h"
#include "playerBehaviourComponent.h"
#include "alien.h"

class Game : public GameObject
{
	bool change_direction = false;

	ObjectPool<class Rocket> rockets_pool;	// used to instantiate rockets
	ObjectPool<class Rocket> bullets_pool;

	ObjectPool<class Alien> aliens;
	class Player* player;

	class Sprite * life_sprite;
	bool game_over = false;

	unsigned int score = 0;

public:

	virtual void Create(class Plaehngine* engine);

	virtual void Init();

	virtual void Update(float dt);

	virtual void Draw();

	virtual void Receive(Message m);

	virtual void Destroy();

protected:

	bool bIsRunning = true;

	virtual void SpawnAliens();
};