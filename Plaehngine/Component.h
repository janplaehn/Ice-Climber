#pragma once

class GameObject;
class Transform;

#include <set>
#include "objectPool.h"
#include "Vector2D.h"
#include "Color.h"
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
	GameObject* _gameObject = nullptr;
	Transform* _transform = nullptr;
	bool _enabled = true;

	template <class T>
	T* GetComponent() {
		return _gameObject->GetComponent<T>();
	}

	virtual void Awake() {};
	virtual void BeginPlay() {};
	bool IsActiveAndEnabled();
	virtual void Update() {};
	virtual void Receive(int message) {}
	virtual void OnCollision(class AABBCollider* otherCollider, struct Vector2D normal) {};
	virtual void OnComponentAdded(Component* component) {};

	virtual void Destroy() {}
};

