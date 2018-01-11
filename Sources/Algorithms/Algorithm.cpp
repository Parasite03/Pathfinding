#include "Algorithm.h"
#include "../Gui/Gui.h"
#include "LeeAlgorithm.h"
#include "AStar.h"

std::map<Algorithm, std::string> algorithm_names;
std::map<Algorithm, std::unique_ptr<BaseAlgorithm>> algorithm_pointers;

void InitializeAlgorithms()
{
	algorithm_names.emplace(Algorithm::Lee, "Lee");
	algorithm_pointers.emplace(Algorithm::Lee, std::unique_ptr<BaseAlgorithm>(new LeeAlgorithm));

	algorithm_names.emplace(Algorithm::AStar, "A*");
	algorithm_pointers.emplace(Algorithm::AStar, std::unique_ptr<BaseAlgorithm>(new AStar));

	algorithm_names.emplace(Algorithm::Dijkstra, "Dijkstra");
	//algorithm_pointers.emplace(Algorithm::Dijkstra, std::unique_ptr<BaseAlgorithm>(new Dijkstra));
}

DWORD WINAPI ProcessAlgorithm(LPVOID lpParameter)
{
	sf::Clock clock;
	algorithm_pointers.at(Gui::GetSelectedAlgorithm()).get()->FindPath();
	Gui::SetRunTime(clock.getElapsedTime());
	return 0;
}