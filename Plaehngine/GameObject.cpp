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
	_gameObjects.push_back(std::shared_ptr<GameObject>(this));
}

void GameObject::BeginPlay()
{
	for (Component* component : _components) {
		component->BeginPlay();
	}
}

void GameObject::Update()
{
	if (!_enabled)
		return;

	for (Component* component : _components) {
		component->Update();
	}		
}

void GameObject::Destroy()
{
	for (Component* component : _components) {
		component->Destroy();
	}
	_components.clear();
	_gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), std::shared_ptr<GameObject>(shared_from_this())), _gameObjects.end());
}

void GameObject::OnCollision(AABBCollider* otherCollider, Vector2D normal)
{
	for (Component* component : _components)
	{
		component->OnCollision(otherCollider, normal);
	}
}

std::vector<std::shared_ptr<GameObject>> GameObject::_gameObjects;
