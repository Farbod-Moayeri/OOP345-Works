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

}
