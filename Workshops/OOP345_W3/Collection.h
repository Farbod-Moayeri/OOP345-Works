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

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H


#include "Book.h"

namespace sdds {

    template<typename T, unsigned C>
    class Collection {
    private:
        static T m_smallestItem;
        static T m_largestItem;

        T m_items[C];
        unsigned m_size = 0;

    protected:
        virtual void setSmallestItem(const T& item) 
        {
            if (item < m_smallestItem) {
                m_smallestItem = item;
            }
        }

        virtual void setLargestItem(const T& item) 
        {
            if (item > m_largestItem) {
                m_largestItem = item;
            }
        }

        virtual T& operator[](unsigned index) 
        {
            return m_items[index];
        }

        virtual void incrSize() 
        {
            if (m_size < C)
            {
                m_size++;
            }
        }

    public:
        Collection() = default;

        // Static functions to get smallest and largest items
        static const T getSmallestItem() 
        { 
            return m_smallestItem; 
        }
        static const T getLargestItem() 
        { 
            return m_largestItem; 
        }

        // Public member functions
        const unsigned size() 
        { 
            return m_size; 
        }
        constexpr unsigned capacity() 
        { 
            return C; 
        }

        virtual bool operator+=(const T& item) 
        {
            unsigned i;
            bool isBiggest = true;
            bool isSmallest = true;
            
            if (m_size >= C) return false;

            for (i = 0; i < m_size; i++) {
                if (item < m_items[i]) {
                    isBiggest = false;
                }
                if (item > m_items[i]) {
                    isSmallest = false;
                }
            }
            
            m_items[m_size++] = item;
            
            if (m_size == 1)
            {
                setLargestItem(m_items[m_size - 1]);
                setSmallestItem(m_items[m_size - 1]);
            }
            else {
                if (isBiggest)
                {
                    setLargestItem(m_items[m_size - 1]);
                }
                else if (isSmallest)
                {
                    setSmallestItem(m_items[m_size - 1]);
                }
            }
           

            return true;
        }

        virtual void print(std::ostream& os) const 
        {
            unsigned i;
            os << "[";
            for (i = 0; i < m_size; ++i) {
                if (i + 1 != m_size)
                {
                    os << m_items[i] << ",";
                }
                else
                {
                    os << m_items[i];
                }
            }
            os << "]" << '\n';
        }
    };

    template<typename T, unsigned C>
    T Collection<T, C>::m_smallestItem = T(9999);

    template<typename T, unsigned C>
    T Collection<T, C>::m_largestItem = T(-9999);

    template<>
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

    template<>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

    template<>
    Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);

    template<>
    Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);

    template<>
    void Collection<Book, 10>::print(std::ostream& os) const 
    {
        unsigned i;
        os << "| ---------------------------------------------------------------------------|" << '\n';
        for (i = 0; i < m_size; ++i) {
            os << "| " << m_items[i] << " |" << '\n';
        }
        os << "| ---------------------------------------------------------------------------|" << '\n';
    }

    template<>
    void Collection<Book, 72>::print(std::ostream& os) const 
    {
        unsigned i;
        os << "| ---------------------------------------------------------------------------|" << '\n';
        for (i = 0; i < m_size; ++i) {
            os << "| " << m_items[i] << " |" << '\n';
        }
        os << "| ---------------------------------------------------------------------------|" << '\n';
    }
    

}
#endif // !SDDS_COLLECTION_H

