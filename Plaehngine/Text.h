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

public:
	friend class cereal::access;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Renderer>(this), _text, _fontName);
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Text, "Text")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Text, Renderer)