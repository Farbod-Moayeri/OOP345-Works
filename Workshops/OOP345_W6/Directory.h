///////////////////////////////////////////////////////
//                  WorkShop 6 - Part 2
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
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H

#include <vector>
#include"Resource.h"

namespace sdds {
	class Directory : public Resource {
		std::vector<Resource*> m_contents{};
		//size_t m_count{};
	public:
		Directory(const std::string& directName);
		virtual void update_parent_path(const std::string& path) override;
		virtual NodeType type() const override;
		virtual std::string path() const override;
		virtual std::string name() const override;
		virtual int count() const override;
		virtual size_t size() const override;
		Directory& operator+=(Resource* inc);
		virtual Resource* find(const std::string& name, const std::vector<OpFlags>& dir = std::vector<OpFlags>());
		virtual ~Directory();

		Directory(const Directory& inc) = delete;
		Directory& operator=(const Directory& inc) = delete;
		Directory(Directory&& inc) = delete;
		Directory&& operator=(Directory&& inc) = delete;

		void remove(const std::string& name, const std::vector<OpFlags>& inc = std::vector<OpFlags>());
		void display(std::ostream& ostr, const std::vector<FormatFlags>& inc = std::vector<FormatFlags>()) const;
	};
}
#endif // !SDDS_DIRECTORY_H
