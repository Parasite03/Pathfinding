#pragma once

class MapController
{
public:
	static void Initialize(sf::RenderWindow* window);
	static void MoveView();
	static void CenterView();

private:
	MapController();
	~MapController();

	static sf::RenderWindow* window_;
};

