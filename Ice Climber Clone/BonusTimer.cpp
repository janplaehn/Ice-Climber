#include "BonusTimer.h"
#include "Scenes.h"
#include "ScoreScene.h"
#include "Scores.h"
#include <iomanip>
#include <sstream>

void BonusTimer::BeginPlay()
{
	_text = GetComponent<Text>();
}

void BonusTimer::Update()
{
	if (!_enabled || !_isCounting) return;

	_currentTime -= GameTime::_delta;

	CheckTimerEnd();
	ApplyText();
}

void BonusTimer::ApplyText()
{
	if (!_text) return;

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << _currentTime;
	std::string s = stream.str();

	int length = s.size();
	for (int i = 0; i < 4 - length; i++)
	{
		s = '0' + s;
	}

	_text->_text = s;
}

void BonusTimer::CheckTimerEnd()
{
	if (_currentTime >= 0) return;

	_currentTime = 0;
	Scores::_hasBonus = false;
	Scenes::LoadScene<ScoreScene>();
}

void BonusTimer::SetTime(float time)
{
	_currentTime = time;
}

void BonusTimer::SetIsCounting(bool isCounting)
{
	_isCounting = isCounting;
}
