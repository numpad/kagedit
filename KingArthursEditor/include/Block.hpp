#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>

class Block {
public:
	int id;
	std::string name;
	unsigned char r, g, b;
	int tileset_pos;
	std::string sprite_path;
	int rotation;
	int team;
	unsigned int type;
	int next_rot;


};

#endif
