#pragma once

#include <set>
#include "objectPool.h"

class GameObject;
class Plaehngine;
class Sprite;

class Component
{

	friend class GameObject;
protected:
	Plaehngine* _engine;	// used to access the engine
	GameObject * _gameObject;		// the game object this component is part of

	//Todo: Add more Sandbox features!
	//Todo: Add Transforms!! (Position, Rotation, Scale, Pivot!)

public:
	Component(Plaehngine* engine, GameObject* go);
	virtual ~Component() {}

	virtual void Init() {}
	virtual void Update(float dt) = 0;
	virtual void Receive(int message) {}
	virtual void Destroy() {}
};

