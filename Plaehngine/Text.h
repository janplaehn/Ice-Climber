#pragma once
#include "Renderer.h"
#include "Font.h"

class Text : public Renderer
{

public:
	Text();

	virtual void Update() {};
	virtual void BeginPlay() override {};
	virtual void Draw();
	virtual void Destroy();
	virtual void SetFont(std::string fontName);

	std::string _text;

private:
	std::string _fontName;
	class Font* _font = nullptr;
};

