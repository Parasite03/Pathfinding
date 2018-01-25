#pragma once

#include "BaseAlgorithm.h"

class LeeAlgorithm : public BaseAlgorithm
{
public:
	LeeAlgorithm();
	~LeeAlgorithm();

	void FindPath() override;

	void ShowPath();
	void ShowCheckedTiles();
	
	unsigned char GetNumberOfDirections();
	short GetPathLength();

private:

	void SetPathLength(const short path_length);
	void SetDirectionCount(const short number_of_directions);
	void SetBackTrace();
	void ResetPathMap();

	short number_of_directions_;
	short path_length_;

	std::vector<sf::Vector2f> path_map_;
	std::vector<std::vector<int>> tile_distance_;
	std::vector<std::vector<bool>> checked_tiles_;

	std::vector<short> offset_by_x_;
	std::vector<short> offset_by_y_;
};
