#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include  "Cheese.h"

namespace sdds {
	class CheeseParty {
		Cheese** m_cheeses{ nullptr };
		size_t  m_numCheese{ 0 };
	public:
		CheeseParty() = default;
		CheeseParty& addCheese(const Cheese& inc);
		CheeseParty& removeCheese();
	};
}
#endif // !SDDS_CHEESEPARTY_H

