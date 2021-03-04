#pragma once
#include "Font.h"

class TtfFont :public Font
{
public:
	static void Create(std::string path, std::string name, int size);

	virtual void Draw(Transform* transform, SDL_Color color, std::string message, Color tint) override;
	virtual void Destroy() override;

protected:
	TTF_Font* _ttf;
};

