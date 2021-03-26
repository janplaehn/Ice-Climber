#include "Plaehngine.h"
#include "PlaehngineEditor.h"
#include "SDL.h"

int main(int argc, char** argv)
{
	Plaehngine* engine = new Plaehngine();;
	PlaehngineEditor* game = new PlaehngineEditor();

	engine->Init(game);
	engine->Run();
	engine->Destroy();
	delete engine;

	return 0;
}