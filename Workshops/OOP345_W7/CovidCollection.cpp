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
#include <numeric>
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

	void CovidCollection::display(std::ostream& out, const std::string& country) const {
		
		unsigned countryDeaths{};
		unsigned countryCases{};
		std::string temp;

		unsigned totalDeaths = std::accumulate(m_covidCollection.begin(), m_covidCollection.end(), 0u,
			[](unsigned sum, const Covid& record) {
				return sum + record.m_numDeaths;
			});
		unsigned totalCases = std::accumulate(m_covidCollection.begin(), m_covidCollection.end(), 0u,
			[](unsigned sum, const Covid& record) {
				return sum + record.m_numCases;
			});

		
		if (country == "ALL") {
			std::for_each(m_covidCollection.begin(), m_covidCollection.end(),
				[&out](const Covid& record) {
					out << record << '\n';
				});
		}
		else {
			
			out << "Displaying information of country = " << country << "\n";
			std::vector<Covid> filteredRecords;
			std::copy_if(m_covidCollection.begin(), m_covidCollection.end(), std::back_inserter(filteredRecords),
				[country](const Covid& record) {
					return record.m_country == country;
				});

			
			countryDeaths = std::accumulate(filteredRecords.begin(), filteredRecords.end(), 0u,
				[](unsigned sum, const Covid& record) {
					return sum + record.m_numDeaths;
				});
			countryCases = std::accumulate(filteredRecords.begin(), filteredRecords.end(), 0u,
				[](unsigned sum, const Covid& record) {
					return sum + record.m_numCases;
				});

			
			std::for_each(filteredRecords.begin(), filteredRecords.end(),
				[&out](const Covid& record) {
					out << record << '\n';
				});

			out << std::setfill('-') << std::setw(89) << '\n' << std::setfill(' ');
		}

		
		
		
		if (country == "ALL") {
			temp = "Total cases around the world: " + std::to_string(totalCases) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
			temp = "Total deaths around the world: " + std::to_string(totalDeaths) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
		}
		else
		{
			temp = "Total cases in " + country + ": " + std::to_string(countryCases) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
			temp = "Total deaths in " + country + ": " + std::to_string(countryDeaths) + " |" + '\n';
			out << "| " << std::setw(87) << temp;
			temp = country + " has " + std::to_string(static_cast<double>(countryCases) / totalCases * 100) + "% of global cases and "
				+ std::to_string(static_cast<double>(countryDeaths) / totalDeaths * 100) + "% of global deaths |" + '\n';
			out << "| " << std::setw(87) << temp;
		}
	}


	void CovidCollection::sort(const std::string& field) {
		std::stable_sort(m_covidCollection.begin(), m_covidCollection.end(),
			[field](const Covid& a, const Covid& b) {
				if (field == "country") {
					if (a.m_country != b.m_country) {
						return a.m_country < b.m_country;
					}
				}
				else if (field == "city") {
					if (a.m_city != b.m_city) {
						return a.m_city < b.m_city;
					}
				}
				else if (field == "variant") {
					if (a.m_variant != b.m_variant) {
						return a.m_variant < b.m_variant;
					}
				}
				else if (field == "general") {
					if (a.m_status != b.m_status) {
						return a.m_status < b.m_status;
					}
				}
				else if (field == "cases") {
					if (a.m_numCases != b.m_numCases) {
						return a.m_numCases < b.m_numCases;
					}
				}
				else if (field == "year") {
					if (a.m_year != b.m_year) {
						return a.m_year < b.m_year;
					}
				}

				
				return a.m_numDeaths < b.m_numDeaths;
			});
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

	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const {
		std::list<Covid> list;

		std::back_insert_iterator<std::list<Covid>> backIt(list);

		std::copy_if(m_covidCollection.begin(), m_covidCollection.end(), backIt,
			[deaths](const Covid& item) {
				return item.m_numDeaths >= deaths;
			});

		return list;
	}


	void CovidCollection::updateStatus()
	{
		std::for_each(m_covidCollection.begin(), m_covidCollection.end(), [](Covid& item) {
			
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
		});
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
