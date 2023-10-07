#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include  "Cheese.h"

namespace sdds {
	class CheeseParty {
		const Cheese** m_cheeses{ nullptr };
		size_t  m_numCheese{ 0 };
		explicit operator bool() const;
	public:

		// requirements
		CheeseParty() = default;
		CheeseParty& addCheese(const Cheese& inc);
		CheeseParty& removeCheese(); 
		friend std::ostream& operator<<(std::ostream& ostr, const CheeseParty& inc);
		// requirements

		


	};
}
#endif // !SDDS_CHEESEPARTY_H

