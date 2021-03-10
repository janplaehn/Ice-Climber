#pragma once
class AABBCollider;
class Rigidbody;
struct Vector2D;
struct SDL_Rect;

#include <vector>

class Physics
{
public:
	static void Run();

	static void DrawCollisions();

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

	static std::vector<Vector2D> _pointCastPositions;
};