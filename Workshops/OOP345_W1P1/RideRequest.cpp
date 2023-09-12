///////////////////////////////////////////////////////
//                  WorkShop 1 - Part 2
// Name: Farbod Moayeri
// Id: 134395227
// Email: fmoayeri2@myseneca.ca
// Section: NFF
// Date: 2023-09-10
///////////////////////////////////////////////////////
// I have done all the coding by myself and only copied
// the code that my professor provided to complete my 
// workshops and assignments.
///////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include <string>
#include "RideRequest.h"

namespace sdds {

	double g_taxrate;
	double g_discount;

	RideRequest::~RideRequest()
	{
		delete[] g_description;
	}

	RideRequest::RideRequest(const RideRequest& inc)
	{
		operator=(inc);
	}


	RideRequest& RideRequest::operator=(const RideRequest& inc)
	{
		if (this != &inc && inc.g_description != nullptr)
		{
			strcpy(g_name, inc.g_name);
			delete[] g_description;
			g_description = new char[strlen(inc.g_description) + 1];
			strcpy(g_description, inc.g_description);
			g_price = inc.g_price;
			g_isDiscount = inc.g_isDiscount;
		}

		return *this;
	}

	RideRequest& RideRequest::read(std::istream& istr)
	{
		if (istr.good())
		{
			RideRequest local{};

			char discountStatus = 'N';
			std::string localDesc{};

			istr.get(local.g_name, NAME_LENGTH, ',');
			istr.ignore();
			std::getline(istr, localDesc, ',');
			// istr.ignore();
			istr >> local.g_price;
			istr.ignore();
			istr >> discountStatus;
			discountStatus == 'Y' ? local.g_isDiscount = true : local.g_isDiscount = false;
			if (!istr.eof())
			{
				if (istr.peek() != EOF)
				{
					istr.ignore();
				}
			}
			
			local.g_description = new char[localDesc.length() + 1];
			strcpy(local.g_description, localDesc.c_str());
			operator=(local);
			
		}

		return *this;
	}

	const RideRequest& RideRequest::display() const
	{
		static int i = 0;
		i++;

		if (g_name[0] == '\0')
		{
			std::cout << i << ". " << "No Ride Request" << '\n';
		}
		else
		{
			std::cout << std::left << std::setw(2) << i << ". " << std::setw(10) << g_name << "|" << std::setw(25) <<
				g_description << "|" << std::setw(12) << std::fixed << std::setprecision(2) << g_price + (g_price * g_taxrate) << "|";
			
			if (g_isDiscount)
			{
				std::cout << std::right << std::setw(13) << g_price - g_discount + (g_price * g_taxrate) << '\n';
			} 
			else
			{
				std::cout << '\n';
			}
			
		}

		return *this;
	}
}

