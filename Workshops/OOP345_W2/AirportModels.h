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
		std::string m_country{};
		double m_lat{ 0.0 };
		double m_long{ 0.0 };
	public:
		// checks if the current object is valid: has a non-empty code
		explicit operator bool() const;
		Airport() = default;
		// rule of three
		virtual ~Airport() = default;
		Airport(const Airport& inc);
		Airport& operator=(const Airport& inc);

		std::ostream& display(std::ostream& ostr) const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Airport& inc);
	std::istream& operator>>(std::istream& istr, Airport& inc);

	class AirportLog {
		std::string m_filename{};
		size_t m_numLogs{ 0 };
		Airport* m_logs{ nullptr };
		explicit operator bool() const;
	public:

		AirportLog() = default;
		AirportLog(const char filename[]);
		void addAirport(const Airport& inc);
	};
}

#endif // !SDDS_AIRPORTMODELS_H
