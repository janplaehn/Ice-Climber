#pragma once
#include "Plaehngine.h"

static class Random
{
	friend class Plaehngine;

public:

	static float Value01();

	static float Range(float min, float max);

private:

	static void Init();

};

