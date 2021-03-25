#include "SceneSerializer.h"
#include "GameObject.h"
#include <cereal/archives/binary.hpp>
#include <sstream>
#include "Transform.h"
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/polymorphic.hpp>
#include "sdl_log.h"
#include <iostream>
#include <fstream>

struct SceneData {
public:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(_gameObjects); // serialize things by passing them to the archive
	}
};


void SceneSerializer::Serialize(std::string path)
{
	std::fstream file(path, std::ios::out);
	SceneData sd;
	sd._gameObjects = GameObject::_gameObjects;
	cereal::BinaryOutputArchive oarchive(file);
	oarchive(sd);
	file.close();
}

void SceneSerializer::Deserialize(std::string path)
{
	std::fstream file(path);
	cereal::BinaryInputArchive iarchive(file); // Create an input archive
	SceneData sd;
	iarchive(sd); // Read the data from the archive
	SDL_Log(sd._gameObjects[0]->_tag.c_str());
	file.close();
}
