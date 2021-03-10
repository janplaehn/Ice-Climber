#pragma once
class GameTime
{
public:
	static void Init();

	static float TimeSinceGameLoad();
	static void Run();

	static float _scale;
	static float _delta;

private:
	static float _lastTime;
};

