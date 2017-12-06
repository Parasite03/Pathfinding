#include "Map.h"
#include <fstream>
#include <sstream>

Map Map::current_map_;

Map::Map()
{

}

Map::~Map()
{

}

void Map::CreateMap(const short width, const short height)
{
	current_map_ = Map();
	current_map_.width_ = width;
	current_map_.height_ = height;

	for (auto i = 0; i < height; ++i)
	{
		std::vector<Tile> vector;
		for (auto j = 0; j < width; ++j)
		{
			Tile tile;
			tile.x = j;
			tile.y = i;
			tile.type = 0;
			vector.push_back(tile);
		}
		current_map_.tiles_.push_back(vector);
	}
}

void Map::LoadMap(const std::string name)
{
	current_map_ = Map();

	// Load the map from file to a vector of strings
	std::ifstream file("./Data/Maps/" + name);
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
	else
	{
		Logger::Error("Failed to load map: " + name);
	}

	// Load the dimensions of the map
	std::string width = strings.at(0).substr(0, strings.at(0).find(","));
	std::string height = strings.at(0).substr(strings.at(0).find(",") + 1, strings.at(0).size());
	strings.erase(strings.begin());

	current_map_.width_ = atoi(width.c_str());
	current_map_.height_ = atoi(height.c_str());
	
	// Convert the map strings into Tile structs
	for (auto i = 0; i < strings.size(); ++i)
	{
		std::vector<Tile> vector;
		for (auto j = 0; j < strings.at(i).size(); ++j)
		{
			Tile tile;
			switch(strings.at(i).at(j))
			{
			case '*':
				tile.type = TILE_BLANK;
				break;

			case '#':
				tile.type = TILE_WALL;
				break;

			case 'S':
				tile.type = TILE_START;
				break;

			case 'E':
				tile.type = TILE_END;
				break;

			default:
				tile.type = TILE_BLANK;
				break;
			}

			tile.x = j;
			tile.y = i;

			vector.push_back(tile);
		}
		current_map_.tiles_.push_back(vector);
	}

}

void Map::SaveMap(const std::string path)
{
	std::ofstream file(path);

	// Save the dimensions of the map
	std::ostringstream oss;
	oss << current_map_.width_ << ',' << current_map_.height_;
	file << oss.str() << "\n";

	// Save all the tiles
	for (auto vector : current_map_.tiles_)
	{
		std::string string;
		for (auto tile : vector)
		{
			switch (tile.type)
			{
			case TILE_BLANK:
				string.push_back('*');
				break;

			case TILE_WALL:
				string.push_back('#');
				break;

			case TILE_START:
				string.push_back('S');
				break;

			case TILE_END:
				string.push_back('E');
				break;

			default:
				string.push_back('*');
				break;
			}
		}
		file << string << "\n";
	}
}

void Map::DrawMap(sf::RenderWindow* window)
{
	sf::Texture tile_texture;
	tile_texture.loadFromFile("./Data/Textures/tile.png");
	sf::Sprite sprite;
	sprite.setTexture(tile_texture);

	/*
	* Tile types and colors
	* 0 - blank   - white
	* 1 - wall    - black
	* 2 - start   - green
	* 3 - end     - red
	* 4 - checked - yellow
	*/

	for (auto vector : current_map_.tiles_)
	{
		for (auto tile : vector)
		{
			switch (tile.type)
			{
			case TILE_BLANK:
				sprite.setColor(sf::Color::White);
				break;

			case TILE_WALL:
				sprite.setColor(sf::Color::Black);
				break;

			case TILE_START:
				sprite.setColor(sf::Color::Green);
				break;

			case TILE_END:
				sprite.setColor(sf::Color::Red);
				break;

			case TILE_CHECKED:
				sprite.setColor(sf::Color::Yellow);
				break;

			default:
				sprite.setColor(sf::Color::White);
				break;
			}

			sf::Vector2f position(tile_texture.getSize().x * tile.x, tile_texture.getSize().y * tile.y);
			sprite.setPosition(position);
			window->draw(sprite);
		}
	}
}

void Map::Paint(sf::RenderWindow* window)
{
	short painting_type;
	sf::Vector2f coordinates;
	coordinates.x = (int)window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x / 16;
	coordinates.y = (int)window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y / 16;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (current_map_.selected_tile_type_ == 0)
			painting_type = 1;
		else
			painting_type = 0;

		
		if (coordinates.x >= 0 && coordinates.y >= 0 && coordinates.x < current_map_.width_ && coordinates.y < current_map_.height_)
			GetTile(coordinates)->type = painting_type;

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (current_map_.selected_tile_type_ == 2)
			painting_type = 3;
		else
			painting_type = 2;

		if (coordinates.x >= 0 && coordinates.y >= 0 && coordinates.x < current_map_.width_ && coordinates.y < current_map_.height_)
			GetTile(coordinates)->type = painting_type;

	}
}

void Map::ProcessEvent(sf::Event::EventType event, sf::RenderWindow* window)
{
	sf::Vector2f coordinates;
	switch (event)
	{
	case sf::Event::MouseButtonPressed:
		coordinates.x = (int)window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x / 16;
		coordinates.y = (int)window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y / 16;
		if (coordinates.x >= 0 && coordinates.y >= 0 && coordinates.x < current_map_.width_ && coordinates.y < current_map_.height_)
			current_map_.selected_tile_type_ = GetTile(coordinates)->type;
		break;

	default:
		break;
	}
}

Map* Map::GetCurrentMap()
{
	return &current_map_;
}

void Map::SetTile(Tile* tile, const short x, const short y)
{
	current_map_.tiles_.at(x).at(y) = *tile;
}

Tile* Map::GetTile(const short x, const short y)
{
	return &current_map_.tiles_.at(y).at(x);
}

Tile* Map::GetTile(const sf::Vector2f position)
{
	return &current_map_.tiles_.at(position.y).at(position.x);
}

short Map::GetWidth()
{
	return current_map_.width_;
}

short Map::GetHeight()
{
	return current_map_.height_;
}

