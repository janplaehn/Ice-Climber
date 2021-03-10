#pragma once
#include "Renderer.h"
#include "Font.h"

class Text : public Renderer
{

public:
	Text();

	virtual void Update() {};
	virtual void BeginPlay();
	virtual void Draw();
	virtual void Destroy();
	virtual void LocateFont();

	std::string _text;
	std::string _fontName;

private:
	class Font* _font = nullptr;
};

