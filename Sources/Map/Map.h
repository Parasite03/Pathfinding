#pragma once

#define TILE_BLANK 0
#define TILE_WALL 1
#define TILE_START 2
#define TILE_END 3
#define TILE_CHECKED 4

struct Tile
{
	unsigned short x = 0;
	unsigned short y = 0;
	short type = 0;
	unsigned int g_cost = 0;
	unsigned int h_cost = 0;
	unsigned int f_cost = 0;
};

class Map
{
public:
	static void CreateMap(const short width, const short height);
	static void LoadMap(const std::string path);
	static void SaveMap(const std::string path);
	static void DrawMap(sf::RenderWindow* window);
	static void Paint(sf::RenderWindow* window);
	static void ProcessEvent(sf::Event::EventType event, sf::RenderWindow* window);
	static void CenterCamera(sf::RenderWindow* window);
	static void MoveCamera(sf::RenderWindow* window);
	static Map* GetCurrentMap();

	static void SetTile(Tile* tile, const short x, const short y);
	static Tile* GetTile(const short x, const short y);
	static Tile* GetTile(const sf::Vector2f position);

	static short GetWidth();
	static short GetHeight();

private:
	static Map current_map_;

	short width_;
	short height_;
	short selected_tile_type_ = 0;

	Map();
	~Map();

	std::vector<std::vector<Tile>> tiles_;
};

