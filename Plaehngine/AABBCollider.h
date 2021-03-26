#pragma once
#include "Component.h"

class AABBCollider : public Component
{

public:

	AABBCollider();

	void ApplySpriteSize(class Sprite* sprite);

	void Render();

	SDL_Rect GetRect();

	void SetScale(Vector2D scale);

	Vector2D GetScale();

	void SetOffset(Vector2D offset);

	Vector2D GetOffset();

	void SetTrigger(bool isTrigger);

	bool IsTrigger();

private:

	virtual void Destroy() override;

	Vector2D _scale = Vector2D(10,10);

	Vector2D _offset;

	bool _isTrigger = false;

public:
	friend class cereal::access;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _scale, _offset, _isTrigger);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(AABBCollider, "AABBCollider")
CEREAL_REGISTER_POLYMORPHIC_RELATION(AABBCollider, Component)
