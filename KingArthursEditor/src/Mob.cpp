#include "Mob.hpp"

Mob::Mob(glm::vec2 pos) {
	this->setName("entity_mob");
	this->setPos(pos);
}

Mob::~Mob() {
	this->setController(nullptr);
}

size_t Mob::setController(Controller *c) {
	for (size_t i = 0; i < this->controllers.size(); ++i) {
		//delete this->controllers.at(i);
		this->deleteController(i);
	}
	this->controllers.clear();
	
	if (c != nullptr) {
		this->addController(c);
		return 0;
	}

	return 0;
}

size_t Mob::addController(Controller *c) {
	size_t i = this->controllers.size();
	this->controllers.push_back(c);
	return i;
}

void Mob::deleteController(size_t i) {
	delete this->controllers.at(i);
	this->controllers.erase(this->controllers.begin() + i);
}

void Mob::update(float dt) {
	for (size_t i = 0; i < this->controllers.size(); ++i) {
		controllers.at(i)->readInput();
		controllers.at(i)->update(dt);
	}

	Entity::update(dt);
}

