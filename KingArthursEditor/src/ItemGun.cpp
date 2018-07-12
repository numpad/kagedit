#include "ItemGun.hpp"

ItemGun::ItemGun(glm::vec2 pos) {
	assert(this->gun_texture.loadFromFile("assets/images/kenney-topdown/weapon_gun.png"));
	this->gun_texture.setSmooth(true);
	this->setPos(pos);
	this->setTexture(this->gun_texture);
}

void ItemGun::onPickup(Entity & by) {
	
}
