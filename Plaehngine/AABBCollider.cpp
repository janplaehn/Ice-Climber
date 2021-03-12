#include "AABBCollider.h"
#include "ComponentEssentials.h"
#include "Graphics.h"
#include "Physics.h"

AABBCollider::AABBCollider()
{
	Physics::_colliders.push_back(this);
}

void AABBCollider::ApplySpriteSize(Sprite* sprite)
{
    _scale.x = sprite->GetWidth();
	_scale.y = sprite->GetHeight();
}

void AABBCollider::Render()
{
	SDL_Rect rect;

	rect.x = _transform->_position.x + _offset.x - Camera::_position.x - _scale.x * _transform->_pivot.x * _transform->_scale.x;
	rect.y = (_transform->_position.y + _offset.y - Camera::_position.y + _scale.y * _transform->_pivot.y * _transform->_scale.y) * -1.0f + Screen::_height;;
	rect.w = _scale.x;
	rect.h = _scale.y;

	Graphics::DrawRect(&rect, Color(0,255,0));
}

void AABBCollider::Destroy()
{
	Physics::_colliders.erase(std::remove(Physics::_colliders.begin(), Physics::_colliders.end(), this), Physics::_colliders.end());
}

SDL_Rect AABBCollider::GetRect()
{
	SDL_Rect rect;
	rect.x = _transform->_position.x + _offset.x - _scale.x * _transform->_pivot.x * _transform->_scale.x;
	rect.y = _transform->_position.y + _offset.y + _scale.y * _transform->_pivot.y * _transform->_scale.y - _scale.y;
	rect.w = _scale.x;
	rect.h = _scale.y;
	return rect;
}

void AABBCollider::SetScale(Vector2D scale)
{
	_scale = scale;
}

Vector2D AABBCollider::GetScale()
{
	return _scale;
}

void AABBCollider::SetOffset(Vector2D offset)
{
	_offset = offset;
}

Vector2D AABBCollider::GetOffset()
{
	return _offset;
}

void AABBCollider::SetTrigger(bool isTrigger)
{
	_isTrigger = isTrigger;
}

bool AABBCollider::IsTrigger()
{
	return _isTrigger;
}
