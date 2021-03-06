#include "MapController.h"
#include "Map.h"
#include "../Utilities/EventManager.h"

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
		view.move(-10, 0);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		view.move(0, -10);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		view.move(10, 0);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		view.move(0, 10);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		view.zoom(1.0100f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		view.setSize(640, 480);

	window_->setView(view);

	

	if (EventManager::GetEvent(sf::Event::KeyPressed) && sf::Keyboard::isKeyPressed(sf::Keyboard::Home))
		CenterView();
}

void MapController::CenterView()
{
	sf::View view = window_->getView();
	view.setCenter(Map::GetMap()->GetWidth() * 8, Map::GetMap()->GetHeight() * 8);
	window_->setView(view);
}


