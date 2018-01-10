#pragma once
#include "Tile.h"

class Map
{
public:
	static void Create(const short width, const short height);
	static void Load(const std::string path);
	static void Save(const std::string path);

	static Map* GetMap();

	short GetWidth() const;
	short GetHeight() const;

	sf::Vector2f GetStart() const;
	sf::Vector2f GetEnd() const;

	void SetStart(const short x, const short y);
	void SetStart(const sf::Vector2f coordinates);
	void SetEnd(const short x, const short y);
	void SetEnd(const sf::Vector2f coordinates);

	Tile* GetTile(const short x, const short y) const;
	Tile* GetTile(const sf::Vector2f coordinates) const;

private:
	Map();
	Map(const short width, const short height);
	~Map();

	static Map map_;

	short width_;
	short height_;

	sf::Vector2f start_;
	sf::Vector2f end_;

	std::vector<std::vector<Tile>> tiles_;
};

