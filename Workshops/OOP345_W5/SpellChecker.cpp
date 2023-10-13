#include <fstream>
#include "SpellChecker.h"

namespace sdds {
	SpellChecker::SpellChecker(const char* filename)
	{
		std::string contents{};

		if (filename != nullptr)
		{
			std::fstream file(filename);

			if (file.is_open())
			{
				file.get(contents,)
			}
			//while(m_badWords[5] == "" || )
		}
		else
		{
			throw "Bad file name!";
		}
	}
	void SpellChecker::operator()(std::string& text)
	{

	}
	void SpellChecker::showStatistics(std::ostream& out) const
	{

	}
}
