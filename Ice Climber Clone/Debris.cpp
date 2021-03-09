#include "Debris.h"
#include "ComponentEssentials.h"
#include <Camera.h>

void Debris::Update()
{
	if (!IsActiveAndEnabled()) return;
	if (_transform->_position.y < Camera::_position.y) {
		GetComponent<Rigidbody>()->_velocity = Vector2D::Zero();
		_gameObject->_enabled = false;
	}
}
