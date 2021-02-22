#include "player.h"
#include "gameSettings.h"

//Todo: Move everything to components!
void Player::Init()
{
	GameObject::Init();
	lives = GameSettings::NUM_LIVES;
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
