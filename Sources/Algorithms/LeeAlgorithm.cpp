#include "LeeAlgorithm.h"

#include <algorithm>
#include <fstream>

#include "../Map/Map.h"
#include "../Map/Tile.h"
#include "../Gui/Gui.h"

void LeeAlgorithm::FindPath()
{
	Map* map = Map::GetMap();

	Gui::SetRunning(true);
	sf::Clock clock;

	setWorldSize({ map->GetWidth(), map->GetHeight() });
	setDiagonalMovement();

	path_map_.clear();
	g_cost_.clear();

	bool first = true;

	for (auto x = 0; x < map->GetWidth(); ++x)
	{
		std::vector<uint> vector;
		for (auto y = 0; y < map->GetHeight(); ++y)
		{
			vector.push_back(0);
		}
		g_cost_.push_back(vector);
	}

	uint current_distance = 1;
	bool open_tiles = false;

	clock.restart();

	g_cost_.at(map->GetStart().x).at(map->GetStart().y) = current_distance;

	do
	{
		open_tiles = false;

		for (auto x = 0; x < world_size_.x; ++x)
			for (auto y = 0; y < world_size_.y; ++y)
			{
				sf::Vector2i current_coordinate = { x, y };

				if (g_cost_.at(x).at(y) == current_distance)
				{
					for (auto i = 0; i < directions_; ++i)
					{
						sf::Vector2i new_coordinates(current_coordinate + direction_.at(i));

						if (new_coordinates.x < 0 || new_coordinates.y < 0 ||
							new_coordinates.x >= map->GetWidth() || new_coordinates.y >= map->GetHeight())
							continue;
						else
							if (map->GetTile(new_coordinates.x, new_coordinates.y)->GetType() == TileType::Checked ||
								map->GetTile(new_coordinates.x, new_coordinates.y)->GetType() == TileType::Wall)
								continue;

						if (first)
							first = false;
						else
							map->GetTile(new_coordinates.x, new_coordinates.y)->SetType(TileType::Checked);
						g_cost_.at(new_coordinates.x).at(new_coordinates.y) = current_distance + 1;
						open_tiles = true;
					}
				}
			}
		++current_distance;
	} while (open_tiles && g_cost_.at(map->GetEnd().x).at(map->GetEnd().y) == 0);

	Gui::SetPathLength(current_distance);

	sf::Vector2i current_coordinate = ftoi(map->GetEnd());

	while (current_distance > 0)
	{
		path_map_.push_back(itof(current_coordinate));
		current_distance--;

		for (auto i = 0; i < directions_; ++i)
		{
			sf::Vector2i new_coordinates(current_coordinate + direction_.at(i));

			if (new_coordinates.x >= 0 && new_coordinates.y >= 0 &&
				new_coordinates.x < map->GetWidth() && new_coordinates.y < map->GetHeight() &&
				g_cost_.at(new_coordinates.x).at(new_coordinates.y) == current_distance)
			{
				current_coordinate = new_coordinates;
				break;
			}
		}
	}

	Gui::SetRunTime(clock.getElapsedTime());
	Gui::SetRunning(false);

	map->GetTile(map->GetStart())->SetType(TileType::Start);
	map->GetTile(map->GetEnd())->SetType(TileType::End);

	for (auto i = 1; i < path_map_.size() ; ++i)
		map->GetTile(path_map_.at(i))->SetType(TileType::Path);
}

void LeeAlgorithm::setWorldSize(sf::Vector2i world_size)
{
	world_size_ = world_size;
}

void LeeAlgorithm::setDiagonalMovement()
{
	directions_ = (Gui::Get8Directions() ? 8 : 4);

	direction_ = {
		{ 0, 1 },{ 1, 0 },{ 0, -1 },{ -1, 0 },
		{ -1, -1 },{ 1, 1 },{ -1, 1 },{ 1, -1 }
	};
}

sf::Vector2i LeeAlgorithm::ftoi(sf::Vector2f vector)
{
	return { (int)vector.x, (int)vector.y };
}

sf::Vector2f LeeAlgorithm::itof(sf::Vector2i vector)
{
	return { (float)vector.x, (float)vector.y };
}