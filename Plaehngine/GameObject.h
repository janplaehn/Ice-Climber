#pragma once

#include <vector>
#include "Screen.h"
#include <string>
#include <memory>

class Transform;
class AABBCollider;
class Component;
class Renderer;
class AABBCollider;

class GameObject : public std::enable_shared_from_this<GameObject>
{
protected:
	std::vector<std::shared_ptr<Component>> _components;

public:

	std::shared_ptr<Transform> _transform = nullptr;
	bool _enabled = true;

	std::string _tag = "Default";

	static std::vector<std::shared_ptr<GameObject>> _gameObjects;

	template<class T>
	std::shared_ptr<T>AddComponent()
	{
		std::shared_ptr<T> t = std::make_shared<T>();
		std::shared_ptr<Component> component = t;
		component->_gameObject = shared_from_this();
		component->_transform = _transform;
		_components.push_back(component);
		for (auto existingComponent : _components)
		{
			if (existingComponent != component) {
				existingComponent->OnComponentAdded(component);
			}
		}
		component->Awake();
		return t;
	}

	template <class T>
	std::shared_ptr<T> GetComponent() {
		for (auto component : _components)
		{
			std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(component);
			if (t != nullptr) {
				return t;
			}
		}
		return nullptr;
	}

	template <class T>
	std::vector<std::shared_ptr<T>> GetComponents() {
		std::vector<std::shared_ptr<T>> foundComponents;
		for (auto component : _components)
		{
			std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(component);
			if (t != nullptr) {
				foundComponents.push_back(t);
			}
		}
		return foundComponents;
	}

	static std::shared_ptr<GameObject> Create();

	virtual void BeginPlay();
	virtual void Update();
	virtual void Destroy();
	void OnCollision(std::shared_ptr<AABBCollider> otherCollider, struct Vector2D normal);

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(_tag, _enabled, _transform); // serialize things by passing them to the archive
	}
};
