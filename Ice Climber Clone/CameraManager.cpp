#include "CameraManager.h"
#include <Camera.h>
#include "ComponentEssentials.h"

void CameraManager::Update()
{
	if (_player->_position.y > _highestPlayerPos) {
		_highestPlayerPos = _player->_position.y;
	}

	if (_highestPlayerPos > (Camera::_position.y + MAX_CAMERA_DISTANCE)) {

		Camera::_position.y += GameTime::_delta * 30;

		if ((Camera::_position.y + MAX_CAMERA_DISTANCE) > _highestPlayerPos) {
			Camera::_position.y = _highestPlayerPos - MAX_CAMERA_DISTANCE;
		}
	}
}
