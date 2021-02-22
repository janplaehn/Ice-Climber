#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

class Plaehngine
{
	friend class Sprite;

public:
	// Destroys the Plaehngine instance
	void Destroy();

	// Destroys the Plaehngine instance and exits
	void Quit();

	// Creates the main window. Returns true on success.
	// Use Player Settings instead
	bool Init(int width, int height);

	// Clears the screen and draws all sprites and texts which have been drawn
	// since the last update call.
	// If update returns false, the application should terminate.
	void ProcessInput();

	void SwapBuffers();

	void ClearWindow();

	// Draws the given text.
	//Should be moved to some sort of UI class
	void DrawText(struct Vector2D position, const char* msg);

	// Todo: Move this to time class!
	// Return the total time spent in the game, in seconds.
	float GetElapsedTime();

	//Todo: Move this stuff to Input class!
	struct KeyStatus
	{
		bool _fire; // space
		bool _left; // left arrow
		bool _right; // right arrow
		bool _escape; // escape button
	};

	// Todo: Move this too!
	// Returns the keyboard status. If a flag is set, the corresponding key is being held down.
	void GetKeyStatus(KeyStatus& keys);

private:
	SDL_Window * _window;
	SDL_Renderer * _renderer;

	TTF_Font* _font;

	KeyStatus _key;
};

