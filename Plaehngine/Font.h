#pragma once
#include "ComponentEssentials.h"
#include "SDL_ttf.h"
#include "Color.h"

class Font
{
public:

	static Font* Locate(std::string fontName);

	static void UnloadAllFonts();

	virtual void Draw(Transform* transform, SDL_Color color, std::string message, Color tint) = 0;

	virtual void Destroy() = 0;

	std::string GetName();
	
protected:

	std::string _name;

	static std::vector<Font*> _fonts;
};

