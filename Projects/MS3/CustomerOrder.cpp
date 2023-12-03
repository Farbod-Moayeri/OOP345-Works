// Name: Farbod Moayeri
// Seneca Student ID: 134395227
// Seneca email: fmoayeri2@myseneca.ca
// Date of completion: 2023/12/02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"

namespace sdds {

	size_t sdds::CustomerOrder::m_widthField;

	size_t CustomerOrder::getOrderCount(const std::string item) const
	{
		size_t count{};

		for (auto i = 0u; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == item)
			{
				count++;
			}
		}
		return count;
	}

	Item* CustomerOrder::getItemNotFilled(const std::string& itemName)
	{

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (itemName == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled == false)
			{
				return m_lstItem[i];
			}
		}


		return nullptr;
		
	}

	CustomerOrder::CustomerOrder(const std::string& order)
	{
		

		if (!order.empty())
		{
			Utilities ut;
			bool more{ true };
			size_t next_pos{ 0 };
			Item* local{ nullptr };
			std::vector<Item*> storage{};


			//try {
				if (more)
					m_name = ut.extractToken(order, next_pos, more);
				if (more)
					m_product = ut.extractToken(order, next_pos, more);
				if (more)
				{
					while (more)
					{
						local = new Item(ut.extractToken(order, next_pos, more));
						storage.push_back(local);
					}
				}
			//}
			//catch (std::invalid_argument& e) {
				
			//}
			
			if (storage.size() > 0)
			{
				int i{};

				m_cntItem = storage.size();

				m_lstItem = new Item * [m_cntItem];


				std::for_each(storage.begin(), storage.end(), [this, &i](Item* current) {

					m_lstItem[i] = current;
					i++;
					});
			}

			if (m_widthField < ut.getFieldWidth())
			{
				m_widthField = ut.getFieldWidth();
			}

		}

		
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& inc)
	{
		throw std::string("Copy Constructor is not allowed for this class");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& inc) noexcept
	{
		*this = std::move(inc);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& inc) noexcept
	{
		if (this != &inc)
		{
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];

			delete[] m_lstItem;
			m_lstItem = inc.m_lstItem;
			inc.m_lstItem = nullptr;

			m_cntItem = inc.m_cntItem;
			inc.m_cntItem = 0;

			m_name = inc.m_name;
			inc.m_name.clear();

			m_product = inc.m_product;
			inc.m_product.clear();

		}

		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];

		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool isFilled = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
			{
				isFilled = false;
			}
		}


		return isFilled;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool isFilled = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (itemName == m_lstItem[i]->m_itemName && m_lstItem[i]->m_isFilled == false)
			{
				isFilled = false;
			}
		}


		return isFilled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		if (containsItem(station.getItemName()))
		{
			
			if (isItemFilled(station.getItemName()) == false)
			{
				if (station.getQuantity() > 0)
				{
					

					Item* item = getItemNotFilled(station.getItemName());
					// item cannot be nullptr because containsItem above already ruled out Item not existing and isItemFilled ruled out the item being already filled
					item->m_isFilled = true;
					station.updateQuantity();
					item->m_serialNumber = station.getNextSerialNumber();

					

					os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << "\n";
				}
				else
				{
					for (auto i = 0u; i < getOrderCount(station.getItemName()); i++)
					{
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]" << "\n";
					}
					
				}
				
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << '\n';
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::right << std::setw(6) <<std::setfill('0') << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";

			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED";
			}
			else
			{
				os << "TO BE FILLED";
			}

			os << "\n";
		}
	}

	bool CustomerOrder::containsItem(const std::string& itemName) const
	{
		bool isFound = false;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (itemName == m_lstItem[i]->m_itemName)
			{
				isFound = true;
			}
		}


		return isFound;
	}
}