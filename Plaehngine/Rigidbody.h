#pragma once
#include "Component.h"

class Rigidbody : public Component
{
	friend class Physics;
public:
	Rigidbody();

	Vector2D _velocity;
	float _gravityScale = 1.0f;
	float _linearDrag = 0.0f;
	bool _isKinematic = false;
	bool _preventCollisions = true;

	const float GRAVITY = 981.0f;

	virtual void BeginPlay();
	virtual void Update() override;
	virtual void Destroy();

protected:
	void ApplyDrag();
	void ApplyGravity();

private:
	Vector2D _previousPosition;
	Vector2D _targetMoveDelta;
	class AABBCollider* _collider = nullptr;
};

