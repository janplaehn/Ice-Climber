#pragma once

class State;
class GameObject;

class FiniteStateMachine
{
public:
	void InitFSM(GameObject* gameObject);
	void UpdateFSM();
	void DestroyFSM();
	void QueueFSMState(State* state);

private:
	void EnterNextState();
	State* _currentState;
	GameObject* _fsmGameObject;
	State* _nextState = nullptr;
};

