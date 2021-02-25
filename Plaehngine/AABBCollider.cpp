#include "AABBCollider.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Sprite.h"

AABBCollider::AABBCollider(Plaehngine* engine, GameObject* go)
	: Component(engine, go)
{
	SpriteRenderer* renderer = GetComponent<SpriteRenderer>();
	if (renderer != nullptr && renderer->_sprite != nullptr) {
		InitializeWithSprite(renderer->_sprite);
	}

	Physics::_colliders.push_back(this);
}

void AABBCollider::InitializeWithSprite(Sprite* sprite)
{
	_width = sprite->GetWidth();
	_height = sprite->GetHeight();
}

void AABBCollider::Update(float dt)
{
}

void AABBCollider::Render()
{
	SDL_Rect rect;

	//Apply Position
	rect.x = _transform->_position.x;
	rect.y = _transform->_position.y * -1.0f + Screen::HEIGHT;
	rect.w = _width;
	rect.h = _height;

	//Apply Scale
	//rect.w *= transform->_scale.x;
	//rect.h *= transform->_scale.y;

	//Apply Pivot
	rect.x -= rect.w * _transform->_pivot.x;
	rect.y -= rect.h * _transform->_pivot.y;

	SDL_SetRenderDrawColor(_engine->_renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(_engine->_renderer, &rect);
}

void AABBCollider::Destroy()
{
	Physics::_colliders.erase(std::remove(Physics::_colliders.begin(), Physics::_colliders.end(), this), Physics::_colliders.end());
}

SDL_Rect AABBCollider::GetRect()
{
	SDL_Rect rect;
	rect.x = _transform->_position.x - _width * _transform->_pivot.x * _transform->_scale.x;
	rect.y = _transform->_position.y + _height * _transform->_pivot.y * _transform->_scale.y;
	rect.w = _width;
	rect.h = _height;
	return rect;
}
