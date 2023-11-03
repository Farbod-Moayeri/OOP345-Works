#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include <string>
#include "Directory.h"

namespace sdds {
	class Filesystem {
		Directory* m_root{};
		Directory* m_current{};
		std::string trim(const std::string& inc);
	public:
		Filesystem(const std::string& name, const std::string& contents = "");

		Filesystem(const Filesystem& inc) = delete;
		Filesystem& operator=(const Filesystem& inc) = delete;

		Filesystem(Filesystem&& inc);
		Filesystem& operator=(Filesystem&& inc);

		Filesystem& operator+=(Resource* inc);
		Directory* change_directory(const std::string& name = "");
		Directory* get_current_directory() const;
		~Filesystem();


	};
}
#endif // !SDDS_FILESYSTEM_H

