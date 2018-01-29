#include "Algorithm.h"
#include "../Gui/Gui.h"
#include "LeeAlgorithm.h"
#include "LeeAlgorithmV2.h"
#include "AStar.h"
#include "Dijkstra.h"

std::map<Algorithm, std::string> algorithm_names;
std::map<Algorithm, std::unique_ptr<BaseAlgorithm>> algorithm_pointers;

void InitializeAlgorithms()
{
	algorithm_names.emplace(Algorithm::AStar, "A*");
	algorithm_pointers.emplace(Algorithm::AStar, std::unique_ptr<BaseAlgorithm>(new AStar));

	algorithm_names.emplace(Algorithm::Wave, "Wave");
	algorithm_pointers.emplace(Algorithm::Wave, std::unique_ptr<BaseAlgorithm>(new LeeAlgorithmV2));

	algorithm_names.emplace(Algorithm::Dijkstra, "Dijkstra");
	algorithm_pointers.emplace(Algorithm::Dijkstra, std::unique_ptr<BaseAlgorithm>(new Dijkstra));
}

DWORD WINAPI ProcessAlgorithm(LPVOID lpParameter)
{
	algorithm_pointers.at(Gui::GetSelectedAlgorithm()).get()->FindPath();
	return 0;
}