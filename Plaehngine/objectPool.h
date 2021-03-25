#pragma once

#include <vector>
#include  "SDL.h"
#include "gameObject.h"

class ObjectPool
{
public:
	~ObjectPool();

	void Add(std::shared_ptr<GameObject> go);

	std::shared_ptr<GameObject> FirstAvailable();

	bool AnyAvailable();

	bool AllAvailable();

private:

	std::vector<std::shared_ptr<GameObject>> _gameObjects;
};