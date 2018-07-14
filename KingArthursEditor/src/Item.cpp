#include "Item.hpp"

void Item::animate(float dt_seconds) {
	this->sprite.rotate(0.975f);

	this->bgshape_radius_extra = sinf(this->animation_time) * this->animation_radius_max;
	this->bgshape.setRadius(this->bgshape_radius + this->bgshape_radius_extra);
	this->bgshape.setOrigin(sf::Vector2f(this->bgshape_radius + this->bgshape_radius_extra, this->bgshape_radius + this->bgshape_radius_extra));
	this->animation_time += this->animation_timestep * dt_seconds;
}

Item::Item() {
	this->bgshape.setRadius(this->bgshape_radius);
	this->bgshape.setOrigin(sf::Vector2f(this->bgshape_radius, this->bgshape_radius));

	this->bgshape.setFillColor(sf::Color(244, 244, 244, 66));
	this->bgshape.setOutlineColor(sf::Color(255, 255, 255, 77));
	
	this->bgshape.setOutlineThickness(3.0f);
}

float Item::getCollectableRadius() {
	return this->collectableRadius;
}

bool Item::isCollectableBy(Entity &e) {
	return (this->distanceTo(e) <= this->getCollectableRadius());
}

void Item::onEntityNear(Entity &entity) {
	glm::vec2 to_entity = entity.getPos() - this->getPos();
	constexpr float move_speed = 2.85f;

	if (glm::length(to_entity) <= move_speed) {
		to_entity = glm::vec2(0.0f);
	} else {
		to_entity = glm::normalize(to_entity);
	}

	this->setVel(to_entity * move_speed);
}

void Item::update(float dt_seconds) {
	this->animate(dt_seconds);
	this->updatePhysics(dt_seconds);
	this->bgshape.setPosition(this->getPos().x, this->getPos().y);
	this->sprite.setPosition(this->getPos().x, this->getPos().y);
}

void Item::draw(sf::RenderTarget &target) {
	target.draw(this->bgshape);
	target.draw(this->sprite);
}
