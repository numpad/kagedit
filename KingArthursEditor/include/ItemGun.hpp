#ifndef ITEMGUN_HPP
#define ITEMGUN_HPP

#include <assert.h>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Item.hpp"

class ItemGun : public Item {
private:
	sf::Texture gun_texture;

public:
	
	ItemGun(glm::vec2 pos);

};

#endif
