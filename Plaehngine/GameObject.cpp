#include "GameObject.h"
#include "Component.h"
#include "Plaehngine.h"
#include "Transform.h"
#include "AABBCollider.h"
#include <set>

GameObject::GameObject(bool placeInWorld)
{
	_isInWorld = placeInWorld;

	if (_isInWorld) {
		_transform = AddComponent<Transform>();
	}

	_enabled = false;

	_gameObjects.push_back(this);
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

	for (auto it = _components.begin(); it != _components.end(); it++)
		(*it)->Update(dt);
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

GameObject::~GameObject()
{

}

void GameObject::AddReceiver(GameObject* go)
{
	_receivers.push_back(go);
}

void GameObject::Send(Message m)
{
	for (auto i = 0; i < _receivers.size(); i++)
	{
		if (!_receivers[i]->_enabled)
			continue;

		_receivers[i]->Receive(m);
	}
}

void GameObject::Receive(Message m) {
	switch (m)
	{
	case GameObject::HIT:
		SDL_Log("HIT RECEIVED!");
		break;
	case GameObject::GAME_OVER:
		break;
	case GameObject::LEVEL_WIN:
		break;
	case GameObject::NO_MSG:
		break;
	case GameObject::QUIT:
		break;
	default:
		break;
	}
}

void GameObject::OnCollision(AABBCollider* otherCollider)
{
	for (Component* component : _components)
	{
		component->OnCollision(otherCollider);
	}
}

Plaehngine* GameObject::_engine;
std::vector<GameObject*> GameObject::_gameObjects;
