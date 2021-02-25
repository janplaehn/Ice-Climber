#pragma once
class Input
{
	friend class Plaehngine;
public:

	struct KeyStatus
	{
		bool _fire; // space
		bool _left; // left arrow
		bool _right; // right arrow
		bool _escape; // escape button
	};

	static void ProcessInput();

	static Input::KeyStatus GetKeyStatus();

private:
	static void Init();

	static KeyStatus _key;
};
