#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <string>
#include <vector>
#include <unordered_map>

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <sol.hpp>

class EventManager {
	sol::state *lua;

	std::unordered_map<std::string, std::vector<sol::object>> events;

public:

	EventManager();
	EventManager(sol::state &lua);

	void setEnvironment(sol::state &lua);

	std::vector<sol::object> &getEvents(std::string name);

	void clearEvents(std::string event_name);
	int addEvent(std::string event_name, sol::object func);
	void deleteEvent(std::string event_name, int index);

	void callEvent(std::string event_name) {
		auto &&search = this->events.find(event_name);
		if (search == this->events.end()) {
			return;
		}

		std::vector<sol::object> funcs = search->second;
		for (size_t i = 0; i < funcs.size(); ++i) {
			sol::function(funcs.at(i)).call();
		}
	}

};

#endif
