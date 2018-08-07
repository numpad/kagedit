#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>
#include <vector>
#include <assert.h>

#include <tinydir.h>

class Filesystem {
	using flag_type = unsigned short;

public:

	enum Flag {
		FILE		= 1,
		DIR			= 2,
		FULL_PATH	= 4
	};

	static std::vector<std::string> list(std::string path, flag_type flags = Flag::FILE);

};

#endif
