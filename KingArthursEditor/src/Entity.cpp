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
	/* calculate drag force */
	float speed = glm::length2(this->vel);
	float dragMag = this->dragCoeff * speed;
	glm::vec2 drag = this->vel;
	drag *= -1.0f;
	drag = glm::normalize(drag);
	drag *= dragMag;
	
	//if (glm::length(this->vel) > 0.000001f)
		//this->acc += drag;

	/* calculate new position TODO: */
	this->vel += this->acc * (dt_seconds * 60.0f);
	this->pos += this->vel * (dt_seconds * 60.0f);
	
	// todo: remove
	this->vel *= 0.95f;

	this->acc = glm::vec2(0.0f);
}

Entity::Entity() {
	printf("[!!!] entity init\n");
	this->events = new EventManager();
}


/******************\
 * public methods *
\******************/

Entity::~Entity() {
	this->events->callEvent("on_destroy");
	printf("[!!!] destructing entity:%s %g,%g\n", this->name.c_str(), this->pos.x, this->pos.y);
	delete this->events;
}

float Entity::distanceTo(Entity &other) {
	return glm::distance(this->getPos(), other.getPos());
}

void Entity::setName(std::string name) {
	this->name = name;
}

std::string Entity::getName() {
	return this->name;
}

EventManager &Entity::getEvents() {
	return *(this->events);
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

float Entity::getDrag() {
	return this->dragCoeff;
}

void Entity::setDrag(float drag) {
	this->dragCoeff = drag;
}

glm::vec2 Entity::getAcc() {
	return this->acc;
}

void Entity::setAcc(glm::vec2 acc) {
	this->acc = acc;
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

/**
 * @brief Update the entity
 *
 * 
 * @param dt Delta Time for variable timestep, in Seconds.
 */
void Entity::update(float dt) {
	this->events->callEvent("on_update", dt);
	this->updatePhysics(dt);
}

void Entity::draw(sf::RenderTarget &target) {
	this->sprite.setPosition(this->pos.x, this->pos.y);
	this->sprite.setRotation(glm::degrees(this->getViewAngle()));
	target.draw(this->sprite);
}
