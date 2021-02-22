#include "alien.h"
#include "AlienBehaviourComponent.h"

Alien::~Alien()
{
}

void Alien::Init()
{
	GameObject::Init();
	alienBehaviourComponent = GetComponent<AlienBehaviourComponent>();
	alienBehaviourComponent->Init();
}

void Alien::Receive(Message m)
{
	if (!_enabled)
		return;

	if (m == HIT)
	{
		_enabled = false;
		Send(ALIEN_HIT);
	}
	else if (m == ALIEN_CHANGEDIR) {
		alienBehaviourComponent->ChangeDirection();
		alienBehaviourComponent->Move(0, 32);
	}
	else if (m == GAME_OVER) {
		_enabled = false;
	}
}
