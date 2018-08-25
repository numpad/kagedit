#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <string>
#include <string.h>
#include <imgui.h>
#include <sol.hpp>


class Script {
public:
	int name_len = 64;
	static int NEXT_ID;
	int id;

	char *name = nullptr;
	sol::state *lua;
	char *src = nullptr;
	size_t len;
	bool shown;
	
	char *err = nullptr;
	size_t err_len;

	Script(sol::state *lua, size_t len = 2048);
	Script(sol::state *lua, char *content, const char *name, bool hidden = false);
	~Script();
	
	void set_err(std::string msg);

	void hide();
	void execute();
	void render();
};

#endif
