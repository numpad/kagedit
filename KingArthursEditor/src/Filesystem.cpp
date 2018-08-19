#include "..\include\Filesystem.hpp"

std::vector<std::string> Filesystem::list(std::string path, Filesystem::flag_type flags) {
	/* open path */
	tinydir_dir dir;
	assert(tinydir_open(&dir, path.c_str()) == 0);

	bool include_files = static_cast<Filesystem::flag_type>(flags) & static_cast<Filesystem::flag_type>(Filesystem::Flag::FILE);
	bool include_dirs = static_cast<Filesystem::flag_type>(flags) & static_cast<Filesystem::flag_type>(Filesystem::Flag::DIR);

	std::vector<std::string> result;

	while (dir.has_next) {
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		/* skip non regular files (., .., etc) */
		const std::string filename(file.name);
		if (filename == "." || filename == "..") {
			tinydir_next(&dir);
			continue;
		}

		bool is_file = !file.is_dir;
		bool is_dir = file.is_dir;

		if (!(is_file && include_files || is_dir && include_dirs)) {
			tinydir_next(&dir);
			continue;
		}


		const char *str = file.name;
		if (static_cast<Filesystem::flag_type>(flags) & static_cast<Filesystem::flag_type>(Filesystem::Flag::FULL_PATH))
			str = file.path;

		result.push_back(std::string(str));
		tinydir_next(&dir);
	}

	/* cleanup */
	tinydir_close(&dir);

	return result;
}
