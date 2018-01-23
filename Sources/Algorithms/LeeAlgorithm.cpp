#include "LeeAlgorithm.h"

#include "../Map/Map.h"
#include "../Map/Tile.h"
#include "../Gui/Gui.h"

void LeeAlgorithm::FindPath()
{
	// Initialization
	Map* map = Map::GetMap();
	sf::Vector2f start_position = Map::GetMap()->GetStart();
	sf::Vector2f end_position = Map::GetMap()->GetEnd();
	short number_of_directions = Gui::Get8Directions() ? 8 : 4;

	// Start/end tile - wall, impossible to determine the path
	if (map->GetTile(map->GetStart())->GetType() == TileType::Wall ||
		map->GetTile(map->GetEnd())->GetType() == TileType::Wall) return;

	// Number of directions
	SetDirectionCount(number_of_directions);

	bool open_tiles;
	short current_distance = 0;

	// Reset previous result
	ResetPathMap();

	// Start tile is marked 0
	tile_distance_.at(map->GetStart().x).at(map->GetStart().y) = current_distance;

	// Wave expansion
	do {
		open_tiles = false;		 // We assume that all free tiles have already been tested

		for (auto y = 0; y < map->GetHeight(); ++y)
			for (auto x = 0; x < map->GetWidth(); ++x)
			{
				if (tile_distance_.at(x).at(y) == current_distance)		// Tile is marked current_distance
				{
					// Note all unlabelled neighbors (in n directions) - current_distance + 1

					for (auto i = 0; i < GetNumberOfDirections(); ++i)
					{
						// Find the coordinates of neighboring tiles (in n directions)
						short delta_y = y + offset_by_y_.at(i),
							delta_x = x + offset_by_x_.at(i);

						if (delta_y >= 0 && delta_x >= 0 && delta_y < map->GetHeight() && delta_x < map->GetWidth()
							&& tile_distance_.at(delta_x).at(delta_y) == -1)
						{
							map->GetTile(x, y)->SetType(TileType::Checked);
							open_tiles = true;												// Unmarked tiles found
							checked_tiles_.at(delta_x).at(delta_y) = true;					// Save tagged tiles
							tile_distance_.at(delta_x).at(delta_y) = current_distance + 1;

						}
					}
				}
			}
		current_distance++;			// Propagation of the wave
	} while (open_tiles && tile_distance_.at(map->GetEnd().x).at(map->GetEnd().y) == -1);

	if (tile_distance_.at(map->GetEnd().x).at(map->GetEnd().y) == -1) return;			// Path not found

	SetBackTrace();
	//ShowCheckedTiles();
	ShowPath();

}

void LeeAlgorithm::SetBackTrace()
{
	Map* map = Map::GetMap();

	// The length of the shortest path from the start tile to the final
	SetPathLength(tile_distance_.at(map->GetEnd().x).at(map->GetEnd().y));

	// Current coordinates - coordinates of the end tile
	sf::Vector2f current_tile_position = map->GetEnd();

	short current_distance = GetPathLength();

	// Looking for a path starting at the end tile
	while (current_distance > 0)
	{
		// Save the current coordinates in the path
		path_map_.push_back(current_tile_position);
		current_distance--;

		for (auto i = 0; i < GetNumberOfDirections(); ++i)
		{
			// Find the coordinates of neighboring tiles (in n directions)
			short delta_y = current_tile_position.y + offset_by_y_.at(i),
				  delta_x = current_tile_position.x + offset_by_x_.at(i);

			if (delta_y >= 0 && delta_x >= 0 && delta_y < map->GetHeight() && delta_x < map->GetWidth()
				&& tile_distance_.at(delta_x).at(delta_y) == current_distance)
			{
				current_tile_position.y = delta_y;			// The current coordinates are the coordinates of the tile, labeled current_distance
				current_tile_position.x = delta_x;			// Go to the tile, which is 1 closer to the start
				break;
			}
		}
	}

	// We store the coordinates of the start tile in the path
	path_map_.push_back(map->GetStart());

}

void LeeAlgorithm::ShowPath()
{
	Map* map = Map::GetMap();

	map->GetTile(map->GetStart())->SetType(TileType::Start);
	map->GetTile(map->GetEnd())->SetType(TileType::End);

	for (auto i = 1; i < path_length_; ++i)
		map->GetTile(path_map_.at(i))->SetType(TileType::Path);
}

void LeeAlgorithm::ShowCheckedTiles()
{
	Map* map = Map::GetMap();

	for (auto y = 0; y < map->GetHeight(); ++y)
		for (auto x = 0; x < map->GetWidth(); ++x)
			if (checked_tiles_.at(x).at(y))
				map->GetTile(x, y)->SetType(TileType::Checked);
}

void LeeAlgorithm::ResetPathMap()
{
	Map* map = Map::GetMap();

	path_map_.clear();
	tile_distance_.clear();
	checked_tiles_.clear();

	for (auto x = 0; x < map->GetWidth(); ++x)
	{
		std::vector<int> temporary_vector_i;
		std::vector<bool> temporary_vector_b;

		for (auto y = 0; y < map->GetHeight(); ++y)
		{
			if (map->GetTile(x, y)->GetType() == TileType::Wall)
				temporary_vector_i.push_back(-2);
			else
				temporary_vector_i.push_back(-1);

			temporary_vector_b.push_back(false);
		}

		tile_distance_.push_back(temporary_vector_i);
		checked_tiles_.push_back(temporary_vector_b);
	}
}

void LeeAlgorithm::SetDirectionCount(const short number_of_directions)
{

	// Number of directions
	number_of_directions_ = number_of_directions;

	// Places corresponding to neighboring tiles in n directions
	if (GetNumberOfDirections() == 4)
	{
		offset_by_x_ = { 1, 0, -1, 0 };
		offset_by_y_ = { 0, 1, 0, -1 };
	}
	else
		if (GetNumberOfDirections() == 8)
		{
			offset_by_x_ = { 1, 0, -1, 0, 1, -1, -1, 1 };
			offset_by_y_ = { 0, 1, 0, -1, 1, 1, -1, -1 };
		}

}

void LeeAlgorithm::SetPathLength(const short path_length)
{
	path_length_ = path_length;
}

unsigned char LeeAlgorithm::GetNumberOfDirections()
{
	return number_of_directions_;
}

short LeeAlgorithm::GetPathLength()
{
	return path_length_;
}

LeeAlgorithm::LeeAlgorithm()
{

}

LeeAlgorithm::~LeeAlgorithm()
{

}