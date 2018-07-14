#ifndef ITEM_HPP
#define ITEM_HPP

#include <math.h>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Item : public Entity {
private:
	float bgshape_radius = 17.0f,
		  bgshape_radius_extra = 0.0f;
	sf::CircleShape bgshape;

	float animation_time = 0.0f,
		  animation_timestep = 2.25f;
	float animation_radius_max = 3.0f;
	void animate(float dt_seconds);

protected:
	float collectableRadius = bgshape_radius + animation_radius_max;

	Item();


public:

	/* member access */
	float getCollectableRadius();
	bool isCollectableBy(Entity &e);

	/* called on specific events */
	virtual void onEntityNear(Entity &entity);
	virtual void onPickup(Entity &by) =0;

	/* update/render */
	void update(float dt_seconds);
	void draw(sf::RenderTarget &);
};

#endif
