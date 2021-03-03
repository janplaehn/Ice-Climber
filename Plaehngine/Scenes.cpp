#include "Scenes.h"

Scene* Scenes::_currentScene;
Scene* Scenes::_sceneToLoad;

void Scenes::Update()
{
	if (_sceneToLoad != nullptr) {
		if (_currentScene) {
			_currentScene->Unload();
			delete _currentScene;
		}
		_sceneToLoad->Load();
		SpriteRenderer::SortRenderers();
		_currentScene = _sceneToLoad;
		_sceneToLoad = nullptr;
	}
}
