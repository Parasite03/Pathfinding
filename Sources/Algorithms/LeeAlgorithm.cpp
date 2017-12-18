#include "LeeAlgorithm.h"

LeeAlgorithm LeeAlgorithm::algorithm_;

LeeAlgorithm::LeeAlgorithm()
{

}

LeeAlgorithm::~LeeAlgorithm()
{

}

void LeeAlgorithm::FindPath(sf::Vector2f start_position, sf::Vector2f end_position, unsigned char number_of_directions)
{
	// Initialization
	algorithm_ = LeeAlgorithm();

	if (Map::GetMap()->GetTile(Map::GetMap()->GetStart())->GetType() == TileType::Wall ||
		Map::GetMap()->GetTile(Map::GetMap()->GetEnd())->GetType() == TileType::Wall) return;

	// Set direction count
	algorithm_.SetDirectionCount(number_of_directions);

	bool open_tiles;
	short current_distance = 0;

	LeeAlgorithm::ResetPath();

	algorithm_.tile_distace_.at(Map::GetMap()->GetStart().x).at(Map::GetMap()->GetStart().y) = current_distance;

	// Wave expansion
	do {
		open_tiles = true;

		for (auto y = 0; y < Map::GetMap()->GetHeight(); ++y)
			for (auto x = 0; x < Map::GetMap()->GetWidth(); ++x)
			{
				if (algorithm_.tile_distace_.at(x).at(y) == current_distance)
				{
					// Mark all unlabeled neighbors of points marked with i with i + 1
					
					for (auto i = 0; i < algorithm_.GetNumberOfDirections(); ++i)
					{
						short delta_y = y + algorithm_.tile_offset_by_y_.at(i),
						      delta_x = x + algorithm_.tile_offset_by_x_.at(i);
						
						if (delta_y >= 0 && delta_x >= 0 && delta_y < Map::GetMap()->GetHeight() && delta_x < Map::GetMap()->GetWidth() 
							&& algorithm_.tile_distace_.at(delta_x).at(delta_y) == -1)
						{
							open_tiles = false;
							algorithm_.tile_distace_.at(delta_x).at(delta_y) = current_distance + 1;
							//Map::GetMap()->GetTile(delta_x, delta_y)->SetType(TileType::Checked);
						}
					}
				}
			}
		current_distance++;
	} while (!open_tiles && algorithm_.tile_distace_.at(Map::GetMap()->GetEnd().x).at(Map::GetMap()->GetEnd().y) == -1);

	if (algorithm_.tile_distace_.at(Map::GetMap()->GetEnd().x).at(Map::GetMap()->GetEnd().y) == -1) return;

	LeeAlgorithm::SetBackTrace();
	LeeAlgorithm::ShowPath();

}

void LeeAlgorithm::SetBackTrace()
{
	algorithm_.path_length_ = algorithm_.tile_distace_.at(Map::GetMap()->GetEnd().x).at(Map::GetMap()->GetEnd().y);
	sf::Vector2f current_tile_position = Map::GetMap()->GetEnd();

	short current_distance = algorithm_.path_length_;

	while (current_distance > 0)
	{
		algorithm_.path_map.push_back(current_tile_position);
		current_distance--;

		for (auto i = 0; i < algorithm_.GetNumberOfDirections(); ++i)
		{
			short delta_y = current_tile_position.y + algorithm_.tile_offset_by_y_.at(i),
				  delta_x = current_tile_position.x + algorithm_.tile_offset_by_x_.at(i);

			if (delta_y >= 0 && delta_x >= 0 && delta_y < Map::GetMap()->GetHeight() && delta_x < Map::GetMap()->GetWidth() 
				&& algorithm_.tile_distace_.at(delta_x).at(delta_y) == current_distance)
			{
				current_tile_position.y = delta_y;
				current_tile_position.x = delta_x;
				break;
			}
		}
	}

	algorithm_.path_map.push_back(Map::GetMap()->GetStart());

}

void LeeAlgorithm::ShowPath()
{
	Map::GetMap()->GetTile(Map::GetMap()->GetStart())->SetType(TileType::Start);
	Map::GetMap()->GetTile(Map::GetMap()->GetEnd())->SetType(TileType::End);

	for (auto i = 1; i < algorithm_.path_length_; ++i)
	{
		Map::GetMap()->GetTile(algorithm_.path_map.at(i))->SetType(TileType::Path);
	}
}

void LeeAlgorithm::SetDirectionCount(unsigned char number_of_directions)
{
	algorithm_.SetNumberOfDirections(number_of_directions);

	if (algorithm_.GetNumberOfDirections() == 4)
	{
		tile_offset_by_x_ = { 1, 0, -1, 0 };
		tile_offset_by_y_ = { 0, 1, 0, -1 };
	}
	else
		if (algorithm_.GetNumberOfDirections() == 8)
		{
			tile_offset_by_x_ = { 1, 1, 0, -1, -1, -1, 0, 1 };
			tile_offset_by_y_ = { 0, 1, 1, 1, 0, -1, -1, -1 };
		}
		
}

void LeeAlgorithm::ResetPath()
{
	algorithm_.tile_distace_.clear();

	for (auto y = 0; y < Map::GetMap()->GetHeight(); ++y)
	{
		std::vector<int> vector;
		for (auto x = 0; x < Map::GetMap()->GetWidth(); ++x)
		{
			if (Map::GetMap()->GetTile(x, y)->GetType() == TileType::Wall)
				vector.push_back(-2);
			else
				vector.push_back(-1);
		}
		algorithm_.tile_distace_.push_back(vector);
	}
}

void LeeAlgorithm::SetNumberOfDirections(unsigned char number_of_directions)
{
	number_of_directions_ = number_of_directions;
}

unsigned char LeeAlgorithm::GetNumberOfDirections()
{
	return number_of_directions_;
}

LeeAlgorithm* LeeAlgorithm::GetAlgorithm()
{
	return &algorithm_;
}

