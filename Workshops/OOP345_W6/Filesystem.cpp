#include <fstream>
#include "Resource.h"
#include "File.h"
#include "Filesystem.h"


namespace sdds {
	std::string Filesystem::trim(const std::string& inc)
	{
		std::string local{};
		size_t first{};
		size_t last{};

		local = inc;
		first = inc.find_first_not_of(' ');

		if (first == std::string::npos)
		{
			first = 0;
		}

		last = inc.find_last_not_of(' ');

		if (last == std::string::npos)
		{
			last = inc.length();
		}

		return inc.substr(first, last - first + 1);
	}

	Filesystem::Filesystem(const std::string& name, const std::string& contents)
	{
		std::string firstPart{};
		std::string secondPart{};
		std::string temp{};
		std::string temp2{};
		bool folderCreated = false;
		bool isComplete = false;
		Resource* local = nullptr;
		Resource* toFind = nullptr;
		Directory* found = nullptr;

		std::vector<OpFlags> recursiveSearch{};
		recursiveSearch.push_back(OpFlags::RECURSIVE);
		
		m_root = new Directory(contents);
		m_current = m_root;

		if (!name.empty())
		{
			std::fstream file(name);
			if (file.is_open())
			{
				while (file.good() && !isComplete)
				{
					std::getline(file, firstPart, '|');
					std::getline(file, secondPart, '\n');

					firstPart = trim(firstPart);
					secondPart = trim(secondPart);

					while (firstPart.find('/') != std::string::npos)
					{
						temp = trim(firstPart.substr(0, firstPart.find('/')));
						firstPart.erase(0, firstPart.find('/') + 1);

						local = new Directory(temp);
						toFind = m_root->find(temp, recursiveSearch);

						if (!folderCreated)
						{
							folderCreated = true;

							if (!toFind)
							{
								m_root->operator+=(local);
								local = nullptr;
							}
							else
							{
								delete[] local;
								local = nullptr;
							}

						}
						else
						{
							if (!toFind)
							{
								found = dynamic_cast<Directory*>(toFind);
								if (found)
								{
									found->operator+=(local);
									local = nullptr;
								}
							}
						}
					}

					folderCreated = false;

					temp = trim(firstPart.substr(0, firstPart.find('\n')));
					firstPart.erase(0, firstPart.find('/') + 1);

					if (temp.length() > 0)
					{
						local = new File(temp, secondPart);
						found->operator+=(local);
						local = nullptr;
					}



				}
			}
		}
		
	}

	Filesystem::Filesystem(Filesystem&& inc)
	{
		std::move(inc);
	}

	Filesystem& Filesystem::operator=(Filesystem&& inc)
	{
		if (&inc != this)
		{
			m_root = inc.m_root;
			inc.m_root = nullptr;

			m_current = inc.m_current;
			inc.m_current = nullptr;
		}

		return *this;
	}

	Filesystem& Filesystem::operator+=(Resource* inc)
	{
		if (m_current->find(inc->name()) == nullptr)
		{
			m_current->operator+=(inc);
		}
	}

	Directory* Filesystem::change_directory(const std::string& name)
	{
		Directory* local = nullptr;
		std::vector<OpFlags> recursiveSearch{};
		recursiveSearch.push_back(OpFlags::RECURSIVE);
		
		if (name.empty())
		{
			m_current = m_root;
		}
		else
		{
			local = dynamic_cast<Directory*>(m_root->find(name, recursiveSearch));
			if (local == nullptr)
			{
				throw std::invalid_argument{"Cannot change directory! DIR_NAME not found!"};
			}
			else
			{
				m_current = local;
			}
		}

		return local;

	}

	Directory* Filesystem::get_current_directory() const 
	{
		return m_current;
	}
}