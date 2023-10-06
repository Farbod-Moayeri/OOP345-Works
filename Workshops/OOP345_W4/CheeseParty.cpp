#include "CheeseParty.h"

namespace sdds {
    CheeseParty& CheeseParty::addCheese(const Cheese& inc)
    {
        size_t i{};
        bool alreadyExists{ false };
        Cheese** local{ nullptr };

        if (inc)
        {
            for (i = 0; i < m_numCheese; i++)
            {
                if (m_cheeses[i] == &inc)
                {
                    alreadyExists = true;
                }

                if (!alreadyExists)
                {
                    local = new Cheese * [m_numCheese + 1];

                    for (i = 0; i < m_numCheese; i++)
                    {
                        local[i] = m_cheeses[i];
                        //
                    }
                }
            }
        }

        return *this;
    }
}
