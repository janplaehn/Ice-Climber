#pragma once

#include <vector>
#include  "SDL.h"
#include "gameObject.h"

class ObjectPool
{
public:
	~ObjectPool();

	void Add(GameObject* go);

	GameObject* FirstAvailable();

	bool AnyAvailable();

	bool AllAvailable();

private:

	std::vector<GameObject*> _gameObjects;
};