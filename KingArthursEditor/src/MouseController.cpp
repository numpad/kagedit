#include "MouseController.hpp"

MouseController::MouseController(Entity *entity, sf::RenderWindow *window) {
	this->entity = entity;
	this->window = window;
}

void MouseController::readInput() {
	sf::Vector2i mpos = sf::Mouse::getPosition(*this->window);

	sf::Vector2f mouse_worldcoords = this->window->mapPixelToCoords(mpos);
	this->mousepos = glm::vec2(
		mouse_worldcoords.x,
		mouse_worldcoords.y
	);

}

void MouseController::update(float dt) {
	(void)dt;
	this->entity->setViewTarget(this->mousepos);
}
