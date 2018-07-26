#ifndef MOUSECONTROLLER_HPP
#define MOUSECONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "Controller.hpp"
#include "Entity.hpp"

class MouseController : public Controller {
private:
	glm::vec2 mousepos;
	sf::Window *window = nullptr;

protected:
	
public:

	MouseController(Entity *entity, sf::Window *window);

	void readInput();
	void update(float dt);
};

#endif
