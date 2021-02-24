#include "CollideComponent.h"
#include "Transform.h"

void CollideComponent::Update(float dt)
{
	//Todo: Have a collision manager do this instead! And don't do this twice duh

	for (auto i = 0; i < _collisionObjects->pool.size(); i++)
	{
		GameObject* other = _collisionObjects->pool[i];
		if (other->_enabled)
		{
			if ((other->_transform->_position.x > _gameObject->_transform->_position.x - 10) &&
				(other->_transform->_position.x < _gameObject->_transform->_position.x + 10) &&
				(other->_transform->_position.y > _gameObject->_transform->_position.y - 10) &&
				(other->_transform->_position.y < _gameObject->_transform->_position.y + 10))
			{
				_gameObject->Receive(GameObject::HIT);
				other->Receive(GameObject::HIT);
			}
		}
	}
}