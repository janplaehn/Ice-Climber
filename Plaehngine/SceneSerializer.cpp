#include "SceneSerializer.h"
#include "Serializable.h"
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/complex.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/polymorphic.hpp>
#include <sstream>
#include <iostream>
#include <fstream>

struct SceneData {
public:
	std::vector<std::shared_ptr<GameObject>> _gameObjects;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(_gameObjects);
	}
};


void SceneSerializer::Serialize(std::string path)
{
	std::ofstream file(path, std::ios::out, std::ios::binary);
	SceneData sceneData;
	sceneData._gameObjects = GameObject::_gameObjects;
	cereal::BinaryOutputArchive oarchive(file);
	oarchive(sceneData);
	file.close();
}

void SceneSerializer::Deserialize(std::string path)
{
	std::ifstream file(path, std::ios::in, std::ios::binary);
	cereal::BinaryInputArchive iarchive(file);
	SceneData sceneData;
	iarchive(sceneData);
	file.close();
}
