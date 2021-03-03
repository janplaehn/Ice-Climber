#include "CameraManager.h"
#include <Camera.h>
#include "ComponentEssentials.h"

void CameraManager::Update()
{
	if (_player->_position.y > (Camera::_position.y + MAX_CAMERA_DISTANCE)) {

		Camera::_position.y += GameTime::_delta * 10;

		if ((Camera::_position.y + MAX_CAMERA_DISTANCE) > _player->_position.y) {
			Camera::_position.y = _player->_position.y - MAX_CAMERA_DISTANCE;
		}
	}
}
