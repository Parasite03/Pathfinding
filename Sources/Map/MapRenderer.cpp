#include "MapRenderer.h"
#include "Map.h"
#include "../Utilities/EventManager.h"

sf::Texture MapRenderer::tile_texture_;
sf::Sprite MapRenderer::tile_sprite_;
sf::RenderWindow* MapRenderer::window_;
TileType MapRenderer::painting_mode_;

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
	//sf::Vector2f start_coordinates = { window_->mapPixelToCoords({0, 0}).x / 16, window_->mapPixelToCoords({ 0, 0 }).y / 16 };
	//sf::Vector2f end_coordinates = window_->mapPixelToCoords({ window_->getSize().x / 16, window_->getSize().y /16 });

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

void MapRenderer::SetPaintingMode(TileType type)
{
	painting_mode_ = type;
}

void MapRenderer::Paint()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ((painting_mode_ == TileType::Blank) || (painting_mode_ == TileType::Wall)))
	{
		sf::Vector2f tile_coordinates(window_->mapPixelToCoords(sf::Mouse::getPosition(*window_)).x / 16, window_->mapPixelToCoords(sf::Mouse::getPosition(*window_)).y / 16);
		if (tile_coordinates.x > 0 && tile_coordinates.y > 0 && tile_coordinates.x < Map::GetMap()->GetWidth() && tile_coordinates.y < Map::GetMap()->GetHeight())
		{
			Map::GetMap()->GetTile(tile_coordinates)->SetType(painting_mode_);
		}
		
	}

	if (EventManager::GetEvent(sf::Event::MouseButtonPressed) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && ((painting_mode_ == TileType::Start) || (painting_mode_ == TileType::End)))
	{
		sf::Vector2f tile_coordinates(window_->mapPixelToCoords(sf::Mouse::getPosition(*window_)).x / 16, window_->mapPixelToCoords(sf::Mouse::getPosition(*window_)).y / 16);
		if (tile_coordinates.x > 0 && tile_coordinates.y > 0 && tile_coordinates.x < Map::GetMap()->GetWidth() && tile_coordinates.y < Map::GetMap()->GetHeight())
		{
			Map::GetMap()->GetTile(tile_coordinates)->SetType(painting_mode_);
			if (painting_mode_ == TileType::Start && (Map::GetMap()->GetStart() != tile_coordinates))
			{
				Map::GetMap()->GetTile(Map::GetMap()->GetStart())->SetType(TileType::Blank);
				Map::GetMap()->SetStart(tile_coordinates);
			}
			else if (painting_mode_ == TileType::End && (Map::GetMap()->GetEnd() != tile_coordinates))
			{
				Map::GetMap()->GetTile(Map::GetMap()->GetEnd())->SetType(TileType::Blank);
				Map::GetMap()->SetEnd(tile_coordinates);
			}
		}
	}
}



