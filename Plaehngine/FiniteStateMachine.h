#pragma once
#include <memory>

class State;
class GameObject;

class FiniteStateMachine
{
public:
	void InitFSM(std::shared_ptr<GameObject> gameObject);
	void UpdateFSM();
	void DestroyFSM();
	void QueueFSMState(State* state);

private:
	void EnterNextState();
	State* _currentState;
	std::shared_ptr<GameObject> _fsmGameObject;
	State* _nextState = nullptr;
};

