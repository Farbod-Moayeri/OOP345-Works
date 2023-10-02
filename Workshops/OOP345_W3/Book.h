///////////////////////////////////////////////////////
//                  WorkShop 3 - Part 2
// Name: Farbod Moayeri
// Id: 134395227
// Email: fmoayeri2@myseneca.ca
// Section: NFF
// Date: 2023-09-23
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
		std::string m_title{};
		unsigned m_numChapters{ 0 };
		unsigned m_numPages{ 0 };

	public:

		Book() = default;
		Book(const std::string& title, unsigned nChapters, unsigned nPages);
		explicit operator bool() const;

		// rule of five
		Book(const Book& inc);
		virtual Book& operator=(const Book& inc);
		virtual ~Book() = default;
		Book(Book&& inc);
		virtual Book& operator=(Book&& inc);
		// rule of five

		virtual std::ostream& print(std::ostream& os) const;

		// getters
		std::string const getTitle() const;
		unsigned getChapters() const;
		unsigned getPages() const;

	};

	bool operator>(const Book& inc1, const Book& inc2);
	bool operator<(const Book& inc1, const Book& inc2);
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}
#endif // !SDDS_BOOK_H

