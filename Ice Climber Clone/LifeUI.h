#pragma once
#include "Component.h"

class Renderer;

class LifeUI : public Component
{
public:

	void UpdateLifeCounter(int amount);
	void AddRenderer(std::shared_ptr<Renderer> renderer);

private:

	std::vector<std::shared_ptr<Renderer>> _lifeRenderers;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(LifeUI, "LifeUI")
CEREAL_REGISTER_POLYMORPHIC_RELATION(LifeUI, Component)