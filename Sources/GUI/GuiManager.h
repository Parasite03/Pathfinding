#pragma once
#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Window.hpp"
#include "SFGUI/Desktop.hpp"
#include "SFGUI/Button.hpp"

class GuiManager
{
public:
	static void Initialize(sf::RenderWindow* render_window);
	static void HandleEvent(const sf::Event event);
	static void Update();

private:
	GuiManager();
	~GuiManager();

	static sf::RenderWindow* render_window_;

	static sfg::SFGUI sfgui_;
	static sfg::Window::Ptr window_;
	static sfg::Desktop desktop_;

	static sfg::Button::Ptr button_;
};

