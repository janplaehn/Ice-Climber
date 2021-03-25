#pragma once
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	class Sprite* _sprite = nullptr;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Renderer>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(SpriteRenderer, "SpriteRenderer")
CEREAL_REGISTER_POLYMORPHIC_RELATION(SpriteRenderer, Renderer)