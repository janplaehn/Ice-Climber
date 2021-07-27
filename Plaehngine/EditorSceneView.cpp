#include "EditorSceneView.h"
#include "Camera.h"
#include "GameTime.h"
#include "Input.h"
#include "GameMath.h"
#include <algorithm>

void EditorSceneView::Init()
{
	Input::WatchKey(SDL_SCANCODE_W);
	Input::WatchKey(SDL_SCANCODE_A);
	Input::WatchKey(SDL_SCANCODE_S);
	Input::WatchKey(SDL_SCANCODE_D);
	Input::WatchKey(SDL_SCANCODE_0);
	Input::WatchButton(SDL_BUTTON_RIGHT);
}

void EditorSceneView::Run()
{
	if (Input::GetKeyStatus(SDL_SCANCODE_W) == Input::HELD) {
		Camera::_position.y += GameTime::_unscaledDelta * _speed / Camera::_tiling;
	}
	else if (Input::GetKeyStatus(SDL_SCANCODE_S) == Input::HELD) {
		Camera::_position.y -= GameTime::_unscaledDelta * _speed / Camera::_tiling;
	}
	if (Input::GetKeyStatus(SDL_SCANCODE_A) == Input::HELD) {
		Camera::_position.x -= GameTime::_unscaledDelta * _speed / Camera::_tiling;
	}
	else if (Input::GetKeyStatus(SDL_SCANCODE_D) == Input::HELD) {
		Camera::_position.x += GameTime::_unscaledDelta * _speed / Camera::_tiling;
	}
	if (Input::GetKeyStatus(SDL_SCANCODE_0) == Input::HELD) {
		Camera::_position = Vector2D::Zero();
		Camera::_tiling = 1;
	}

	if (Input::GetButtonStatus(SDL_BUTTON_RIGHT) == Input::HELD) {
		Camera::_position.x -= Input::_mouseDelta.x * GameTime::_unscaledDelta * _speed / Camera::_tiling;
		Camera::_position.y += Input::_mouseDelta.y * GameTime::_unscaledDelta * _speed / Camera::_tiling;
		_speed += Input::_mouseWheelDelta.y * GameTime::_unscaledDelta * 20;
	}
	else {
		Camera::_tiling *= 1 + (Input::_mouseWheelDelta.y * GameTime::_unscaledDelta);
	}
}

float EditorSceneView::_speed = 20;
