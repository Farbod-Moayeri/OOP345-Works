///////////////////////////////////////////////////////
//                  WorkShop 7 - Part 2
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

#include <iomanip>
#include <fstream>
#include <algorithm>
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

	void CovidCollection::display(std::ostream& out, const std::string& country) const
	{
		unsigned deaths{};
		unsigned cases{};
		unsigned countryDeaths{};
		unsigned countryCases{};
		std::string temp{};

		if (country == "ALL")
		{
			for (const auto& record : m_covidCollection) {
				out << record << '\n';
				deaths += record.m_numDeaths;
				cases += record.m_numCases;
			}
			temp = "Total cases around the world: " + std::to_string(cases) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
			temp = "Total deaths around the world: " + std::to_string(deaths) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
		}
		else
		{
			out << "Displaying information of country = " << country << "\n";
			for (const auto& record : m_covidCollection) {
				countryDeaths += record.m_numDeaths;
				countryCases += record.m_numCases;
				if (record.m_country == country)
				{
					out << record << '\n';
					deaths += record.m_numDeaths;
					cases += record.m_numCases;
				}				
			}
			out << std::setfill('-') << std::setw(89) << '\n' << std::setfill(' ');
			temp = "Total cases around the world: " + std::to_string(cases) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
			temp = "Total deaths around the world: " + std::to_string(deaths) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
			temp = country + " has " + std::to_string((double)cases / countryCases * 100) + " of global cases and " + std::to_string((double)deaths / countryDeaths * 100) + " of global deaths" + " |" + '\n';
			out << "| " << std::setw(87) << temp;
		}
		
	}

	void CovidCollection::sort(const std::string& field) {
		auto byField = [field](const Covid& a, const Covid& b) -> bool {
			if (field == "country") return a.m_country < b.m_country;
			if (field == "city") return a.m_city < b.m_city;
			if (field == "variant") return a.m_variant < b.m_variant;
			if (field == "general") return a.m_status < b.m_status;
			return false; 
		};

		if (field == "deaths") {
			std::sort(m_covidCollection.begin(), m_covidCollection.end(), [](const Covid& a, const Covid& b) {
				return a.m_numDeaths < b.m_numDeaths;
				});
		}
		else if (field == "cases") {
			std::sort(m_covidCollection.begin(), m_covidCollection.end(), [](const Covid& a, const Covid& b) {
				return a.m_numCases < b.m_numCases;
				});
		}
		else {
			
			std::sort(m_covidCollection.begin(), m_covidCollection.end(), [byField](const Covid& a, const Covid& b) {
				if (byField(a, b)) return true;
				if (byField(b, a)) return false;
				return a.m_numDeaths < b.m_numDeaths; 
				});
		}
	}


	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
	{
		
		if (std::find_if(m_covidCollection.begin(), m_covidCollection.end(), [variant, country, deaths](const Covid& inc1) {
			return inc1.m_country == country && inc1.m_variant == variant && inc1.m_numDeaths > deaths;
			}) != m_covidCollection.end())
		{
			return true;
		}
		
		return false;
	}

	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		std::list<Covid> list{};

		for (const auto& item : m_covidCollection)
		{
			if (item.m_numDeaths >= deaths)
			{
				list.push_back(item);
			}
		}

		return list;
	}

	void CovidCollection::updateStatus()
	{
		for (auto& item : m_covidCollection)
		{
			if (item.m_numDeaths > 300)
			{
				item.m_status.assign("EPIDEMIC");
			}
			else if (item.m_numDeaths < 50)
			{
				item.m_status.assign("EARLY");
			}
			else
			{
				item.m_status.assign("MILD");
			}
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
		ostr << " | " << std::setw(8) << std::right << inc.m_status << " |";
		return ostr;
	}

	bool Covid::operator==(const Covid& inc) const
	{
		return this->m_city == inc.m_city && this->m_country == inc.m_country && this->m_numCases == inc.m_numCases 
			&& this->m_numDeaths == inc.m_numDeaths && this->m_status == inc.m_status && this->m_variant == inc.m_variant && this->m_year == inc.m_year;
	}

}
