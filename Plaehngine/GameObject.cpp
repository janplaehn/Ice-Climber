#include "GameObject.h"
#include "Component.h"
#include "Plaehngine.h"
#include "Transform.h"
#include "AABBCollider.h"
#include "GameTime.h"
#include <set>

void GameObject::BeginPlay()
{
	for (auto component : _components) {
		component->BeginPlay();
	}
}

void GameObject::Update()
{
	if (!_enabled)
		return;

	for (auto component : _components) {
		component->Update();
	}		
}

void GameObject::Destroy()
{
	for (auto component : _components) {
		component->Destroy();
	}
	_components.clear();
	_gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), std::shared_ptr<GameObject>(shared_from_this())), _gameObjects.end());
}

void GameObject::OnCollision(std::shared_ptr<AABBCollider> otherCollider, Vector2D normal)
{
	for (auto component : _components)
	{
		component->OnCollision(otherCollider, normal);
	}
}

std::shared_ptr<GameObject> GameObject::Create() {
	{
		std::shared_ptr<GameObject> newGo = std::make_shared<GameObject>();
		newGo->_transform = newGo->AddComponent<Transform>();
		_gameObjects.push_back(newGo);
		return newGo;
	}
}

std::vector<std::shared_ptr<GameObject>> GameObject::_gameObjects;
