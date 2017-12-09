#include "Tile.h"
#include "Map.h"

Tile::Tile()
{

}

Tile::Tile(int x, int y, TileType type)
{
	x_ = x;
	y_ = y;
	type_ = type;
}

Tile::Tile(const int x, const int y, const char type)
{
	x_ = x;
	y_ = y;
	SetTypeChar(type);
}

Tile::~Tile()
{

}

sf::Vector2f Tile::GetCoordinates() const
{
	return sf::Vector2f(x_, y_);
}

short Tile::GetX() const
{
	return x_;
}

short Tile::GetY() const
{
	return y_;
}

TileType Tile::GetType() const
{
	return type_;
}

char Tile::GetTypeChar() const
{
	switch (type_)
	{
	case TileType::Blank:
		return '*';

	case TileType::Wall:
		return '#';
	
	case TileType::Start:
		return 'S';
	
	case TileType::End:
		return 'E';
	
	default:
		return '*';
	}
}

void Tile::SetType(const TileType type)
{
	type_ = type;
}

void Tile::SetTypeChar(const char type)
{
	switch (type)
	{
	case '*':
		type_ = TileType::Blank;
		break;

	case '#':
		type_ = TileType::Wall;
		break;
	
	case 'S':
		type_ = TileType::Start;
		Map::GetMap()->SetStart(x_, y_);
		break;
	
	case 'E':
		type_ = TileType::End;
		Map::GetMap()->SetEnd(x_, y_);
		break;
	
	default:
		type_ = TileType::Blank;
		break;
	}
}

sf::Color Tile::GetColor() const
{
	switch (type_)
	{
	case TileType::Blank:
		return sf::Color::White;
		break;
	
	case TileType::Wall:
		return sf::Color::Black;
		break;
	
	case TileType::Start:
		return sf::Color::Green;
		break;
	
	case TileType::End:
		return sf::Color::Red;
		break;
	
	case TileType::Checked:
		return sf::Color::Yellow;
		break;
	
	case TileType::Path:
		return sf::Color::Cyan;
		break;
	
	default:
		return sf::Color::White;
		break;
	}
}

