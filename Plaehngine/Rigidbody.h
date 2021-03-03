#pragma once
#include "Component.h"

class Rigidbody : public Component
{
	friend class Physics;
public:
	Rigidbody(Plaehngine* engine, GameObject* go);

	Vector2D _velocity;
	float _gravityScale = 1.0f;
	float _linearDrag = 1.0f;
	bool _isKinematic = false;
	bool _preventCollisions = true;

	bool IsOnGround() const;

	const float GRAVITY = 981.0f;

	virtual void Update() override;
	virtual void OnCollision(class AABBCollider* otherCollider);
	virtual void Destroy();

protected:
	void ApplyDrag();
	void ApplyGravity();

private:
	Vector2D _previousPosition;
	Vector2D _targetMoveDelta;
	bool _isOnGround;
	class AABBCollider* _collider;
};

