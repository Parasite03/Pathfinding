#include "Algorithms.h"
#include "../Gui/Gui.h"
#include "LeeAlgorithm.h"
#include "AStar.h"

DWORD WINAPI ProcessAlgorithm(LPVOID t)
{
	LeeAlgorithm lee;
	AStar astar;
	sf::Clock clock;
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);

	Gui::SetVirtualMemUsedPassive(memInfo.ullTotalPageFile - memInfo.ullAvailPageFile);
	Gui::SetVirtualMemUsedActive(0);

	switch(Gui::GetSelectedtAlgorithm())
	{
	case Algorithms::Lee:
		lee.FindPath();
		if (Gui::GetVirtualMemUsedActive() < memInfo.ullTotalPageFile - memInfo.ullAvailPageFile)
			Gui::SetVirtualMemUsedActive(memInfo.ullTotalPageFile - memInfo.ullAvailPageFile);
		break;
	case Algorithms::AStar:
		astar.FindPath();
		break;
	default:
		break;
	}
	return 0;
}
