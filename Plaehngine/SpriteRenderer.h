#pragma once
#include "Component.h"

class SpriteRenderer : public Component
{

public:
	SpriteRenderer(Plaehngine* engine, GameObject* go);

	virtual void Update(float dt);
	virtual void Draw();
	virtual void Destroy();

	int order = 0;

	class Sprite* _sprite;

	static std::vector<SpriteRenderer*> _spriteRenderers;

	static void SortRenderers();

private:

	struct furtherBack
	{
		inline bool operator() (SpriteRenderer* sr1, SpriteRenderer* sr2)
		{
			return (sr1->order < sr2->order);
		}
	};

};
