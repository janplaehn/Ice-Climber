#include "ObjectPool.h"

ObjectPool::~ObjectPool()
{
	for (std::shared_ptr<GameObject> go : _gameObjects) {
		go->Destroy();
	}
}

void ObjectPool::Add(std::shared_ptr<GameObject> go)
{
	_gameObjects.push_back(go);
	go->_enabled = false;
}

std::shared_ptr<GameObject> ObjectPool::FirstAvailable() {
	for (std::shared_ptr<GameObject> go : _gameObjects) {
		if (!go->_enabled) {
			go->_enabled = true;
			return go;
		}
	}
	return nullptr;
}

bool ObjectPool::AnyAvailable()
{
	for (std::shared_ptr<GameObject> go : _gameObjects)
	{
		if (!go->_enabled) return true;
	}
	return false;
}

bool ObjectPool::AllAvailable()
{
	for (std::shared_ptr<GameObject> go : _gameObjects)
	{
		if (go->_enabled) return false;
	}
	return true;
}
