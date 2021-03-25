#pragma once
#include "Component.h"
#include "Transform.h"
#include "Graphics.h"

class Renderer :  public Component
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	int _order = 0;
	Color _tint = Color::White();

	static std::vector<std::shared_ptr<Renderer>> _renderers;
	static void SortRenderers();

private:
	struct FurtherBack
	{
		inline bool operator() (std::shared_ptr<Renderer> sr1, std::shared_ptr<Renderer> sr2) {
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