#include "Topi.h"
#include "ComponentEssentials.h"
#include "TopiWalkingState.h"
#include "TopiWalkingDeadState.h"

void Topi::BeginPlay()
{
	InitFSM(_gameObject);
	QueueFSMState(new TopiWalkingState());
}

void Topi::Update()
{
	UpdateFSM();
	return;
}

void Topi::ChangeDirection()
{
	_transform->_flipType = (_transform->_flipType == SDL_FLIP_HORIZONTAL) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

void Topi::Damage()
{
	QueueFSMState(new TopiWalkingDeadState());
	_deathSource->Play();
}
