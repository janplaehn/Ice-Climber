#pragma once

#include "SDL.h"

#ifndef NDEBUG
#define PLAEHNGINE_EDITOR
#endif

class Game;

class Plaehngine final
{

public:
	Plaehngine(Game* game);

	void Run();

	// Destroys the Plaehngine instance
	void Destroy();

	// Destroys the Plaehngine instance and exits
	void Quit();

private:
	static void Init(Game* game);
};

