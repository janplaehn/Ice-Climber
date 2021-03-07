#pragma once
#include <vector>

class Input
{
public:
	static void Init(class Plaehngine* engine);

	enum KeyStatus {
		IDLE,
		PRESSED,
		HELD,
		RELEASED,
		UNDEFINED
	};

	struct Key {
		int _scanCode = 0;
		KeyStatus _status = IDLE;
	};

	static std::vector<Key> _keys;

	static void ProcessInput();

	static KeyStatus GetKeyStatus(int scanCode);

	static void WatchKey(int scanCode);

	static void Quit();

private:
	static class Plaehngine* _engine;
};

