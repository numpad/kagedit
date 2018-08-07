#include "ItemGun.hpp"

ItemGun::ItemGun(glm::vec2 pos) {
	this->gun_texture = AssetManager::load("assets/images/kenney-topdown/weapon_gun.png");
	this->gun_texture->setSmooth(true);
	this->setPos(pos);
	this->setTexture(*this->gun_texture);
}

ItemGun::~ItemGun() {
	
}

