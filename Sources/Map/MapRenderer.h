#pragma once
#include "TileType.h"

class MapRenderer
{
public:
	static void Initialize(sf::RenderWindow* window);
	static void Draw();
	static void SetPaintingMode(TileType type);
	static void Paint();

private:
	MapRenderer();
	~MapRenderer();

	static sf::Texture tile_texture_;
	static sf::Sprite tile_sprite_;
	static sf::RenderWindow* window_;

	static TileType painting_mode_;
};

