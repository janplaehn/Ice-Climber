#pragma once
struct Color
{
public:
	int r = 256, g = 256, b = 256, a = 256;

	Color(int r, int g, int b, int a);
	Color(int r, int g, int b);
	Color();

	static Color White();
	static Color Red();
	static Color Green();
	static Color Blue();
};

