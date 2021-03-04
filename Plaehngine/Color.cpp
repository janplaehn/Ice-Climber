#include "Color.h"

Color::Color(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}
Color::Color()
{
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
}

Color Color::White()
{
	return Color(255,255,255);
}

Color Color::Red()
{
	return Color(255,0,0);
}

Color Color::Green()
{
	return Color(0,255,0);
}

Color Color::Blue()
{
	return Color(0,0,255);
}
