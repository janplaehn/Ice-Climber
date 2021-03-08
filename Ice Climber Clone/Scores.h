#pragma once
class Scores
{
public:
	static int _eggplants;
	static int _nitpickers;
	static int _ice;
	static int _tiles;
	static bool _hasBonus;

	static void Reset();
	static int CalculateTotal();
};

