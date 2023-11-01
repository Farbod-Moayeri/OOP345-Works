#include "File.h"

namespace sdds {
	File::File(const std::string& filename, const std::string& contents)  
	{
		if (filename.length() > 0)
		{
			m_name = filename;
		}

		if (contents.length() > 0)
		{
			m_contents = contents;
		}
	}
	void File::update_parent_path(const std::string& inc)
	{
		m_parent_path = inc;
	}

	NodeType File::type() const
	{
		return sdds::NodeType::FILE;
	}
	std::string File::path() const
	{
		return m_parent_path;
	}
	std::string File::name() const
	{
		return m_name;
	}
	int File::count() const
	{
		return -1;
	}
	size_t File::size() const
	{
		return m_contents.size();
	}
}
