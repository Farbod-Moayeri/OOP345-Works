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

                m_numCheese++;
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

    CheeseParty::~CheeseParty()
    {
        delete[] m_cheeses;
    }

    CheeseParty::CheeseParty(const CheeseParty& inc)
    {
        operator=(inc);
    }

    CheeseParty& CheeseParty::operator=(const CheeseParty& inc)
    {
        size_t i{};

        if (this != &inc && inc)
        {
            delete[] m_cheeses;
            m_numCheese = inc.m_numCheese;

            m_cheeses = new const Cheese * [m_numCheese];
            
            for (i = 0; i < m_numCheese; i++)
            {
                m_cheeses[i] = inc.m_cheeses[i];
            }

        }

        return *this;
    }

    CheeseParty::CheeseParty(CheeseParty&& inc) noexcept
    {
        *this = std::move(inc);
    }

    CheeseParty& CheeseParty::operator=(CheeseParty&& inc) noexcept
    {
        if (this != &inc)
        {
            delete[] m_cheeses;
            m_cheeses = inc.m_cheeses;
            inc.m_cheeses = nullptr;

            m_numCheese = inc.m_numCheese;
            inc.m_numCheese = 0;
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
                if (inc.m_cheeses[i] != nullptr)
                {
                    ostr << *inc.m_cheeses[i];
                }
            }
        }
        else
        {
            ostr << "This party is just getting started!" << '\n';
        }

        ostr << "--------------------------" << '\n';

        return ostr;
    }

}
