#pragma once

// GameObject represents objects which moves are drawn
#include <vector>
#include "Screen.h"

class Component;
class Transform;

class GameObject
{
protected:
	std::vector<GameObject*> _receivers;
	std::vector<Component*> _components;

public:
	GameObject(bool placeInWorld = true);

	Transform* _transform = nullptr;
	bool _enabled;
	bool _isInWorld;

	static class Plaehngine* _engine;
	static std::vector<GameObject*> _gameObjects;	// http://www.cplusplus.com/reference/set/set/

	virtual ~GameObject();

	template <class T>
	T* AddComponent() {
		Component* component = new T(_engine, this);
		_components.push_back(component);
		return dynamic_cast<T*>(component);
	}

	template <class T>
	T* GetComponent() {
		for (Component* component : _components)
		{
			T* t = dynamic_cast<T*>(component);
			if (t != nullptr) {
				return t;
			}
		}
		return nullptr;
	}

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	void OnCollision(class AABBCollider* otherCollider);
};