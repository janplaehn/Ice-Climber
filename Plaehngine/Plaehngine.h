#pragma once

class Game;

#include "SDL.h"
#include "SDL_ttf.h"

class Plaehngine final
{
	friend class Sprite;

public:

	// Creates the main window. Returns true on success.
	// Use Player Settings instead
	bool Init(Game* game);

	void Run();

	// Draws the given text.
	//Should be moved to some sort of UI class
	void DrawText(struct Vector2D position, const char* msg);

	// Destroys the Plaehngine instance
	void Destroy();

	// Destroys the Plaehngine instance and exits
	void Quit();

	SDL_Renderer* _renderer;

	void RenderPoint(Vector2D point);

private:
	//Todo: Move to Renderer
	void SwapBuffers();

	//Todo: Move to Renderer
	void ClearWindow();

	SDL_Window * _window;
	TTF_Font* _font;
	Game* _game;
};

