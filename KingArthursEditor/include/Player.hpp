#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <math.h>
#include <assert.h>
#include <imgui.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.hpp"
#include "Controller.hpp"
#include "KeyboardController.hpp"

class Player : public Entity {
	sf::Texture skin_stand, skin_gun;
	
	//int joystick_id = 0;
	
	Controller *controller;

public:
	 
	Player(glm::vec2 pos);

	/* entity update & render */
	void update(float dt);
};

#endif
