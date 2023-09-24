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

#include <fstream>
#include <iomanip>
#include "AirportModels.h"


namespace sdds {
	Airport::operator bool() const
	{
		return m_code.empty() ? false : true;
	}

	Airport::Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& state, const std::string& country, const double lat, const double lon)
	{
		if (!code.empty() && !name.empty() && !city.empty() && !state.empty() && !country.empty())
		{
			m_code = code;
			m_name = name;
			m_city = city;
			m_state = state;
			m_country = country;
			m_lat = lat;
			m_long = lon;
		}
	}
	
	std::ostream& operator<<(std::ostream& ostr, const Airport& inc)
	{
		return inc.display(ostr);
	}

	std::istream& operator>>(std::istream& istr, Airport& inc)
	{
		return inc.read(istr);
	}

	Airport::~Airport()
	{
		// exists for strings
	}

	Airport::Airport(const Airport& inc)
	{
		operator=(inc);
	}

	Airport& Airport::operator=(const Airport& inc)
	{
		if (&inc != this && inc)
		{
			m_code = inc.m_code;
			m_name = inc.m_name;
			m_city = inc.m_city;
			m_state = inc.m_state;
			m_country = inc.m_country;
			m_lat = inc.m_lat;
			m_long = inc.m_long;
		}

		return *this;
	}

	std::ostream& Airport::display(std::ostream& ostr) const
	{
		if (*this) {
			ostr << std::setfill('.');
			ostr << std::right << std::setw(23) << "Airport Code : " << std::left << std::setw(30) << m_code << '\n';
			ostr << std::right << std::setw(23) << "Airport Name : " << std::left << std::setw(30) << m_name << '\n';
			ostr << std::right << std::setw(23) << "City : " << std::left << std::setw(30) << m_city << '\n';
			ostr << std::right << std::setw(23) << "State : " << std::left << std::setw(30) << m_state << '\n';
			ostr << std::right << std::setw(23) << "Country : " << std::left << std::setw(30) << m_country << '\n';
			ostr << std::right << std::setw(23) << "Latitude : " << std::left << std::setw(30) << m_lat << '\n';
			ostr << std::right << std::setw(23) << "Longitude : " << std::left << std::setw(30) << m_long << '\n';
			ostr << std::setfill(' ');
		}
		else
		{
			ostr << "Empty Airport";
		}

		return ostr;
	}

	std::istream& Airport::read(std::istream& istr)
	{
		Airport temp{};
		istr.clear();

		if (istr.peek() == '\n')
		{
			istr.ignore();
		}

		std::getline(istr ,temp.m_code, ',');
		std::getline(istr, temp.m_name, ',');
		std::getline(istr, temp.m_city, ',');
		std::getline(istr, temp.m_state, ',');
		std::getline(istr, temp.m_country, ',');
		istr >> temp.m_lat;
		istr.ignore();
		istr >> temp.m_long;
		
		if (!istr.eof())
		{
			istr.ignore();
		}

		if (istr.good())
		{
			*this = temp;
		}

		return istr;

	}

	std::ostream& Airport::write(std::ostream& ostr) const
	{
		if (*this)
		{
			ostr << m_code << ',';
			ostr << m_name << ',';
			ostr << m_city << ',';
			ostr << m_state << ',';
			ostr << m_country << ',';
			ostr << m_lat << ',';
			ostr << m_long << '\n';
		}

		return ostr;
	}

	const std::string& Airport::getState() const
	{
		return m_state;
	}

	const std::string& Airport::getCountry() const
	{
		return m_country;
	}


	void AirportLog::increaseSize(const int amount)
	{
		unsigned i{};

		if (amount > 0)
		{
			m_numLogs += amount;
			Airport* temp = new Airport[m_numLogs];

			
			for (i = 0; i < m_numLogs - 1; i++)
			{
				temp[i] = m_logs[i];
			}
			

			delete[] m_logs;
			m_logs = temp;
			temp = nullptr;
		}
	}

	AirportLog::AirportLog(const std::string& filename)
	{
		unsigned i{};
		std::ifstream file;
		std::string temp;
		std::string firstLineLength{};

		if (!filename.empty())
		{
			file.open(filename, std::ifstream::in);

			if (file.is_open())
			{
				while (!file.eof())
				{
					std::getline(file, temp, '\n');

					if (m_numLogs == 0)
					{
						firstLineLength = temp;
					}
					
					m_numLogs++;
				}

				m_numLogs-= 2; // for first line and last line

				if (m_numLogs > 0)
				{
					m_logs = new Airport[m_numLogs];
					file.clear();
					file.seekg(firstLineLength.length(), std::ios::beg);

					if (!file)
					{
						std::cout << "ERROR: File pointer out of bounds." << '\n';
					}
					else 
					{
						for (i = 0; i < m_numLogs; i++)
						{
							file >> m_logs[i];
						}
					}
				}
			}
			else
			{
				std::cout << "Failed to open file." << '\n';
			}

			file.close();

		}
	}

	AirportLog::~AirportLog()
	{
		delete[] m_logs;
	}

	AirportLog& AirportLog::operator=(const AirportLog& inc)
	{
		unsigned i{};

		if (this != &inc && inc.m_numLogs > 0 && inc.m_logs != nullptr)
		{
			m_numLogs = inc.m_numLogs;
			delete[] m_logs;
			m_logs = new Airport[m_numLogs];

			for (i = 0; i < m_numLogs; i++)
			{
				m_logs[i] = inc.m_logs[i];
			}
		}

		return *this;
	}

	AirportLog::AirportLog(const AirportLog& inc)
	{
		operator=(inc);
	}

	AirportLog::AirportLog(AirportLog&& inc) noexcept
	{
		m_logs = inc.m_logs;
		inc.m_logs = nullptr;

		m_numLogs = inc.m_numLogs;
		inc.m_numLogs = 0;
	}

	AirportLog& AirportLog::operator=(AirportLog&& inc) noexcept
	{
		if (this != &inc)
		{
			delete[] m_logs;
			m_logs = inc.m_logs;
			inc.m_logs = nullptr;

			m_numLogs = inc.m_numLogs;
			inc.m_numLogs = 0;
		}

		return *this;
	}

	
	AirportLog::AirportLog(const AirportLog& inc, const std::string& state, const std::string& country)
	{
		unsigned i{};
		unsigned y{0};
		if (inc.m_logs != nullptr && inc.m_numLogs > 0)
		{
			
			for (i = 0; i < inc.m_numLogs; i++)
			{
				if (inc.m_logs[i].getState() == state && inc.m_logs[i].getCountry() == country)
				{
					m_numLogs++;
				}
			}

			m_logs = new Airport[m_numLogs];

			for (i = 0; i < inc.m_numLogs; i++)
			{
				if (inc.m_logs[i].getState() == state && inc.m_logs[i].getCountry() == country)
				{
					m_logs[y++] = inc.m_logs[i];
				}
			}
		}
	}

	void AirportLog::addAirport(const Airport& inc)
	{
		if (inc)
		{
			increaseSize();
			m_logs[m_numLogs - 1] = inc;
		}
	}

	AirportLog AirportLog::findAirport(const std::string& state, const std::string& country) const
	{
		AirportLog temp(*this, state, country);

		return temp;
	}

	const Airport AirportLog::operator[](const size_t index) const
	{
		// return index < m_numLogs ? m_logs[index] : Airport();

		if (index < m_numLogs)
		{
			return m_logs[index];
		}
		else
		{
			return Airport();
		}
	}

	AirportLog::operator size_t() const
	{
		return m_numLogs;
	}

}
