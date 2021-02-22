#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "Plaehngine.h"
#include "objectPool.h"

#include <set>


#include "component.h"
#include "gameObject.h"
#include "gameSettings.h"


#include "rocket.h"
#include "player.h"

#include "game.h"
#include "Screen.h"


int main(int argc, char** argv)
{

	Plaehngine engine;

	engine.Init(Screen::WIDTH, Screen::HEIGHT);

	Game game;
	game.Create(&engine);
	game.Init();

	float lastTime = engine.GetElapsedTime();
	while (true)
	{
		float newTime = engine.GetElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * GameSettings::time_multiplier;
		lastTime = newTime;

		engine.ProcessInput();
		game.Update(dt);
		game.Draw();
	}

	// clean up
	game.Destroy();
	engine.Destroy();

	return 0;
}



