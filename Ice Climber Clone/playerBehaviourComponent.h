#pragma once

#include "component.h";

class PlayerBehaviourComponent : public Component
{

	float time_fire_pressed;	// time from the last time the fire button was pressed

public:
	PlayerBehaviourComponent(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual ~PlayerBehaviourComponent() {}

	virtual void Init();

	virtual void Update(float dt);

	// move the player left or right
	// param move depends on the time, so the player moves always at the same speed on any computer
	void Move(float move);

	// return true if enough time has passed from the previous rocket
	bool CanFire();

	ObjectPool<class Rocket>* rockets_pool;
};
