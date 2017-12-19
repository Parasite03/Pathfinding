#pragma once

#include "../Map/Map.h"
#include "../Map/Tile.h"

struct Node 
{
	short x;
	short y;
	short distance;
};

class LeeAlgorithm
{
public:
	static void FindPath(sf::Vector2f start_position, sf::Vector2f end_position, unsigned char number_of_directions);
	static void SetBackTrace();
	static void ShowPath();
	static void ShowCheckedTiles();
	static void ResetPath();

	static LeeAlgorithm* GetAlgorithm();

	void SetNumberOfDirections(unsigned char number_of_directions);
	unsigned char GetNumberOfDirections();

	void SetDirectionCount(unsigned char number_of_directions);

private:
	LeeAlgorithm();
	~LeeAlgorithm();

	static LeeAlgorithm algorithm_;

	unsigned char number_of_directions_;
	short path_length_;

	std::vector<sf::Vector2f> path_map;
	std::vector<std::vector<int>> tile_distace_;
	//std::vector<std::vector<bool>> closed_set;
	//std::vector<std::vector<bool>> closed_set;

	std::vector<short> tile_offset_by_x_;
	std::vector<short> tile_offset_by_y_;
};

