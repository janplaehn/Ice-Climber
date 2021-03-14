#include "FiniteStateMachine.h"
#include "State.h"
#include "ComponentEssentials.h"
#include "SDL_log.h"

void FiniteStateMachine::InitFSM(GameObject* gameObject)
{
	_fsmGameObject = gameObject;
}

void FiniteStateMachine::UpdateFSM()
{
	if (_fsmGameObject == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Can't run state machine without initializing it first!");
	}
	if (_currentState != nullptr) {
		_currentState->Run();
		State* newState = _currentState->GetNextState();
		QueueFSMState(newState);
	}

	EnterNextState();
	_nextState = nullptr;
}

void FiniteStateMachine::QueueFSMState(State* state)
{
	if (_nextState != nullptr) return;
	if (state == nullptr) return;
	if (state == _currentState) return;
	_nextState = state;
}

void FiniteStateMachine::EnterNextState()
{
	if (_nextState == nullptr) return;
	if (_nextState == _currentState) return;

	if (_currentState != nullptr) {
		_currentState->Exit();
		delete _currentState;
	}
	_currentState = _nextState;
	_currentState->_gameObject = _fsmGameObject;
	_currentState->_transform = _fsmGameObject->_transform;
 	_currentState->Enter();
}

void FiniteStateMachine::DestroyFSM()
{
	if (_currentState != nullptr) {
		delete _currentState;
	}
}
