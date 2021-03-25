#pragma once
#include "Component.h"

class Text;

class BonusTimer : public Component
{
public:

	void SetTime(float time);
	void SetIsCounting(bool shouldCount);

	virtual void Update() override;
	virtual void BeginPlay() override;

protected:

	void ApplyText();
	void CheckTimerEnd();

	float _currentTime = 40;
	std::shared_ptr<Text> _text = nullptr;
	bool _isCounting = true;

public:
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(cereal::base_class<Component>(this));
	}
};

CEREAL_REGISTER_TYPE_WITH_NAME(BonusTimer, "BonusTimer")
CEREAL_REGISTER_POLYMORPHIC_RELATION(BonusTimer, Component)