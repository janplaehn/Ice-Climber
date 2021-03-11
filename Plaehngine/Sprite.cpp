#include "sprite.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Vector2D.h"
#include "Transform.h"
#include "Screen.h"
#include "Camera.h"
#include "Graphics.h"

Sprite::Sprite(SDL_Texture* texture)
{
	this->_texture = texture;
}


void Sprite::Draw(Transform* transform, Color tint)
{
	SDL_Rect clip;
	clip.x = clip.y = 0;
	clip.w = GetWidth();
	clip.h = GetHeight();
	Draw(transform, clip, tint);
}

void Sprite::Draw(Transform* transform, SDL_Rect clip, Color tint)
{
	SDL_Rect rect;


	if (transform->_isInScreenSpace) {
		//Apply Position
		rect.x = transform->_position.x;
		rect.y = transform->_position.y * -1.0f + Screen::_height;
	}
	else {
		//Apply Position & Camera
		rect.x = transform->_position.x - Camera::_position.x;
		rect.y = (transform->_position.y - Camera::_position.y) * -1.0f + Screen::_height;
	}

	//Apply Scale
	rect.w = clip.w * transform->_scale.x;
	rect.h = clip.h * transform->_scale.y;

	//Apply Pivot
	rect.x -= rect.w * transform->_pivot.x;
	rect.y -= rect.h * transform->_pivot.y;

	Graphics::RenderTexture(_texture, &clip, &rect, transform->_rotation, transform->_flipType, tint);
}

Sprite* Sprite::Create(const char* path)
{
	SDL_Texture* texture = Graphics::CreateTexture(path);

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