#pragma once
#include "Scene.h"

class Scenes
{
public:

	template <class T>
	static void LoadScene() {
		_sceneToLoad = new T();
	}
	static void UnloadAll() {
		if (_currentScene) {
			_currentScene->Unload();
		}
	}

	static void Update();

private:
	static Scene* _currentScene;
	static Scene* _sceneToLoad;
};

