#include "Algorithm.h"
#include "../Gui/Gui.h"
#include "LeeAlgorithm.h"
#include "LeeAlgorithm(ver.2).h"
#include "AStar.h"
#include "Dijkstra.h"

std::map<Algorithm, std::string> algorithm_names;
std::map<Algorithm, std::unique_ptr<BaseAlgorithm>> algorithm_pointers;

void InitializeAlgorithms()
{
	algorithm_names.emplace(Algorithm::AStar, "A*");
	algorithm_pointers.emplace(Algorithm::AStar, std::unique_ptr<BaseAlgorithm>(new AStar));

	algorithm_names.emplace(Algorithm::Dijkstra, "Dijkstra");
	algorithm_pointers.emplace(Algorithm::Dijkstra, std::unique_ptr<BaseAlgorithm>(new Dijkstra));

	algorithm_names.emplace(Algorithm::Lee, "Wave");
	algorithm_pointers.emplace(Algorithm::Lee, std::unique_ptr<BaseAlgorithm>(new LeeAlgorithm));

	algorithm_names.emplace(Algorithm::SecondLee, "Wave v2");
	algorithm_pointers.emplace(Algorithm::SecondLee, std::unique_ptr<BaseAlgorithm>(new SecondLeeAlgorithm));
}

DWORD WINAPI ProcessAlgorithm(LPVOID lpParameter)
{
	algorithm_pointers.at(Gui::GetSelectedAlgorithm()).get()->FindPath();
	return 0;
}