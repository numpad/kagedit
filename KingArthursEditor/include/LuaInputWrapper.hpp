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
	static sf::RenderWindow *window;
	static sf::View *camera;

	static void REGISTER(sol::state *lua, sf::RenderWindow *window, sf::View *camera);

	glm::vec2 getMousePosition();

};

#endif
