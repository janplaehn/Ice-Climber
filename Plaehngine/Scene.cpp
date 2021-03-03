#include "Scene.h"
#include "GameObject.h"

void Scene::Unload()
{
	for (int i = GameObject::_gameObjects.size() - 1; i >= 0; i--)
	{
		if (GameObject::_gameObjects[i] != nullptr) {
			GameObject::_gameObjects[i]->Destroy();
		}
	}
	GameObject::_gameObjects.clear();
	Camera::_position = Vector2D::Zero();
}
