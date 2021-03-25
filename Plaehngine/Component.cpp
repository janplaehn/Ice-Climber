#include "component.h"
#include "GameObject.h"

bool Component::IsActiveAndEnabled()
{
	return (_enabled && _gameObject->_enabled);
}
