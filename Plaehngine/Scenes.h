#pragma once
#include "Scene.h"

class Scenes
{
public:

	template <class T>
	static void LoadScene() {
		_sceneToLoad = new T();
	}

	template <class T>
	static std::vector<std::shared_ptr<T>> FindComponents() {
		std::vector<std::shared_ptr<T>> foundComponents;
		for (auto go : GameObject::_gameObjects)
		{
			std::vector<std::shared_ptr<T>> components = go->GetComponents<T>();
			for (auto c : components)
			{
				foundComponents.push_back(c);
			}
		}
		return foundComponents;
	}

	template <class T>
	static std::vector<std::shared_ptr<T>> FindComponent() {
		for (auto go : GameObject::_gameObjects)
		{
			std::shared_ptr<T> component = go->GetComponent<T>();
			if (component != nullptr) return component;
		}
		return nullptr;
	}

	static void Quit();

	static void Run();

private:
	static Scene* _currentScene;
	static Scene* _sceneToLoad;
};

