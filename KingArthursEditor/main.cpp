#include <iostream>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_impl.h>
#include <sqlite3/sqlite3.h>

#define __VERSION__ "0.0.1"

#if defined(_WIN32) && !defined(_DEBUG)
#include <Windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main(int argc, char *argv[]) {
#endif

	sf::RenderWindow window(sf::VideoMode(800, 600), "kageditor " __VERSION__);
	window.setVerticalSyncEnabled(true);

	/* init imgui */
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::SFML::Init(window);
	ImGui::StyleColorsLight();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	
	sf::Time dt;
	sf::Clock dt_clock;
	while (window.isOpen()) {
		sf::Time dt = dt_clock.restart();
		sf::Event e;

		static bool close = false;
		if (close) window.close();

		while (window.pollEvent(e)) {
			ImGui::SFML::ProcessEvent(e);
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
				break;
			};
		}
		ImGui::SFML::Update(window, dt);

		window.clear(sf::Color(33, 33, 33));

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				ImGui::MenuItem("Open", "CTRL+O");
				ImGui::MenuItem("Save as...", "CTRL+S");
				ImGui::Separator();
				ImGui::MenuItem("Close", NULL, &close);
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		ImGui::EndFrame();
		ImGui::SFML::Render(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
			window.close();
		}


		window.display();
		dt = dt_clock.getElapsedTime();
	}

	ImGui::SFML::Shutdown();

	return 0;
}
