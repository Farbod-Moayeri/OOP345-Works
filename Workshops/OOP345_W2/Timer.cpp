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

#include "Timer.h"

namespace sdds {
	void Timer::start()
	{
		m_startTime = std::chrono::steady_clock::now();
	}

	long long Timer::stop()
	{
		std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
		std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_startTime);
		return duration.count();
	}
}
