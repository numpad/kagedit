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

World::World(sf::RenderWindow &window)
	: window(window)
{
	this->camera.reset(sf::FloatRect(0.0f, 0.0f, (float)window.getSize().x, (float)window.getSize().y));
	this->window.setView(this->camera);
}

World::~World() {
	//this->destroy();
}

void World::destroy() {
	puts("WORLD DESTRUCT start <");
	printf("  #items=%d\n", (int)items.size());
	for (size_t i = 0; i < items.size(); ++i)    delete items.at(i);
	printf("  #entities=%d\n", (int)entities.size());
	for (size_t i = 0; i < entities.size(); ++i) delete entities.at(i);
	entities.clear();
	items.clear();
	puts("WORLD DESTRUCT end   >");
}

void World::spawnEntity(Entity *e) {
	this->entities.push_back(e);
}

void World::spawnItem(Item *i) {
	this->items.push_back(i);
}

sf::View &World::getCamera() {
	return this->camera;
}

void World::update(float dt) {
	this->removeCollectedItems();

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

void World::render() {
	this->window.setView(this->camera);

	for (Item *item : this->items) {
		item->draw(window);
	}
	for (Entity *entity : this->entities) {
		entity->draw(window);
	}
}
