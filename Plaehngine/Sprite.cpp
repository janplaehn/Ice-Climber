#include "sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Screen.h"

Sprite::Sprite(SDL_Texture* texture)
{
	this->_texture = texture;
}


void Sprite::Draw(Transform* transform)
{
	SDL_Rect rect;

	//Apply Position
	rect.x = transform->_position.x;
	rect.y = transform->_position.y * -1.0f + Screen::HEIGHT;

	SDL_QueryTexture(_texture, NULL, NULL, &(rect.w), &(rect.h));

	//Apply Scale
	rect.w *= transform->_scale.x;
	rect.h *= transform->_scale.y;

	//Apply Pivot
	rect.x -= rect.w * transform->_pivot.x;
	rect.y -= rect.h * transform->_pivot.y;

	SDL_RenderCopyEx(_renderer, _texture, NULL /*clip*/, &rect, transform->_rotation, NULL /*center*/, transform->_flipType);
}

Sprite* Sprite::Create(const char* path)
{
	SDL_Surface* surf = IMG_Load(path);
	if (surf == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Create texture from surface pixels
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surf);
	if (texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surf);

	Sprite* sprite = new Sprite(texture);

	return sprite;
}

int Sprite::GetWidth()
{
	int width, height;
	SDL_QueryTexture(_texture, NULL, NULL, &width, &height);
	return width;
}

int Sprite::GetHeight()
{
	int width, height;
	SDL_QueryTexture(_texture, NULL, NULL, &width, &height);
	return height;
}


void Sprite::Destroy()
{
	SDL_DestroyTexture(_texture);
}

SDL_Renderer* Sprite::_renderer = nullptr;