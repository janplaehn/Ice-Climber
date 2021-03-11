#pragma once
#include "Component.h"

class AABBCollider;
class AudioSource;
class ObjectPool;

class HammerTrigger : public Component
{
public:

	void SetTileBreakAudioSource(AudioSource* source);

	void SetDebrisPool(ObjectPool* pool);

private:

	const float OVERLAP_COOLDOWN = 0.3f;

	virtual void Update() override;

	void OnCollision(AABBCollider* other, Vector2D normal) override;

	GameObject* FindClosestOverlappingTile();

	void BreakTiles();

	void BreakTile(GameObject* tile);

	void SpawnDebris(Vector2D position);

	AudioSource* _tileBreakSource;

	ObjectPool* _debrisPool;

	std::vector<GameObject*> _overlappingTiles;

	float _timer = 0;
};

