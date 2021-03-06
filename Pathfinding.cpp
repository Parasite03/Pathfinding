#include "Sources/Map/Map.h"
#include "Sources/Map/MapRenderer.h"
#include "Sources/Map/MapController.h"
#include "Sources/Utilities/EventManager.h"
#include "Clock.h"
#include "Sources/Gui/Gui.h"
#include "Sources/ImGui/imgui-SFML.h"


sf::Clock kClock;

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	EventManager::Initialize(&window);
	MapRenderer::Initialize(&window);
	MapController::Initialize(&window);
	Gui::Initialize(&window);


	Map::Create(50, 37);

	while (window.isOpen())
	{
		// Event handling
		EventManager::Update();
		if (EventManager::GetEvent(sf::Event::Closed))
			window.close();

		// Update
		MapController::MoveView();
		Gui::Update();
	
		// Drawing
		window.clear(sf::Color(128, 128, 128));
		
		MapRenderer::Paint();
		MapRenderer::Draw();
		Gui::Draw();

		window.display();
		kClock.restart();
	}

	ImGui::SFML::Shutdown();

    return 0;
}

