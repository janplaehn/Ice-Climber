#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	Transform(const std::shared_ptr<Transform> transform);
	virtual void Update() {};

	Vector2D _position = Vector2D::Zero();
	float _rotation;
	Vector2D _scale;
	Vector2D _pivot;
	SDL_RendererFlip _flipType;
	bool _isInScreenSpace = false;

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this), _isInScreenSpace); // serialize things by passing them to the archive
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(Transform, "Transform");
CEREAL_REGISTER_POLYMORPHIC_RELATION(Transform, Component)