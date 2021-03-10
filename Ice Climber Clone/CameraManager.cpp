#include "CameraManager.h"
#include <Camera.h>
#include "ComponentEssentials.h"

void CameraManager::SetPlayerTransform(Transform* player)
{
	_player = player;
}

void CameraManager::Update()
{
	if (_player->_position.y > _highestPlayerPosition) {
		_highestPlayerPosition = _player->_position.y;
	}

	if (_highestPlayerPosition > (Camera::_position.y + MAX_CAMERA_DISTANCE)) {

		Camera::_position.y += GameTime::_delta * 30;

		if ((Camera::_position.y + MAX_CAMERA_DISTANCE) > _highestPlayerPosition) {
			Camera::_position.y = _highestPlayerPosition - MAX_CAMERA_DISTANCE;
		}
	}
}
