#pragma once

#include <vector>
#include  "SDL.h"
#include "gameObject.h"

class ObjectPool
{
public:
	~ObjectPool()
	{
		for (auto it = pool.begin(); it != pool.end(); it++)
			(*it)->Destroy();
	}

	void AddGameObject(GameObject* go) {
		pool.push_back(go);
		go->_enabled = false;
	}

	GameObject* FirstAvailable()
	{
		for (GameObject* go : pool) {
			if (!go->_enabled) {
				go->_enabled = true;
				return go;
			}
		}
		return nullptr;
	}

	bool AnyAvailable() {
		for (auto it = pool.begin(); it != pool.end(); it++)
		{
			if (!(**it)._enabled) return true;
		}
		return false;
	}

	bool AllAvailable() {
		for (auto it = pool.begin(); it != pool.end(); it++)
		{
			if ((**it)._enabled) return false;
		}
		return true;
	}

	// select a random, enabled element in the object pool
	GameObject* SelectRandom()
	{
		int offset = (rand() / (float)RAND_MAX) * pool.size();

		for (int i = 0; i < pool.size(); i++)
		{
			int index = (i + offset) % pool.size();

			if (pool[index]->_enabled)
				return pool[index];
		}

		return NULL;
	}

	std::vector<GameObject*> pool;
};