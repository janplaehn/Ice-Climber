#pragma once
class AABBCollider;
class Rigidbody;
struct Vector2D;
struct SDL_Rect;

#include <vector>
#include <memory>

class Physics
{
public:

	static const float GRAVITY;

	static void Run();

	static void DrawCollisions();

	static bool IsColliding(Vector2D point, std::shared_ptr<AABBCollider> collider);

	static std::shared_ptr<AABBCollider> PointCast(Vector2D position, bool includeDisabled);

	static std::vector<std::shared_ptr<AABBCollider>> _colliders;
	static std::vector<std::shared_ptr<Rigidbody>> _rigidbodies;

protected:

	static float SweptAABB(std::shared_ptr<Rigidbody> rb, std::shared_ptr<AABBCollider> collider, Vector2D &normal);
	static bool AABBCheck(SDL_Rect r1, SDL_Rect r2);
	static SDL_Rect GetSweptBroadphaseRect(std::shared_ptr<Rigidbody> rb);
	static void PreventCollisions(std::shared_ptr<Rigidbody> rb);
	static void PreventCollisions(std::shared_ptr<Rigidbody> rb, std::shared_ptr<AABBCollider> collider);

	static std::vector<Vector2D> _pointCastPositions;
};