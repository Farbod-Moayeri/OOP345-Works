///////////////////////////////////////////////////////
//                  WorkShop 8 - Part 2
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

// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		bool skip = false;

		for (auto i = 0u; i < allProfiles.size(); i++)
		{
			skip = false;

			for (auto j = 0u; j < bannedProfiles.size(); j++)
			{
				if ((allProfiles[i].m_age == bannedProfiles[j].m_age) && (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name))
				{
					skip = true;
					break;
				}

			}

			if (!skip)
			{
				
				Profile *temp = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				try {
					temp->validateAddress();
				}
				catch (const std::string& e)
				{
					delete temp;
					throw e;
				}

				result += temp;
				delete temp;
				temp = nullptr;
				
			}
		}


		return result;
	}

	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		
		

		DataBase<Profile> result;
		bool skip = false;

		for (auto i = 0u; i < allProfiles.size(); i++)
		{
			skip = false;

			for (auto j = 0u; j < bannedProfiles.size(); j++)
			{
				if ((allProfiles[i].m_age == bannedProfiles[j].m_age) && (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name))
				{
					skip = true;
					break;
				}

			}

			if (!skip)
			{

				std::shared_ptr<Profile> temp(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));

				try {
					temp->validateAddress();
				}
				catch (const std::string& e)
				{
					
					throw e;
				}

				result += temp;

			}
		}


		return result;
		
	}
}
