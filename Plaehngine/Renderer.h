#pragma once
#include "Component.h"
#include "Transform.h"
class Renderer :  public Component
{
public:
	Renderer(Plaehngine* engine, GameObject* go) : Component(engine, go) {};

	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	int _order = 0;

	static std::vector<Renderer*> _renderers;

	static void SortRenderers();

private:

	struct furtherBack
	{
		inline bool operator() (Renderer* sr1, Renderer* sr2) {
			if (!sr1->_transform->_isInScreenSpace && sr2->_transform->_isInScreenSpace) {
				return true;
			}
			if (sr1->_transform->_isInScreenSpace && !sr2->_transform->_isInScreenSpace) {
				return false;
			}
			return (sr1->_order < sr2->_order);
		}
	};
};

