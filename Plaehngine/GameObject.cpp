#include "GameObject.h"
#include "Component.h"
#include "Plaehngine.h"
#include "Transform.h"
#include "AABBCollider.h"
#include "GameTime.h"
#include <set>

GameObject::GameObject()
{
	_transform = AddComponent<Transform>();

	_enabled = false;

	_gameObjects.push_back(this);

	BeginPlay();
}

void GameObject::BeginPlay()
{

	for (auto it = _components.begin(); it != _components.end(); it++)
		(*it)->Init();

	_enabled = true;
}

void GameObject::Update()
{
	if (!_enabled)
		return;

	for (auto it = _components.begin(); it != _components.end(); it++) {
		if ((*it)->_enabled) {
			(*it)->Update();
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
	_components.clear();
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
