#include "Physics.h"
#include "AABBCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Rigidbody.h"
#include "Plaehngine.h"
#include "Graphics.h"

void Physics::Run()
{
	for (int i = 0; i < _rigidbodies.size(); i++)
	{
		if (!_rigidbodies[i]->_enabled || !_rigidbodies[i]->_gameObject->_enabled) return;

		_rigidbodies[i]->_transform->_position = _rigidbodies[i]->_transform->_position + _rigidbodies[i]->_targetMoveDelta;

		for (int j = 0; j < _colliders.size(); j++)
		{
			if (_rigidbodies[i]->_collider == _colliders[j]) continue;

			if (!_colliders[j]->_enabled || !_colliders[j]->_gameObject->_enabled) continue;

			if (IsColliding(_rigidbodies[i]->_collider, _colliders[j])) {

				if (!_rigidbodies[i]->_collider->_isTrigger && !_colliders[j]->_isTrigger) PreventCollision(_rigidbodies[i], _colliders[j]);

				_rigidbodies[i]->_collider->_gameObject->OnCollision(_colliders[j]);
				_colliders[j]->_gameObject->OnCollision(_colliders[i]);
			}
		}
	}
}

bool Physics::IsColliding(AABBCollider* a, AABBCollider* b)
{
	SDL_Rect rectA = a->GetRect();
	SDL_Rect rectB = b->GetRect();

	float aLeft, aRight, aTop, aBottom, bLeft, bRight, bTop, bBottom;

	aLeft = rectA.x;
	bLeft = rectB.x;

	aRight = rectA.x + a->_width;
	bRight = rectB.x + b->_width;

	aBottom = rectA.y - a->_height;
	bBottom = rectB.y - b->_height;

	aTop = rectA.y;
	bTop = rectB.y;

	if (aRight < bLeft) return false;
	if (bRight < aLeft) return false;
	if (aTop < bBottom) return false;
	if (bTop < aBottom) return false;
	return true;
}

bool Physics::IsColliding(Vector2D point, AABBCollider* collider)
{
	SDL_Rect rect = collider->GetRect();

	float left, right, top, bottom;

	left = rect.x;
	right = rect.x + collider->_width;
	bottom = rect.y - collider->_height;
	top = rect.y;

	if (right < point.x) return false;
	if (point.x < left) return false;
	if (top < point.y) return false;
	if (point.y < bottom) return false;
	return true;


}

bool Physics::PointCast(Vector2D position, AABBCollider** result, bool includeDisabled)
{
	_pointCastPositions.push_back(position);

	for (int j = 0; j < _colliders.size(); j++)
	{
		if (!(_colliders[j]->_enabled && _colliders[j]->_gameObject->_enabled) && !includeDisabled) continue;

		if (IsColliding(position, _colliders[j])) {
			*result = _colliders[j];
			return true;
		}
	}
	return false;
}

void Physics::PreventCollision(Rigidbody* rb, AABBCollider* collider)
{
	//Undo the move applied to transform
	rb->_transform->_position.y = rb->_transform->_position.y - rb->_targetMoveDelta.y;
	rb->_velocity.y = 0;
}

void Physics::DrawCollisions(Plaehngine* engine)
{
	for (int i = 0; i < _colliders.size(); i++)
	{
		_colliders[i]->Render();
	}

	for (int i = 0; i < _pointCastPositions.size(); i++)
	{
		Graphics::RenderPoint(_pointCastPositions[i], Color(0,255,0,255));
	}

	_pointCastPositions.clear();
}

std::vector<AABBCollider*> Physics::_colliders;
std::vector<Rigidbody*> Physics::_rigidbodies;
std::vector<Vector2D> Physics::_pointCastPositions;
