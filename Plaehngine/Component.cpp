#include "component.h"

//Todo: Add AnimationComponent

Component::Component()
{
}

bool Component::IsActiveAndEnabled()
{
	return (_enabled && _gameObject->_enabled);
}
