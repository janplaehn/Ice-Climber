#include "IntroCamera.h"
#include "Camera.h"
#include "Scenes.h"
#include "LevelScene.h"

void IntroCamera::Update()
{
	Camera::_position.y += GameTime::_delta * SPEED;
	if (Camera::_position.y > MAX_POSITION_Y) {
		Scenes::LoadScene<LevelScene>();
	}
}
