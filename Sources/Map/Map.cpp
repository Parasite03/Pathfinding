#include "Map.h"
#include <fstream>
#include <sstream>

Map Map::map_;

std::vector<std::string> LoadFile(const std::string path)
{
	std::ifstream file(path);
	std::vector<std::string> strings;
	
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string string;
			file >> string;
			strings.push_back(string);
		}
	}
	return strings;
}

std::vector<std::string> SplitString(std::string string, const char delimiter)
{
	std::vector<std::string> strings;
	while (string.size() > 0)
	{
		if (std::count(string.begin(), string.end(), delimiter) > 0)
		{
			strings.push_back(string.substr(0, string.find(delimiter)));
			string.erase(0, string.find(delimiter) + 1);
		}
		else
		{
			strings.push_back(string.substr(0, string.size()));
			string.erase(0, string.size());
		}
		
	}
	return strings;
}

Map::Map()
{
	
}

Map::Map(const short width, const short height)
{
	width_ = width;
	height_ = height;
}

Map::~Map()
{
	
}

void Map::Create(const short width, const short height)
{
	map_ = Map(width, height);
	for (auto i = 0; i < height; ++i)
	{
		std::vector<Tile> vector;
		for (auto j = 0; j < width; ++j)
			vector.push_back(Tile(j, i, TileType::Blank));
		map_.tiles_.push_back(vector);
	}
}

void Map::Load(const std::string path)
{
	// Load the map file into a vector of strings
	std::vector<std::string> strings = LoadFile(path);

	// Get map width and height from the first string and erase them from the string vector
	std::vector<std::string> dimensions = SplitString(strings.at(0), ',');
	strings.erase(strings.begin());
	short width = atoi(dimensions.at(0).c_str());
	short height = atoi(dimensions.at(1).c_str());

	// Initialize the map
	map_ = Map(width, height);

	// Fill the map with tiles
	for (auto i = 0; i < strings.size(); i++)
	{
		std::vector<Tile> vector;
		for (auto j = 0; j < strings.at(i).size(); ++j)
			vector.push_back(Tile(j, i, strings.at(i).at(j)));
		map_.tiles_.push_back(vector);
	}

}

void Map::Save(const std::string path)
{
	std::ofstream file(path);
	
	// Save the dimensions of the map
	std::ostringstream oss;
	oss << map_.width_ << ',' << map_.height_ << "\n";
	file << oss.str();

	// Save all the tiles
	for (auto vector : map_.tiles_)
	{
		std::string string;
		for (auto tile : vector)
			string.push_back(tile.GetTypeChar());
		file << string << "\n";
	}
}

Map* Map::GetMap()
{
	return &map_;
}

short Map::GetWidth() const
{
	return width_;
}

short Map::GetHeight() const
{
	return height_;
}

sf::Vector2f Map::GetStart() const
{
	return start_;
}

sf::Vector2f Map::GetEnd() const
{
	return end_;
}

void Map::SetStart(const short x, const short y)
{
	start_.x = x;
	start_.y = y;
}

void Map::SetStart(const sf::Vector2f coordinates)
{
	start_ = coordinates;
}

void Map::SetEnd(const short x, const short y)
{
	end_.x = x;
	end_.y = y;
}

void Map::SetEnd(const sf::Vector2f coordinates)
{
	end_ = coordinates;
}

Tile* Map::GetTile(const short x, const short y) const
{
	return &map_.tiles_.at(y).at(x);
}

Tile* Map::GetTile(const sf::Vector2f coordinates) const
{
	return &map_.tiles_.at(coordinates.y).at(coordinates.x);
}


