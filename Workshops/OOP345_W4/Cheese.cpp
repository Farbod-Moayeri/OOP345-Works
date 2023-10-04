#include "Cheese.h"

namespace sdds {
	Cheese::Cheese(const std::string& str)
	{
		if (str.length() > 0)
		{
			std::string cpy = str;

			m_name = cpy.substr(cpy.find(','));
			cpy.erase(0, cpy.find(','));

			m_weight = std::stoul(cpy.substr(cpy.find(',')));
			cpy.erase(0, cpy.find(','));

			m_price = std::stoul(cpy.substr(cpy.find(',')));
			cpy.erase(0, cpy.find(','));


			
		}
	}
}
