#pragma once
#include "Renderer.h"
class Animation : public Renderer
{

public:
	Animation();

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	class Sprite* _spriteSheet = nullptr;
	int _spriteWidth = 8;
	float _frameRate = 12;

	float _timer = 0;
	int _frame = 0;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Renderer>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Animation, "Animation")
CEREAL_REGISTER_POLYMORPHIC_RELATION(Animation, Renderer)