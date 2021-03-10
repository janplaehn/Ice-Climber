#include "ImageFont.h"
#include "Sprite.h"

void ImageFont::Create(std::string path, std::string name, std::string glyphs, int glyphWidth, int glyphHeight)
{
	ImageFont* font = new ImageFont();
	font->_spriteSheet = Sprite::Create(path.c_str());
	font->_glyphs = glyphs;
	font->_glyphWidth = glyphWidth;
	font->_glyphHeight = glyphHeight;
	font->_name = name;
	_fonts.push_back(font);
}

void ImageFont::Draw(Transform* transform, SDL_Color color, std::string message, Color tint)
{
	Transform* letterTransform = new Transform(transform);

	//Apply Pivot to text
	letterTransform->_position = letterTransform->_position - letterTransform->_pivot * (message.size() - 1) * _glyphWidth;

	for (char& c : message) {
		if (c == ' ') {
			letterTransform->_position.x += _glyphWidth;
			continue;
		}
		int i = FindCharInGlyphs(c);
		SDL_Rect clip;
		clip.x = _glyphWidth * i;
		clip.y = 0;
		clip.w = _glyphWidth;
		clip.h = _glyphHeight;
		_spriteSheet->Draw(letterTransform, clip, tint);
		letterTransform->_position.x += _glyphWidth;
	}

	letterTransform->Destroy();
	delete letterTransform;
}

void ImageFont::Destroy()
{
	_spriteSheet->Destroy();
}

int ImageFont::FindCharInGlyphs(char c)
{
	for (int i = 0; i < _glyphs.size(); i++) {
		if (c == _glyphs[i]) return i;
	}
	return 0;
}
