#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <string>
#include <ostream>

namespace sdds {
	class Airport {
		std::string m_code{};
		std::string m_name{};
		std::string m_city{};
		std::string m_state{};
		std::string m_state{};
		std::string m_country{};
		double m_lat{ 0.0 };
		double m_long{ 0.0 };
		// checks if the current object is valid: has a non-empty code
		explicit operator bool() const;
	public:
		Airport() = default;
		// rule of three
		~Airport() = default;
		Airport(const Airport& inc) = delete;
		Airport& operator=(const Airport& inc) = delete;

		std::ostream& display(std::ostream& ostr) const;
		std::istream& write(std::istream& istr);
	};

	std::ostream& operator<<(std::ostream& ostr, const Airport& inc);
	std::istream& operator>>(std::istream& istr, Airport* inc);

	class AirportLog {
		size_t m_numLogs{ 0 };
		Airport* m_logs{ nullptr };
	public:

		AirportLog() = default;
		AirportLog(const char filename[]);
	};
}

#endif // !SDDS_AIRPORTMODELS_H
