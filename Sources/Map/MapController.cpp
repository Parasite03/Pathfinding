#include "MapController.h"
#include "Map.h"

sf::RenderWindow* MapController::window_;

MapController::MapController()
{

}

MapController::~MapController()
{

}

void MapController::Initialize(sf::RenderWindow* window)
{
	window_ = window;
}

void MapController::MoveView()
{
	sf::View view = window_->getView();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		view.move(-5, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		view.move(0, -5);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		view.move(5, 0);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		view.move(0, 5);
	}
	window_->setView(view);
}

void MapController::CenterView()
{
	sf::View view = window_->getView();
	view.setCenter(Map::GetMap()->GetWidth() * 8, Map::GetMap()->GetHeight() * 8);
	window_->setView(view);
}


