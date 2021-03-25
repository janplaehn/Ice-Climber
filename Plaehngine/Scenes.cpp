#include "Scenes.h"
#include "SceneSerializer.h"
#include <memory>
#include "Physics.h"

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

			Renderer::_renderers.clear();
			Physics::_colliders.clear();
			Physics::_rigidbodies.clear();

			delete _currentScene;
		}
		_sceneToLoad->Load();
		Renderer::SortRenderers();
		_currentScene = _sceneToLoad;
		_sceneToLoad = nullptr;

		for (auto go : GameObject::_gameObjects) {
			go->BeginPlay();
		}

		for (auto renderer : Scenes::FindComponents<Renderer>()) {
			Renderer::_renderers.push_back(renderer);
		}
		for (auto collider : Scenes::FindComponents<AABBCollider>()) {
			Physics::_colliders.push_back(collider);
		}
		for (auto rb : Scenes::FindComponents<Rigidbody>()) {
			Physics::_rigidbodies.push_back(rb);
		}

		SceneSerializer::Deserialize("test.txt");
	}
}
