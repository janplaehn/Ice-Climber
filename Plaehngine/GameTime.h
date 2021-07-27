#pragma once
class GameTime
{
public:
	static void Init();

	static float SDLTicks();
	static void Run();

	static float _scale;
	static float _delta;
	static float _unscaledDelta;
	static float _timeSinceGameLoad;
	static float _unscaledTimeSinceGameLoad;

private:
	static float _lastTime;
};

