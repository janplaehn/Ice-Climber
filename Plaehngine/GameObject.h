#pragma once

#include <vector>
#include "Screen.h"
#include <string>
#include <memory>

class Component;
class Transform;

class GameObject : public std::enable_shared_from_this<GameObject>
{
protected:
	std::vector<Component*> _components;

public:
	GameObject();

	Transform* _transform = nullptr;
	bool _enabled = true;

	std::string _tag = "Default";

	static std::vector<std::shared_ptr<GameObject>> _gameObjects;

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
	void OnCollision(class AABBCollider* otherCollider, struct Vector2D normal);

	int x, y, z;

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(x, y, z, _tag); // serialize things by passing them to the archive
	}
};