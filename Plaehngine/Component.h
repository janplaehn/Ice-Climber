#pragma once

class GameObject;
class Transform;

#include <set>
#include "Vector2D.h"
#include "Color.h"
#include "GameTime.h"
#include "SDL.h"
#include "Input.h"
#include "GameTime.h"
#include <string>
#include <memory>
#include "GameObject.h"
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>

class Component
{
	friend class GameObject;

public:
	std::shared_ptr<GameObject> _gameObject = nullptr;
	std::shared_ptr<Transform> _transform = nullptr;
	bool _enabled = true;

	template <class T>
	std::shared_ptr<T> GetComponent() {
		return _gameObject->GetComponent<T>();
	}

	virtual void Awake() {};
	virtual void BeginPlay() {};
	bool IsActiveAndEnabled();
	virtual void Update() {};
	virtual void Receive(int message) {}
	virtual void OnCollision(std::shared_ptr<AABBCollider> otherCollider, struct Vector2D normal) {};
	virtual void OnComponentAdded(std::shared_ptr<Component> component) {};

	virtual void Destroy() {};

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(_enabled); // serialize things by passing them to the archive
	}

private:
	template<class T>
	static std::shared_ptr<T> Create() {
		std::shared_ptr<T> t = std::make_shared<T>();
		std::shared_ptr<Component> component = t;
		return t;
	}
};