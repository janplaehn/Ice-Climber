#pragma once
#include "SDL.h"
#include "Plaehngine.h"

class Sprite
{
	friend class Plaehngine;

	SDL_Texture* _texture;


	Sprite(SDL_Texture* texture);

public:

	// Destroys the sprite instance
	void Destroy();

	// Draw the sprite at the given position.
	// Valid coordinates are between (0,0) (upper left) and (width-32, height-32) (lower right).
	// (All sprites are 32*32 pixels, clipping is not supported)
	void Draw(class Transform* transform);

	// Create a sprite given a string.
	// All sprites are 32*32 pixels.
	// Todo: This should be moved to Sprite class for sure
	static Sprite* Create(const char* path);	

private:
	static SDL_Renderer* _renderer;
};
