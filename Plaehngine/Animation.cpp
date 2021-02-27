#include "Animation.h"
#include "Sprite.h"

Animation::Animation(Plaehngine* engine, GameObject* go)
	: Renderer(engine, go)
{
	_renderers.push_back(this);
}

void Animation::Update(float dt)
{
	if (_frameRate == 0) return;
	
	_timer += dt;
	if (_timer > (1 / _frameRate)) {
		_timer -= (1 / _frameRate);
		_frame++;

		if ((_frame + 1) * _spriteWidth > _spriteSheet->GetWidth()) { //Loop back
			_frame = 0;
		}
	}
}

void Animation::Draw()
{
	if (!_enabled || _spriteSheet == nullptr) return;

	SDL_Rect clip;
	clip.x = _frame * _spriteWidth;
	clip.y = 0;
	clip.h = _spriteSheet->GetHeight();
	clip.w = _spriteWidth;
	_spriteSheet->Draw(_transform, clip);
}

void Animation::Destroy()
{
}
