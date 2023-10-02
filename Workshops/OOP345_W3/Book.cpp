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

#include "Book.h"

#include <iomanip>

namespace sdds {

	Book::Book(const std::string& title, unsigned nChapters, unsigned nPages)
	{
		if (title.length() > 0 && nChapters > 0 && nPages > 0)
		{
			m_title = title;
			m_numChapters = nChapters;
			m_numPages = nPages;
		}
	}

	Book::operator bool() const
	{
		bool isValid = false;

		if (m_title.length() > 1 && m_numPages > 1 && m_numChapters > 1)
		{
			isValid = true;
		}

		return isValid;
	}
	Book::Book(const Book& inc)
	{
		operator=(inc);
	}
	Book& Book::operator=(const Book& inc)
	{
		if (&inc != this && inc)
		{
			m_title = inc.m_title;
			m_numPages = inc.m_numPages;
			m_numChapters = inc.m_numChapters;
		}
		
		return *this;
	}

	Book::Book(Book&& inc)
	{
		*this = std::move(inc);
	}
	Book& Book::operator=(Book&& inc)
	{
		if (&inc != this && inc)
		{
			m_title = inc.m_title;
			m_numPages = inc.m_numPages;
			m_numChapters = inc.m_numChapters;

			inc.m_title = "";
			inc.m_numPages = 0;
			inc.m_numChapters = 0;
		}

		return *this;
	}
	
	std::ostream& Book::print(std::ostream& os) const
	{
		if (*this)
		{
			std::string firstLine = m_title + ',' + std::to_string(m_numChapters) + ',' + std::to_string(m_numPages);
			std::string secondLine = "(" + std::to_string(static_cast<double> (m_numPages) / m_numChapters) + ")";

			os << std::setw(56) << std::right << firstLine << " | " << std::setw(15) << std::left << secondLine;
		}
		else
		{
			os << "| " << "Invalid book data";
		}

		return os;
	}

	std::string const Book::getTitle() const 
	{
		return m_title;
	}

	unsigned Book::getChapters() const
	{
		return m_numChapters;
	}

	unsigned Book::getPages() const
	{
		return m_numPages;
	}

	bool operator>(const Book& inc1, const Book& inc2)
	{
		bool isValid = false;

		if (inc1 && inc2)
		{
			isValid = static_cast<double> (inc1.getPages()) / inc1.getChapters() > static_cast<double> (inc2.getPages()) / inc2.getChapters();
		}
		else if (inc1)
		{
			isValid = true;
		}
		else if (inc2)
		{
			isValid = false;
		}
		
		return isValid;
	}

	bool operator<(const Book& inc1, const Book& inc2)
	{
		bool isValid = false;

		if (inc1 && inc2)
		{
			isValid =  static_cast<double> (inc1.getPages()) / inc1.getChapters() < static_cast<double> (inc2.getPages()) / inc2.getChapters();
		}
		else if (inc1)
		{
			isValid = true;
		}
		else if (inc2)
		{
			isValid = false;
		}

		return isValid;
	}

	std::ostream& operator<<(std::ostream& os, const Book& bk)
	{
		bk.print(os);

		return os;
	}
}

