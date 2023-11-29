#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <string>
#include <iostream>
#include "Station.h"  
#include "CustomerOrder.h"  

namespace sdds {


    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{};

    public:
        Workstation(const std::string& str);

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;

        Workstation(const Workstation& inc) = delete;            
        Workstation& operator=(const Workstation& inc) = delete; 
        Workstation(Workstation&& inc) = delete;                 
        Workstation& operator=(Workstation&& inc) = delete;      

        Workstation& operator+=(CustomerOrder&& newOrder);
    };

}
#endif // !SDDS_WORKSTATION_H