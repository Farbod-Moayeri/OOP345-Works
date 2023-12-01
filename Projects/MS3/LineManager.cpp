#include <fstream>
#include <algorithm>
#include "LineManager.h"


namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		std::ifstream openFile(file);
		
		if (openFile)
		{
			Utilities ut;
			std::string line, firstToken, secondToken;
			size_t next{ 0 };
			Workstation* firstStation{};
			Workstation* secondStation{};
			bool more{ true };

			ut.setDelimiter('|');
		
			
			while (openFile.good())
			{
				next = 0;
				std::getline(openFile, line, '\n');
					
				try {
					firstToken = ut.extractToken(line, next, more);

					if (more)
					{
						secondToken = ut.extractToken(line, next, more);
					}
				}
				catch (std::invalid_argument inc)
				{

				}

				if (!firstToken.empty())
				{
					firstStation = *std::find_if(stations.begin(), stations.end(), [&firstToken](Workstation* current) {
						return current->getItemName() == firstToken;
						});

					if (firstStation)
					{
						//auto first = std::find(m_activeLine.begin(), m_activeLine.end(), firstStation);

						/*if (first == m_activeLine.end())
						{
							m_activeLine.push_back(firstStation);
						}*/
					}
				}

				if (!secondToken.empty())
				{
					secondStation = *std::find_if(stations.begin(), stations.end(), [&secondToken](Workstation* current) {
						return current->getItemName() == secondToken;
						});

					//m_activeLine.push_back(secondStation);

					if (firstStation != nullptr && secondStation != nullptr)
					{
						firstStation->setNextStation(secondStation);
					}

					//m_activeLine.back()->setNextStation(secondStation);
					
				}

				if (firstStation)
				{
					m_activeLine.push_back(firstStation);
				}

				

				firstStation = nullptr;
				secondStation = nullptr;
				firstToken.clear();
				secondToken.clear();

			}
			
			m_firstStation = m_activeLine.front();
			m_cntCustomerOrder = g_pending.size();
		}
	}
	void LineManager::reorderStations()
	{
		std::vector<Workstation*> sorted;
		Workstation* current = m_firstStation;

		while (current != nullptr) {
			sorted.push_back(current);
			current = current->getNextStation();
		}

		m_activeLine = std::move(sorted);
	}

	bool LineManager::run(std::ostream& os) {
		static size_t iteration = 0;
		os << "Line Manager Iteration: " << ++iteration << std::endl;

		if (!g_pending.empty()) {
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		for (auto& station : m_activeLine) {
			station->fill(os);
		}

		for (auto& station : m_activeLine) {
			station->attemptToMoveOrder();
		}

		return std::all_of(m_activeLine.begin(), m_activeLine.end(),
			[](const Workstation* ws) { return ws->getQuantity() == 0; });
	}

	void LineManager::display(std::ostream& os) const {
		for (const auto& station : m_activeLine) {
			station->display(os);
		}
	}
}