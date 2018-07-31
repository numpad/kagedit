#define __VERSION__ "0.0.1"
#define SOL_CHECK_ARGUMENTS 1
#define SOL_NO_EXCEPTIONS 1

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <string.h>
#include <stdio.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_impl.h>
#include <sqlite3/sqlite3.h>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

#include <sol.hpp>
#include <tinydir.h>

#include "Entity.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "ItemGun.hpp"
#include "KeyboardController.hpp"
#include "MouseController.hpp"
#include "JoystickController.hpp"

#include "World.hpp"

#include "LuaInputWrapper.hpp"

#if !defined(_WIN32)
#define sprintf_s sprintf
#endif

#define CALL_SCRIPTFUNC(func, ...) \
	do { \
		sol::function luafunc = lua[func]; \
		if (luafunc.get_type() == sol::type::function) \
			luafunc(__VA_ARGS__); \
	} while (0)

void handle_events(sf::Window &window, bool render_imgui, sol::state &lua) {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (render_imgui)
			ImGui::SFML::ProcessEvent(e);
		
		switch (e.type) {
		case sf::Event::Closed:
			CALL_SCRIPTFUNC("on_close");
			window.close();
			break;
		case sf::Event::Resized:
			CALL_SCRIPTFUNC("on_resize", e.size.width, e.size.height);
			break;
		case sf::Event::LostFocus:
			CALL_SCRIPTFUNC("on_focuschange", false);
			break;
		case sf::Event::GainedFocus:
			CALL_SCRIPTFUNC("on_focuschange", true);
			break;
		case sf::Event::MouseWheelScrolled:
			CALL_SCRIPTFUNC("on_mousescroll", e.mouseWheelScroll.delta, e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel);
			break;
		case sf::Event::MouseMoved:
			CALL_SCRIPTFUNC("on_mousemove", e.mouseMove.x, e.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed: {
			const char *t;
			sf::Mouse::Button b = e.mouseButton.button;
			switch (b) {
				case sf::Mouse::Left:		t = "left";		break;
				case sf::Mouse::Right:		t = "right";	break;
				case sf::Mouse::Middle:		t = "middle";	break;
				case sf::Mouse::XButton1:	t = "x1";		break;
				case sf::Mouse::XButton2:	t = "x2";		break;
				default: t = ""; break;
			};
			CALL_SCRIPTFUNC("on_mousebutton", e.mouseButton.x, e.mouseButton.y, t, true);
			break;
		}
		case sf::Event::MouseButtonReleased: {
			const char *t;
			sf::Mouse::Button b = e.mouseButton.button;
			switch (b) {
			case sf::Mouse::Left:		t = "left";		break;
			case sf::Mouse::Right:		t = "right";	break;
			case sf::Mouse::Middle:		t = "middle";	break;
			case sf::Mouse::XButton1:	t = "x1";		break;
			case sf::Mouse::XButton2:	t = "x2";		break;
			default: t = ""; break;
			};
			CALL_SCRIPTFUNC("on_mousebutton", e.mouseButton.x, e.mouseButton.y, t, false);
			break;
		}
		case sf::Event::MouseEntered:
			CALL_SCRIPTFUNC("on_mousefocuschange", true);
			break;
		case sf::Event::MouseLeft:
			CALL_SCRIPTFUNC("on_mousefocuschange", false);
			break;
		case sf::Event::JoystickConnected:
			CALL_SCRIPTFUNC("on_joystickconnection", e.joystickConnect.joystickId, true);
			break;
		};
	}
}

glm::vec2 get_axis(unsigned int joystick, sf::Joystick::Axis axis1, sf::Joystick::Axis axis2) {
	if (!sf::Joystick::isConnected(joystick) || !sf::Joystick::hasAxis(joystick, axis1) || !sf::Joystick::hasAxis(joystick, axis2))
		return glm::vec2(0.0f);
	
	return glm::vec2(
		sf::Joystick::getAxisPosition(joystick, axis1) * 0.01f,
		sf::Joystick::getAxisPosition(joystick, axis2) * 0.01f
	);
}

std::vector<std::string> list_files(std::string path = ".") {
	tinydir_dir dir;
	tinydir_open(&dir, path.c_str());

	std::vector<std::string> res;

	while (dir.has_next) {
		tinydir_file f;
		tinydir_readfile(&dir, &f);

		if (!f.is_dir)
			res.push_back(std::string(f.name));
		
		tinydir_next(&dir);
	}
	tinydir_close(&dir);

	return res;
}

static int luaapi_listfiles(lua_State *L) {
	/* retrieve parameter */
	std::string path = "assets/";
	if (lua_gettop(L) > 0) {
		char full[512];
		const char *asset_path = lua_tostring(L, 1);
		sprintf(full, "%s%s", path.c_str(), asset_path);
		path = std::string(full);
	}

	/* read filenames */
	std::vector<std::string> files = list_files(path);

	/* return table */
	lua_newtable(L);
	int i = 1;
	for (std::string &fn : files) {
		lua_pushstring(L, fn.c_str());
		lua_seti(L, -2, i++);
	}

	return 1;
}

void register_luaapi(sol::state &lua) {
	lua_State *L = lua.lua_state();

	/* register listfiles */
	lua_pushcfunction(L, luaapi_listfiles);
	lua_setglobal(L, "list_files");
}

class Script {
public:
	int name_len = 64;
	static int NEXT_ID;
	int id;

	char *name;
	sol::state *lua;
	char *src;
	size_t len;
	bool shown;

	Script(sol::state *lua, size_t len = 2048) {
		this->src = new char[len]();
		this->len = len;
		this->shown = true;
		this->id = Script::NEXT_ID++;
		this->lua = lua;

		this->name = new char[Script::name_len]();
		sprintf(this->name, "Script #%d", this->id);
	}

	Script(sol::state *lua, char *content, const char *name, bool hidden = false) {
		this->len = MAX(strlen(content) * 2, 2048);
		this->src = new char[this->len + 1]();

		strncpy(this->src, content, this->len);

		this->shown = !hidden;
		this->id = Script::NEXT_ID++;
		this->lua = lua;

		this->name_len = strlen(name) + 1;
		this->name = new char[this->name_len]();
		strncpy(this->name, name, strlen(name));
	}

	~Script() {
		delete[] this->src;
	}

	void hide() {
		this->shown = false;
	}

	void execute() {
		this->lua->safe_script(this->src);
	}

	void render() {
		if (!this->shown) return;

		char title[128];
		sprintf(title, "%s###1%d", this->name, this->id);

		ImGui::Begin(title, &this->shown);
			ImGui::InputText("##Name", this->name, Script::name_len);
			ImGui::SameLine();
			if (ImGui::Button("Run")) {
				this->execute();
			}
			float height = 62.0f;
			ImGui::InputTextMultiline("", this->src, this->len, ImVec2(ImGui::GetWindowWidth() - 18.0f, ImGui::GetWindowHeight() - height));
		ImGui::End();
	}
};
int Script::NEXT_ID = 0;

void loadscripts(sol::state &lua, std::vector<Script *> &script_srcs, const char *basepath = "assets/scripts/debug/") {
	/* load debug scripts */
	script_srcs.clear();
	for (std::string &fn : list_files(basepath)) {
		char path[512];
		sprintf(path, "%s%s", basepath, fn.c_str());

		FILE *fp = fopen(path, "r");
		if (!fp) continue;

		fseek(fp, 0, SEEK_END);
		size_t len = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		char *src = new char[len + 1]();
		fread(src, sizeof(char), len, fp);

		fclose(fp);

		script_srcs.push_back(new Script(&lua, src, fn.c_str(), true));
	}
}

sol::state new_luastate(sf::RenderWindow *window, sf::View *camera, std::vector<Entity *> &entities, std::vector<Item *> &items) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::string, sol::lib::os, sol::lib::math, sol::lib::table, sol::lib::package);
	register_luaapi(lua);
	LuaInputWrapper::REGISTER(&lua, window, camera);
	
	/* register __pointers__ table */
	lua["__pointers__"]["entities"] = &entities;
	lua["__pointers__"]["items"] = &items;

	/* run loader script */
	lua.script_file("assets/scripts/loader.lua");

	return lua;
}

#if defined(_WIN32)
#include <Windows.h>
#endif

Entity &luaapi_deref(Entity *t) {
	return *t;
}

#if defined(_WIN32) && !defined(_DEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(int argc, char *argv[]) {
#endif
	bool vsync_enabled = true;
	sf::RenderWindow window(sf::VideoMode(800, 600), "p.flesh " __VERSION__);
	window.setVerticalSyncEnabled(vsync_enabled);

	/* init imgui */
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui::SFML::Init(window);
	ImGui::StyleColorsLight();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	
	World world(window);
	Player *player = new Player(glm::vec2(350.0f), &window);
	world.spawnEntity(player);

	/* open lua state, load init script */
	sol::state lua = new_luastate(&window, &world.getCamera(), world.entities, world.items);
	std::vector<Script *> script_srcs;
	loadscripts(lua, script_srcs);
	

	sf::Time dt;
	sf::Clock dt_clock;
	int asks = 0, asks_count = 10;
	float dt_sum = 0.0f;
	
	while (window.isOpen()) {
		sf::Time dt = dt_clock.restart();
		window.setView(lua["camera"]);
		
		static bool close = false, render_imgui = true, render_imgui_toggle = false;
		if (close) window.close();
		handle_events(window, render_imgui, lua);

		if (render_imgui) {
			ImGui::SFML::Update(window, dt);

			ImGui::Begin("Items");
				static float _ipos[2];
				ImGui::Text("Spawn Item:");
				ImGui::InputFloat2("pos", _ipos);
				ImGui::SameLine();
				if (ImGui::Button("Spawn")) {
					world.spawnItem(new ItemGun(glm::vec2(_ipos[0], _ipos[1])));
				}
				ImGui::SameLine();
				if (ImGui::Button("Random")) {
					for (int i = 0; i < 10; ++i) {
						float x = (float)rand() / (float)RAND_MAX;
						float y = (float)rand() / (float)RAND_MAX;
						world.spawnItem(new ItemGun(glm::vec2(x * 800.0f, y * 600.0f)));
					}
				}
				ImGui::Separator();

				static bool controller_keyboard = true;
				ImGui::Text("Controls:");
				if (ImGui::RadioButton("Keyboard", controller_keyboard) && !controller_keyboard) {
					player->setController(new KeyboardController(player));
					player->addController(new MouseController(player, &window));
					controller_keyboard = !controller_keyboard;
				}
				
				if (ImGui::RadioButton("Joystick", !controller_keyboard) && controller_keyboard) {
					player->setController(new JoystickController(player, 0));
					controller_keyboard = !controller_keyboard;
				}
				
			ImGui::End();

			for (Script *s : script_srcs) {
				s->render();
			}
		}

		if (render_imgui && ImGui::BeginMainMenuBar()) {
			static char fps[32];
			if (asks == (asks_count - 1)) {
				sprintf_s(fps, "FPS: %.0f", 1.0f / (dt_sum / (float)asks_count));
				asks = 0;
				dt_sum = 0.0f;
			} else {
				++asks;
				dt_sum += dt.asSeconds();
			}
			if (ImGui::MenuItem(fps)) {
				vsync_enabled = !vsync_enabled;
				window.setVerticalSyncEnabled(vsync_enabled);
			}

			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Hide Menubar")) {
					render_imgui_toggle = true;
				}
				ImGui::Separator();
				ImGui::MenuItem("Close", NULL, &close);
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Script")) {
				if (ImGui::MenuItem("New")) {
					script_srcs.push_back(new Script(&lua));
				}
				if (ImGui::MenuItem("Reset State")) {
					lua = new_luastate(&window, &world.getCamera(), world.entities, world.items);
					loadscripts(lua, script_srcs);
				}
				ImGui::Separator();
				/* show menu item to open hidden scripts */
				if (ImGui::BeginMenu("Show hidden")) {
					for (Script *s : script_srcs) {
						if (!s->shown) {
							if (ImGui::MenuItem(s->name)) {
								s->shown = true;
							}
						}
					}
					ImGui::EndMenu();
				}
				/* show menu item to run scripts */
				if (ImGui::BeginMenu("Run")) {
					for (Script *s : script_srcs) {
						if (ImGui::MenuItem(s->name)) {
							s->execute();
						}
					}
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		
		/* update */
		glm::vec2 stick_right = get_axis(0, sf::Joystick::Axis::Z, sf::Joystick::Axis::R);
		player->setViewDirection(stick_right);
	
		world.update(dt.asSeconds(), lua);
		
		/* render */
		window.clear(sf::Color(33, 33, 33));
		world.render();
		
		/* imgui render */
		if (render_imgui) {
			ImGui::EndFrame();
			ImGui::SFML::Render(window);
		}
		window.display();
		dt = dt_clock.getElapsedTime();
		if (render_imgui_toggle) {
			render_imgui = !render_imgui;
			render_imgui_toggle = false;
		}
	}

	for (Script *s : script_srcs) delete s;

	ImGui::SFML::Shutdown();
	
	return 0;
}
