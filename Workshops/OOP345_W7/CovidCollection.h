#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <string>
#include <vector>

namespace sdds {
	struct Covid {
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		int m_year{};
		unsigned m_numCases{};
		unsigned m_numDeaths{};
	};

	class CovidCollection {
		std::vector<Covid> m_covidCollection{};
		std::string trim(const std::string& inc);
	public:
		CovidCollection(const std::string& filename);
		void display(std::ostream& ostr) const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Covid& inc);
}
#endif // !SDDS_COVIDCOLLECTION_H
