#include "MouseController.hpp"

MouseController::MouseController(Entity *entity, sf::Window *window) {
	this->entity = entity;
	this->window = window;
}

void MouseController::readInput() {
	this->mousepos = glm::vec2(
		(float)sf::Mouse::getPosition(*this->window).x,
		(float)sf::Mouse::getPosition(*this->window).y
	);

}

void MouseController::update(float dt) {
	(void)dt;
	this->entity->setViewTarget(this->mousepos);
}
