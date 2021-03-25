#pragma once
#include "Component.h"

class AABBCollider;

class Rigidbody : public Component
{
	friend class Physics;
public:
	Rigidbody();

	Vector2D _velocity = Vector2D::Zero();
	float _gravityScale = 1.0f;
	float _linearDrag = 0.0f;
	bool _isKinematic = false;

private:
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void Destroy() override;

	void ApplyDrag();
	void ApplyGravity();

	Vector2D _previousPosition;
	Vector2D _targetMoveDelta;
	std::shared_ptr<AABBCollider> _collider = nullptr;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Rigidbody, "Rigigdbody")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Rigidbody, Component)