#ifndef KeyboardController_HPP
#define KeyboardController_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Entity.hpp"
#include "Controller.hpp"

class KeyboardController : public Controller {
private:
	glm::vec2 axis = glm::vec2(0.0f);
	bool gotActiveInput = false;

protected:
	std::unordered_map<std::string, sf::Keyboard::Key> keymap;
	
	float isKeyDown(std::string key);
public:
	KeyboardController(Entity *e);
	
	/* configure */
	void mapKey(const std::string name, const sf::Keyboard::Key key);
	
	void readInput();
	void update(float dt_seconds);
};

#endif

