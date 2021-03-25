#pragma once
#include "FiniteStateMachine.h"
#include "GameObject.h"
#include <memory>

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
	std::shared_ptr<T> GetComponent() {
		return _gameObject->GetComponent<T>();
	}

protected:
	std::shared_ptr<GameObject> _gameObject;
	std::shared_ptr<Transform> _transform;
};