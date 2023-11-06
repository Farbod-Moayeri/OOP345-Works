///////////////////////////////////////////////////////
//                  WorkShop 6 - Part 2
// Name: Farbod Moayeri
// Id: 134395227
// Email: fmoayeri2@myseneca.ca
// Section: NFF
// Date: 2023-10-05
///////////////////////////////////////////////////////
// I have done all the coding by myself and only copied
// the code that my professor provided to complete my 
// workshops and assignments.
///////////////////////////////////////////////////////

#include <algorithm>
#include <iomanip>
#include "Directory.h"

namespace sdds {
	Directory::Directory(const std::string& directName)
	{
		if (directName.length() > 0)
		{
			m_name = directName;
		}
	}
	void Directory::update_parent_path(const std::string& path)
	{
		if (path.length() > 0)
		{
			m_parent_path = path;
			
			for (size_t i = 0u; i < m_contents.size(); i++)
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
		return (m_parent_path + m_name);
	}
	std::string Directory::name() const
	{
		return m_name;
	}
	int Directory::count() const
	{
		return (int)m_contents.size();
	}
	size_t Directory::size() const
	{
		size_t size = 0u;

		for (size_t i = 0u; i < m_contents.size(); i++)
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
			for (size_t i = 0u; i < m_contents.size() && !alreadyExists; i++)
			{
				alreadyExists = m_contents[i]->name() == inc->name();
			}

			if (!alreadyExists)
			{
				m_contents.push_back(inc);
				m_contents.back()->update_parent_path(m_parent_path + m_name);
			}
			else
			{
				std::string err = "EXCEPTION: " + inc->name() + "already exists in the root\n";
				delete inc;
				inc = nullptr;
				throw err;
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
				for (size_t i = 0u; i < m_contents.size(); i++) {
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
			else
			{
				for (size_t i = 0u; i < m_contents.size(); i++) {
					if (m_contents[i]->type() == NodeType::DIR)
					{
						if (m_contents[i]->name() == name)
						{
							temp = m_contents.data()[i];
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
		m_contents.clear();
	}
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& inc)
	{
		Resource* temp = this->find(name, inc);
		bool isRecursive = std::find(inc.begin(), inc.end(), OpFlags::RECURSIVE) != inc.end();
		

		if (temp == nullptr)
		{
			throw std::string("Name does not exist in " + name);
		}
		else
		{
			auto ele = std::find(m_contents.begin(), m_contents.end(), temp);
			if (temp->type() == sdds::NodeType::DIR)
			{
				if (isRecursive)
				{
					if (ele != m_contents.end())
					{
						delete temp;
						m_contents.erase(ele);
					}
					
				}
				else
				{
					throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
				}
			}
			else
			{
				if (ele != m_contents.end())
				{
					delete temp;
					m_contents.erase(ele);
				}
			}
			
		}
	}
	void Directory::display(std::ostream& ostr, const std::vector<FormatFlags>& inc) const
	{
		ostr << "Total size: " << this->size() << " bytes\n";
		bool isDir = false;
		bool isLong = std::find(inc.begin(), inc.end(), sdds::FormatFlags::LONG) != inc.end();
		std::string temp{};

		for (size_t i = 0u; i < m_contents.size(); i++)
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

			
			if (isLong)
			{
				ostr << " | " << std::left << std::setw(15) << m_contents[i]->name();
				temp = std::to_string(m_contents[i]->size()) + " bytes";
				if (isDir)
				{
					ostr << " | " <<  std::right << std::setw(2) << m_contents[i]->count() << " | " << std::right << std::setw(10) << temp << " | \n";
				}
				else
				{
					ostr << " |    | " << std::right << std::setw(10) << temp << " | \n";
				}
			}
			else
			{
				ostr << " | " << std::left << std::setw(15) << m_contents[i]->name() << " |" << "\n";
			}
		}
	}
}
