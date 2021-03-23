#pragma once
#include <string>

class SceneSerializer
{
public:
	static void Serialize(std::string path);
	static void Deserialize(std::string path);
};

