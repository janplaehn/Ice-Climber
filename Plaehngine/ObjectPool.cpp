#include "ObjectPool.h"

ObjectPool::~ObjectPool()
{
	for (GameObject* go : _gameObjects) {
		go->Destroy();
	}
}

void ObjectPool::Add(GameObject* go)
{
	_gameObjects.push_back(go);
	go->_enabled = false;
}

GameObject* ObjectPool::FirstAvailable() {
	for (GameObject* go : _gameObjects) {
		if (!go->_enabled) {
			go->_enabled = true;
			return go;
		}
	}
	return nullptr;
}

bool ObjectPool::AnyAvailable()
{
	for (GameObject* go : _gameObjects)
	{
		if (!go->_enabled) return true;
	}
	return false;
}

bool ObjectPool::AllAvailable()
{
	for (GameObject* go : _gameObjects)
	{
		if (go->_enabled) return false;
	}
	return true;
}
