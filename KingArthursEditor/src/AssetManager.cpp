#include "AssetManager.hpp"
std::unordered_map<std::string, sf::Texture *> AssetManager::textures;

sf::Texture *AssetManager::loadAsset(std::string path) {
	sf::Texture *tex = new sf::Texture();

	if (!tex->loadFromFile(path)) {
		printf("[AssetManager] Cannot load \"%s\"!\n", path.c_str());
		return nullptr;
	}

	AssetManager::textures.insert(std::make_pair(path, tex));
	
	return tex;
}

sf::Texture *AssetManager::load(std::string path) {
	auto search = AssetManager::textures.find(path);
	if (search == AssetManager::textures.end()) {
		printf("[AssetManager] Don't have \"%s\" in RAM. Loading...\n", path.c_str());
		return AssetManager::loadAsset(path);
	}

	return search->second;
}

void AssetManager::destroy() {
	for (auto it = AssetManager::textures.begin(); it != AssetManager::textures.end(); ++it) {
		delete it->second;
	}
	
	AssetManager::textures.clear();
}
