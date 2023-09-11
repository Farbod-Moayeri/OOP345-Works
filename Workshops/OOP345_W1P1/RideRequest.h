///////////////////////////////////////////////////////
//                  WorkShop 1 - Part 1
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

#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>

namespace sdds {

	const int NAME_LENGTH = 9;
	const int DESCRIPTION_LENGTH = 24;

	class RideRequest {
		char g_name[NAME_LENGTH + 1]{};
		char g_description[DESCRIPTION_LENGTH + 1]{};
		double g_price{ 0.0 };
		bool g_isDiscount{ false };
	public:
		RideRequest() = default;
		~RideRequest() = default;
		RideRequest(const RideRequest& inc);
		RideRequest& operator=(const RideRequest& inc);
		RideRequest& read(std::istream& istr = std::cin);
		RideRequest& display();
	};

	extern double g_taxrate;
	extern double g_discount;
}

#endif // !SDDS_RIDEREQUEST_H

