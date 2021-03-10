#pragma once
#include "Component.h"

class Text;

class BonusTimer : public Component
{
public:

	void SetTime(float time);
	void SetIsCounting(bool shouldCount);

protected:

	virtual void Update() override;
	virtual void BeginPlay() override;

	void ApplyText();
	void CheckTimerEnd();

	float _currentTime = 40;
	Text* _text = nullptr;
	bool _isCounting = true;
};

