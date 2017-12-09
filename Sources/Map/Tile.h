#pragma once
#include "TileType.h"

class Tile
{
public:
	Tile();
	Tile(int x, int y, TileType type);
	Tile(int x, int y, char type);
	~Tile();

	sf::Vector2f GetCoordinates() const;
	short GetX() const;
	short GetY() const;

	TileType GetType() const;
	char GetTypeChar() const;
	
	void SetType(const TileType type);
	void SetTypeChar(const char type);

	sf::Color GetColor() const;

private:
	short x_;
	short y_;
	TileType type_;
};

