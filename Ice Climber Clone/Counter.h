#pragma once
#include "Component.h"

class Text;
class AudioSource;

class Counter : public Component
{
public:

	void SetTargetNumber(float number);
	void SetDigitCount(float count);
	void SetDelay(float delay);
	void SetSpeed(float speed);

	virtual void Update() override;
	virtual void BeginPlay() override;

private:

	int _targetNumber = 0;
	int _digitCount = 6;
	float _delay = 0;
	float _speed = 4;
	static std::string ToString(int number, int digitCount);

	float _timer = 0;
	float _currentNumber = 0;
	std::shared_ptr<Text> _text = nullptr;
	std::shared_ptr<AudioSource> _source = nullptr;
};

