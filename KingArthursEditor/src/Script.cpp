#include "Script.hpp"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int Script::NEXT_ID = 0;

Script::Script(sol::state *lua, size_t len) {
	this->src = new char[len]();
	this->len = len;
	this->shown = true;
	this->id = Script::NEXT_ID++;
	this->lua = lua;

	this->name = new char[Script::name_len]();
	sprintf(this->name, "Script #%d", this->id);
}

Script::Script(sol::state *lua, char *content, const char *name, bool hidden) {
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

Script::~Script() {
	delete[] this->src;
}

void Script::hide() {
	this->shown = false;
}

void Script::execute() {
	this->lua->safe_script(this->src);
}

void Script::render() {
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
