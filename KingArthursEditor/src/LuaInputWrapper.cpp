#include "LuaInputWrapper.hpp"

/* static */
sol::state *LuaInputWrapper::lua = NULL;
sf::RenderWindow *LuaInputWrapper::window = NULL;
sf::View *LuaInputWrapper::camera = NULL;


void LuaInputWrapper::REGISTER_PLAYER(sol::state *lua) {
	lua->new_usertype<Entity>(
		"Entity",
		/* entity base class */
		"pos", sol::property(&Entity::setPos, &Entity::getPos),
		"vel", sol::property(&Entity::setVel, &Entity::getVel),
		"acc", sol::property(&Entity::setAcc, &Entity::getAcc),
		"new", sol::no_constructor,
		"distanceTo", &Entity::distanceTo,
		"getPos", &Entity::getPos,
		"setPos", &Entity::setPos,
		"getVel", &Entity::getVel,
		"setVel", &Entity::setVel,
		"getAcc", &Entity::getAcc,
		"setAcc", &Entity::setAcc,
		"getDrag", &Entity::getDrag,
		"setDrag", &Entity::setDrag,
		"getViewDirection", &Entity::getViewDirection,
		"getViewAngle", &Entity::getViewAngle,
		"setViewTarget", &Entity::setViewTarget,
		"setViewDirection", &Entity::setViewDirection,
		"update", &Entity::update
	);

	lua->new_usertype<Player>(
		"Player",
		sol::base_classes, sol::bases<Entity>(),
		/* entity base class */
		"pos", sol::property(&Entity::setPos, &Entity::getPos),
		"vel", sol::property(&Entity::setVel, &Entity::getVel),
		"acc", sol::property(&Entity::setAcc, &Entity::getAcc),
		"new", sol::no_constructor,
		"distanceTo", &Entity::distanceTo,
		"getPos", &Entity::getPos,
		"setPos", &Entity::setPos,
		"getVel", &Entity::getVel,
		"setVel", &Entity::setVel,
		"getAcc", &Entity::getAcc,
		"setAcc", &Entity::setAcc,
		"getDrag", &Entity::getDrag,
		"setDrag", &Entity::setDrag,
		"getViewDirection", &Entity::getViewDirection,
		"getViewAngle", &Entity::getViewAngle,
		"setViewTarget", &Entity::setViewTarget,
		"setViewDirection", &Entity::setViewDirection,
		"update", &Entity::update
	);
}

void LuaInputWrapper::REGISTER_ITEMS(sol::state *lua) {
	lua->new_usertype<Item>(
		"Item",
		sol::base_classes, sol::bases<Entity>(),
		/* entity base class */
		"pos", sol::property(&Entity::setPos, &Entity::getPos),
		"vel", sol::property(&Entity::setVel, &Entity::getVel),
		"acc", sol::property(&Entity::setAcc, &Entity::getAcc),
		"new", sol::no_constructor,
		"distanceTo", &Entity::distanceTo,
		"getPos", &Entity::getPos,
		"setPos", &Entity::setPos,
		"getVel", &Entity::getVel,
		"setVel", &Entity::setVel,
		"getAcc", &Entity::getAcc,
		"setAcc", &Entity::setAcc,
		"getDrag", &Entity::getDrag,
		"setDrag", &Entity::setDrag,
		"getViewDirection", &Entity::getViewDirection,
		"getViewAngle", &Entity::getViewAngle,
		"setViewTarget", &Entity::setViewTarget,
		"setViewDirection", &Entity::setViewDirection,
		"update", &Entity::update

	);
}

void LuaInputWrapper::REGISTER(sol::state *lua, sf::RenderWindow *window, sf::View *camera) {
	LuaInputWrapper::lua = lua;
	LuaInputWrapper::window = window;
	LuaInputWrapper::camera = camera;

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
	
	LuaInputWrapper::lua->create_named_table("__pointers__");
	
	LuaInputWrapper::lua->create_named_table("input",
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
	
	LuaInputWrapper::lua->new_usertype<sf::View>(
		"camera2d",
		sol::constructors<sf::View()>(),
		"getPosition", [](const sf::View &camera){ const sf::Vector2f pos = camera.getCenter(); return glm::vec2(pos.x, pos.y); },
		"getSize", [](const sf::View &camera){ const sf::Vector2f s = camera.getSize(); return glm::vec2(s.x, s.y); },
		"getRotation", [](const sf::View &camera){ return camera.getRotation(); },
		"setPosition", [](sf::View &camera, const glm::vec2 &p){ camera.setCenter(p.x, p.y); },
		"setSize", [](sf::View &camera, const glm::vec2 &s){ camera.setSize(s.x, s.y); },
		"setRotation", [](sf::View &camera, float rad){ camera.setRotation(glm::degrees(rad)); },
		"move", [](sf::View &camera, const glm::vec2 &d){ camera.move(d.x, d.y); },
		"rotate", [](sf::View &camera, float rad){ camera.rotate(glm::degrees(rad)); },
		"zoom", [](sf::View &camera, float f){ camera.zoom(f); }
	);
	LuaInputWrapper::lua->set("camera", *camera);

	LuaInputWrapper::REGISTER_PLAYER(lua);
}

glm::vec2 LuaInputWrapper::getMousePosition() {
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	return glm::vec2((float)mouse.x, (float)mouse.y);
}
