#include "Sources/Map/Map.h"
#include "Sources/Map/MapRenderer.h"
#include "Sources/Map/MapController.h"
#include "Sources/Utilities/EventManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding", sf::Style::Titlebar | sf::Style::Close);
	EventManager::Initialize(&window);
	MapRenderer::Initialize(&window);
	MapController::Initialize(&window);

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

		window.display();
	}

	Map::Save("new_map.txt");

    return 0;
}

