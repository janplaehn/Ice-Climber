#pragma once
class GameTime
{
public:
	// Return the total time spent in the game, in seconds.
	static float GetElapsedTime();

	static float _timeScale;
};

