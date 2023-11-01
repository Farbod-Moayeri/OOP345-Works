#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include <string>
#include "Resource.h"

namespace sdds {
	class File : public Resource{
		std::string m_contents{};
	public:
		File() = default;
		File(const std::string& filename, const std::string& contents = "");
		virtual void update_parent_path(const std::string& inc) override;
		virtual NodeType type() const override;
		virtual std::string path() const override;
		virtual std::string name() const override;
		virtual int count() const override;
		virtual size_t size() const override;
	};
}
#endif // !SDDS_FILE_H

