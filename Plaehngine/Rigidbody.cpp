#include "Rigidbody.h"
#include "Transform.h"
#include "AABBCollider.h"

Rigidbody::Rigidbody()
{
	Physics::_rigidbodies.push_back(this);
}

void Rigidbody::BeginPlay()
{
	_previousPosition = _transform->_position;
	_collider = GetComponent<AABBCollider>();
}


bool Rigidbody::IsOnGround() const
{
	return _isOnGround;
}

void Rigidbody::Update()
{
	_previousPosition = _transform->_position;

	if (_isKinematic) {
		_velocity = Vector2D::Zero();
		_targetMoveDelta = Vector2D::Zero();
		return;
	}

	ApplyDrag();
	ApplyGravity();
	
	_targetMoveDelta = _velocity * GameTime::_delta;
}

void Rigidbody::ApplyDrag()
{
	float appliedDrag = (1.0f - _linearDrag * GameTime::_delta);
	if (appliedDrag < 0) appliedDrag = 0;
	_velocity = _velocity * appliedDrag;
}

void Rigidbody::ApplyGravity()
{
	_velocity.y -= GRAVITY * GameTime::_delta * _gravityScale;
}

void Rigidbody::OnCollision(AABBCollider* otherCollider) {
	if (_preventCollisions) {

	}
}

void Rigidbody::Destroy()
{
	Physics::_rigidbodies.erase(std::remove(Physics::_rigidbodies.begin(), Physics::_rigidbodies.end(), this), Physics::_rigidbodies.end());
}
