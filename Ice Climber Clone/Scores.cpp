#include "Scores.h"

void Scores::Reset()
{
    _eggplants = 0;
    _nitpickers = 0;
    _ice = 0;
    _tiles = 0;
}

int Scores::CalculateTotal()
{
    int bonus = _hasBonus ? 3000 : 0;
    return _eggplants * 300 + _nitpickers * 800 + _ice * 400 + _tiles * 10 + bonus;
}

int Scores::_eggplants = 0;
int Scores::_nitpickers = 0;
int Scores::_ice = 0;
int Scores::_tiles = 0;
bool Scores::_hasBonus = false;