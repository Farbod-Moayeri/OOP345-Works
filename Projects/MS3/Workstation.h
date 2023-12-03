// Name: Farbod Moayeri
// Seneca Student ID: 134395227
// Seneca email: fmoayeri2@myseneca.ca
// Date of completion: 2023/12/02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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
        virtual ~Workstation() = default;

        size_t getOrderSize() const;
        Workstation& operator+=(CustomerOrder&& newOrder);
        
    };

}
#endif // !SDDS_WORKSTATION_H
