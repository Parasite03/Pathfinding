#include "MapRenderer.h"
#include "Map.h"

sf::Texture MapRenderer::tile_texture_;
sf::Sprite MapRenderer::tile_sprite_;
sf::RenderWindow* MapRenderer::window_;

MapRenderer::MapRenderer()
{

}

MapRenderer::~MapRenderer()
{

}

void MapRenderer::Initialize(sf::RenderWindow* window)
{
	tile_texture_.loadFromFile("./Data/Textures/tile.png");
	tile_sprite_.setTexture(tile_texture_);
	window_ = window;
}

void MapRenderer::Draw()
{
	for (auto i = 0; i < Map::GetMap()->GetHeight(); i++)
	{
		for (auto j = 0; j < Map::GetMap()->GetWidth(); j++)
		{
			sf::Vector2f position(tile_texture_.getSize().x * Map::GetMap()->GetTile(j, i)->GetX(), tile_texture_.getSize().y * Map::GetMap()->GetTile(j, i)->GetY());
			tile_sprite_.setPosition(position);
			tile_sprite_.setColor(Map::GetMap()->GetTile(j, i)->GetColor());
			window_->draw(tile_sprite_);
		}
	}
}


