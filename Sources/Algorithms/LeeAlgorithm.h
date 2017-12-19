#pragma once

#include "../Map/Map.h"
#include "../Map/Tile.h"

class LeeAlgorithm
{
public:
	static void FindPath(sf::Vector2f start_position, sf::Vector2f end_position, short number_of_directions);
	static void SetBackTrace();
	static void ShowPath();
	static void ShowCheckedTiles();
	static void ResetPathMap();

	static LeeAlgorithm* GetAlgorithm();
	
	void SetDirectionCount(const short number_of_directions);
	void SetPathLength(const short path_length);
	
	unsigned char GetNumberOfDirections();
	short GetPathLength();

private:
	LeeAlgorithm();
	~LeeAlgorithm();

	static LeeAlgorithm algorithm_;

	short number_of_directions_;
	short path_length_;

	std::vector<sf::Vector2f> path_map_;
	std::vector<std::vector<int>> tile_distace_;
	std::vector<std::vector<bool>> checked_tile_;

	std::vector<short> offset_by_x_;
	std::vector<short> offset_by_y_;
};

