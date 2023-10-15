///////////////////////////////////////////////////////
//                  WorkShop 5 - Part 2
// Name: Farbod Moayeri
// Id: 134395227
// Email: fmoayeri2@myseneca.ca
// Section: NFF
// Date: 2023-10-05
///////////////////////////////////////////////////////
// I have done all the coding by myself and only copied
// the code that my professor provided to complete my 
// workshops and assignments.
///////////////////////////////////////////////////////

#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <string>

namespace sdds {
	template<typename T>
	class Collection {
		std::string m_name{};
		T** m_array{};
		size_t m_size{};
		void (*m_observer)(const Collection<T>&, const T&){};
	public:
		Collection<T>(const std::string& name) 
		{
			if (name.length() > 0)
			{
				m_name = name;
			}
		}
		Collection<T>(const Collection<T>& col) = delete;
		Collection<T>& operator=(const Collection<T> col) = delete;
		~Collection() 
		{
			for (size_t i = 0; i < m_size; i++)
			{
				delete m_array[i];
			}

			delete[] m_array;
		}
		const std::string& name() const 
		{
			return m_name;
		}
		size_t size() const 
		{
			return m_size;
		}
		void setObserver(void (*observer)(const Collection<T>& col, const T& instance)) 
		{ //
			if (observer != nullptr)
			{
				m_observer = observer;
			}
		}
		Collection<T>& operator+=(const T& item) 
		{

			for (size_t i = 0; i < m_size; ++i) 
			{
				if (m_array[i]->title() == item.title()) {
					return *this;
				}
			}
			
			T** local = new T * [m_size + 1];
			for (size_t i = 0; i < m_size; i++)
			{
				local[i] = new T;
				*local[i] = *m_array[i];
				delete m_array[i];
			}

			delete[] m_array;

			local[m_size] = new T(item);

			m_array = local;
			m_size++;

			if (m_observer != nullptr)
			{
				m_observer(*this, item);
			}

			

			return *this;

		}
		T& operator[](size_t idx) const 
		{
			if (idx >= m_size)
			{
				throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
			}
			else
			{
				return *m_array[idx];
			}
		}
		T* operator[](const std::string& title) const 
		{
			for (size_t i = 0; i < m_size; i++)
			{
				if (m_array[i]->title() == title)
				{
					return m_array[i];
				}
			}

			return nullptr;
		}
	};
	template<typename T>
	std::ostream& operator<<(std::ostream& ostr, const Collection<T>& col)
	{
		for (size_t i = 0; i < col.size(); i++)
		{
			ostr << col[i];
		}
		return ostr;
	}
}
#endif // !SDDS_COLLECTION_H
