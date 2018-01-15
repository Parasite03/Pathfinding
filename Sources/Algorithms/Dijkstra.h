#pragma once
#include "BaseAlgorithm.h"

class Dijkstra : public BaseAlgorithm
{

public:
	Dijkstra();
	~Dijkstra();

	void FindPath() override;

	void SetDirectionCount(const short number_of_directions);
	
	void SetPathLength(const short path_length);

	unsigned char GetNumberOfDirections();
	short GetPathLength();

private:

	void SetBackTrace();
	void ShowPath();
	void ShowCheckedTiles();
	void InitializationLinkMatrix();
	sf::Vector2f ConvertToVector(short vertex);
	short ConvertToNumber(sf::Vector2f vertex);

	short number_of_directions_;
	short matrix_size_;
	short path_length_;

	short end_tile_position_;
	short start_tile_position_;

	std::vector<sf::Vector2f> path_map_;
	std::vector<std::vector<short>> link_matrix_;
	std::vector<short> minimum_distance_;
	std::vector<bool> checked_tiles_;
	std::vector<int> offset_;

};
