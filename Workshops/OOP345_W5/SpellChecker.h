#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

#include <string>

namespace sdds {
	class SpellChecker {
		std::string m_badWords[6]{};
		std::string m_goodWords[6]{};
		size_t m_wordReplaced[6]{};
		size_t m_wordsStored{};
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;
	};
}
#endif // !SDDS_SPELLCHECKER_H

