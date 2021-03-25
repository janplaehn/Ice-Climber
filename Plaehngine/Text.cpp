#include "Text.h"

Text::Text()
{
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
	if (!_enabled) return;
	_font->Draw(_transform, SDL_Color(), _text, _tint);
}

void Text::Destroy()
{
}
