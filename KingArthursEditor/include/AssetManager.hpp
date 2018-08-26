#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <SFML/Graphics.hpp>

class AssetManager {

	static std::unordered_map<std::string, sf::Texture *> textures;

	static sf::Texture *loadAsset(std::string path);

public:

	static sf::Texture *load(std::string path);
	static void destroy();

};

#endif
