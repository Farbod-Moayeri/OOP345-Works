#include <iostream>
#include "CheeseShop.h"

namespace sdds {
	CheeseShop::CheeseShop(const std::string& name)
	{
		m_name = name;
	}
	CheeseShop& CheeseShop::addCheese(const Cheese& inc)
	{
		Cheese** local{ nullptr };
		size_t i{};

		if (inc.getName() != "NaC")
		{
			local = new Cheese*[m_numProducts + 1];

			for (i = 0; i < m_numProducts; i++)
			{
				local[i] = this->m_products[i];
			}
			
			
			*local[m_numProducts] = inc;
			m_numProducts++;

			/*for (i = 0; i < m_numProducts; i++)
			{
				delete m_products[i];
			}*/
			
			delete[] m_products;
			m_products = local;
		}

		return *this;
	}

	CheeseShop::~CheeseShop()
	{
		size_t i{};

		/*for (i = 0; i < m_numProducts; i++)
		{
			delete[] m_products[i];
		}*/

		delete[] m_products;
	}

	CheeseShop::CheeseShop(const CheeseShop& inc)
	{

	}

	CheeseShop& CheeseShop::operator=(const CheeseShop& inc)
	{
		size_t i{};

		if (this != &inc && inc.m_numProducts > 0)
		{
			for (i = 0; i < m_numProducts; i++)
			{
				delete[]
			}
		}

		return *this;
	}

	CheeseShop::CheeseShop(CheeseShop&& inc) noexcept
	{
	}

	CheeseShop& CheeseShop::operator=(CheeseShop&& inc) noexcept
	{
		// TODO: insert return statement here
	}

	std::ostream& operator<<(std::ostream& ostr, const CheeseShop& inc)
	{
		size_t i{};

		ostr << "--------------------------" << '\n';
		ostr << "SHOP_NAME" << '\n';
		ostr << "--------------------------" << '\n';

		if (inc.m_numProducts > 0)
		{
			for (i = 0; i < inc.m_numProducts; i++)
			{
				ostr << inc.m_products[i];
			}
		}
		else
		{
			ostr << "This shop is out of cheese!" << '\n';
		}

		ostr << "--------------------------";

		return ostr;
	}
}
