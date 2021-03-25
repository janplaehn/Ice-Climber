#pragma once
#include "Button.h"

class AudioSource;

class IceClimberButton : public Button
{
public:
	virtual void Awake() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void OnPressed() override;
	virtual void OnSelected() override;
	virtual void OnDeselected() override;
	virtual void OnDeactivate() override;
	virtual void OnActivate() override;
protected:

	const Color COLOR_SELECTED = Color::White();
	const Color COLOR_DEFAULT = Color(128, 128, 128);

	std::shared_ptr<AudioSource> _source = nullptr;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Button>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(IceClimberButton, "IceClimberButton")
CEREAL_REGISTER_POLYMORPHIC_RELATION(IceClimberButton, Button)