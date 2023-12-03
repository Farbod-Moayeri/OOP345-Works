// Name: Farbod Moayeri
// Seneca Student ID: 134395227
// Seneca email: fmoayeri2@myseneca.ca
// Date of completion: 2023/12/02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include "Workstation.h"

namespace sdds {


    class LineManager {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{};

    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };

}
#endif // !SDDS_LINEMANAGER_H
