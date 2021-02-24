#define _CRT_SECURE_NO_WARNINGS

#include "Plaehngine.h"
#include "IceClimberGame.h"

int main(int argc, char** argv)
{
	Plaehngine engine;
	IceClimberGame* game = new IceClimberGame();

	engine.Init(game);
	engine.Run();
	engine.Destroy();

	return 0;
}