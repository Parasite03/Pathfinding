#pragma once

enum class Algorithms
{
	Lee,
	AStar
};

DWORD WINAPI ProcessAlgorithm(LPVOID t);