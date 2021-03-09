#pragma once

#include "Component.h"
class BonusTimer : public Component
{
	virtual void Update() override;

public:
	float _currentTime = 40;
	class Text* _text = nullptr;
	bool _shouldCount = true;
};

