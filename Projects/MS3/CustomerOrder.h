// Name: Farbod Moayeri
// Seneca Student ID: 134395227
// Seneca email: fmoayeri2@myseneca.ca
// Date of completion: 2023/11/17
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <string>
#include "Station.h"

namespace sdds {

	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name;
		std::string m_product;
		size_t m_cntItem{ 0 };
		Item** m_lstItem{ nullptr };

		static size_t m_widthField;

		size_t getOrderCount(const std::string item) const;
		Item* getItemNotFilled(const std::string& itemName);

	public:
		CustomerOrder() = default;
		CustomerOrder(const std::string& order);

		CustomerOrder(const CustomerOrder& inc);
		CustomerOrder& operator=(const CustomerOrder& inc) = delete;
		CustomerOrder(CustomerOrder&& inc) noexcept;
		CustomerOrder& operator=(CustomerOrder&& inc) noexcept;
		virtual ~CustomerOrder();

		bool isOrderFilled() const;

		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);

		void display(std::ostream& os) const;

		bool containsItem(const std::string& itemName) const;
		

	};
}
#endif // !SDDS_CUSTOMERORDER_H

