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
		Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& state, const std::string& country, const double lat, const double lon);
		// rule of three
		virtual ~Airport() = default;
		Airport(const Airport& inc);
		Airport& operator=(const Airport& inc);
		//
		virtual std::ostream& display(std::ostream& ostr) const;
		virtual std::istream& read(std::istream& istr);
		virtual std::ostream& write(std::ostream& ostr) const;

		const std::string& getState() const;
		const std::string& getCountry() const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Airport& inc);
	std::istream& operator>>(std::istream& istr, Airport& inc);

	class AirportLog {
		std::string m_filename{};
		size_t m_numLogs{ 0 };
		Airport* m_logs{ nullptr };
		explicit operator bool() const;
		void increaseSize(const int amount = 1);
	public:

		AirportLog() = default;
		AirportLog(const char filename[]);
		// rule of three
		~AirportLog();
		AirportLog& operator=(const AirportLog& inc);
		AirportLog(const AirportLog& inc);
		// AirportLog(AirportLog&& inc);
		// AirportLog& operator=(AirportLog&& inc);

		//
		AirportLog(const AirportLog& inc, const std::string& state, const std::string& country);
		virtual void addAirport(const Airport& inc);
		AirportLog findAirport(const std::string& state, const std::string& country) const;
		virtual const Airport operator[](const size_t index) const;
		virtual operator size_t() const;
	};
}

#endif // !SDDS_AIRPORTMODELS_H
