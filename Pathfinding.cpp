#include "Sources/Map/Map.h"
#include "Sources/Map/MapRenderer.h"
#include "Sources/Map/MapController.h"
#include "Sources/Utilities/EventManager.h"
#include "Clock.h"
#include "Sources/GUI/GuiManager.h"

sf::Clock kClock;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding", sf::Style::Titlebar | sf::Style::Close);
	EventManager::Initialize(&window);
	MapRenderer::Initialize(&window);
	MapController::Initialize(&window);
	GuiManager::Initialize(&window);

	Map::Create(50, 37);
	//Map::Load("./Data/Maps/test_map.txt");
	MapController::CenterView();

	while (window.isOpen())
	{
		// Event handling
		EventManager::Update();
		if (EventManager::GetEvent(sf::Event::Closed))
			window.close();

		// Update
		MapController::MoveView();

		// Drawing
		window.clear();
		
		MapRenderer::Draw();
		GuiManager::Update();

		window.display();
		kClock.restart();
	}

	Map::Save("new_map.txt");

    return 0;
}

