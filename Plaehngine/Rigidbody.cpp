#include "Rigidbody.h"
#include "Transform.h"
#include "AABBCollider.h"

Rigidbody::Rigidbody(Plaehngine* engine, GameObject* go)
	: Component(engine, go)
{
	_previousPosition = _transform->_position;
	_collider = GetComponent<AABBCollider>();
	Physics::_rigidbodies.push_back(this);
}

bool Rigidbody::IsOnGround() const
{
		return _isOnGround;
}

void Rigidbody::Update(float dt)
{
	_previousPosition = _transform->_position;

	if (_isKinematic) {
		_velocity = Vector2D::Zero();
		_targetMoveDelta = Vector2D::Zero();
		return;
	}

	ApplyDrag(dt);
	ApplyGravity(dt);
	
	_targetMoveDelta = _velocity * dt;
}

void Rigidbody::ApplyDrag(float dt)
{
	float appliedDrag = (1.0f - _linearDrag * dt);
	if (appliedDrag < 0) appliedDrag = 0;
	_velocity = _velocity * appliedDrag;
}

void Rigidbody::ApplyGravity(float dt)
{
	_velocity.y -= GRAVITY * dt * _gravityScale;
}

void Rigidbody::OnCollision(AABBCollider* otherCollider) {
	if (_preventCollisions) {

	}
}

void Rigidbody::Destroy()
{
	Physics::_rigidbodies.erase(std::remove(Physics::_rigidbodies.begin(), Physics::_rigidbodies.end(), this), Physics::_rigidbodies.end());
}
