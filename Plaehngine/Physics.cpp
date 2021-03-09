#include "Physics.h"
#include "AABBCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Rigidbody.h"
#include "Plaehngine.h"
#include "Graphics.h"
#include <limits>
#include "GameMath.h"

void Physics::Run()
{
	for (Rigidbody* rb : _rigidbodies)
	{
		PreventCollisions(rb);
	}
}

bool Physics::IsColliding(Vector2D point, AABBCollider* collider)
{
	SDL_Rect rect = collider->GetRect();

	float left, right, top, bottom;

	left = rect.x;
	right = rect.x + collider->_width;
	bottom = rect.y;
	top = rect.y + collider->_height;

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
		if (!_colliders[j]->IsActiveAndEnabled() && !includeDisabled) continue;

		if (IsColliding(position, _colliders[j])) {
			*result = _colliders[j];
			return true;
		}
	}
	return false;
}

//https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
float Physics::SweptAABB(Rigidbody* rb, AABBCollider* collider, Vector2D& normal)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	SDL_Rect rbRect = rb->_collider->GetRect();
	SDL_Rect colRect = collider->GetRect();

	// find the distance between the objects on the near and far sides for both x and y 

	if (rb->_targetMoveDelta.x > 0.0f)
	{
		xInvEntry = colRect.x - (rbRect.x + rbRect.w);
		xInvExit = (colRect.x + colRect.w) - rbRect.x;
	}
	else
	{
		xInvEntry = (colRect.x + colRect.w) - rbRect.x;
		xInvExit = colRect.x - (rbRect.x + rbRect.w);
	}

	if (rb->_targetMoveDelta.y > 0.0f)
	{
		yInvEntry = colRect.y - (rbRect.y + rbRect.h);
		yInvExit = (colRect.y + colRect.h) - rbRect.y;
	}
	else
	{
		yInvEntry = (colRect.y + colRect.h) - rbRect.y;
		yInvExit = colRect.y - (rbRect.y + rbRect.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero) 
	float xEntry, yEntry;
	float xExit, yExit;

	if (rb->_targetMoveDelta.x == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / rb->_targetMoveDelta.x;
		xExit = xInvExit / rb->_targetMoveDelta.x;
	}

	if (rb->_targetMoveDelta.y == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / rb->_targetMoveDelta.y;
		yExit = yInvExit / rb->_targetMoveDelta.y;
	}

	// find the earliest/latest times of collision
	float entryTime = std::max(xEntry, yEntry);
	float exitTime = std::min(xExit, yExit);

	// if there was no collision
	if ((entryTime > exitTime) || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	{
		//Debug
		/*Graphics::DrawRect(&rbRect, Color::Blue());
		Graphics::DrawRect(&colRect, Color::Blue());*/

		normal.x = 0.0f;
		normal.y = 0.0f;
		return 1.0f;
	}
	else // if there was a collision 
	{
		//Debug
		/*Graphics::DrawRect(&rbRect, Color::Red());
		Graphics::DrawRect(&colRect, Color::Red());*/

		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normal.x = 1.0f;
				normal.y = 0.0f;
			}
			else
			{
				normal.x = -1.0f;
				normal.y = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f)
			{
				normal.x = 0.0f;
				normal.y = 1.0f;
			}
			else
			{
				normal.x = 0.0f;
				normal.y = -1.0f;
			}
		} 
		// return the time of collision
		return entryTime; 
	}
}

bool Physics::AABBCheck(SDL_Rect r1, SDL_Rect r2)
{
	return !(r1.x + r1.w < r2.x || r1.x > r2.x + r2.w || r1.y + r1.h < r2.y || r1.y > r2.y + r2.h);
}

SDL_Rect Physics::GetSweptBroadphaseRect(Rigidbody* rb)
{
	SDL_Rect rect = rb->_collider->GetRect();
	SDL_Rect bpRect;
	bpRect.x = rb->_velocity.x > 0 ? rect.x : rect.x + rb->_velocity.x;
	bpRect.y = rb->_velocity.y > 0 ? rect.y : rect.y + rb->_velocity.y;
	bpRect.w = rb->_velocity.x > 0 ? rb->_velocity.x + rect.w : rect.w - rb->_velocity.x;
	bpRect.h = rb->_velocity.y > 0 ? rb->_velocity.y + rect.h : rect.h - rb->_velocity.y;
	return bpRect;
}

void Physics::PreventCollisions(Rigidbody* rb)
{
	if (!rb->IsActiveAndEnabled()) return;

	if (rb->_collider != nullptr) {
		for (int j = 0; j < _colliders.size(); j++)
		{
			PreventCollisions(rb, _colliders[j]);
		}
	}

	rb->_transform->_position = rb->_transform->_position + rb->_targetMoveDelta;
	rb->_targetMoveDelta = Vector2D::Zero();
}

void Physics::PreventCollisions(Rigidbody* rb, AABBCollider* collider)
{
	if (rb->_collider == collider) return;
	if (!collider->IsActiveAndEnabled()) return;

	SDL_Rect broadphaseRect = GetSweptBroadphaseRect(rb);
	if (!AABBCheck(broadphaseRect, collider->GetRect())) return;

	if (rb->_isKinematic) {
		rb->_collider->_gameObject->OnCollision(collider, Vector2D::Zero());
		collider->_gameObject->OnCollision(rb->_collider, Vector2D::Zero());
		return;
	}

	Vector2D out_normal = Vector2D::Zero();
	float collisiontime = SweptAABB(rb, collider, out_normal);
	if (collisiontime >= 1.0f) return;

	float remainingtime = 1.0f - collisiontime;

	if (!rb->_collider->_isTrigger && !collider->_isTrigger && !rb->_isKinematic) {

		// slide 
		float dotprod = (rb->_targetMoveDelta.x * out_normal.y + rb->_targetMoveDelta.y * out_normal.x) * remainingtime;
		float velDotprod = (rb->_velocity.x * out_normal.y + rb->_velocity.y * out_normal.x) * remainingtime;

		rb->_targetMoveDelta.x = dotprod * out_normal.y;
		rb->_targetMoveDelta.y = dotprod * out_normal.x;


		//This is bad and only works in our case!
		if (out_normal.y == -1 && rb->_velocity.y < 0) {
			rb->_transform->_position.y = collider->GetRect().y + collider->GetRect().h + rb->_collider->_offset.y - 2.0f;
		}

		if (GameMath::Sign(out_normal.x) == GameMath::Sign(rb->_velocity.x)) {
			rb->_velocity.x = velDotprod * out_normal.y;
		}
		if (GameMath::Sign(-out_normal.y) == GameMath::Sign(rb->_velocity.y)) {
			rb->_velocity.y *= velDotprod * out_normal.x;
		}
	}

	rb->_collider->_gameObject->OnCollision(collider, out_normal);
	collider->_gameObject->OnCollision(rb->_collider, out_normal);
}

void Physics::DrawCollisions()
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
