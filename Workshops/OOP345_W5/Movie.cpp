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
#include "Movie.h"

namespace sdds {
    std::string Movie::trim(const std::string& inc) const
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
    Movie::operator bool() const
    {
        return m_title.length() > 0 && m_year != 0 && m_description.length() > 0;
    }
    const std::string& Movie::title() const
    {
        return m_title;
    }

    Movie::Movie(const std::string& strMovie)
    {
        std::string local{};

        if (strMovie.length() > 0)
        {
            local = strMovie;

            m_title = trim(local.substr(0, local.find(',')));
            local.erase(0, local.find(',') + 1);

            m_year = stoi(trim(local.substr(0, local.find(','))));
            local.erase(0, local.find(',') + 1);

            m_description = trim(local.substr(0, local.find('\n')));
        }


    }
    std::ostream& operator<<(std::ostream& ostr, const Movie& inc)
    {
        if (inc)
        {
            ostr << std::setw(40) << inc.m_title << " | " << std::setw(4) << inc.m_year << " | " << inc.m_description << '\n';
        }

        return ostr;
    }
}
