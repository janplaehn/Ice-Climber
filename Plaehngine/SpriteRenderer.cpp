#include "SpriteRenderer.h"
#include "Sprite.h"
#include "AABBCollider.h"
#include <algorithm>

SpriteRenderer::SpriteRenderer(Plaehngine* engine, GameObject* go)
	: Component(engine, go)
{
	_spriteRenderers.push_back(this);
}

void SpriteRenderer::Update(float dt)
{
	if (!_gameObject->_enabled) return;
}

void SpriteRenderer::Draw()
{
	if (_gameObject->_transform == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Can not draw a component that is not placed in the world!");
		return;
	}

	if (_sprite) _sprite->Draw(_gameObject->_transform);
}

void SpriteRenderer::Destroy()
{
	if (_sprite != NULL)
		_sprite->Destroy();
	_sprite = NULL;
	_spriteRenderers.erase(std::remove(_spriteRenderers.begin(), _spriteRenderers.end(), this), _spriteRenderers.end());
}

void SpriteRenderer::SortRenderers()
{
	std::sort(_spriteRenderers.begin(), _spriteRenderers.end(), furtherBack());
}

std::vector<SpriteRenderer*> SpriteRenderer::_spriteRenderers;