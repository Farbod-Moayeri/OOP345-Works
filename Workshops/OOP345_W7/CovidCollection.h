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

#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <string>
#include <vector>
#include <list>

namespace sdds {
	struct Covid {
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		int m_year{};
		unsigned m_numCases{};
		unsigned m_numDeaths{};
		std::string m_status{"General"};

		bool operator==(const Covid& inc) const;
	};

	class CovidCollection {
		std::vector<Covid> m_covidCollection{};
		std::string trim(const std::string& inc);
	public:
		CovidCollection(const std::string& filename);
		void display(std::ostream& out, const std::string& country = "ALL") const;
		void sort(const std::string& field = "country");
		bool inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const;
		std::list<Covid> getListForDeaths(unsigned int deaths) const;
		void updateStatus();


	};

	std::ostream& operator<<(std::ostream& ostr, const Covid& inc);
}
#endif // !SDDS_COVIDCOLLECTION_H
