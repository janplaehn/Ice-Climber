#pragma once


struct Vector2D
{
public:
	float x, y;
	Vector2D();

	Vector2D(float xy);

	Vector2D(float x, float y);

	Vector2D operator+(const Vector2D& rhs);

	Vector2D operator-(const Vector2D& rhs);

	Vector2D operator*(const Vector2D& rhs);

	Vector2D operator/(const double& rhs);

	Vector2D operator*(const double& rhs);

	bool operator==(const Vector2D& rhs);

	float Length();

	float SquaredLength();

	static float Dot(const Vector2D first, const Vector2D second);

	static float Distance(Vector2D vector, Vector2D otherVector);

	Vector2D Normalized();

	static Vector2D Zero();

	static Vector2D Up();

	static Vector2D Right();

	static Vector2D Down();

	static Vector2D Left();

	static Vector2D One();

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(x,y); // serialize things by passing them to the archive
	}
};

