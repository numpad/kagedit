#define __VERSION__ "0.0.1"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_impl.h>
#include <sqlite3/sqlite3.h>

#include "Entity.hpp"
#include "Player.hpp"
#include "Item.hpp"
#include "ItemGun.hpp"

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

#if defined(_WIN32) && !defined(_DEBUG)
#include <Windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(int argc, char *argv[]) {
#endif
	sf::RenderWindow window(sf::VideoMode(800, 600), "kageditor " __VERSION__);
	bool vsync_enabled = true;
	window.setVerticalSyncEnabled(vsync_enabled);
	sf::View default_view(sf::FloatRect(0.0f, 0.0f, window.getSize().x, window.getSize().y));

	/* init imgui */
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::SFML::Init(window);
	ImGui::StyleColorsLight();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	
	std::vector<Entity *> entities;
	std::vector<Item *> items;
	Player *player = new Player(glm::vec2(350.0f));

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
