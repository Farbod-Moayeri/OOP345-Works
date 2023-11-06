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
		Resource* tempR = nullptr;

		std::vector<OpFlags> recursiveSearch{};
		recursiveSearch.push_back(OpFlags::RECURSIVE);
		
		
		
		
		

		if (!name.empty())
		{
			

			std::fstream file(name);

			if (file.is_open())
			{
				m_root = new Directory(contents);
				m_current = m_root;
				while (file.good() && !isComplete)
				{
				
					toFind = nullptr;
					std::getline(file, firstPart, '\n');
					
					if (firstPart.find('|') != std::string::npos)
					{
						secondPart = firstPart.substr(firstPart.find('|') + 1, firstPart.find('\n'));
						firstPart.erase(firstPart.find('|'));
						firstPart = trim(firstPart);
						secondPart = trim(secondPart);
					}
					else
					{
						secondPart = "";
					}
					
					while (firstPart.find('/') != std::string::npos)
					{
						temp2 = temp;
						temp = trim(firstPart.substr(0, firstPart.find('/') + 1));

						firstPart.erase(0, firstPart.find('/') + 1);

						if (toFind == nullptr)
						{
							toFind = m_root->find(temp, recursiveSearch);
							if (toFind != nullptr)
								continue;
						}
					
						if (toFind == nullptr)
						{
							local = new Directory(temp);
							//local->update_parent_path(m_root->path());

							if (!folderCreated)
							{
								folderCreated = true;
							}
							else
							{
								if ((toFind = dynamic_cast<Directory*>(local)->find(temp2, recursiveSearch)) == nullptr)
								{
									tempR = new Directory(temp);
									tempR->update_parent_path(dynamic_cast<Directory*>(local)->name());
									dynamic_cast<Directory*>(local)->operator+=(tempR);
									tempR = nullptr;
								}
								else
								{
									tempR = new Directory(temp);
									tempR->update_parent_path(dynamic_cast<Directory*>(toFind)->name());
									dynamic_cast<Directory*>(toFind)->operator+=(tempR);
									tempR = nullptr;
								}
							}
						}
						else
						{
							tempR = new Directory(temp);
							tempR->update_parent_path(dynamic_cast<Directory*>(toFind)->path());
							dynamic_cast<Directory*>(toFind)->operator+=(tempR);
							tempR = nullptr;
							toFind = nullptr;
						}
					}

					if (!secondPart.empty())
					{
						temp2 = temp;
						temp = trim(firstPart.substr(0, firstPart.find('\n')));
						firstPart.erase();

						if (!temp.empty())
						{
							if (local != nullptr)
							{
								tempR = new File(temp, secondPart);
								tempR->update_parent_path(local->path());
								dynamic_cast<Directory*>(local)->operator+=(tempR);
								tempR = nullptr;

							}
							else 
							{
								if ((toFind = m_root->find(temp2, recursiveSearch)) != nullptr)
								{
									tempR = new File(temp, secondPart);
									tempR->update_parent_path(toFind->path());
									dynamic_cast<Directory*>(toFind)->operator+=(tempR);
									tempR = nullptr;
								}
								else
								{
									m_root->operator+=(new File(temp, secondPart));
								}
							}
						}
					}
					
					if(folderCreated)
						m_root->operator+=(local);
						
					folderCreated = false;
					local = nullptr;
					temp = "";
				}
			}
			else
			{
				throw "Filesystem not created with invalid filename.\n";
			}

			if (file.is_open())
				file.close();
		}
		
	}

	Filesystem::Filesystem(Filesystem&& inc)
	{
		*this = std::move(inc);
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

		return *this;
	}

	Directory* Filesystem::change_directory(const std::string& name)
	{
		Directory* local = nullptr;
		std::vector<OpFlags> recursiveSearch{};
		recursiveSearch.push_back(OpFlags::RECURSIVE);
		
		if (name.empty())
		{
			m_current = m_root;
			local = m_root;
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

	Filesystem::~Filesystem()
	{
		delete m_root;
	}
}