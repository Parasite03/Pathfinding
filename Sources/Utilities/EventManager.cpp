#include "EventManager.h"
#include "../GUI/GuiManager.h"

std::vector<sf::Event> EventManager::events_;
sf::RenderWindow* EventManager::window_;
GuiManager* EventManager::gui_manager_;

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::Update()
{
	events_.clear();
	sf::Event event;
	while (window_->pollEvent(event))
	{
		events_.push_back(event);
		gui_manager_->HandleEvent(event);
	}
}

bool EventManager::GetEvent(const sf::Event::EventType event_type)
{
	for (auto event : events_)
		if (event.type == event_type) return true;
	return false;
}

void EventManager::Initialize(sf::RenderWindow* window, GuiManager* gui_manager)
{
	window_ = window;
	gui_manager_ = gui_manager;
}
