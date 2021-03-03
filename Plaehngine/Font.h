#pragma once
#include "ComponentEssentials.h"
#include "SDL_ttf.h"

class Font
{
public:
	virtual void Draw(Transform* transform, SDL_Color color, std::string message) = 0;
	virtual void Destroy() = 0;

	static Font* Locate(std::string fontName);
	static void UnloadAllFonts();

	std::string _name;
protected:
	static std::vector<Font*> _fonts;
};
