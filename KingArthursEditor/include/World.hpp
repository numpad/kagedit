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
#include "EventManager.hpp"
#include "TileMap.hpp"

#include "LuaWrapper.hpp"

class World {
	sf::View camera;
	std::string name = "unnamed_world";

	std::vector<TileMap *> layers;
	
	EventManager *events;

public:
	std::vector<Item *> items;
	std::vector<Entity *> entities;
	
	static World *load(std::string worldname, sol::state &lua);

	World();
	~World();
	
	void loadLayerFromLua(sol::table table, std::string tileset_path, int width, int height, int tilesize);

	EventManager &getEvents();

	void destroy();
	void removeCollectedItems();

	void spawnEntity(Entity *e);
	void spawnItem(Item *i);

	sf::View &getCamera();

	void update(float dt);
	void render(sf::RenderTarget &target);
};

#endif
