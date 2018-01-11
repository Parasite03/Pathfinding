#pragma once
#include "BaseAlgorithm.h"

class LeeAlgorithm : public BaseAlgorithm
{
public:
	LeeAlgorithm();
	~LeeAlgorithm();

	void FindPath() override;
	void SetDirectionCount(const short number_of_directions);
	void SetPathLength(const short path_length);

	unsigned char GetNumberOfDirections();
	short GetPathLength();

private:

	void SetBackTrace();
	void ShowPath();
	void ShowCheckedTiles();
	void ResetPathMap();

	short number_of_directions_;
	short path_length_;

	std::vector<sf::Vector2f> path_map_;
	std::vector<std::vector<int>> tile_distace_;
	std::vector<std::vector<bool>> checked_tile_;

	std::vector<short> offset_by_x_;
	std::vector<short> offset_by_y_;
};

