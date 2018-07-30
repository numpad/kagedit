#include "Player.hpp"

void Player::setController(Controller *c) {
	for (size_t i = 0; i < this->controllers.size(); ++i) {
		delete this->controllers.at(i);
	}
	this->controllers.clear();

	this->addController(c);
}

void Player::addController(Controller *c) {
	this->controllers.push_back(c);
}

Player::Player(glm::vec2 pos, sf::RenderWindow *window) {
	this->setPos(pos);
	this->drag = 0.75f;

	/* load texture and sprite */
	assert(this->skin_stand.loadFromFile("assets/images/kenney-topdown/Survivor 1/survivor1_stand.png"));
	assert(this->skin_gun.loadFromFile("assets/images/kenney-topdown/Survivor 1/survivor1_gun.png"));
	this->skin_stand.setSmooth(true);
	this->skin_gun.setSmooth(true);

	/* center origin */
	this->setTexture(this->skin_stand);

	/* controls */
	this->addController(new KeyboardController(this));
	this->addController(new MouseController(this, window));
	//this->addController(new JoystickController(this, 0));
}

Player::~Player() {
	this->setController(nullptr);
}

void Player::update(float dt) {
	for (size_t i = 0; i < this->controllers.size(); ++i) {
		controllers.at(i)->readInput();
		controllers.at(i)->update(dt);
	}

	this->updatePhysics(dt);
}

