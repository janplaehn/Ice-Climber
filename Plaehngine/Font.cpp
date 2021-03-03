#include "Font.h"

Font* Font::Locate(std::string fontName)
{
	for (Font* font : _fonts)
	{
		if (fontName == font->_name) {
			return font;
		}
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Font '%' can not be found in created Fonts!", fontName.c_str());
	return nullptr;
}

void Font::UnloadAllFonts()
{
	for (int i = 0; i < _fonts.size(); i++)
	{
		_fonts[i]->Destroy();
		delete _fonts[i];
	}
	_fonts.clear();
}

std::vector<Font*> Font::_fonts;