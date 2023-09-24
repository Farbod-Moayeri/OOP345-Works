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

#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H

#include <chrono>

namespace sdds {
	class Timer {
		std::chrono::time_point<std::chrono::steady_clock> m_startTime{};
	public:
		void start();
		long long stop();
	};
}
#endif // !SDDS_TIMER_H

