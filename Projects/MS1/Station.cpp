#include "Station.h"
#include <iomanip>

namespace sdds {
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        try {
            m_itemName = util.extractToken(record, next_pos, more);
            if (more) {
                m_serialNumber = std::stoi(util.extractToken(record, next_pos, more));
            }
            if (more) {
                m_quantity = std::stoul(util.extractToken(record, next_pos, more));
            }
            if (more) {
                m_widthField = std::max(m_widthField, util.getFieldWidth());
                m_description = util.extractToken(record, next_pos, more);
            }

            m_id = ++id_generator;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::setfill('0') << m_id << " | ";
        os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << std::right << " | ";
        os << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << m_quantity << " | "
                << m_description << std::endl;
        }
        else {
            os << std::endl;
        }
    }
}
