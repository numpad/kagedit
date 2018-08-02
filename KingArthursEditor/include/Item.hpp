#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <math.h>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>

#include "Entity.hpp"

class Item : public Entity {
private:
	sf::Sprite sprite;
	float bgshape_radius = 17.0f,
		  bgshape_radius_extra = 0.0f;
	sf::CircleShape bgshape;

	float animation_time = 0.0f,
		  animation_timestep = 2.25f;
	float animation_radius_max = 3.0f;
	void animate(float dt_seconds);

protected:
	float collectableMagneticRadius = 45.0f;
	float collectInRadius = 14.0f;
	bool collected = false;

	std::string script_src = "print('item collected')";

	Item();

public:
	
	Item(const Item &other) {
		puts("[...] item copied");
	}

	~Item();

	/* member access */
	float getCollectableRadius();
	bool isCollectableBy(Entity &e);
	bool isCollected();
	void setCollected(bool collected = true);

	/* called on specific events */
	void onEntityNear(Entity &entity, sol::state &lua);
	void onPickup(Entity &entity, sol::state &lua);

	/* update/render */
	void update(float dt_seconds);
	void draw(sf::RenderTarget &);
};

#endif
