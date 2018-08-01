#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <string>
#include <imgui.h>
#include <sol.hpp>


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

	Script(sol::state *lua, size_t len = 2048);
	Script(sol::state *lua, char *content, const char *name, bool hidden = false);
	~Script();
	
	void hide();
	void execute();
	void render();
};

#endif
