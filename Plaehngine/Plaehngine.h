#pragma once

class Game;

#include "SDL.h"
#include "SDL_ttf.h"

class Plaehngine
{
	friend class Sprite;

public:

	// Creates the main window. Returns true on success.
	// Use Player Settings instead
	bool Init(Game* game);


	//Todo: Move to Renderer
	void SwapBuffers();

	//Todo: Move to Renderer
	void ClearWindow();

	void Run();

	// Draws the given text.
	//Should be moved to some sort of UI class
	void DrawText(struct Vector2D position, const char* msg);

	// Destroys the Plaehngine instance
	void Destroy();

	// Destroys the Plaehngine instance and exits
	void Quit();

private:
	SDL_Window * _window;
	SDL_Renderer * _renderer;
	TTF_Font* _font;
	Game* _game;
};

