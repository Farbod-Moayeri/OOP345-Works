///////////////////////////////////////////////////////
//                  WorkShop 4 - Part 2
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

#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include <string>
#include "Cheese.h"

namespace sdds {
	class CheeseShop {
		std::string m_name{};
		Cheese** m_products{ nullptr };
		size_t m_numProducts{ 0 };
		explicit operator bool() const;
	public:
		// spec requirements
		CheeseShop(const std::string& name = "No Name");
		CheeseShop& addCheese(const Cheese& inc);
		friend std::ostream& operator<<(std::ostream& ostr, const CheeseShop& inc);
		// spec requirements
		
		// rule of five
		~CheeseShop();
		CheeseShop(const CheeseShop& inc);
		CheeseShop& operator=(const CheeseShop& inc);
		CheeseShop(CheeseShop&& inc) noexcept;
		CheeseShop& operator=(CheeseShop&& inc) noexcept;
		// rule of five
	};

	
}
#endif // !SDDS_CHEESESHOP_H

