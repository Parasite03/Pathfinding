#pragma once
#include "SFGUI/SFGUI.hpp"
#include "SFGUI/Widgets.hpp"

class GuiManager
{
public:
	GuiManager();
	GuiManager(sf::RenderWindow* render_window);
	~GuiManager();

	void HandleEvent(const sf::Event event);
	void Update();
	sfg::SFGUI GuiManager::GetSfgui();

private:
	// Render window pointer
	sf::RenderWindow* render_window_;

	// Core things
	sfg::SFGUI sfgui_;
	sfg::Desktop desktop_;
	sfg::Box::Ptr box_;
	sfg::Window::Ptr window_;

	//Painting Window
	sfg::Box::Ptr painting_box_;
	sfg::Button::Ptr paint_blank_button_;
	sfg::Button::Ptr paint_wall_button_;
	sfg::Button::Ptr paint_start_button_;
	sfg::Button::Ptr paint_end_button_;
	
	// Map management window
	sfg::Box::Ptr map_management_box_;
	sfg::Button::Ptr create_map_button_;
	sfg::Button::Ptr load_map_button_;
	sfg::Button::Ptr save_map_button_;
};

