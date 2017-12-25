#pragma once
class AStar
{
public:
	static void FindPath(sf::Vector2f start_position, sf::Vector2f end_position, short number_of_directions);


private:
	AStar();
	~AStar();
};

