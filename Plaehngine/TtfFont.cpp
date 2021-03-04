#include "TtfFont.h"

void TtfFont::Create(std::string path, std::string name, int size)
{
	TtfFont* font = new TtfFont();
	font->_name = name;
	font->_ttf = TTF_OpenFont(path.c_str(), size); //this opens a font style and sets a size
	if (font->_ttf == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
	}
	_fonts.push_back(font);
}

void TtfFont::Draw(Transform* transform, SDL_Color color, std::string message, Color tint)
{
	Graphics::DrawText(_ttf, transform->_position, message.c_str(), tint);
}

void TtfFont::Destroy()
{
	TTF_CloseFont(_ttf);
}
