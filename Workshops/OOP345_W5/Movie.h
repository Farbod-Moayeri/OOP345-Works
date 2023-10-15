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

#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H

#include <string>

namespace sdds {
	class Movie {
		std::string m_title{};
		size_t m_year{};
		std::string m_description{};
		std::string trim(const std::string& inc) const;
		explicit operator bool() const;
	public:
		Movie() = default;
		const std::string& title() const;
		Movie(const std::string& strMovie);
		template<typename T>
		void fixSpelling(T& spellChecker)
		{
			spellChecker.operator()(m_title);
			spellChecker.operator()(m_description);
		}
		friend std::ostream& operator<<(std::ostream& ostr, const Movie& inc);
	};
}
#endif // !SDDS_MOVIE_H

