///////////////////////////////////////////////////////
//                  WorkShop 5 - Part 2
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

#include <iostream>
#include <fstream>
#include <iomanip>
#include "SpellChecker.h"


namespace sdds {
	std::string SpellChecker::trim(const std::string& inc) const
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
	SpellChecker::SpellChecker(const char* filename)
	{
		std::string contents{};
		size_t numLines{};
		size_t i{};

		if (filename != nullptr)
		{
			std::fstream file(filename);

			if (file.is_open())
			{
				while (file.good())
				{
					std::getline(file, contents, '\n');
					if (contents.length() > 0)
					{
						numLines++;
					}
				}

				file.clear();
				file.seekg(0, std::ios::beg);

				std::getline(file, contents, '\0');

				for (i = 0; i < numLines; i++)
				{
					m_badWords[i] = contents.substr(0, contents.find(' '));
					contents.erase(0, contents.find(' ') + 1);

					m_goodWords[i] = trim(contents.substr(0, contents.find_first_of('\n')));
					contents.erase(0, contents.find('\n') + 1);
				}
				
				m_wordsStored = i;

				file.close();
			}
			else
			{
				throw "Bad file name!";
			}
		}
		else
		{
			throw "Bad file name!";
		}
	}
	void SpellChecker::operator()(std::string& text)
	{
		size_t i{};
		size_t start{};

		if (text.length() > 0)
		{
			for (i = 0; i < m_wordsStored; i++)
			{
				start = 0;
				while ((start = text.find(m_badWords[i], start)) != std::string::npos)
				{
					text.replace(start, m_badWords[i].length(), m_goodWords[i]);
					start += m_goodWords[i].length();
					m_wordReplaced[i]++;
				}
			}
		}
	}
	void SpellChecker::showStatistics(std::ostream& out) const
	{
		std::cout << "Spellchecker Statistics\n";
		for (size_t i = 0; i < m_wordsStored; i++)
		{
			out << std::right << std::setw(15) << m_badWords[i] << ": " << m_wordReplaced[i] << " replacements\n";
		}
	}
}
