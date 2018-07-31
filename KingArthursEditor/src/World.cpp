#include "World.hpp"

void World::removeCollectedItems() {
	for (size_t i = 0; i < this->items.size(); ++i) {
		Item *item = this->items.at(i);
		if (item->isCollected()) {
			items.erase(this->items.begin() + i);
			continue;
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
	for (Entity *e : entities)
		delete e;
	
	for (Item *i : items)
		delete i;
}

void World::spawnEntity(Entity *e) {
	this->entities.push_back(e);
}

void World::spawnItem(Item *i) {
	this->items.push_back(i);
}

sf::View & World::getCamera() {
	return this->camera;
}

void World::update(float dt, sol::state &lua) {
	this->removeCollectedItems();

	for (auto it = entities.begin(); it != entities.end(); ++it) {
		Entity *entity = *it;
		entity->update(dt);
		for (auto item_it = items.begin(); item_it != items.end(); ++item_it) {
			Item *item = *item_it;
			if (!item->isCollected() && item->isCollectableBy(*entity)) {
				item->onEntityNear(*entity, lua);
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
