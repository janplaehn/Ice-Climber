#include "IntroCamera.h"
#include "Camera.h"
#include <Scenes.h>
#include "PlayScene.h"

void IntroCamera::Update()
{
	Camera::_position.y += GameTime::_delta * _speed;
	if (Camera::_position.y > 700) {
		Scenes::LoadScene<PlayScene>();
	}
}
