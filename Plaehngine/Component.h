#pragma once

class GameObject;
class Transform;

#include <set>
#include "objectPool.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Plaehngine.h"
#include "GameTime.h"
#include "SDL.h"
#include "Input.h"
#include "GameTime.h"
#include <string>

class Component
{
	friend class GameObject;

public:
	GameObject* _gameObject;
	Transform* _transform;
	bool _enabled = true;

	Component();
	virtual ~Component() {}

	template <class T>
	T* GetComponent() {
		return _gameObject->GetComponent<T>();
	}

	virtual void BeginPlay() {};
	virtual void Update() = 0;
	virtual void Receive(int message) {}
	virtual void OnCollision(class AABBCollider* otherCollider) {};
	virtual void OnComponentAdded(Component* component) {};

	virtual void Destroy() {}
};

