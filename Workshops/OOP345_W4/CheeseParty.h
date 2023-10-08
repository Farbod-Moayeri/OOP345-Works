///////////////////////////////////////////////////////
//                  WorkShop 4 - Part 2
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

		// rule of five
		~CheeseParty();
		CheeseParty(const CheeseParty& inc);
		CheeseParty& operator=(const CheeseParty& inc);
		CheeseParty(CheeseParty&& inc) noexcept;
		CheeseParty& operator=(CheeseParty&& inc) noexcept;
		// rule of five

	};
}
#endif // !SDDS_CHEESEPARTY_H

