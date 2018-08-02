#include "Item.hpp"

void Item::animate(float dt_seconds) {
	this->sprite.rotate(0.975f);

	this->bgshape_radius_extra = sinf(this->animation_time) * this->animation_radius_max;
	this->bgshape.setRadius(this->bgshape_radius + this->bgshape_radius_extra);
	this->bgshape.setOrigin(sf::Vector2f(this->bgshape_radius + this->bgshape_radius_extra, this->bgshape_radius + this->bgshape_radius_extra));
	this->animation_time += this->animation_timestep * dt_seconds;
}

Item::Item() {
	this->setName("entity_item");

	this->bgshape.setRadius(this->bgshape_radius);
	this->bgshape.setOrigin(sf::Vector2f(this->bgshape_radius, this->bgshape_radius));

	this->bgshape.setFillColor(sf::Color(244, 244, 244, 66));
	this->bgshape.setOutlineColor(sf::Color(255, 255, 255, 77));
	
	this->bgshape.setOutlineThickness(3.0f);
}

Item::~Item() {
	
}

float Item::getCollectableRadius() {
	return this->collectableMagneticRadius;
}

bool Item::isCollectableBy(Entity &e) {
	return (this->distanceTo(e) <= this->getCollectableRadius());
}

bool Item::isCollected() {
	return this->collected;
}

void Item::setCollected(bool collected) {
	this->collected = collected;
}

void Item::onEntityNear(Entity &entity) {
	glm::vec2 to_entity = entity.getPos() - this->getPos();
	float dist = glm::length(to_entity);
	float move_vel = dist / 10.0f;

	if (dist < this->collectInRadius) {
		move_vel = 1.0f;
		this->onPickup(entity);
	} else {
		to_entity = glm::normalize(to_entity);
	}

	this->setVel(to_entity * move_vel);
}

void Item::onPickup(Entity &entity) {
	this->setCollected();

	// execute on pickup script
	entity.getEvents().callEvent("on_collect", this);
	/* check again, maybe the entity script denied pickup */
	if (this->isCollected())
		this->events->callEvent("on_collected", &entity);
}

void Item::update(float dt_seconds) {
	this->animate(dt_seconds);
	Entity::update(dt_seconds);
}

void Item::draw(sf::RenderTarget &target) {
	this->bgshape.setPosition(this->getPos().x, this->getPos().y);
	this->sprite.setPosition(this->getPos().x, this->getPos().y);
	target.draw(this->bgshape);
	target.draw(this->sprite);
}
