#include "LuaWrapper.hpp"

/* static */
sol::state *LuaWrapper::lua = NULL;
sf::RenderWindow *LuaWrapper::window = NULL;
sf::View *LuaWrapper::camera = NULL;


void LuaWrapper::REGISTER_PLAYER(sol::state *lua) {
	lua->new_usertype<Entity>(
		"Entity",
		/* entity base class */
		"events", sol::property(&Entity::getEvents),
		"name", sol::property(&Entity::setName, &Entity::getName),
		"pos", sol::property(&Entity::setPos, &Entity::getPos),
		"vel", sol::property(&Entity::setVel, &Entity::getVel),
		"acc", sol::property(&Entity::setAcc, &Entity::getAcc),
		"new", sol::no_constructor,
		"distanceTo", &Entity::distanceTo,
		"pickup", [](Entity &e, Item *i){ i->onPickup(e); },
		"getName", &Entity::getName,
		"setName", &Entity::setName,
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
		"new", sol::factories([](glm::vec2 pos){ return new Player(pos, LuaWrapper::window); })
	);
}

void LuaWrapper::REGISTER_ITEMS(sol::state *lua) {
	lua->new_usertype<Item>(
		"Item",
		sol::base_classes, sol::bases<Entity>(),
		"new", sol::no_constructor,
		"collected", sol::property(&Item::setCollected, &Item::isCollected)
	);

	lua->new_usertype<ItemGun>(
		"ItemGun",
		sol::base_classes, sol::bases<Entity, Item>(),
		"new", sol::factories([](glm::vec2 p){ return new ItemGun(p); })
	);
}

template <class T>
static T *luaapi_ptrcast(void *d) {
	return (T *)d;
}

void LuaWrapper::REGISTER_CASTS(sol::state &lua) {
	lua.create_named_table("__pointers__");
	lua["__pointers__"]["typecast"] = lua.create_table_with(
		"toEntity",			&luaapi_ptrcast<Entity>,
		"toPlayer",			&luaapi_ptrcast<Player>,
		"toItem",			&luaapi_ptrcast<Item>
	);

}

void LuaWrapper::REGISTER_EVENTMANAGER(sol::state &lua) {
	lua.new_usertype<EventManager>(
		"EventManager",
		"new", sol::no_constructor,
		"add", &EventManager::addEvent,
		"set", [](EventManager &em, const std::string &name, sol::object func){ em.clearEvents(name); em.addEvent(name, func); },
		"delete", &EventManager::deleteEvent,
		"clear", &EventManager::clearEvents,
		"get", &EventManager::getEvents,
		"list", &EventManager::getList,
		"call", &EventManager::callEventFromLua
	);
}

extern lua_State *lState;
extern void LoadImguiBindings();

void LuaWrapper::REGISTER_IMGUI(sol::state &lua) {
	static lua_State *L = sol::state_view(lua);
	lState = L;
	LoadImguiBindings();
}

void LuaWrapper::REGISTER(sol::state *lua, sf::RenderWindow *window, sf::View *camera) {
	LuaWrapper::lua = lua;
	LuaWrapper::window = window;
	LuaWrapper::camera = camera;

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

	LuaWrapper::lua->new_usertype<glm::vec2>(
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
		"dot",								[](const glm::vec2 &a, const glm::vec2 &b){ return glm::dot(a, b); },
		"normalize",						[](const glm::vec2 &v){ return glm::normalize(v); },
		"rotate",							[](const glm::vec2 &v, float radians){ return glm::rotate(v, radians); }
	);
		
	LuaWrapper::lua->create_named_table("input",
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
	
	/* camera */
	auto cam_getpos = [](const sf::View &camera){ const sf::Vector2f pos = camera.getCenter(); return glm::vec2(pos.x, pos.y); };
	auto cam_setpos = [](sf::View &camera, const glm::vec2 &p){ camera.setCenter(p.x, p.y); };
	auto cam_getsize = [](const sf::View &camera){ const sf::Vector2f s = camera.getSize(); return glm::vec2(s.x, s.y); };
	auto cam_setsize = [](sf::View &camera, const glm::vec2 &s){ camera.setSize(s.x, s.y); };
	auto cam_getrot = [](const sf::View &camera){ return camera.getRotation(); };
	auto cam_setrot = [](sf::View &camera, float rad){ camera.setRotation(glm::degrees(rad)); };
	LuaWrapper::lua->new_usertype<sf::View>(
		"Camera",
		sol::constructors<sf::View()>(),
		"pos", sol::property(cam_getpos, cam_setpos),
		"size", sol::property(cam_getsize, cam_setsize),
		"rotation", sol::property(cam_getrot, cam_setrot),
		"getPos", cam_getpos,
		"setPos", cam_setpos,
		"getSize", cam_getsize,
		"setSize", cam_setsize,
		"getRotation", cam_getrot,
		"setRotation", cam_setrot,
		"move", [](sf::View &camera, const glm::vec2 &d){ camera.move(d.x, d.y); },
		"rotate", [](sf::View &camera, float rad){ camera.rotate(glm::degrees(rad)); },
		"zoom", [](sf::View &camera, float f){ camera.zoom(f); },
		"toWorldspace", [window](const sf::View &view, const glm::vec2 &p){
			sf::Vector2f coords = window->mapPixelToCoords(sf::Vector2i((int)p.x, (int)p.y), view);
			return glm::vec2(coords.x, coords.y);
		},
		"toScreenspace", [window](const sf::View &view, const glm::vec2 &p){
			sf::Vector2i coords = window->mapCoordsToPixel(sf::Vector2f(p.x, p.y), view);
			return glm::vec2(coords.x, coords.y);
		}
	);
	LuaWrapper::lua->set("camera", camera);

	LuaWrapper::REGISTER_PLAYER(lua);
	LuaWrapper::REGISTER_ITEMS(lua);
	LuaWrapper::REGISTER_CASTS(*lua);
	LuaWrapper::REGISTER_EVENTMANAGER(*lua);
	LuaWrapper::REGISTER_IMGUI(*lua);
	LuaWrapper::REGISTER_WORLD(*lua);
	LuaWrapper::REGISTER_SFML(*lua);
}

void LuaWrapper::REGISTER_WORLD(sol::state &lua) {
	lua.new_usertype<World>(
		"World",
		"items", &World::items,
		"entities", &World::entities,
		"events", sol::property(&World::getEvents),
		"new", sol::factories([](){ new World(); }),
		"spawnEntity", &World::spawnEntity,
		"spawnItem", &World::spawnItem,
		"loadLayer", &World::loadLayerFromLua
	);
}

void LuaWrapper::REGISTER_SFML(sol::state &lua) {
	lua.new_usertype<sf::RenderWindow>(
		"RenderWindow",
		"getSize", [](sf::RenderWindow &window){ return glm::vec2((float)window.getSize().x, (float)window.getSize().y); }
	);
}

glm::vec2 LuaWrapper::getMousePosition() {
	sf::Vector2i mouse = sf::Mouse::getPosition(*window);
	return glm::vec2((float)mouse.x, (float)mouse.y);
}

