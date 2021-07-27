#include "Text.h"

Text::Text()
{
	_renderers.push_back(this);
}

void Text::Draw()
{
	if (!_enabled) return;
	if (!_font) return;
	_font->Draw(_transform, SDL_Color(), _text, _tint);
}

void Text::Destroy()
{
	_renderers.erase(std::remove(_renderers.begin(), _renderers.end(), this), _renderers.end());
}

void Text::SetFont(std::string fontName)
{
	_fontName = fontName;
	_font = Font::Locate(_fontName);
}
