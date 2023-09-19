#include <fstream>
#include <iomanip>
#include "AirportModels.h"


namespace sdds {
	Airport::operator bool() const
	{
		return m_code.empty() ? false : true;
	}
	
	std::ostream& operator<<(std::ostream& ostr, const Airport& inc)
	{
		inc.display(ostr);
	}

	std::istream& operator>>(std::istream& istr, Airport& inc)
	{
		inc.read(istr);
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
	}

	std::ostream& Airport::display(std::ostream& ostr) const
	{
		if (*this) {
			ostr << std::setfill('.');
			ostr << std::right << std::setw(20) << "Airport Code : " << std::left << std::setw(30) << m_code;
			ostr << std::right << std::setw(20) << "Airport Name : " << std::left << std::setw(30) << m_name;
			ostr << std::right << std::setw(20) << "Airport City : " << std::left << std::setw(30) << m_city;
			ostr << std::right << std::setw(20) << "Airport State : " << std::left << std::setw(30) << m_state;
			ostr << std::right << std::setw(20) << "Airport Country : " << std::left << std::setw(30) << m_country;
			ostr << std::right << std::setw(20) << "Airport Latitude : " << std::left << std::setw(30) << m_lat;
			ostr << std::right << std::setw(20) << "Airport Longitude : " << std::left << std::setw(30) << m_long;
			ostr << std::setfill(' ');
		}
		else
		{
			ostr << "Empty Airport";
		}
	}

	std::istream& Airport::read(std::istream& istr)
	{
		Airport temp{};
	
		std::getline(istr ,temp.m_code, ',');
		std::getline(istr, temp.m_name, ',');
		std::getline(istr, temp.m_city, ',');
		std::getline(istr, temp.m_state, ',');
		std::getline(istr, temp.m_country, ',');
		istr >> temp.m_lat;
		istr.ignore();
		istr >> temp.m_long;
		istr.ignore();

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
	}

	AirportLog::operator bool() const
	{
		return m_filename.empty() ? false : true;
	}

	AirportLog::AirportLog(const char filename[])
	{
		int i{};
		std::ifstream file;
		std::string temp;

		if (filename != nullptr && filename[0] != '\0')
		{
			m_filename.assign(filename);

			file.open(m_filename);

			if (file)
			{
				while (!file.eof())
				{
					std::getline(file, temp, '\n');
					m_numLogs++;
				}

				m_numLogs--; // accounts for header at top of csv

				if (m_numLogs > 0)
				{
					m_logs = new Airport[m_numLogs];
					file.seekg(1, std::ios_base::cur);

					for (i = 0; i < m_numLogs; i++)
					{
						file >> m_logs[i];
					}
				}
			}

			file.close();

		}
	}

	void AirportLog::addAirport(const Airport& inc)
	{
		if (inc && *this)
		{
			// TO DO
		}
	}

}
