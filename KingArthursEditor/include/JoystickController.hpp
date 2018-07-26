#ifndef JOYSTICKCONTROLLER_HPP
#define JOYSTICKCONTROLLER_HPP

#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "Controller.hpp"
#include "Entity.hpp"

class JoystickController : public Controller {
private:
	glm::vec2 axis = glm::vec2(0.0f);
	int joystick_id = -1;

protected:
	

public:
	JoystickController(Entity *e, int id);

	void readInput();
	void update(float dt);
};

#endif
