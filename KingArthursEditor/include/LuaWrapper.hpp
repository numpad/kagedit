#ifndef LUAWRAPPER_HPP
#define LUAWRAPPER_HPP

#include <sol.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include "Entity.hpp"
#include "Player.hpp"

#include "Item.hpp"
#include "ItemGun.hpp"

#include "EventManager.hpp"

class LuaWrapper {

	static void REGISTER_PLAYER(sol::state *lua);
	static void REGISTER_ITEMS(sol::state *lua);
	static void REGISTER_CASTS(sol::state &lua);
	static void REGISTER_EVENTMANAGER(sol::state &lua);

public:
	static sol::state *lua;
	static sf::RenderWindow *window;
	static sf::View *camera;

	static void REGISTER(sol::state *lua, sf::RenderWindow *window, sf::View *camera);

	glm::vec2 getMousePosition();

};

#endif
