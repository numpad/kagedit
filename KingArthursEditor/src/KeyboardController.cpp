#include "KeyboardController.hpp"

float KeyboardController::isKeyDown(std::string key) {
	auto search = this->keymap.find(key);
	if (search == this->keymap.end()) {
		/* key not found in keymap, default to not-pressed */
		return 0.0f;
	}

	return sf::Keyboard::isKeyPressed(search->second) ? 1.0f : 0.0f;
}

KeyboardController::KeyboardController(Entity *e) {
	this->entity = e;

	mapKey("up", sf::Keyboard::W);
	mapKey("down", sf::Keyboard::S);
	mapKey("left", sf::Keyboard::A);
	mapKey("right", sf::Keyboard::D);
}

void KeyboardController::mapKey(const std::string name, const sf::Keyboard::Key key) {
	this->keymap[name] = key;
}

void KeyboardController::readInput() {
	this->axis.x = this->isKeyDown("right");
	this->axis.x -= this->isKeyDown("left");
	this->axis.y = this->isKeyDown("down");
	this->axis.y -= this->isKeyDown("up");

	if (glm::length(this->axis) > 1.0f) {
		this->axis = glm::normalize(this->axis);
	}
}

void KeyboardController::update(float dt_seconds) {
	entity->setAcc(this->axis * 0.75f);
}

