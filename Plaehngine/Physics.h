#pragma once
class AABBCollider;
class Rigidbody;
class Vector2D;
class SDL_Rect;

#include <vector>

class Physics
{
public:
	static void Run();

	//For Debugging Purposes
	static void DrawCollisions();

	static bool IsColliding(AABBCollider* first, AABBCollider* second);
	static bool IsColliding(Vector2D point, AABBCollider* collider);

	static bool PointCast(Vector2D position, AABBCollider** result, bool includeDisabled);

	static std::vector<AABBCollider*> _colliders;
	static std::vector<Rigidbody*> _rigidbodies;

protected:

	static float SweptAABB(Rigidbody* rb, AABBCollider* collider, Vector2D &normal);
	static bool AABBCheck(SDL_Rect r1, SDL_Rect r2);
	static SDL_Rect GetSweptBroadphaseRect(Rigidbody* rb);
	static void PreventCollisions(Rigidbody* rb);
	static void PreventCollisions(Rigidbody* rb, AABBCollider* collider);
	static void ResolveCollision(Rigidbody* rb, AABBCollider* collider);

	static std::vector<Vector2D> _pointCastPositions;
};