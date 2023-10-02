///////////////////////////////////////////////////////
//                  WorkShop 3 - Part 2
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

#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H

#include "Collection.h"

namespace sdds {
	template<typename T>
	class OrderedCollection : public Collection<T, 72> {
	public:
        bool operator+=(const T& item) {
            unsigned i;
            unsigned j;

            if (!Collection<T, 72>::operator+=(item)) 
            {
                return false;
            }

            for (i = 0; i < this->size() - 1; i++) 
            {
                for (j = 0; j < this->size() - i - 1; j++) 
                {
                    if (this->operator[](j) > this->operator[](j + 1)) 
                    {
                        T temp = this->operator[](j);
                        this->operator[](j) = this->operator[](j + 1);
                        this->operator[](j + 1) = temp;
                    }
                }
            }

            return true;
        }

	};
}

#endif // !SDDS_ORDEREDCOLLECTION_H
