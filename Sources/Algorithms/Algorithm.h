#pragma once
#include "BaseAlgorithm.h"
#include <memory>

enum class Algorithm
{
	AStar,
	Wave,
	Dijkstra
};

extern std::map<Algorithm, std::string> algorithm_names;
extern std::map<Algorithm, std::unique_ptr<BaseAlgorithm>> algorithm_pointers;

void InitializeAlgorithms();
DWORD WINAPI ProcessAlgorithm(LPVOID lpParameter);
