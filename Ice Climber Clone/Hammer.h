#pragma once
#include "Component.h"

class AABBCollider;
class AudioSource;
class ObjectPool;

class Hammer : public Component
{
public:

	void SetTileBreakAudioSource(std::shared_ptr<AudioSource> source);

	void SetDebrisPool(ObjectPool* pool);

	virtual void Update() override;

	void OnCollision(std::shared_ptr<AABBCollider> other, Vector2D normal) override;

private:

	const float OVERLAP_COOLDOWN = 0.3f;

	std::shared_ptr<GameObject> FindClosestOverlappingTile();

	void BreakTiles();

	void BreakTile(std::shared_ptr<GameObject> tile);

	void SpawnDebris(Vector2D position);

	std::shared_ptr<AudioSource> _tileBreakSource;

	ObjectPool* _debrisPool;

	std::vector< std::shared_ptr<GameObject>> _overlappingTiles;

	float _timer = 0;

public:
	friend class cereal::access;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _tileBreakSource);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Hammer, "Hammer")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Hammer, Component)