///////////////////////////////////////////////////////
//                  WorkShop 4 - Part 2
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

#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <string>

namespace sdds {
	class Cheese {
		std::string m_name{ "NaC" };
		unsigned m_weight{ 0 };
		double m_price{ 0.0 };
		std::string m_features{};
		virtual std::string trim(const std::string& inc) const;
	public:
		Cheese() = default;
		Cheese(const std::string& str);
		virtual Cheese slice(size_t weight);

		explicit operator bool() const;

		// rule of five
		virtual ~Cheese() = default;
		Cheese(const Cheese& inc);
		virtual Cheese& operator=(const Cheese& inc);
		Cheese(Cheese&& inc) noexcept;
		virtual Cheese& operator=(Cheese&& inc) noexcept;
		// rule of five

		// getters
		std::string getName() const;
		int getWeight() const;
		double getPrice() const;
		std::string getFeatures() const;
		// getters
	};

	std::ostream& operator<<(std::ostream& ostr, const Cheese& inc);
}
#endif // !SDDS_CHEESE_H

