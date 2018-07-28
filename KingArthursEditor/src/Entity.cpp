#include "Entity.hpp"

/********************\
* protected methods *
\********************/

/**
 * @brief Set the entitys current texture.
 *
 * 
 * @param [in] texture The texture to set.
 * @param origin Origin of the sprite: left-top=(0, 0), right-bottom=(1, 1).
 */
void Entity::setTexture(const sf::Texture &texture, glm::vec2 origin) {
	this->sprite.setTexture(texture);
	sf::Vector2f center(texture.getSize().x * origin.x, texture.getSize().y * origin.y);
	this->sprite.setOrigin(center);
}

void Entity::updatePhysics(float dt_seconds) {
	/* calculate new position TODO: */
	this->pos += this->vel * (dt_seconds * 60.0f);
	this->vel *= 0.935f;
}

Entity::Entity() {

}


/******************\
 * public methods *
\******************/

Entity::~Entity() {

}

float Entity::distanceTo(Entity &other) {
	return glm::distance(this->getPos(), other.getPos());
}

glm::vec2 Entity::getPos() {
	return this->pos;
}

void Entity::setPos(glm::vec2 pos) {
	this->pos = pos;
}

glm::vec2 Entity::getVel() {
	return this->vel;
}

void Entity::setVel(glm::vec2 vel) {
	this->vel = vel;
}

glm::vec2 Entity::getViewDirection() {
	return this->view_dir;
}

/**
 * @brief Returns the angle the entity is currently looking in.
 * 
 * Get the angle oriented to base_dir in radians.
 *
 * @param base_dir The base direction.
 * @returns The angle of the viewing direction (radians).
 */
float Entity::getViewAngle(glm::vec2 base_dir) {
	return glm::orientedAngle(base_dir, this->view_dir);
}


/**
* @brief Set View Target in World Space.
*
* Rotates the player towards the targets position.
*
* @param target_pos Position (in Worldspace).
*/
void Entity::setViewTarget(glm::vec2 target_pos) {
	glm::vec2 dir = target_pos - this->pos;
	this->view_dir = glm::normalize(dir);
}

/**
* @brief Set View direction.
*
* Rotate to this angle.
*
* @param target_dir Direction.
*/
void Entity::setViewDirection(glm::vec2 target_dir) {
	constexpr float STICK_DEAD_RADIUS = 0.3f;
	if (glm::length(target_dir) < STICK_DEAD_RADIUS)
		return; /* return without updating target dir */
	this->view_dir = glm::normalize(target_dir);
}

void Entity::onCollect(Item &item) {
}

/**
 * @brief Update the entity
 *
 * 
 * @param dt Delta Time for variable timestep, in Seconds.
 */
void Entity::update(float dt) {

}

void Entity::draw(sf::RenderTarget &target) {
	this->sprite.setPosition(this->pos.x, this->pos.y);
	this->sprite.setRotation(glm::degrees(this->getViewAngle()));
	target.draw(this->sprite);
}
