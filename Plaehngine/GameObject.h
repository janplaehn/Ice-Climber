#pragma once

// GameObject represents objects which moves are drawn
#include <vector>
#include <set>
class Component;
class Transform;

class GameObject
{
protected:
	std::vector<GameObject*> _receivers;
	std::vector<Component*> _components;

public:
	enum Message { HIT, ALIEN_HIT, ALIEN_CHANGEDIR, GAME_OVER, LEVEL_WIN, NO_MSG, QUIT };

	Transform* _transform = nullptr;
	bool _enabled;
	bool _isInWorld;

	static class Plaehngine* _engine;
	static std::set<GameObject*> _gameObjects;	// http://www.cplusplus.com/reference/set/set/

	virtual ~GameObject();

	virtual void Create(bool placeInWorld);

	template <class T>
	T* AddComponent() {
		Component* component = new T(_engine, this);
		_components.push_back(component);
		return dynamic_cast<T*>(component);
	}

	template <class T>
	T* GetComponent() {
		for (Component* component : _components)
		{
			T* t = dynamic_cast<T*>(component);
			if (t != nullptr) {
				return t;
			}
		}
		return nullptr;
	}

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	void Send(Message m);
};