#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>

namespace sdds {

	const int NAME_LENGTH = 9;
	const int DESCRIPTION_LENGTH = 24;

	constexpr double TAXRATE = 0.0;
	constexpr double DISCOUNT = 0.0;

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
}

#endif // !SDDS_RIDEREQUEST_H

