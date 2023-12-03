// Name: Farbod Moayeri
// Seneca Student ID: 134395227
// Seneca email: fmoayeri2@myseneca.ca
// Date of completion: 2023/12/02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace sdds {

	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;


	Workstation::Workstation(const std::string& str) : Station(str)
	{

	}

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {

			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool moved = false;

		if (!m_orders.empty()) {
			
			if (!m_orders.front().containsItem(Station::getItemName()) || (m_orders.front().containsItem(Station::getItemName()) && m_orders.front().isItemFilled(Station::getItemName())) || Station::getQuantity() < 1) {
				if (!m_pNextStation) {
					
					if (m_orders.front().isOrderFilled()) {
						g_completed.push_back(std::move(m_orders.front()));
					}
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
					}
					moved = true;
				}
				else {
					*m_pNextStation += std::move(m_orders.front());
					moved = true;
				}
				m_orders.pop_front();
			}
		}
		return moved;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		
		m_pNextStation = station;
		
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		os << (m_pNextStation ? m_pNextStation->getItemName() : "End of Line") << std::endl;
	}

	size_t Workstation::getOrderSize() const
	{
		return m_orders.size();
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}

}
