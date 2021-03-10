#pragma once
#include "Font.h"
class ImageFont : public Font
{
public:
	static void Create(std::string path, std::string name, std::string glyphs, int glyphWidth, int glyphHeight);

	virtual void Draw(Transform* transform, SDL_Color color, std::string message, Color tint) override;
	virtual void Destroy() override;
	virtual int FindCharInGlyphs(char c);

private:
	std::string _glyphs;
	class Sprite* _spriteSheet;
	int _glyphWidth = 0;
	int _glyphHeight = 0;
};

