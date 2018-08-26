#ifndef MOB_HPP
#define MOB_HPP

#include <math.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.hpp"
#include "Controller.hpp"

#include "AssetManager.hpp"

class Mob : public Entity {
	
	std::vector<Controller *> controllers;

public:
	
	Mob(glm::vec2 pos);
	virtual ~Mob();
	
	size_t setController(Controller *c);
	size_t addController(Controller *c);
	void deleteController(size_t i);

	virtual void update(float dt);
};

#endif

