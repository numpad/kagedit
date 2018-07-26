#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Entity.hpp"

class Controller {
protected:
	Entity *entity = nullptr;
	
public:

	virtual void readInput() =0;
	virtual void update(float dt) =0;
};

#endif

