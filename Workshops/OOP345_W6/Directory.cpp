#include <algorithm>
#include <iomanip>
#include "Directory.h"

namespace sdds {
	Directory::Directory(const std::string& directName)
	{
		if (directName.length() > 0)
		{
			m_name.assign(directName, 0, directName.length());
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
		bool isFound = false;

		if (!name.empty()) {

			isRecursive = std::find(dir.begin(), dir.end(), OpFlags::RECURSIVE) != dir.end();

			if (isRecursive) {
				for (size_t i = 0u; i < m_count; i++) {
					if (m_contents[i]->type() == NodeType::DIR) 
					{
						if (m_contents[i]->name() == name)
						{
							temp = m_contents.data()[i];
						}
						else
						{
							Directory* dirPtr = dynamic_cast<Directory*>(m_contents[i]);
							temp = dirPtr->find(name, dir);
						}
					}
					else
					{
						if (m_contents[i]->name() == name)
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
		for (auto ptr : m_contents)
		{
			delete ptr;
		}
	}
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& inc)
	{
		Resource* temp = this->find(name, inc);
		bool isRecursive = std::find(inc.begin(), inc.end(), OpFlags::RECURSIVE) != inc.end();

		if (temp == nullptr)
		{
			throw std::string("Name does not exist in " + name);
		}
		else if (temp != nullptr)
		{
			if (temp->type() == sdds::NodeType::DIR)
			{
				if (isRecursive)
				{
					delete temp;
					temp = nullptr;
				}
				else
				{
					throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
				}
			}
			else
			{
				delete temp;
				temp = nullptr;
			}
			
		}
	}
	void Directory::display(std::ostream& ostr, const std::vector<FormatFlags>& inc) const
	{
		ostr << "Total size: " << this->size() << " bytes\n";
		bool isDir = false;
		bool isLong = std::find(inc.begin(), inc.end(), sdds::FormatFlags::LONG) != inc.end();

		for (size_t i = 0u; i < m_count; i++)
		{
			isDir = m_contents[i]->type() == sdds::NodeType::DIR;

			if (isDir)
			{
				ostr << "D";
			}
			else
			{
				ostr << "F";
			}

			ostr << " | " << std::left << std::setw(15) << m_contents[i]->name();
			// m_contents.size(); 
			if (isLong)
			{
				if (isDir)
				{
					ostr << " | " <<  std::right << std::setw(2) << m_contents[i]->count() << " | " << std::right << std::setw(10) << m_contents[i]->size() << " bytes |\n";
				}
				else
				{
					ostr << " | "  << std::setw(2) << " | " << std::right << std::setw(10) << m_contents[i]->size() << " bytes |\n";
				}


			}
		}
	}
}
