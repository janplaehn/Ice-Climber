#include "Scenes.h"
#include "SceneSerializer.h"
#include "GameTime.h"
#include "ApplicationState.h"

Scene* Scenes::_currentScene;
Scene* Scenes::_sceneToLoad;

void Scenes::Quit()
{
	if (_currentScene) {
		_currentScene->Unload();
	}
}

void Scenes::Run()
{
	if (ApplicationState::IsRunning()) {
		for (auto go : GameObject::_gameObjects)
		{
			go->Update();
		}
	}

	if (_sceneToLoad != nullptr) {
		if (_currentScene) {
			_currentScene->Unload();
			delete _currentScene;
		}
		_sceneToLoad->Load();
		Renderer::SortRenderers();
		_currentScene = _sceneToLoad;
		_sceneToLoad = nullptr;

		if (ApplicationState::IsRunning()) {
			BeginPlay();
		}
	}
}

void Scenes::BeginPlay()
{
	Camera::_position = Vector2D::Zero();
	Camera::_tiling = 1.0f;
	for (auto go : GameObject::_gameObjects) {
		go->BeginPlay();
	}
}
