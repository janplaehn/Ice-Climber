#pragma once
#include <vector>
#include <SDL_scancode.h>
#include <SDL_mouse.h>


struct Vector2D;

class Input
{
public:
	static void Init();

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

	static std::vector<Key> _buttons;

	static void ProcessInput();

	static KeyStatus GetKeyStatus(int scanCode);

	static KeyStatus GetButtonStatus(int button);

	static void WatchButton(int button);

	static void WatchKey(int scanCode);

	static void Quit();

	static Vector2D _mousePosition;
	static Vector2D _mouseDelta;
	static Vector2D _mouseWheelDelta;
	static bool _isQueueingQuit;
};

