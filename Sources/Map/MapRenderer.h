#pragma once

class MapRenderer
{
public:
	static void Initialize(sf::RenderWindow* window);
	static void Draw();

private:
	MapRenderer();
	~MapRenderer();

	static sf::Texture tile_texture_;
	static sf::Sprite tile_sprite_;
	static sf::RenderWindow* window_;
};

