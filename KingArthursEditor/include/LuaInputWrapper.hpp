#ifndef LUAINPUTWRAPPER_HPP
#define LUAINPUTWRAPPER_HPP

#include <sol.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class LuaInputWrapper {

public:
	static sol::state *lua;
	static sf::Window *window;

	static void REGISTER(sol::state *lua, sf::Window *window);

	glm::vec2 getMousePosition();

};

#endif
