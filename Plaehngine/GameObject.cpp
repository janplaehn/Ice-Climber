#include "gameObject.h"
#include "component.h"
#include "Plaehngine.h"
#include "Transform.h"
#include <set>

void GameObject::Create(bool placeInWorld)
{

	_isInWorld = placeInWorld;

	if (_isInWorld) {
		_transform = AddComponent<Transform>();
	}

	_enabled = false;
	_gameObjects.insert(this);
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

Plaehngine* GameObject::_engine;
std::set<GameObject*> GameObject::_gameObjects;
