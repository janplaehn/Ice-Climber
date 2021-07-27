#pragma once
#include "Scene.h"

class Scenes
{
public:

	template <class T>
	static void LoadScene() {
		_sceneToLoad = new T();
	}

	static void Quit();
	static void Run();
	static void BeginPlay();

private:
	static Scene* _currentScene;
	static Scene* _sceneToLoad;
};

