#include "Item.hpp"

void Item::animate(float dt_seconds) {
	this->sprite.rotate(0.975f);
	float scale = cosf(this->animation_time += this->animation_timestep) / 10.0f + 1.0f;
	this->highlight.setScale(scale, scale);
}

Item::Item() {
	this->setName("entity_item");
	this->hightlight_texture = AssetManager::load("assets/images/effects/item_highlight.png");

	this->hightlight_texture->setSmooth(true);
	this->highlight.setTexture(*this->hightlight_texture);
	sf::Vector2f center(this->hightlight_texture->getSize().x * 0.5f, this->hightlight_texture->getSize().y * 0.5f);
	this->highlight.setOrigin(center);
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
	if (entity.hasEvents())
		entity.getEvents().callEvent("on_collect", this);

	/* check again, maybe the entity script denied pickup */
	if (this->isCollected()) {
		if (this->hasEvents())
			this->events->callEvent("on_collected", &entity);
	}
}

void Item::update(float dt_seconds) {
	this->animate(dt_seconds);
	Entity::update(dt_seconds);
}

void Item::draw(sf::RenderTarget &target) {
	this->highlight.setPosition(this->getPos().x, this->getPos().y);
	this->sprite.setPosition(this->getPos().x, this->getPos().y);
	target.draw(this->highlight);
	target.draw(this->sprite);
}
