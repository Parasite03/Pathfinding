#include "Dijkstra.h"

#include "../Map/Map.h"
#include "../Map/Tile.h"
#include "../Gui/Gui.h"

#include <iostream>

#define INF 32667


void Dijkstra::FindPath()
{
	Map* map = Map::GetMap();

	end_tile_position_ = (int)map->GetEnd().y * map->GetWidth() + map->GetEnd().x;
	start_tile_position_ = (int)map->GetStart().y * map->GetWidth() + map->GetStart().x;

	matrix_size_ = map->GetHeight() * map->GetWidth();

	SetDirectionCount(4);
	InitializationLinkMatrix();

	minimum_distance_.at(start_tile_position_) = 0;

	short minimum_index = 0, min = 0, temporary = 0;

	do {

		minimum_index = INF;
		min = INF;

		for (auto i = 0; i < matrix_size_; ++i)
		{
			if (!checked_tiles_.at(i) && minimum_distance_.at(i) < min)
			{
				min = minimum_distance_.at(i);
				minimum_index = i;
			}
		}

		if (minimum_index != INF)
		{
			for (auto i = 0; i < matrix_size_; ++i)
			{
				if (link_matrix_.at(minimum_index).at(i) != INF && map->GetTile(ConvertToVector(i))->GetType() != TileType::Wall)
				{
					temporary = min + link_matrix_.at(minimum_index).at(i);
					if (temporary < minimum_distance_.at(i))
						minimum_distance_.at(i) = temporary;
				}
			}
			map->GetTile(ConvertToVector(minimum_index))->SetType(TileType::Checked);
			checked_tiles_.at(minimum_index) = true;
		}

	} while (minimum_index < INF && !checked_tiles_.at(end_tile_position_));
	
	/*for (auto i = 0; i < matrix_size_; ++i)
	{
		if (i % map->GetWidth() == 0)
			std::cout << "\n";

		std::cout << minimum_distance_.at(i) << " ";
	}*/

	SetBackTrace();
	ShowCheckedTiles();
	ShowPath();

}

//void Dijkstra::SetBackTrace()
//{
//	Map* map = Map::GetMap();
//
//	short current_tile_position = end_tile_position_ - 1;
//	path_map_.push_back(ConvertToVector(current_tile_position + 1));
//
//	SetPathLength(minimum_distance_.at(end_tile_position_ - 1));
//	short current_weight = GetPathLength();
//
//	while (current_tile_position != start_tile_position_)
//	{
//		for (auto i = 0; i < matrix_size_; ++i)
//			if (link_matrix_.at(current_tile_position).at(i) != 0)
//			{
//				int temporary = current_weight - link_matrix_.at(current_tile_position).at(i);
//				if (temporary == minimum_distance_.at(i))
//				{
//					current_weight = temporary;
//					current_tile_position = i;
//					path_map_.push_back(ConvertToVector(i + 1));
//				}
//			}
//	}
//
//
//	/*std::vector<int> ver(matrix_size_);
//	int end = end_tile_position_ - 1;
//	ver[0] = end + 1;
//	path_map_.push_back(ConvertToVector(end + 1));
//	int k = 1;
//	int weight = minimum_distance_[end];
//
//	while (end != start_tile_position_)
//	{
//		for (int i = 0; i < matrix_size_; ++i)
//			if (link_matrix_.at(end).at(i) != 0)
//			{
//				int temp = weight - link_matrix_.at(end).at(i);
//				if (temp == minimum_distance_.at(i))
//				{
//					weight = temp;
//					end = i;
//					ver.at(k) = i + 1;
//					path_map_.push_back(ConvertToVector(i + 1));
//					k++;
//				}
//			}
// 	}
//
//	for (int i = 0; i < path_map_.size(); ++i)
//	{
//		if (i % map->GetWidth() == 0)
//			std::cout << "\n";
//
//		std::cout << ver.at(i) << " ";
//	}*/
//}

void Dijkstra::SetBackTrace()
{
	Map* map = Map::GetMap();
	
	SetPathLength(minimum_distance_.at(end_tile_position_));
	short current_distance = GetPathLength();

	sf::Vector2f current_tile_position = ConvertToVector(end_tile_position_);

	while (current_distance > 0)
	{
	
		path_map_.push_back(current_tile_position);
		current_distance--;

		for (auto i = 0; i < GetNumberOfDirections(); ++i)
		{
			
			short delta = ConvertToNumber(current_tile_position) + offset_.at(i);

			if (i % map->GetWidth() == 0 && delta % map->GetWidth() == map->GetWidth() - 1)
				continue;

			if (i % map->GetWidth() == 5 && delta % map->GetWidth() == 0)
				continue;

			if (delta >= 0 && delta < matrix_size_ && minimum_distance_.at(delta) == current_distance)
			{
				current_tile_position = ConvertToVector(delta);
				break;
			}

			/*if (delta_y >= 0 && delta_x >= 0 && delta_y < map->GetHeight() && delta_x < map->GetWidth()
				&& tile_distance_.at(delta_x).at(delta_y) == current_distance)
			{
				current_tile_position.y = delta_y;			
				current_tile_position.x = delta_x;			
				break;
			}*/
		}
	}

	path_map_.push_back(map->GetStart());

}


void Dijkstra::InitializationLinkMatrix()
{
	Map* map = Map::GetMap();

	path_map_.clear();
	minimum_distance_.clear();
	checked_tiles_.clear();
	link_matrix_.clear();

	minimum_distance_.resize(matrix_size_);
	checked_tiles_.resize(matrix_size_);
	link_matrix_.resize(matrix_size_);
	
	for (auto i = 0; i < matrix_size_; ++i)
		link_matrix_.at(i).resize(matrix_size_);

	for (auto i = 0; i < matrix_size_; ++i)
		for (auto j = 0; j < matrix_size_; ++j)
			link_matrix_.at(i).at(j) = INF;

	for (auto i = 0; i < matrix_size_; ++i)
		for (auto j = 0; j < GetNumberOfDirections(); ++j)
		{
			short delta = i + offset_.at(j);

			if (i % map->GetWidth() == 0 && delta % map->GetWidth() == map->GetWidth() - 1)
				continue;

			if (i % map->GetWidth() == 5 && delta % map->GetWidth() == 0 )
				continue;

			if (delta >= 0 && delta < matrix_size_)
					link_matrix_.at(i).at(delta) = 1;
		}

	for (auto i = 0; i < matrix_size_; ++i)
	{
		minimum_distance_.at(i) = INF;
		checked_tiles_.at(i) = false;
	}

}

void Dijkstra::ShowPath()
{
	Map* map = Map::GetMap();

	map->GetTile(map->GetStart())->SetType(TileType::Start);
	map->GetTile(map->GetEnd())->SetType(TileType::End);

	for (auto i = 1; i < path_map_.size(); ++i)
		map->GetTile(path_map_.at(i))->SetType(TileType::Path);
}

void Dijkstra::ShowCheckedTiles()
{
	Map* map = Map::GetMap();

	for (auto i = 0; i < matrix_size_; ++i)
		if (checked_tiles_.at(i))
			map->GetTile(ConvertToVector(i))->SetType(TileType::Checked);
}

void Dijkstra::SetDirectionCount(const short number_of_directions)
{
	Map* map = Map::GetMap();

	number_of_directions_ = number_of_directions;
	
	if (GetNumberOfDirections() == 4)
		offset_ = { -1, -map->GetWidth(), 1, map->GetWidth() };
	else
		if (GetNumberOfDirections() == 8)
			offset_ = { -1, -map->GetWidth(), 1, map->GetWidth(),
						-map->GetWidth() - 1, -map->GetWidth() + 1, map->GetWidth() - 1, map->GetWidth() + 1 };

}

unsigned char Dijkstra::GetNumberOfDirections()
{
	return number_of_directions_;
}

void Dijkstra::SetPathLength(const short path_length)
{
	path_length_ = path_length;
}

short Dijkstra::GetPathLength()
{
	return path_length_;
}

sf::Vector2f Dijkstra::ConvertToVector(short vertex)
{
	Map* map = Map::GetMap();

	sf::Vector2f vector;

	vector.x = vertex % map->GetWidth();
	vector.y = vertex / map->GetWidth();

	return vector;
}

short Dijkstra::ConvertToNumber(sf::Vector2f vertex)
{
	Map* map = Map::GetMap();

	short number;

	number = (int)vertex.y * map->GetWidth() + vertex.x;

	return number;

}

Dijkstra::Dijkstra()
{

}

Dijkstra::~Dijkstra()
{

}