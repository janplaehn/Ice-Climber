#include "Scenes.h"
#include "SceneSerializer.h"

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
	for (auto go : GameObject::_gameObjects)
	{
		go->Update();
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

		for (auto go : GameObject::_gameObjects) {
			go->BeginPlay();
		}
	}
}
