#include "SpriteRenderer.h"
#include "Sprite.h"
#include "AABBCollider.h"
#include <algorithm>

SpriteRenderer::SpriteRenderer(Plaehngine* engine, GameObject* go)
	: Renderer(engine, go)
{
	_renderers.push_back(this);
}

void SpriteRenderer::Update(float dt)
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

	if (_sprite) _sprite->Draw(_transform);
}

void SpriteRenderer::Destroy()
{
	if (_sprite != NULL)
		_sprite->Destroy();
	_sprite = NULL;
	_renderers.erase(std::remove(_renderers.begin(), _renderers.end(), this), _renderers.end());
}