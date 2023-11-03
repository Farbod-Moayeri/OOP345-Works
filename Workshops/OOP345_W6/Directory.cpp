#include "Directory.h"

namespace sdds {
	Directory::Directory(const std::string& directName)
	{
		if (directName.length() > 0)
		{
			m_name.assign(directName, 0, directName.length() - 1);
		}
	}
	void Directory::update_parent_path(const std::string& path)
	{
		if (path.length() > 0)
		{
			m_parent_path = path;
			
			for (size_t i = 0u; i < m_count; i++)
			{
				m_contents[i]->update_parent_path(m_parent_path);
			}
		}
	}
	NodeType Directory::type() const
	{
		return sdds::NodeType::DIR;
	}
	std::string Directory::path() const
	{
		return m_parent_path + m_name;
	}
	std::string Directory::name() const
	{
		return m_name;
	}
	int Directory::count() const
	{
		return (int)m_count;
	}
	size_t Directory::size() const
	{
		size_t size = 0u;

		for (size_t i = 0u; i < m_count; i++)
		{
			size += m_contents[i]->size();
		}

		return size;
	}
	Directory& Directory::operator+=(Resource* inc)
	{
		bool alreadyExists = false;

		if (inc != nullptr)
		{
			for (size_t i = 0u; i < m_count && !alreadyExists; i++)
			{
				alreadyExists = m_contents[i]->name() == inc->name();
			}

			if (!alreadyExists)
			{
				m_contents.push_back(inc);
				m_count++;
				// inc = nullptr;
				m_contents.back()->update_parent_path(m_parent_path);
			}
			else
			{
				std::string err = "EXCEPTION: " + inc->name() + "already exists in the root\n";
				throw err.c_str();
			}
		}

		return *this;
		
	}
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& dir) {
		Resource* temp = nullptr;
		bool isRecursive = false;

		if (!name.empty()) {
			
			isRecursive = std::find(dir.begin(), dir.end(), OpFlags::RECURSIVE) != dir.end();

			
			if (isRecursive) {
				for (size_t i = 0u; i < m_count; i++) {
					if (m_contents[i]->type() == NodeType::DIR) {

						Directory* dirPtr = dynamic_cast<Directory*>(m_contents[i]);
						temp = dirPtr->find(name, dir); 
						
					}
					else
					{
						if(m_contents[i]->name() == name)
							temp = m_contents.data()[i];
					}

					if (temp != nullptr) {
						break;
					}
				}
			}
			
		}

		return temp;
	}

	Directory::~Directory()
	{
		for (size_t i = 0u; i < m_count; i++)
		{
			m_contents.pop_back();
		}
	}
}
