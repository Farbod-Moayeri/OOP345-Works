#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <string>

namespace sdds {
	class Cheese {
		std::string m_name{ "NaC" };
		int m_weight{ 0 };
		double m_price{ 0.0 };
		std::string m_features{};
	public:
		Cheese() = default;
		Cheese(const std::string& str);
		virtual Cheese slice(size_t weight);
		// rule of five
		virtual ~Cheese();
		Cheese(const Cheese& inc);
		Cheese& operator=(const Cheese& inc);
		Cheese(Cheese&& inc);
		Cheese& operator=(Cheese&& inc);
		// rule of five

		// getters
		std::string getName() const;
		int getWeight() const;
		double getPrice() const;
		std::string getFeatures() const;
	};

	std::ostream& operator<<(std::ostream& ostr, const Cheese& inc);
}
#endif // !SDDS_CHEESE_H

