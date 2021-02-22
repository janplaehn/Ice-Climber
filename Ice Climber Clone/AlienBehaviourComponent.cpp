#include "AlienBehaviourComponent.h"
#include "gameObject.h"
#include "alien.h"
#include "rocket.h"
#include "Random.h"
#include "Screen.h"
#include "Vector2D.h"
#include "Transform.h"

void AlienBehaviourComponent::Update(float dt)
{
	Move(dt);
	ShootIfTimeToShoot(dt);
}

void AlienBehaviourComponent::Init()
{
	bMoveRight = true;
}

void AlienBehaviourComponent::Create(ObjectPool<Rocket>* bulletsPool)
{
	bullets_pool = bulletsPool;
	ComputeNewShootInterval();
}

void AlienBehaviourComponent::Move(float dt)
{
	float moveAmount = MOVESPEED * dt * Direction();
	Move(moveAmount, 0);
	if (ShouldChangeDirection()) {
		_gameObject->Send(GameObject::ALIEN_CHANGEDIR);
	}
}

void AlienBehaviourComponent::Move(float moveX, float moveY)
{
	_gameObject->_transform->_position.x += moveX;
	_gameObject->_transform->_position.y += moveY;
}

bool AlienBehaviourComponent::ShouldChangeDirection() {

	bool bTooFarRight = bMoveRight && _gameObject->_transform->_position.x > (float)(Screen::WIDTH - 32);
	bool bTooFarLeft = !bMoveRight && _gameObject->_transform->_position.x < 0;
	return (bTooFarLeft || bTooFarRight);
}

void AlienBehaviourComponent::ChangeDirection()
{
	_gameObject->_transform->_position.x = _gameObject->_transform->_position.x > (float)(Screen::WIDTH - Alien::WIDTH) ? (float)(Screen::WIDTH - Alien::WIDTH) : _gameObject->_transform->_position.x;
	_gameObject->_transform->_position.x = _gameObject->_transform->_position.x < 0 ? 0 : _gameObject->_transform->_position.x;
	bMoveRight = !bMoveRight;
}

int AlienBehaviourComponent::Direction()
{
	return bMoveRight ?  1 : -1;
}

void AlienBehaviourComponent::ShootIfTimeToShoot(float dt)
{
	_timeSinceLastShot += dt;
	if (_timeSinceLastShot > _currentShootInterval) {
		ComputeNewShootInterval();
		Shoot();
	}
}

void AlienBehaviourComponent::Shoot()
{
	Rocket* bullet = bullets_pool->FirstAvailable();
	if (bullet != nullptr)
	{
		bullet->Init(Vector2D(_gameObject->_transform->_position.x, _gameObject->_transform->_position.y));
		GameObject::_gameObjects.insert(bullet);
	}
}

void AlienBehaviourComponent::ComputeNewShootInterval()
{
	_timeSinceLastShot = 0;
	_currentShootInterval = Random::Range(_minShootInterval, _maxShootInterval);
}

void AlienBehaviourComponent::CheckGameOver()
{

	if (_gameObject->_transform->_position.y > (float)(Screen::HEIGHT - 32 - Alien::WIDTH)) {
		_gameObject->Send(GameObject::GAME_OVER);
	}
}