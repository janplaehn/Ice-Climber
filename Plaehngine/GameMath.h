#pragma once

class GameMath {
public:
	template <typename T> 
	static int Sign(T val) {
		return (T(0) < val) - (val < T(0));
	}

	template <typename T>
	static int Clamp(T value, T min, T max) {
		return std::min(std::max(value, min), max);
	}

};