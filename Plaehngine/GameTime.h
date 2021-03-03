#pragma once
class GameTime
{
public:
	static void Init();

	// Return the total time spent in the game, in seconds.
	static float GetElapsedTime();
	static void Run();

	static float _scale;
	static float _delta;

private:
	static float _lastTime;
};

