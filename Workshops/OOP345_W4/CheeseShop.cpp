#include <iostream>
#include "CheeseShop.h"

namespace sdds {
	CheeseShop::operator bool() const
	{
		return m_numProducts > 0;
	}
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
				local[i] = new Cheese;
				*local[i] = *this->m_products[i];
			}
			
			local[m_numProducts] = new Cheese;
			*local[m_numProducts] = inc;

			for (i = 0; i < m_numProducts; i++)
			{
				delete[] m_products[i];
			}

			delete[] m_products;

			m_numProducts++;


			m_products = local;
		}

		return *this;
	}

	CheeseShop::~CheeseShop()
	{
		size_t i{};

		for (i = 0; i < m_numProducts; i++)
		{
			delete m_products[i];
		}

		delete[] m_products;
	}

	CheeseShop::CheeseShop(const CheeseShop& inc)
	{
		operator=(inc);
	}

	CheeseShop& CheeseShop::operator=(const CheeseShop& inc)
	{
		size_t i{};

		if (this != &inc && inc)
		{
			for (i = 0; i < m_numProducts; i++)
			{
				delete m_products[i];
			}

			delete[] m_products;

			m_name = inc.m_name;
			m_numProducts = inc.m_numProducts;
			m_products = new Cheese * [m_numProducts];

			for (i = 0; i < m_numProducts; i++)
			{
				m_products[i] = new Cheese;
				*m_products[i] = *inc.m_products[i];
			}
		}

		return *this;
	}

	CheeseShop::CheeseShop(CheeseShop&& inc) noexcept
	{
		*this = std::move(inc);
	}

	CheeseShop& CheeseShop::operator=(CheeseShop&& inc) noexcept
	{
		size_t i{};

		if (this != &inc && inc)
		{
			for (i = 0; i < m_numProducts; i++)
			{
				delete m_products[i];
			}

			delete[] m_products;

			m_name = std::move(inc.m_name);
			m_numProducts = inc.m_numProducts;
			m_products = inc.m_products;

			inc.m_name = "";
			inc.m_numProducts = 0;
			inc.m_products = nullptr;
		}

		return *this;
	}

	std::ostream& operator<<(std::ostream& ostr, const CheeseShop& inc)
	{
		size_t i{};

		ostr << "--------------------------" << '\n';
		if (inc.m_name.length() > 0)
		{
			ostr << inc.m_name << '\n';
		}
		else
		{
			ostr << '\n';
		}
		ostr << "--------------------------" << '\n';

		if (inc)
		{
			for (i = 0; i < inc.m_numProducts; i++)
			{
				ostr << *inc.m_products[i];
			}
		}
		else
		{
			ostr << "This shop is out of cheese!" << '\n';
		}

		ostr << "--------------------------" << '\n';

		return ostr;
	}
}
