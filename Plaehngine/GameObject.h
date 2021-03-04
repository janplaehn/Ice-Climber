#pragma once

// GameObject represents objects which moves are drawn
#include <vector>
#include "Screen.h"
#include <string>

class Component;
class Transform;

class GameObject
{
protected:
	std::vector<GameObject*> _receivers;
	std::vector<Component*> _components;

public:
	GameObject();

	Transform* _transform = nullptr;
	bool _enabled = true;

	std::string _tag = "Default";

	static std::vector<GameObject*> _gameObjects;	// http://www.cplusplus.com/reference/set/set/

	virtual ~GameObject();

	template <class T>
	T* AddComponent() {
		Component* component = new T();
		component->_gameObject = this;
		component->_transform = _transform;
		_components.push_back(component);
		for (Component* existingComponent : _components)
		{
			if (existingComponent != component) {
				existingComponent->OnComponentAdded(component);
			}
		}
		component->Awake();
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

	virtual void BeginPlay();
	virtual void Update();
	virtual void Destroy();
	void OnCollision(class AABBCollider* otherCollider);
};