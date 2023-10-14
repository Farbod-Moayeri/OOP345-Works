#include <fstream>
#include "SpellChecker.h"

namespace sdds {
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
					numLines++;
				}

				file.clear();
				file.seekg(0, std::ios::beg);

				file >> contents;

				for (i = 0; i < numLines; i++)
				{
					m_badWords[i] = contents.substr(0, contents.find(' '));
					contents.erase(0, contents.find_last_of(' ') + 1);

					m_goodWords[i] = contents.substr(0, contents.find(' '));
					contents.erase(0, contents.find('\n') + 1);
				}
				
				m_wordsStored = i;

				file.close();
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
				while(start = text.find())
				text.replace(start,text.find(m_badWords[i]), m_goodWords[i]);

			}
		}
	}
	void SpellChecker::showStatistics(std::ostream& out) const
	{

	}
}
