#include "SpriteRenderer.h"
#include "Sprite.h"
#include "AABBCollider.h"
#include <algorithm>
#include "GameObject.h"

void SpriteRenderer::Update()
{
	if (!_gameObject->_enabled) return;
}

void SpriteRenderer::Draw()
{
	if (!_enabled) return;

	if (_transform == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Can not draw a component that is not placed in the world!");
		return;
	}

	if (_sprite) _sprite->Draw(_transform, _tint);
}

void SpriteRenderer::Destroy()
{
	if (_sprite != NULL)
		_sprite->Destroy();
	_sprite = NULL;
}