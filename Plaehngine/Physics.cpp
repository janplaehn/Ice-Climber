#include "Physics.h"
#include "AABBCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Rigidbody.h"
#include "Plaehngine.h"

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

Vector2D Physics::CalculateColliderDistance(AABBCollider* a, AABBCollider* b)
{
	float dx = 0;
	float dy = 0;

	SDL_Rect rectA = a->GetRect();
	SDL_Rect rectB = b->GetRect();

	if (rectA.x < rectB.x)
	{
		dx = rectB.x - (rectA.x + rectA.w);
	}
	else if (rectA.x > rectB.x)
	{
		dx = rectA.x - (rectB.x + rectB.w);
	}

	if (rectA.y < rectB.y)
	{
		dy = rectB.y - (rectA.y + rectA.h);
	}
	else if (rectA.y > rectB.y)
	{
		dy = rectA.y - (rectB.y + rectB.h);
	}

	return Vector2D(dx,dy);
}

void Physics::PreventCollision(Rigidbody* rb, AABBCollider* collider)
{
	//Undo the move applied to transform
	rb->_transform->_position.y = rb->_transform->_position.y - rb->_targetMoveDelta.y;
	rb->_velocity.y = 0;
	return;

	Vector2D distance = Physics::CalculateColliderDistance(rb->_collider, collider);
	float xAxisTimeToCollide = (int)rb->_targetMoveDelta.x != 0 ? abs(distance.x / (int)rb->_targetMoveDelta.x) : 0;
	float yAxisTimeToCollide = (int)rb->_targetMoveDelta.y != 0 ? abs(distance.y / (int)rb->_targetMoveDelta.y) : 0;

	SDL_Rect* intersection = new SDL_Rect();
	const SDL_Rect* rectA = new SDL_Rect(rb->_collider->GetRect());
	const SDL_Rect* rectB = new SDL_Rect(collider->GetRect());
	SDL_IntersectRect(rectA, rectB, intersection);

	//Clamp MoveDelta?


	Vector2D clampedMoveDelta = rb->_targetMoveDelta;
	if (rb->_targetMoveDelta.x != 0) {
		float xRatio = abs(intersection->w) / abs(rb->_targetMoveDelta.x);
		if (xRatio < 1) {
			rb->_velocity.x *= xRatio;
			clampedMoveDelta.x = rb->_targetMoveDelta.x * xRatio;
		}
	}

	if (rb->_targetMoveDelta.y != 0) {
		float yRatio = abs(intersection->h) / abs(rb->_targetMoveDelta.y);
		if (yRatio < 1) {
			rb->_velocity.y *= yRatio;
			clampedMoveDelta.y = rb->_targetMoveDelta.y * yRatio;
		}
	}

	if (abs(clampedMoveDelta.x) < abs(intersection->w) && abs(rb->_targetMoveDelta.x) > abs(intersection->w)) {
		//Collision on top or bottom
		rb->_transform->_position.y = rb->_transform->_position.y - rb->_targetMoveDelta.y;
		rb->_velocity.y = 0;
	}
	if (abs(clampedMoveDelta.y) < abs(intersection->h) && abs(rb->_targetMoveDelta.y) > abs(intersection->h)) {
		//Collision on right or left
		rb->_transform->_position.x = rb->_transform->_position.x - rb->_targetMoveDelta.x;
		rb->_velocity.x = 0;
	}
	else {
		//Collision exactly on corner
		rb->_transform->_position = rb->_transform->_position - rb->_targetMoveDelta;
		rb->_velocity = Vector2D::Zero();
	}

}

void Physics::DrawCollisions(Plaehngine* engine)
{
	for (int i = 0; i < _colliders.size(); i++)
	{
		_colliders[i]->Render();
	}

	for (int i = 0; i < _pointCastPositions.size(); i++)
	{
		engine->RenderPoint(_pointCastPositions[i]);
	}

	_pointCastPositions.clear();
}

std::vector<AABBCollider*> Physics::_colliders;
std::vector<Rigidbody*> Physics::_rigidbodies;
std::vector<Vector2D> Physics::_pointCastPositions;
