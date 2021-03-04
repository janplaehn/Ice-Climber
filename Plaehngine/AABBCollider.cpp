#include "AABBCollider.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "Camera.h"
#include "Graphics.h"

AABBCollider::AABBCollider()
{
	Physics::_colliders.push_back(this);
}

void AABBCollider::BeginPlay() {

}

void AABBCollider::ApplySpriteSize(Sprite* sprite)
{
	_width = sprite->GetWidth();
	_height = sprite->GetHeight();
}

void AABBCollider::Update()
{
}

void AABBCollider::Render()
{
	SDL_Rect rect;

	//Apply Position
	rect.x = _transform->_position.x + _offset.x - Camera::_position.x;
	rect.y = (_transform->_position.y + _offset.y - Camera::_position.y) * -1.0f + Screen::_height;
	rect.w = _width;
	rect.h = _height;

	//Apply Scale
	//rect.w *= transform->_scale.x;
	//rect.h *= transform->_scale.y;

	//Apply Pivot
	rect.x -= rect.w * _transform->_pivot.x;
	rect.y -= rect.h * _transform->_pivot.y;

	Graphics::DrawRect(&rect, Color(0,255,0));
}

void AABBCollider::Destroy()
{
	Physics::_colliders.erase(std::remove(Physics::_colliders.begin(), Physics::_colliders.end(), this), Physics::_colliders.end());
}

SDL_Rect AABBCollider::GetRect()
{
	SDL_Rect rect;
	rect.x = _transform->_position.x + _offset.x - _width * _transform->_pivot.x * _transform->_scale.x;
	rect.y = _transform->_position.y + _offset.y + _height * _transform->_pivot.y * _transform->_scale.y;
	rect.w = _width;
	rect.h = _height;
	return rect;
}
