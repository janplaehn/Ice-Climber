#include "Vector2D.h"
#include <math.h>
#include "SDL.h"
#include "Camera.h"
#include "Screen.h"

Vector2D::Vector2D()
{
	this->x = 0;
	this->y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D Vector2D::operator+(const Vector2D& rhs)
{
	return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D& rhs)
{
	return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator*(const Vector2D& rhs)
{
	return Vector2D(x * rhs.x, y * rhs.y);
}

Vector2D Vector2D::operator/(const double& rhs)
{
	return Vector2D(x / rhs, y / rhs);
}

Vector2D Vector2D::operator*(const double& rhs)
{
	return Vector2D(x * rhs, y * rhs);
}

bool Vector2D::operator==(const Vector2D& rhs)
{
	return x == rhs.x && y == rhs.y;
}

float Vector2D::Dot(const Vector2D first, const Vector2D second)
{
	return first.x * second.x + first.y * second.y;
}

float Vector2D::Length()
{
	return sqrt(SquaredLength());
}

float Vector2D::SquaredLength()
{
	return pow(x, 2) + pow(y, 2);
}

float Vector2D::Distance(Vector2D vector, Vector2D otherVector)
{
	return (vector - otherVector).Length();
}

Vector2D Vector2D::Normalized()
{
	float l = Length();
	return Vector2D(x / l, y / l);
}

Vector2D Vector2D::Zero()
{
	return Vector2D(0, 0);
}

Vector2D Vector2D::One()
{
	return Vector2D(1, 1);
}

Vector2D Vector2D::Up()
{
	return Vector2D(0, 1);
}

Vector2D Vector2D::Down()
{
	return Vector2D(0, -1);
}

Vector2D Vector2D::Right()
{
	return Vector2D(1, 0);
}

Vector2D Vector2D::Left()
{
	return Vector2D(-1, 0);
}
