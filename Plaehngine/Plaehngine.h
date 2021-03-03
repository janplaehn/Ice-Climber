#pragma once

class Game;

class Plaehngine final
{

public:

	// Creates the main window. Returns true on success.
	// Use Player Settings instead
	bool Init(Game* game);
	void Run();

	// Destroys the Plaehngine instance
	void Destroy();

	// Destroys the Plaehngine instance and exits
	void Quit();

private:
	Game* _game;
};

