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
	_gameObjects.push_back(this);
}

void GameObject::BeginPlay()
{
	for (Component* c : _components) {
		c->BeginPlay();
	}
}

void GameObject::Update()
{
	if (!_enabled)
		return;

	for (Component* c : _components) {
		c->Update();
	}		
}

void GameObject::Destroy()
{
	for (Component* c : _components) {
		c->Destroy();
	}
	_components.clear();
	_gameObjects.erase(std::remove(_gameObjects.begin(), _gameObjects.end(), this), _gameObjects.end());
}

void GameObject::OnCollision(AABBCollider* otherCollider, Vector2D normal)
{
	for (Component* component : _components)
	{
		component->OnCollision(otherCollider, normal);
	}
}


GameObject::~GameObject()
{

}

std::vector<GameObject*> GameObject::_gameObjects;
