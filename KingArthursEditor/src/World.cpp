#include "World.hpp"

void World::removeCollectedItems() {
	for (auto it = this->items.begin(); it != this->items.end(); ++it) {
		Item *item = *it;
		if (item->isCollected()) {
			delete item;
			it = this->items.erase(it);
			if (it == this->items.end()) return;
		}
	}
}

World *World::load(std::string worldname, sol::state &lua) {
	/* build dir paths */
	char basepath[1024] = {0};
	sprintf(basepath, "assets/worlds/%s", worldname.c_str());
	char loader_path[1024] = {0};
	sprintf(loader_path, "%s/loader.lua", basepath);
	char data_path[1024] = {0};
	sprintf(data_path, "./%s/data/?.lua", basepath);
	
	World *w = new World();
	
	/* create lua state to load world */
	std::string old_require_path = lua["package"]["path"];
	char full_require_path[2048];
	sprintf(full_require_path, "%s;%s", data_path, old_require_path.c_str());

	/* set require path relative to  */
	lua["package"]["path"] = std::string(full_require_path);
	lua.script_file(loader_path);
	lua["package"]["path"] = std::string(old_require_path);
	
	return w;
}

World::World() {
	this->events = new EventManager();
}

World::~World() {
	//this->destroy();
}

void World::loadLayerFromLua(sol::table table, std::string tileset_path, int width, int height, int tilesize) {
	std::vector<TileMap::tile_type> tiles(table.size());
	for (size_t i = 0; i < table.size(); ++i) {
		tiles[i] = table[i + 1];
		tiles[i]--;
	}

	TileMap *tm = new TileMap();
	tm->load(
		tiles,
		AssetManager::load(tileset_path),
		width, height,
		tilesize
	);

	this->layers.push_back(tm);
}

EventManager &World::getEvents() {
	return *(this->events);
}

void World::destroy() {
	this->events->callEvent("on_destroy");

	for (TileMap *tm : this->layers) {
		delete tm;
	}
	puts("WORLD DESTRUCT start <");
	printf("  #items=%d\n", (int)items.size());
	for (size_t i = 0; i < items.size(); ++i)    delete items.at(i);
	printf("  #entities=%d\n", (int)entities.size());
	for (size_t i = 0; i < entities.size(); ++i) delete entities.at(i);
	entities.clear();
	items.clear();
	delete this->events;
	puts("WORLD DESTRUCT end   >");
}

void World::spawnEntity(Entity *e) {
	this->events->callEvent("on_spawnEntity", e);
	this->entities.push_back(e);
}

void World::spawnItem(Item *i) {
	this->events->callEvent("on_spawnItem", i);
	this->items.push_back(i);
}

sf::View &World::getCamera() {
	return this->camera;
}

void World::update(float dt) {
	this->removeCollectedItems();
	
	this->events->callEvent("on_update", dt);

	for (auto it = entities.begin(); it != entities.end(); ++it) {
		Entity *entity = *it;
		entity->update(dt);
		for (auto item_it = items.begin(); item_it != items.end(); ++item_it) {
			Item *item = *item_it;
			if (!item->isCollected() && item->isCollectableBy(*entity)) {
				item->onEntityNear(*entity);
			}
		}
	}
	for (Item *item : items) {
		item->update(dt);
	}

}

void World::render(sf::RenderTarget &target) {
	target.setView(this->camera);
	
	for (TileMap *tilemap : this->layers) {
		target.draw(*tilemap);
	}

	for (Item *item : this->items) {
		item->draw(target);
	}
	for (Entity *entity : this->entities) {
		entity->draw(target);
	}
}
