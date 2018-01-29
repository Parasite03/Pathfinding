#pragma once

#include "BaseAlgorithm.h"
#include <functional>
#include <set>

class LeeAlgorithmV2 : public BaseAlgorithm
{
public:
	using uint = unsigned int;
	using CoordinateList = std::vector<sf::Vector2i>;
	
	void FindPath() override;

	void setWorldSize(sf::Vector2i worldSize);
	void setDiagonalMovement();

	sf::Vector2i ftoi(sf::Vector2f vector);
	sf::Vector2f itof(sf::Vector2i vector);

private:
	
	std::vector<std::vector<uint>> g_cost_;
	std::vector<sf::Vector2f> path_map_;

	sf::Vector2i world_size_;

	CoordinateList direction_;
	uint directions_;

};