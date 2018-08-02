#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_impl.h>
#include <sqlite3/sqlite3.h>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include <sol.hpp>
#include <tinydir.h>

#include "Entity.hpp"
#include "Player.hpp"
#include "Item.hpp"

class World {
	sf::RenderWindow &window;
	sf::View camera;
	
public:
	std::vector<Item *> items;
	std::vector<Entity *> entities;


	World(sf::RenderWindow &window);
	~World();
	
	void destroy();

	void removeCollectedItems();

	void spawnEntity(Entity *e);
	void spawnItem(Item *i);

	sf::View &getCamera();

	void update(float dt);
	void render();
};

#endif
