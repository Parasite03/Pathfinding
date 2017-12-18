#pragma once
#include "../GUI/GuiManager.h"

class EventManager
{
public:
	static void Update();
	static bool GetEvent(const sf::Event::EventType event_type);
	static void Initialize(sf::RenderWindow* window, GuiManager* gui_manager);

private:
	EventManager();
	~EventManager();

	static std::vector<sf::Event> events_;
	static sf::RenderWindow* window_;
	static GuiManager* gui_manager_;
};

