#pragma once

#include "Component.h"
class BonusTimer : public Component
{
	virtual void Update() override;

public:
	float _currentTime = 40;
	class Text* _text;
	bool _shouldCount = true;
};

