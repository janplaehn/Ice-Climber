#pragma once
#include "Component.h"

class TopiBehaviour : public Component
{
public:
	TopiBehaviour(Plaehngine* engine, GameObject* go);

	virtual void Update(float dt);

	class Animation* _animation;
	GameObject* _ice;

protected:
	const float WALKSPEED = 10;

	enum TopiState
	{
		WALKING,
		FETCHICE,
		WALKWITHICE
	};

	TopiState _state = WALKING;

	virtual void ChangeDirection();

private:
};

