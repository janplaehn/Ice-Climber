#include "Hammer.h"
#include "ComponentEssentials.h"
#include "Enemy.h"
#include "Scores.h"

void Hammer::Update()
{
	_timer -= GameTime::_delta;
	if (_timer > 0) return;

	BreakTiles();
}

void Hammer::BreakTiles()
{
	if (_overlappingTiles.size() == 0) return;

	GameObject* closest = FindClosestOverlappingTile();
	BreakTile(closest);
}

void Hammer::BreakTile(GameObject* tile)
{
	tile->_enabled = false;
	_tileBreakSource->Play();
	_timer = OVERLAP_COOLDOWN;
	_overlappingTiles.clear();
	Scores::_tiles++;
	SpawnDebris(tile->_transform->_position);
}

GameObject* Hammer::FindClosestOverlappingTile()
{
	if (_overlappingTiles.size() == 0) return nullptr;

	GameObject* closest = _overlappingTiles[0];
	float currentDistance = abs(closest->_transform->_position.x - _transform->_position.x);
	for (int i = 0; i < _overlappingTiles.size(); i++)
	{
		float distance = abs(_overlappingTiles[i]->_transform->_position.x - _transform->_position.x);
		if (distance < currentDistance) {
			currentDistance = distance;
			closest = _overlappingTiles[i];
		}
	}
	return closest;
}

void Hammer::SpawnDebris(Vector2D position)
{
	if (_debrisPool->AnyAvailable()) {
		GameObject* debris = _debrisPool->FirstAvailable();
		debris->_transform->_position = position;

		if (position.x > _transform->_position.x) {
			debris->GetComponent<Rigidbody>()->_velocity = Vector2D(50, 250);
		}
		else {
			debris->GetComponent<Rigidbody>()->_velocity = Vector2D(-50, 250);
		}
	}
}

void Hammer::OnCollision(AABBCollider* other, Vector2D normal)
{
	if (_timer > 0) return;

	if (other->_gameObject->_tag == "Tile") {
		_overlappingTiles.push_back(other->_gameObject);
	}
	else if (other->_gameObject->_tag == "Enemy") {
		Enemy* enemy = other->_gameObject->GetComponent<Enemy>();
		if (enemy != nullptr) {
			enemy->Damage();
		}
	}
}

void Hammer::SetTileBreakAudioSource(AudioSource* source)
{
	_tileBreakSource = source;
}

void Hammer::SetDebrisPool(ObjectPool* pool)
{
	_debrisPool = pool;
}