#ifndef UTIL_HPP
#define UTIL_HPP

#include <string.h>
#include <string>
#include <SFML/Window/Keyboard.hpp>

namespace Util {
	
	const char *KeyToString(sf::Keyboard::Key key);
	sf::Keyboard::Key StringToKey(const char *name);
}

#endif

