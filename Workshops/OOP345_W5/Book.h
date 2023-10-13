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

#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <string>

namespace sdds {
	class Book {
		std::string m_author{};
		std::string m_title{};
		std::string m_country{};
		size_t m_year{};
		double m_price{};
		std::string m_description{};
		std::string trim(const std::string& inc) const;
		explicit operator bool() const;
	public:
		// assignment specs
		Book() = default;
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();
		Book(const std::string& strBook);
		virtual friend std::ostream& operator<<(std::ostream& ostr, const Book& inc);
		// assignment specs

		// rule of five
		virtual ~Book() = default;
		Book(const Book& inc) = default;
		virtual Book& operator=(const Book& inc) = default;
		Book(Book&& inc) = default;
		virtual Book& operator=(Book&& inc) = default;
	};
}

#endif // !SDDS_BOOK_H

