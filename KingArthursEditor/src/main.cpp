#define __VERSION__ "0.0.1"
#include <iostream>
#include <string>

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

#include "Entity.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "ItemGun.hpp"
#include "KeyboardController.hpp"
#include "MouseController.hpp"
#include "JoystickController.hpp"

#if !defined(_WIN32)
#define sprintf_s sprintf
#endif

void handle_events(sf::Window &window, bool render_imgui) {
	sf::Event e;
	while (window.pollEvent(e)) {
		if (render_imgui)
			ImGui::SFML::ProcessEvent(e);
		
		switch (e.type) {
		case sf::Event::Closed:
			window.close();
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

struct ball {
	int x, y;
	
	ball(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
	
	void fall() {
		this->y += 1;
	}

	void print() {
		std::cout << x << ", " << y << std::endl;
	}
};

#if defined(_WIN32)
#include <Windows.h>
#endif

#if defined(_WIN32) && !defined(_DEBUG)
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(int argc, char *argv[]) {
#endif

	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::string, sol::lib::os, sol::lib::math, sol::lib::table);
	lua.new_usertype<ball>("ball",
		sol::constructors<ball(), ball(int, int)>(),
		"x", &ball::x,
		"y", &ball::y,
		"fall", &ball::fall,
		"print", &ball::print
	);

	for (int i = 0; i < 10; ++i) {
		using namespace std;
		cout << "#" << i + 1 << "> ";
		string l;
		getline(std::cin, l);
		lua.script(l);
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "p.flesh " __VERSION__);
	bool vsync_enabled = true;
	window.setVerticalSyncEnabled(vsync_enabled);
	sf::View default_view(sf::FloatRect(0.0f, 0.0f, (float)window.getSize().x, (float)window.getSize().y));
	
	/* init imgui */
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui::SFML::Init(window);
	ImGui::StyleColorsLight();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	
	std::vector<Entity *> entities;
	std::vector<Item *> items;
	Player *player = new Player(glm::vec2(350.0f), &window);
	
	entities.push_back(player);

	sf::Time dt;
	sf::Clock dt_clock;
	int asks = 0, asks_count = 10;
	float dt_sum = 0.0f;

	while (window.isOpen()) {
		sf::Time dt = dt_clock.restart();
		default_view.setSize(window.getSize().x, window.getSize().y);
		window.setView(default_view);
		
		static bool close = false, render_imgui = true, render_imgui_toggle = false;
		if (close) window.close();
		handle_events(window, render_imgui);

		if (render_imgui) {
			ImGui::SFML::Update(window, dt);

			ImGui::Begin("Items");
				static float _ipos[2];
				ImGui::Text("Spawn Item:");
				ImGui::InputFloat2("pos", _ipos);
				ImGui::SameLine();
				if (ImGui::Button("Spawn")) {
					items.push_back(new ItemGun(glm::vec2(_ipos[0], _ipos[1])));
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
			ImGui::EndMainMenuBar();
		}
		
		/* update */
		glm::vec2 stick_right = get_axis(0, sf::Joystick::Axis::Z, sf::Joystick::Axis::R);

		for (Entity *entity : entities) {
			entity->update(dt.asSeconds());
			for (Item *item : items) {
				if (item->isCollectableBy(*entity)) {
					item->onEntityNear(*entity);
				}
			}
		}
		for (Item *item : items) {
			item->update(dt.asSeconds());
		}

		player->setViewDirection(stick_right);
		
		/* render */
		window.clear(sf::Color(33, 33, 33));
		for (Item *item : items) {
			item->draw(window);
		}
		for (Entity *entity : entities) {
			entity->draw(window);
		}
		

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

	for (Entity *e : entities) delete e;
	for (Item *i : items) delete i;

	ImGui::SFML::Shutdown();

	return 0;
}
