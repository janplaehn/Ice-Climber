#include "ApplicationState.h"
#include "Scenes.h"

void ApplicationState::Start()
{
	_isRunning = true;
	Scenes::BeginPlay();
}

bool ApplicationState::IsRunning()
{
	return _isRunning;
}

bool ApplicationState::_isRunning = false;
