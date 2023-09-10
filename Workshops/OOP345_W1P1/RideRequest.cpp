#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <string>
#include "RideRequest.h"


namespace sdds {
	
	RideRequest::RideRequest(const RideRequest& inc)
	{
		operator=(inc);
	}
	RideRequest& RideRequest::operator=(const RideRequest& inc)
	{
		if (inc.g_name[0] != '\0') {
			strcpy(g_name, inc.g_name);
			strcpy(g_description, inc.g_description);
			g_price = inc.g_price;
			g_isDiscount = inc.g_isDiscount;
		}
	}
	RideRequest& RideRequest::read(std::istream& istr = std::cin)
	{
		if (istr.good())
		{
			char localName[NAME_LENGTH + 1];
			char localDescription[DESCRIPTION_LENGTH + 1];
			double localRate{};
			char discountStatus = 'N';

			istr.get(localName, NAME_LENGTH, '\n');
			istr.ignore();
			istr.get(localDescription, DESCRIPTION_LENGTH, '\n');
			istr.ignore();
			istr >> localRate;
			istr.ignore();
			istr >> discountStatus;
			istr.ignore();

			if (istr.good())
			{
				strcpy(g_name, localName);
				strcpy(g_description, localDescription);
				g_price = localRate;
				g_isDiscount = true ? discountStatus == 'Y' : false;
			}
		}
	}
}

