///////////////////////////////////////////////////////
//                  WorkShop 2 - Part 2
// Name: Farbod Moayeri
// Id: 134395227
// Email: fmoayeri2@myseneca.ca
// Section: NFF
// Date: 2023-09-23
///////////////////////////////////////////////////////
// I have done all the coding by myself and only copied
// the code that my professor provided to complete my 
// workshops and assignments.
///////////////////////////////////////////////////////

#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <string>
#include <iostream>

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
		virtual ~Airport();
		Airport(const Airport& inc);
		virtual Airport& operator=(const Airport& inc);
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
		size_t m_numLogs{ 0 };
		Airport* m_logs{ nullptr };
		void increaseSize(const int amount = 1);
	public:

		AirportLog() = default;
		AirportLog(const std::string& filename);
		// rule of three
		virtual ~AirportLog();
		virtual AirportLog& operator=(const AirportLog& inc);
		AirportLog(const AirportLog& inc);
		AirportLog(AirportLog&& inc) noexcept;
		virtual AirportLog& operator=(AirportLog&& inc) noexcept;

		//
		AirportLog(const AirportLog& inc, const std::string& state, const std::string& country);
		virtual void addAirport(const Airport& inc);
		virtual AirportLog findAirport(const std::string& state, const std::string& country) const;
		virtual const Airport operator[](const size_t index) const;
		virtual operator size_t() const;
	};
}

#endif // !SDDS_AIRPORTMODELS_H
