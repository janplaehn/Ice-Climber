#include "BonusTimer.h"
#include "Scenes.h"
#include "ScoreScreen.h"
#include <iomanip>
#include <sstream>

void BonusTimer::Update()
{
	if (!_enabled || !_shouldCount) return;
	_currentTime -= GameTime::_delta;
	if (_currentTime < 0) {
		_currentTime = 0;
		Scenes::LoadScene<ScoreScreen>();
	}
	if (_text) {
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << _currentTime;
		std::string s = stream.str();
		_text->_text = s;
	}
}
