#include "Counter.h"
#include "Text.h"
#include "ComponentEssentials.h"

void Counter::BeginPlay()
{
	_text = GetComponent<Text>();
	_source = GetComponent<AudioSource>();
	_text->_text = ToString(0, _digitCount);
}

void Counter::Update()
{
	_timer += GameTime::_delta;
	if (_timer < _delay) return;

	if (_timer - GameTime::_delta < _delay) {
		_source->Play();
	}

	_currentNumber += _speed * GameTime::_delta * _targetNumber;
	if (_currentNumber >= _targetNumber) {
		_currentNumber = _targetNumber;
		_source->Stop();
	}

	_text->_text = ToString((int)_currentNumber, _digitCount);
}

std::string Counter::ToString(int number, int digitCount)
{
	std::string string = std::to_string(number);
	int length = string.size();
	for (int i = 0; i < digitCount - length; i++)
	{
		string = '0' + string;
	}
	return string;
}

void Counter::SetTargetNumber(float number)
{
	_targetNumber = number;
}

void Counter::SetDigitCount(float count)
{
	_digitCount = count;
}

void Counter::SetDelay(float delay)
{
	_delay = delay;
}

void Counter::SetSpeed(float speed)
{
	_speed = speed;
}