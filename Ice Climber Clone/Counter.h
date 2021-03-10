#pragma once
#include "Component.h"
#include "Text.h"

class Counter : public Component
{
	virtual void Update() override;
	virtual void BeginPlay() override;

public:
	int _targetNumber = 0;
	int _digitCount = 6;
	float _delay = 0;
	float _speed = 4;
	static std::string ToString(int number, int digitCount);

private:
	float _timer = 0;
	float _currentNumber = 0;
	Text* _text = nullptr;
};

