#include "Sources/Map/Map.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pathfinding", sf::Style::Titlebar | sf::Style::Close);

	Map::CreateMap(50, 37);
	//Map::LoadMap("test_map.txt");

	// Event handling
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseButtonPressed:
				Map::ProcessEvent(sf::Event::MouseButtonPressed, &window);
				break;

			default:
				break;
			}
		}

		window.clear();
		
		Map::Paint(&window);
		Map::DrawMap(&window);

		window.display();
	}

	Map::SaveMap("new_map.txt");

    return 0;
}

