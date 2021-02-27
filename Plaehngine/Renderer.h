#pragma once
#include "Component.h"
class Renderer :  public Component
{
public:
	Renderer(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	int order = 0;

	static std::vector<Renderer*> _renderers;

	static void SortRenderers();

private:

	struct furtherBack
	{
		inline bool operator() (Renderer* sr1, Renderer* sr2) {
			return (sr1->order < sr2->order);
		}
	};
};

