#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <sol.hpp>

class EventManager {
	std::unordered_map<std::string, std::vector<sol::object>> events;

public:

	EventManager();
	EventManager(const EventManager &other);
	~EventManager();

	std::vector<std::tuple<std::string, size_t>> getList();
	std::vector<sol::object> &getEvents(std::string name);

	void clearEvents(std::string event_name);
	int addEvent(std::string event_name, sol::object func);
	void deleteEvent(std::string event_name, int index);

	void callEventFromLua(std::string event_name, sol::variadic_args args) {
		auto search = this->events.find(event_name);
		if (search == this->events.end()) {
			return;
		}

		std::vector<sol::object> &funcs = search->second;
		for (auto it = funcs.begin(); it != funcs.end(); ++it) {
			((sol::function)*it).call(args);
		}
	}

	template <class... Args>
	void callEvent(std::string event_name, Args&&... args) {
		auto search = this->events.find(event_name);
		if (search == this->events.end()) {
			return;
		}

		std::vector<sol::object> &funcs = search->second;
		for (auto it = funcs.begin(); it != funcs.end(); ++it) {
			((sol::function)*it).call(std::forward<Args>(args)...);
		}
	}

};

#endif
