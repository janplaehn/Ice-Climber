#pragma once
#include "FiniteStateMachine.h"
#include "GameObject.h"

class Transform;

class State
{
	friend class FiniteStateMachine;

public:
	virtual void Enter() = 0;
	virtual void Run() = 0;
	virtual State* GetNextState() = 0;
	virtual void Exit() = 0;

	template <class T>
	T* GetComponent() {
		return _gameObject->GetComponent<T>();
	}

protected:
	GameObject* _gameObject;
	Transform* _transform;
};