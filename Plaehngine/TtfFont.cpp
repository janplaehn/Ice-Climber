#include "TtfFont.h"

void TtfFont::Create(std::string path, std::string name, int size)
{
	TtfFont* font = new TtfFont();
	font->_ttf = TTF_OpenFont(path.c_str(), size);

	if (font->_ttf == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		delete font;
		return;
	}

	font->_name = name;

	_fonts.push_back(font);
}

void TtfFont::Draw(std::shared_ptr<Transform> transform, SDL_Color color, std::string message, Color tint)
{
	Graphics::DrawText(_ttf, transform->_position, message.c_str(), tint);
}

void TtfFont::Destroy()
{
	TTF_CloseFont(_ttf);
}
