#include "Plaehngine.h"
#include "IceClimberGame.h"

int main(int argc, char** argv)
{
	IceClimberGame* game = new IceClimberGame();
	Plaehngine* engine = new Plaehngine(game);
	delete engine;
	delete game;

	return 0;
}