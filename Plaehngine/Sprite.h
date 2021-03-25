#pragma once
#include "SDL.h"
#include "Plaehngine.h"
#include "Color.h"
#include <memory>

class Transform;

class Sprite
{
	Sprite(SDL_Texture* texture);

public:

	static Sprite* Create(const char* path);

	void Destroy();

	void Draw(std::shared_ptr<Transform> transform, Color tint);
	void Draw(std::shared_ptr<Transform> transform, SDL_Rect clip, Color tint);

	int GetWidth();
	int GetHeight();

protected:

	SDL_Texture* _texture;
};
