#include "Text.h"

Text::Text()
{
	_renderers.push_back(this);
}

void Text::Update()
{
	if (!_enabled) return;
	_font->Draw(_transform, SDL_Color(), _text);
}

void Text::BeginPlay()
{
	LocateFont();
}

void Text::LocateFont()
{
	_font = Font::Locate(_fontName);
}

void Text::Draw()
{
}

void Text::Destroy()
{
	_renderers.erase(std::remove(_renderers.begin(), _renderers.end(), this), _renderers.end());
}
