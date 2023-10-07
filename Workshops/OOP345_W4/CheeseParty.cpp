#include <iostream>
#include "CheeseParty.h"

namespace sdds {
    CheeseParty& CheeseParty::addCheese(const Cheese& inc)
    {
        size_t i{};
        bool alreadyExists{ false };
        const Cheese** local{ nullptr };

        if (inc)
        {
            for (i = 0; i < m_numCheese; i++)
            {
                if (m_cheeses[i] == &inc)
                {
                    alreadyExists = true;
                }
            }

            if (!alreadyExists)
            {
                local = new const Cheese * [m_numCheese + 1];

                for (i = 0; i < m_numCheese; i++)
                {
                    local[i] = m_cheeses[i];
                }

                local[m_numCheese] = &inc;

                delete[] m_cheeses;
                m_cheeses = local;
            }
        }

        return *this;
    }
    CheeseParty& CheeseParty::removeCheese()
    {
        size_t i{};

        for (i = 0; i < m_numCheese; i++)
        {
            if (m_cheeses[i] != nullptr && m_cheeses[i]->getWeight() == 0)
            {
                m_cheeses[i] = nullptr;
            }
        }

        return *this;
    }

    CheeseParty::operator bool() const
    {
        return m_numCheese > 0;
    }
    
    std::ostream& operator<<(std::ostream& ostr, const CheeseParty& inc)
    {
        size_t i{};

        ostr << "--------------------------" << '\n';
        ostr << "Cheese Party" << '\n';
        ostr << "--------------------------" << '\n';

        if (inc)
        {
            for (i = 0; i < inc.m_numCheese; i++)
            {
                ostr << *inc.m_cheeses[i];
            }
        }
        else
        {
            ostr << "This party is just getting started!" << '\n';
        }

        ostr << "--------------------------";

        return ostr;
    }

}
