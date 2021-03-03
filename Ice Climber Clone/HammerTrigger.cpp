#include "HammerTrigger.h"
#include "ComponentEssentials.h"
#include "Enemy.h"

void HammerTrigger::Update()
{
	_timer -= GameTime::_delta;
	if (_timer > 0) return;

	if (_triggeredTiles.size() == 0) return;

	GameObject* closest = _triggeredTiles[0];
	float currentDistance = abs(closest->_transform->_position.x - _transform->_position.x);
	for (int i = 0; i < _triggeredTiles.size(); i++)
	{
		float distance = abs(_triggeredTiles[i]->_transform->_position.x - _transform->_position.x);
		if (distance < currentDistance) {
			currentDistance = distance;
			closest = _triggeredTiles[i];
		}
	}
	closest->_enabled = false;
	_tileBreakSource->Play();
	_timer = _coolDown;
	_triggeredTiles.clear();
}

void HammerTrigger::OnCollision(AABBCollider* other)
{
	if (other->_gameObject->_tag == "Tile" && _timer <= 0) {
		_triggeredTiles.push_back(other->_gameObject);
	}
	else if (other->_gameObject->_tag == "Topi" && _timer <= 0) {
		Enemy* enemy = other->_gameObject->GetComponent<Enemy>();
		if (enemy != nullptr) {
			enemy->Damage();
		}
	}
}
