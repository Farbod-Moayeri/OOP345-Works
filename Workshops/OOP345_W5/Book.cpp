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

#include <iomanip>
#include <ostream>
#include "Book.h"

namespace sdds {
    std::string Book::trim(const std::string& inc) const
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
    Book::operator bool() const
    {
        return m_author.length() > 0;
    }
    const std::string& Book::title() const
    {
        return m_title;
    }
    const std::string& Book::country() const
    {
        return m_country;
    }
    const size_t& Book::year() const
    {
        return m_year;
    }
    double& Book::price()
    {
        return m_price;
    }
    Book::Book(const std::string& strBook)
    {
        if (strBook.length() > 0)
        {
            std::string cpy = strBook;

            m_author = trim(cpy.substr(0, cpy.find(',')));
            cpy.erase(0, cpy.find(',') + 1);

            m_title = trim(cpy.substr(0, cpy.find(',')));
            cpy.erase(0, cpy.find(',') + 1);

            m_country = trim(cpy.substr(0, cpy.find(',')));
            cpy.erase(0, cpy.find(',') + 1);

            m_price = std::stod(trim(cpy.substr(0, cpy.find(','))));
            cpy.erase(0, cpy.find(',') + 1);

            m_year = std::stoul(trim(cpy.substr(0, cpy.find(','))));
            cpy.erase(0, cpy.find(',') + 1);

            m_description = trim(cpy.substr(0, cpy.find(',')));
            cpy.erase(0, cpy.find('\n'));
        }
    }
    std::ostream& operator<<(std::ostream& ostr, const Book& inc)
    {
        if (inc)
        {
            ostr << std::setw(20) << inc.m_author << " | ";
            ostr << std::setw(22) << inc.m_title << " | ";
            ostr << std::setw(5) << inc.m_country << " | ";
            ostr << std::setw(4) << inc.m_year << " | ";
            ostr << std::setw(6) << std::setprecision(2) << inc.m_price << " | ";
            ostr << inc.m_description << '\n';
        }

        return ostr;
    }
}
