#include "EventManager.hpp"

EventManager::EventManager() {
}

EventManager::~EventManager() {
	puts("[xxx] destructing eventmanager...");
}

std::vector<std::tuple<std::string, size_t>> EventManager::getList() {
	std::vector<std::tuple<std::string, size_t>> list;

	for (auto it = this->events.begin(); it != this->events.end(); ++it) {
		list.push_back(
			std::make_tuple(it->first, it->second.size())
		);
	}

	return list;
}

std::vector<sol::object> &EventManager::getEvents(std::string name) {
	auto search = this->events.find(name);
	if (search == this->events.end()) {
		this->events[name] = std::vector<sol::object>();
	}

	return this->events.at(name);
}

void EventManager::clearEvents(std::string event_name) {
	auto search = this->events.find(event_name);
	if (search == this->events.end())
		return;

	search->second.clear();
}

int EventManager::addEvent(std::string event_name, sol::object func) {
	if (func.get_type() == sol::type::function) {
		std::vector<sol::object> &list = this->getEvents(event_name);
		list.push_back(func);
		return list.size() - 1;
	}
	
	return -1;
}

void EventManager::deleteEvent(std::string event_name, int index) {
	auto search = this->events.find(event_name);
	if (search == this->events.end())
		return;

	search->second.erase(search->second.begin() + index);
}

