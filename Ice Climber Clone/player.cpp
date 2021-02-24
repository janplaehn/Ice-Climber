#include "player.h"

//Todo: Move everything to components!
void Player::Init()
{
	GameObject::Init();
	lives = 3;
}

void Player::Receive(Message m)
{
	if (m == HIT)
	{
		RemoveLife();

		if (lives < 0) {
			Send(GAME_OVER);
			_enabled = false;
		}
	}
}

void Player::RemoveLife()
{
	lives--;
}

Player::~Player()
{
}
