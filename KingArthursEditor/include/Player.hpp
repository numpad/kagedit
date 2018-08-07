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
#include "MouseController.hpp"
#include "JoystickController.hpp"

#include "AssetManager.hpp"

class Player : public Entity {
	sf::Texture *skin_stand, *skin_gun;
	
	std::vector<Controller *> controllers;

public:
	
	void setController(Controller *c);
	void addController(Controller *c);

	Player(glm::vec2 pos, sf::RenderWindow *window);
	~Player();
	
	/* entity update & render */
	void update(float dt);
};

#endif
