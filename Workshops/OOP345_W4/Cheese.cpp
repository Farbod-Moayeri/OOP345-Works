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

#include <iostream>
#include <iomanip>
#include "Cheese.h"

namespace sdds {
	std::string Cheese::trim(const std::string& inc) const
	{
		std::string local{};
		size_t first{};
		size_t last{};
		
		local = inc;
		first = inc.find_first_not_of(' ');

		if (first == std::string::npos)
		{
			first = 0;
		}
		
		last = inc.find_last_not_of(' ');
		
		if (last == std::string::npos)
		{
			last = inc.length();
		}

		return inc.substr(first, last - first + 1);
	}
	Cheese::Cheese(const std::string& str)
	{
		if (str.length() > 0)
		{
			std::string cpy = str;

			m_name = trim(cpy.substr(0, cpy.find(',')));
			cpy.erase(0, cpy.find(',') + 1);

			m_weight = std::stoul(trim(cpy.substr(0 , cpy.find(','))));
			cpy.erase(0, cpy.find(',') + 1);

			m_price = std::stod(trim(cpy.substr(0 , cpy.find(','))));
			cpy.erase(0, cpy.find(',') + 1);

			while (cpy.length() > 0)
			{
				m_features += trim(cpy.substr(0, cpy.find(','))) + " ";

				if (cpy.find(',') == std::string::npos)
				{
					cpy = "";
				}
				else
				{
					cpy.erase(0, cpy.find(',') + 1);
				}
				
			}

			// m_features = trim(m_features);
		}
	}
	Cheese Cheese::slice(size_t weight)
	{
		Cheese local{};

		if (weight < m_weight)
		{
			local = *this;

			m_weight -= weight;

			local.m_weight = weight;
		}

		return local;
	}
	Cheese::Cheese(const Cheese& inc)
	{
		*this = inc;
	}
	Cheese& Cheese::operator=(const Cheese& inc)
	{
		if (this != &inc && inc.m_name.length() > 0 && inc.m_name != "NaC")
		{
			m_name = inc.m_name;
			m_weight = inc.m_weight;
			m_price = inc.m_price;
			m_features = inc.m_features;
		}

		return *this;
	}
	Cheese::Cheese(Cheese&& inc) noexcept
	{
		*this = std::move(inc);
	}
	Cheese& Cheese::operator=(Cheese&& inc) noexcept
	{
		if (this != &inc)
		{
			m_name = std::move(inc.m_name);
			m_weight = inc.m_weight;
			m_price = inc.m_price;
			m_features = std::move(inc.m_features);

			inc.m_name = "";
			inc.m_weight = 0;
			inc.m_price = 0.0;
			inc.m_features = "";
		}

		return *this;
	}
	std::string Cheese::getName() const
	{
		return m_name;
	}
	int Cheese::getWeight() const
	{
		return m_weight;
	}
	double Cheese::getPrice() const
	{
		return m_price;
	}
	std::string Cheese::getFeatures() const
	{
		return m_features;
	}

	std::ostream& operator<<(std::ostream& ostr, const Cheese& inc)
	{
		ostr << "|" << std::left << std::setw(21) << inc.getName();
		ostr << "|" << std::setw(5) << inc.getWeight();
		ostr << "|" << std::fixed << std::setprecision(2) << std::setw(5) << inc.getPrice();
		ostr << "|" << std::right << std::setw(34) << inc.getFeatures() << "|" << '\n';

		return ostr;
	}
}
