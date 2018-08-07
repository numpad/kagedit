#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <math.h>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include "Entity.hpp"

#include "AssetManager.hpp"

class Item : public Entity {
private:
	float bgshape_radius = 17.0f,
		  bgshape_radius_extra = 0.0f;

	/* TODO: handle resources in a resource manager, keep one texture in there and reference it */
	sf::Texture *hightlight_texture;
	sf::Sprite highlight;

	float animation_time = 0.0f,
		  animation_timestep = 0.025f;
	
	void animate(float dt_seconds);

protected:
	float collectableMagneticRadius = 45.0f;
	float collectInRadius = 14.0f;
	bool collected = false;

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
	void onEntityNear(Entity &entity);
	void onPickup(Entity &entity);

	/* update/render */
	void update(float dt_seconds);
	void draw(sf::RenderTarget &);
};

#endif
