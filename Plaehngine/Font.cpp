#include "Font.h"

Font* Font::Locate(std::string fontName)
{
	for (Font* font : _fonts)
	{
		if (fontName == font->_name) {
			return font;
		}
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font '%s' can not be found in created Fonts!", fontName.c_str());
	return nullptr;
}

void Font::UnloadAllFonts()
{
	for (Font* font : _fonts)
	{
		font->Destroy();
		delete font;
	}
	_fonts.clear();
}

std::string Font::GetName()
{
	return _name;
}

std::vector<Font*> Font::_fonts;