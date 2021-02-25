#pragma once
class AABBCollider;
class Rigidbody;
class Vector2D;

#include <vector>

class Physics
{
public:
	static void Run();

	//For Debugging Purposes
	static void DrawCollisions();

	static bool IsColliding(AABBCollider* first, AABBCollider* second);

	static Vector2D CalculateColliderDistance(AABBCollider* a, AABBCollider* b);

	static std::vector<AABBCollider*> _colliders;
	static std::vector<Rigidbody*> _rigidbodies;

protected:
	static void PreventCollision(Rigidbody* rb, AABBCollider* collider);
};