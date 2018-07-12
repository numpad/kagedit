#include "Player.hpp"

Player::Player(glm::vec2 pos) {
	this->setPos(pos);

	/* load texture and sprite */
	assert(this->skin_stand.loadFromFile("assets/images/kenney-topdown/Survivor 1/survivor1_stand.png"));
	assert(this->skin_gun.loadFromFile("assets/images/kenney-topdown/Survivor 1/survivor1_gun.png"));
	this->skin_stand.setSmooth(true);
	this->skin_gun.setSmooth(true);

	/* center origin */
	this->setTexture(this->skin_stand);

}

static float easeInOut(float t, float b, float c, float d, float exp) {
	// t : current time (frames/ms)
	// b : start value
	// c : change in value
	// d : duration (frames/ms)

	t /= d / 2.0f;
	if (t < 1.0f) return c / 2.0f * pow(t, exp) + b;
	t -= 2.0f;
	return -c / 2.0f * (powf(t, exp) - 2.0f) + b;
}

static glm::vec2 easeInOut(glm::vec2 axis, float b, float c, float d, float exp) {
	float len = glm::length(axis);
	float fact = easeInOut(len, 0.0f, 1.0f, 1.0f, exp);

	return glm::vec2(
		axis.x * fact,
		axis.y * fact
	);
}

void Player::update(float dt) {
	glm::vec2 axis(0.0f);
	if (sf::Joystick::isConnected(this->joystick_id)) {
		axis.x = sf::Joystick::getAxisPosition(this->joystick_id, sf::Joystick::Axis::X) * 0.01f;
		axis.y = sf::Joystick::getAxisPosition(this->joystick_id, sf::Joystick::Axis::Y) * 0.01f;
		
		if (glm::length(axis) > 1.0f)
			axis = glm::normalize(axis);
		
		float axis_len_raw = glm::length(axis);

		static float s = 1.0f, b = 0.0f, c = 1.0f, d = 1.0f;
		static int exp = 4;
		axis = easeInOut(axis, b, c, d, exp) * s;
	}

	this->vel = axis * 3.75f;
	this->updatePhysics(dt);
	this->sprite.setPosition(this->pos.x, this->pos.y);
	
	/* set sprites rotation */
	static glm::vec2 texture_viewdir(1.0f, 0.0f);
	this->sprite.setRotation(glm::degrees(this->getViewAngle(texture_viewdir)));

}
