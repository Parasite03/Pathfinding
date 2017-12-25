#pragma once

class EventManager
{
public:
	static void Update();
	static bool GetEvent(const sf::Event::EventType event_type);
	static void Initialize(sf::RenderWindow* window);

private:
	EventManager();
	~EventManager();

	static std::vector<sf::Event> events_;
	static sf::RenderWindow* window_;
};

