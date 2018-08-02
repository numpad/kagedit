#include "JoystickController.hpp"

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

JoystickController::JoystickController(Entity *e, int id) {
	this->entity = e;
	this->joystick_id = id;
}
JoystickController::~JoystickController() {
	
}

void JoystickController::readInput() {
	if (sf::Joystick::isConnected(this->joystick_id)) {
		axis.x = sf::Joystick::getAxisPosition(this->joystick_id, sf::Joystick::Axis::X) * 0.01f;
		axis.y = sf::Joystick::getAxisPosition(this->joystick_id, sf::Joystick::Axis::Y) * 0.01f;

		if (glm::length(axis) > 1.0f)
			axis = glm::normalize(axis);

		static float s = 1.0f, b = 0.0f, c = 1.0f, d = 1.0f;
		static int exp = 4;
		axis = easeInOut(axis, b, c, d, (float)exp) * s;
	} else {
		axis.x = axis.y = 0.0f;
	}
}

void JoystickController::update(float dt) {
	entity->setVel(this->axis * 3.75f);
}
