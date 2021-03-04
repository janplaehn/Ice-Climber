#pragma once
struct Color
{
public:
	int r = 255, g = 255, b = 255, a = 255;

	Color(int r, int g, int b, int a);
	Color(int r, int g, int b);

	static Color White();
	static Color Red();
	static Color Green();
	static Color Blue();
};

