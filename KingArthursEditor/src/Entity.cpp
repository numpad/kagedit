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
	printf("setting texture: %dx%d\n", texture.getSize().x, texture.getSize().y);
	this->sprite.setTexture(texture, true);
	sf::Vector2f center(texture.getSize().x * origin.x, texture.getSize().y * origin.y);
	this->sprite.setOrigin(center);
}

void Entity::updatePhysics(float dt_seconds) {
	/* quit early if at least one event exists  */
	if (this->hasEvents()) {
		if (this->events->callEvent("updatephysics", dt_seconds)) {
			return;
		}
	}
	
	glm::vec2 inv_vel(0.0f);
	if (glm::length(this->vel) > 0.01f) {
		inv_vel = -this->vel;
		inv_vel = (inv_vel) * 0.125f;

		if (glm::length2(inv_vel) > glm::length2(this->vel))
			inv_vel = -this->vel;
	}

	/* calculate new position TODO: */
	this->vel += this->acc * (dt_seconds * 60.0f);
	this->pos += this->vel * (dt_seconds * 60.0f);
	
	// todo: remove
	//this->vel *= 0.95f;
	this->vel += inv_vel * (dt_seconds * 60.0f);

	this->acc = glm::vec2(0.0f);
}

Entity::Entity() {
	printf("[!!!] entity init\n");
	//this->events = new EventManager();
}


/******************\
 * public methods *
\******************/

Entity::~Entity() {
	if (this->hasEvents())
		this->events->callEvent("on_destroy");
	printf("[!!!] destructing entity:%s %g,%g\n", this->name.c_str(), this->pos.x, this->pos.y);
	delete this->events;
}

float Entity::distanceTo(Entity &other) {
	return glm::distance(this->getPos(), other.getPos());
}

void Entity::setTextureColor(float r, float g, float b, float a) {
	this->sprite.setColor(sf::Color(
		r * 255, g * 255, b * 255, a * 255
	));
}

void Entity::loadTexture(std::string name) {
	sf::Texture *tex = AssetManager::load("assets/" + name);
	if (tex != nullptr)
		this->setTexture(*tex, glm::vec2(0.5f));
}

void Entity::setName(std::string name) {
	this->name = name;
}

std::string Entity::getName() {
	return this->name;
}

EventManager &Entity::getEvents() {
	if (!this->hasEvents()) {
		/* create eventmanager if none exists */
		this->events = new EventManager();
	}
	return *(this->events);
}

bool Entity::hasEvents() {
	return (this->events != nullptr);
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
	if (this->hasEvents())
		this->events->callEvent("on_update", dt);
	
	this->updatePhysics(dt);
}

void Entity::draw(sf::RenderTarget &target) {
	this->sprite.setPosition(this->pos.x, this->pos.y);
	this->sprite.setRotation(glm::degrees(this->getViewAngle()));
	target.draw(this->sprite);
}
