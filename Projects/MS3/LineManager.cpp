#include <fstream>
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
			Workstation* firstStation, secondStation;
			bool more{ true };

			ut.setDelimiter('|');
		
			
			while (openFile.good())
			{
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
						auto first = std::find(m_activeLine.begin(), m_activeLine.end(), firstStation);

						if (first == m_activeLine.end())
						{
							m_activeLine.push_back(firstStation);
						}
					}
				}

				if (!secondToken.empty())
				{
					secondStation = *std::find_if(stations.begin(), stations.end(), [&secondToken](Workstation* current) {
						return current->getItemName() == secondToken;
						});
				}

				




				firstStation = nullptr;
				secondStation = nullptr;


			}
			
			
		}
	}
}