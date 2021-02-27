#include "GameObject.h"
#include "Component.h"
#include "Plaehngine.h"
#include "Transform.h"
#include "AABBCollider.h"
#include <set>

GameObject::GameObject()
{
	_transform = AddComponent<Transform>();

	_enabled = false;

	_gameObjects.push_back(this);

	Init();
}

void GameObject::Init()
{

	for (auto it = _components.begin(); it != _components.end(); it++)
		(*it)->Init();

	_enabled = true;
}

void GameObject::Update(float dt)
{
	if (!_enabled)
		return;

	for (auto it = _components.begin(); it != _components.end(); it++) {
		if ((*it)->_enabled) {
			(*it)->Update(dt);
		}
	}
		
}

void GameObject::Destroy()
{
	for (auto it = _components.begin(); it != _components.end(); it++) {
		if ((*it) != nullptr) {
			(*it)->Destroy();
		}
	}
	_gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), this), _gameObjects.end());
}

void GameObject::OnCollision(AABBCollider* otherCollider)
{
	for (Component* component : _components)
	{
		component->OnCollision(otherCollider);
	}
}


GameObject::~GameObject()
{

}

Plaehngine* GameObject::_engine;
std::vector<GameObject*> GameObject::_gameObjects;
