#include "Animation.h"
#include "Sprite.h"

Animation::Animation(Plaehngine* engine, GameObject* go)
	: Renderer(engine, go)
{
	_renderers.push_back(this);
}

void Animation::Update(float dt)
{
	_timer += dt;
	if (_frameRate == 0) {
		return;
	}

	if (_timer > (1 / _frameRate)) {
		_timer = 0;
		_frameStart += _spriteWidth;
		if (_frameStart + _spriteWidth > _spriteSheet->GetWidth()) {
			_frameStart = 0;
		}
	}
}

void Animation::Draw()
{
	if (!_enabled || _spriteSheet == nullptr) return;

	if (_transform == nullptr) {
		SDL_LogWarn(SDL_LOG_CATEGORY_RENDER, "Can not draw a component that is not placed in the world!");
		return;
	}

	SDL_Rect clip;
	clip.x = _frameStart;
	clip.y = 0;
	clip.h = _spriteSheet->GetHeight();
	clip.w = _spriteWidth;
	if (_spriteSheet) _spriteSheet->Draw(_transform, clip);
}

void Animation::Destroy()
{
}
