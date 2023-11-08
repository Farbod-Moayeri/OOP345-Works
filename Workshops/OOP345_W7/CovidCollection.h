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
		std::string m_general{};
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
