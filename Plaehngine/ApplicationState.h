#pragma once
class ApplicationState
{
public:
	static void Start();

	static bool IsRunning();

private:
	static bool _isRunning;
};

