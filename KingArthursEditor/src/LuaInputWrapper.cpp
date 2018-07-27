#include "LuaInputWrapper.hpp"

/* static */
sol::state *LuaInputWrapper::lua = NULL;
sf::Window *LuaInputWrapper::window = NULL;

void LuaInputWrapper::REGISTER(sol::state *lua, sf::Window *window) {
	LuaInputWrapper::lua = lua;
	LuaInputWrapper::window = window;

	/* register glm::vec2 */
	auto glm_vec2_add_overload = sol::overload(
		[](const glm::vec2 &a, const glm::vec2 &b){ return a + b; },
		[](float a, const glm::vec2 &b){ return a + b; },
		[](const glm::vec2 &a, float b){ return a + b; }
	);
	auto glm_vec2_sub_overload = sol::overload(
		[](const glm::vec2 &a, const glm::vec2 &b){ return a - b; },
		[](float a, const glm::vec2 &b){ return a - b; },
		[](const glm::vec2 &a, float b){ return a - b; }
	);
	auto glm_vec2_mult_overload = sol::overload(
		[](const glm::vec2 &a, const glm::vec2 &b){ return a * b; },
		[](const glm::vec2 &a, const float b){ return a * b; },
		[](const float a, const glm::vec2 &b){ return a * b; }
	);
	auto glm_vec2_div_overload = sol::overload(
		[](const glm::vec2 &a, const glm::vec2 &b){ return a / b; },
		[](const glm::vec2 &a, const float b){ return a / b; },
		[](const float a, const glm::vec2 &b){ return a / b; }
	);
	auto glm_vec2_concat_overload = sol::overload(
		[](const char *str, const glm::vec2 &v){ std::ostringstream oss; oss << str << "(" << v.x << ", " << v.y << ")"; return oss.str(); },
		[](const glm::vec2 &v, const char *str){ std::ostringstream oss; oss << "(" << v.x << ", " << v.y << ")" << str; return oss.str(); }
	);

	LuaInputWrapper::lua->new_usertype<glm::vec2>(
		"vec2",
		sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
		"x", &glm::vec2::x,
		"y", &glm::vec2::y,
		sol::meta_function::addition,		glm_vec2_add_overload,
		sol::meta_function::subtraction,	glm_vec2_sub_overload,
		sol::meta_function::unary_minus,	[](const glm::vec2 &a){ return -a; },
		sol::meta_function::multiplication,	glm_vec2_mult_overload,
		sol::meta_function::division,		glm_vec2_div_overload,
		sol::meta_function::to_string,		[](const glm::vec2 &v){ std::ostringstream oss; oss << "(" << v.x << ", " << v.y << ")"; return oss.str(); },
		sol::meta_function::concatenation,	glm_vec2_concat_overload,
		"angle",							[](const glm::vec2 &v){ return glm::orientedAngle(v, glm::vec2(1.0f, 0.0f)); },
		"length",							[](const glm::vec2 &v){ return glm::length(v); },
		"dot",								[](const glm::vec2 &a, const glm::vec2 &b){ return glm::dot(a, b); }
	);

	LuaInputWrapper::lua->create_named_table("input",
		"__window", LuaInputWrapper::window,
		"getMousePosition", [window](){ sf::Vector2i mp = sf::Mouse::getPosition(*window); return glm::vec2((float)mp.x, (float)mp.y); },
		"getMouseButton", [](const char *key){
			if (key == nullptr) return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
			if (strcmp(key, "left") == 0) return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
			if (strcmp(key, "right") == 0) return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
			if (strcmp(key, "middle") == 0) return sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
			if (strcmp(key, "x1") == 0) return sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton1);
			if (strcmp(key, "x2") == 0) return sf::Mouse::isButtonPressed(sf::Mouse::Button::XButton2);
			return false;
		}
	);
}

glm::vec2 LuaInputWrapper::getMousePosition() {
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	return glm::vec2((float)mouse.x, (float)mouse.y);
}
