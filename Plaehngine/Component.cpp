#include "component.h"

bool Component::IsActiveAndEnabled()
{
	return (_enabled && _gameObject->_enabled);
}
