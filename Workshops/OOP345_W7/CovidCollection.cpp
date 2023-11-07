#include <iomanip>
#include <fstream>
#include "CovidCollection.h"

namespace sdds {
	std::string CovidCollection::trim(const std::string& inc)
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

	CovidCollection::CovidCollection(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file) {
			throw std::invalid_argument("Could not open file");
		}

		std::string line{};

		while (getline(file, line)) {
			
			Covid local;
			local.m_country = trim(line.substr(0, 25));
			local.m_city = trim(line.substr(25, 25));
			local.m_variant = trim(line.substr(50, 25));
			local.m_year = std::stoi(trim(line.substr(75, 5)));
			local.m_numCases = std::stoul(trim(line.substr(80, 5)));
			local.m_numDeaths = std::stoul(trim(line.substr(85, 5)));
			m_covidCollection.push_back(local);
			
		}
	}

	void CovidCollection::display(std::ostream& ostr) const
	{
		for (const auto& record : m_covidCollection) {
			ostr << record << '\n';
		}
	}

	std::ostream& operator<<(std::ostream& ostr, const Covid& inc) {
		ostr << "| " << std::left << std::setw(21) << inc.m_country
			<< " | " << std::setw(15) << inc.m_city
			<< " | " << std::setw(20) << inc.m_variant
			<< " | ";
		if (inc.m_year >= 0) { 
			ostr << std::right << std::setw(6) << inc.m_year;
		}
		else {
			ostr << std::right << std::setw(6) << ""; 
		}
		ostr << " | " << std::setw(4) << inc.m_numCases
			<< " | " << std::setw(3) << inc.m_numDeaths << " |";
		return ostr;
	}

}
