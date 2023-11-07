// Name: Farbod Moayeri
// Seneca Student ID:
// Seneca email: fmoayeri2@outlook.ca
// Date of completion: 2023/11/07
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <stdexcept>
#include "Utilities.h"

namespace sdds {


    char Utilities::m_delimiter = ' '; 

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
       
        size_t pos = str.find(m_delimiter, next_pos);

        if (pos == next_pos) {
            more = false;
            throw std::invalid_argument("Delimiter found at next_pos.");
        }

        more = (pos != std::string::npos);
        std::string token = str.substr(next_pos, pos - next_pos);
        next_pos = more ? pos + 1 : pos;

        
        token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
        token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), token.end());

        
        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

}
